#include "Physic/Physics.h"
#include "Physic/RigidBody.h"

#include "Core/Time.h"
#include "Core/SceneManager.h"
#include "ComponentSystem/GameObject.h"

#include <thread>
#include "Debug/Assert.h"

#define PVD_HOST "127.0.0.1"	//Set this to the IP address of the system running the PhysX Visual Debugger that you want to connect to.
#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL;	}
#define DEFAULT_DENSITY 1

using namespace Galatea;
using namespace physx;

Physics::Physics() :
    currentScene {nullptr}
{
}

Physics::~Physics()
{
    Destroy();
}

void Physics::Init() noexcept
{
    LogMsg("Init Physics");

    foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);

    //Init physX Visual Debugger
    pvd = PxCreatePvd(*foundation);
    PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
    pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

    physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);

    dispatcher = PxDefaultCpuDispatcherCreate(std::thread::hardware_concurrency());
}

void Physics::Destroy() noexcept
{
    //Remove all the scenes
    for (int i = scenes.size() - 1; i >= 0; i--)
        PX_RELEASE(scenes[i]);

    scenes.clear();
    currentScene = nullptr;

    PX_RELEASE(dispatcher);
    PX_RELEASE(physics);
    if (pvd)
    {
        PxPvdTransport* transport = pvd->getTransport();
        pvd->release();
        pvd = NULL;
        PX_RELEASE(transport);
    }
    PX_RELEASE(foundation);

}

PxFilterFlags ReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
    PxFilterObjectAttributes attributes1, PxFilterData filterData1,
    PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
    PX_UNUSED(attributes0);
    PX_UNUSED(attributes1);
    PX_UNUSED(filterData0);
    PX_UNUSED(filterData1);
    PX_UNUSED(constantBlockSize);
    PX_UNUSED(constantBlock);

    // all initial and persisting reports for everything, with per-point data
    pairFlags = PxPairFlag::eCONTACT_DEFAULT | PxPairFlag::eTRIGGER_DEFAULT;
    return PxFilterFlag::eDEFAULT;
}

void    Physics::CreateScene()  noexcept
{
    PxSceneDesc sceneDesc(physics->getTolerancesScale());

    sceneDesc.cpuDispatcher = dispatcher;

    sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
    sceneDesc.filterShader = PxDefaultSimulationFilterShader;
    sceneDesc.filterShader = ReportFilterShader;
    sceneDesc.simulationEventCallback = &simulationEventCallback;
    scenes.push_back(physics->createScene(sceneDesc));

    //Set flag to get the active actors in the Update
    scenes.back()->setFlag(PxSceneFlag::eENABLE_ACTIVE_ACTORS, true);

    if (currentScene == nullptr)
        currentScene = scenes.back();
}

void Physics::CreateObject(RigidBody& _rigidBody, void*& _actor)	noexcept
{
    AssertMsg(currentScene != nullptr, "currentScene is null");

    if (_actor != nullptr)
        static_cast<PxRigidActor*>(_actor)->release();

    Transform t = _rigidBody.GetOwner()->transform;

    PxGeometry* geometry = CreateGeometry(_rigidBody.GetGeometry(), _rigidBody.GetColliderScale());

    //Search if the material already exists => to not have copy
    PxMaterial* actorMaterial;
    actorMaterial = GetExistingMaterial(Vec3(_rigidBody.GetStaticFriction(), _rigidBody.GetDynamicFriction(), _rigidBody.GetRestitution()));
    
    //Create a new material if the research doesn't succed
    if (actorMaterial == nullptr)
        actorMaterial = physics->createMaterial(_rigidBody.GetStaticFriction(), _rigidBody.GetDynamicFriction(), _rigidBody.GetRestitution());

    PxRigidActor* actor;

    if (_rigidBody.GetIsStatic())
    {
        actor = PxCreateStatic(*physics,
            PxTransform(t.position.x, t.position.y, t.position.z,
                PxQuat(t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w)),
            *geometry, *actorMaterial);
    }
    else
    {
        actor = PxCreateDynamic(*physics,
            PxTransform(t.position.x, t.position.y, t.position.z,
                PxQuat(t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w)),
            *geometry, *actorMaterial, DEFAULT_DENSITY);

        SetActorLockFlags(actor, _rigidBody.GetFreezePosition(), _rigidBody.GetFreezeRotation());

		SetActorMass(actor, _rigidBody.GetMass());
    }

    actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
    SetShapeFlags(actor, _rigidBody.GetIsTrigger());

    //Set the userData with rigidBody to update his transform later
    //Like that the rigidBody don't need to call function, Physics do all the work
    actor->userData = &_rigidBody;
    currentScene->addActor(*actor);
	
	delete geometry;
	
	_actor = actor; //DO NOT REMOVE
}

