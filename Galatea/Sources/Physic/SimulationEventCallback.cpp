#include "Physic/SimulationEventCallback.h"
#include "Physic/RigidBody.h"
#include <vector>

using namespace Galatea;

void	SimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	PX_UNUSED(pairs); PX_UNUSED(nbPairs);

	RigidBody* actor0 = static_cast<RigidBody*>(pairHeader.actors[0]->userData);
	RigidBody* actor1 = static_cast<RigidBody*>(pairHeader.actors[1]->userData);

	actor0->OnContact(actor1);
	actor1->OnContact(actor0);
}

void	SimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	PX_UNUSED(count);

	RigidBody* actor0 = static_cast<RigidBody*>(pairs->triggerActor->userData);
	RigidBody* actor1 = static_cast<RigidBody*>(pairs->otherActor->userData);

	actor0->OnContact(actor1);
	actor1->OnContact(actor0);
}