PxGeometry* Physics::CreateGeometry(const EGeometryType& _geomType, const Vec3& _colliderScale)	noexcept
{
    PxGeometry* geometry;

    //The scale is divide by 2 because physX use half size
    switch (_geomType)
    {
    case EGeometryType::BOX:
        geometry = new PxBoxGeometry(_colliderScale.x / 2, _colliderScale.y / 2, _colliderScale.z / 2);
        break;

    case EGeometryType::SPHERE:
        geometry = new PxSphereGeometry(_colliderScale.x);
        break;

    case EGeometryType::CAPSULE:
        geometry = new PxCapsuleGeometry(_colliderScale.x / 2, _colliderScale.y / 2);
        break;

    default:
        geometry = new PxBoxGeometry(_colliderScale.x / 2, _colliderScale.y / 2, _colliderScale.z / 2);
        break;
    }

    return geometry;
}

PxMaterial*	Physics::GetExistingMaterial(const Vec3& _matValue)	noexcept
{
    unsigned int nbMaterials = physics->getNbMaterials();
    PxMaterial** materials = new PxMaterial * [nbMaterials];

    physics->getMaterials(materials, nbMaterials);

    for (unsigned int i = 0; i < nbMaterials; i++)
    {
        if (_matValue == Vec3((float)materials[i]->getStaticFriction(),
                            (float)materials[i]->getDynamicFriction(),
                            (float)materials[i]->getRestitution()))
        {
			PxMaterial* mat = std::move(materials[i]);
			delete[] materials;
			return mat;
        }
    }
	delete[] materials;
    return nullptr;
}

void    Physics::FixedUpdate() noexcept
{
    AssertMsg(currentScene != nullptr, "currentScene is null");
    
    //Update physX scene
    currentScene->simulate(Time::GetFixUpdateDeltaTime());
    currentScene->fetchResults(true);

    SetActiveActorsPos();
}

void    Physics::SetActiveActorsPos()   noexcept
{
    // retrieve array of actors that moved
    PxU32 nbActiveActors;
    PxActor** activeActors = currentScene->getActiveActors(nbActiveActors);

    // update each RigidBody with the new transform
    for (PxU32 i = 0; i < nbActiveActors; ++i)
    {
        if (activeActors[i]->userData != nullptr)
        {
            //Get actor pos
            PxTransform t = static_cast<PxRigidDynamic*>(activeActors[i])->getGlobalPose();

            //Set RigidBody pos with userData
            RigidBody* rigidBody = static_cast<RigidBody*>(activeActors[i]->userData);
            if (rigidBody->owner->isActive && rigidBody->isActive)
                rigidBody->SetOwnerTransform({ t.p.x, t.p.y, t.p.z }, { t.q.w, t.q.x, t.q.y, t.q.z });

            //Apply custom gravity
            Vec3 g = rigidBody->GetGravity() * rigidBody->GetMass();
            static_cast<PxRigidDynamic*>(activeActors[i])->addForce(PxVec3(g.x, g.y, g.z), PxForceMode::eFORCE);
        }
        else
        {
            //If the component is delete (RigidBody) -> delete the actor in the physX scene
            currentScene->removeActor(*activeActors[i]);
        }
    }
}

bool    Physics::SetCurrentScene(unsigned int _sceneID) noexcept
{
    if (_sceneID >= scenes.size())
        return false;

    currentScene = scenes[_sceneID];

    //Set physX Visual Debugger on the current scene
    PxPvdSceneClient* pvdClient = currentScene->getScenePvdClient();
    if (pvdClient)
    {
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }

    return true;
}

void	Physics::RemoveScene(unsigned int _sceneID)  noexcept
{
    //Check if the scene exists
    if (_sceneID >= scenes.size())
        return;

    if (currentScene == scenes[_sceneID])
        currentScene = nullptr;

    PX_RELEASE(scenes[_sceneID]);

    std::vector<PxScene*>::const_iterator it = scenes.begin();
    scenes.erase(it + _sceneID);
}

void    Physics::EnableActor(void* _actor, const bool _enable)  noexcept
{
    PxRigidActor* actor = static_cast<PxRigidActor*>(_actor);

    if (actor == nullptr)
        return;

    PxActorFlags flags;

    if (_enable)
        flags = PxActorFlag::eDISABLE_GRAVITY;
    else
        flags = PxActorFlag::eDISABLE_GRAVITY | PxActorFlag::eDISABLE_SIMULATION;

    actor->setActorFlags(flags);
}

void    Physics::SetActorPos(void* _actor, const Vec3& _pos, const Quat& _rot)    noexcept
{
    PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(_actor);

    if (actor == nullptr)
        return;

    actor->setGlobalPose(PxTransform({ _pos.x, _pos.y, _pos.z }, {_rot.x, _rot.y, _rot.z, _rot.w}));
}

void    Physics::SetActorGeometry(void* _actor, const EGeometryType& _geom, const Vec3& _colliderScale)  noexcept
{
    PxShape** shapesBuffer = new PxShape * [1];
    PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(_actor);

    if (actor != nullptr)
    {
        actor->getShapes(shapesBuffer, 1);

        if (shapesBuffer[0] != nullptr)
        {
            shapesBuffer[0]->setGeometry(*CreateGeometry(_geom, _colliderScale));
        }
    }
	delete[] shapesBuffer;
}

void    Physics::SetActorLockFlags(void* _actor, const Vec3& _freezePosition, const Vec3& _freezeRotation)    noexcept
{
    PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(_actor);

    if (actor == nullptr)
        return;

    PxRigidDynamicLockFlags flags;

    if (_freezePosition.x == 1)
        flags |= PxRigidDynamicLockFlag::eLOCK_LINEAR_X;
    if (_freezePosition.y == 1)
        flags |= PxRigidDynamicLockFlag::eLOCK_LINEAR_Y;
    if (_freezePosition.z == 1)
        flags |= PxRigidDynamicLockFlag::eLOCK_LINEAR_Z;

    if (_freezeRotation.x == 1)
        flags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_X;
    if (_freezeRotation.y == 1)
        flags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y;
    if (_freezeRotation.z == 1)
        flags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z;

    actor->setRigidDynamicLockFlags(flags);
}

void    Physics::SetActorMaterial(void* _actor, const float _staticFriction,
                                    const float _dynamicFriction, const float _restitution)    noexcept
{
    PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(_actor);

    if (actor == nullptr)
        return;

    PxShape** shapesBuffer = new PxShape * [1];

    if (actor != nullptr)
    {
        actor->getShapes(shapesBuffer, 1);

        if (shapesBuffer[0] != nullptr)
        {
            PxMaterial** mat = new PxMaterial * [1];
            mat[0] = GetExistingMaterial(Vec3(_staticFriction, _dynamicFriction, _restitution));
            
            if (mat[0] == nullptr)
                mat[0] = physics->createMaterial(_staticFriction, _dynamicFriction, _dynamicFriction);

            shapesBuffer[0]->setMaterials(mat, 1);
			delete[] mat;
        }
    }
	delete[] shapesBuffer;
}

void    Physics::SetActorMass(void* actor, const float _mass)   noexcept
{
    static_cast<PxRigidDynamic*>(actor)->setMass(_mass);
}

void    Physics::SetShapeFlags(void* _actor, const bool _isTrigger) noexcept
{
    PxRigidActor* actor = static_cast<PxRigidActor*>(_actor);

    if (actor == nullptr)
        return;

    PxU32 nbShapes = actor->getNbShapes();
    
    if (nbShapes > 0)
    {
        PxShape** shapes = new PxShape * [nbShapes];
        actor->getShapes(shapes, nbShapes);

        PxShapeFlags shapeFlags;
        if (_isTrigger)
            shapeFlags = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE | PxShapeFlag::eTRIGGER_SHAPE;
        else
            shapeFlags = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE | PxShapeFlag::eSIMULATION_SHAPE;
        
        shapes[0]->setFlags(shapeFlags);
		delete[] shapes;
    }
}

void    Physics::AddForce(void* _actor, const Vec3& _force, const EForceType& _type)    noexcept
{
    PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(_actor);

    if (actor == nullptr)
        return;

    PxForceMode::Enum forceMode;
    switch (_type)
    {
    case EForceType::ACCELERATION:
        forceMode = PxForceMode::eACCELERATION;
        break;

    case EForceType::FORCE:
        forceMode = PxForceMode::eFORCE;
        break;

    case EForceType::IMPULSE:
        forceMode = PxForceMode::eIMPULSE;
        break;

    case EForceType::VELOCITY_CHANGE:
        forceMode = PxForceMode::eVELOCITY_CHANGE;
        break;

    default:
        forceMode = PxForceMode::eFORCE;
        break;
    }

    actor->addForce(PxVec3(_force.x, _force.y, _force.z), forceMode);
}

void    Physics::ResetVelocity(void* _actor) noexcept
{
	static_cast<PxRigidDynamic*>(_actor)->setLinearVelocity({ 0, 0, 0 });
}

RigidBody&	Physics::Raycast(const Vec3& _origin, const Vec3& _dir, const float _maxDist)	noexcept
{
    RigidBody*  rigidBodyHit    { nullptr };

    Vec3 dir = _dir.Normalized();
    if (dir == Vec3::zero)
        return *rigidBodyHit;

    float       minDist         { FLT_MAX };

    std::vector<RigidBody*> rbList = Scene::GetCurrentScene()->GetComponentsManager()->GetrbList();

    for (int i = 0; i < rbList.size(); i++)
    {
        rbList[i]->GetPhysicsActor();
        PxShape** shapesBuffer = new PxShape * [1];
        PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(rbList[i]->GetPhysicsActor());
        
        if (actor != nullptr)
        {
            actor->getShapes(shapesBuffer, 1);

            if (shapesBuffer[0] != nullptr)
            {
                PxRaycastHit hitInfo;
                PxU32 maxHits = 1;
                PxHitFlags hitFlags = PxHitFlag::ePOSITION;
                PxU32 hitCount = PxGeometryQuery::raycast(PxVec3(_origin.x, _origin.y, _origin.z), PxVec3(dir.x, dir.y, dir.z),
                    shapesBuffer[0]->getGeometry().any(), actor->getGlobalPose(),
                    _maxDist,
                    hitFlags,
                    maxHits, &hitInfo);

                if (hitCount > 0 && hitInfo.distance < minDist)
                {
                    minDist = hitInfo.distance;
                    rigidBodyHit = rbList[i];
                }
            }
        }
		delete[] shapesBuffer;
    }

    return *rigidBodyHit;
}
