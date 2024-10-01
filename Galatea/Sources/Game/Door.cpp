#include "Core/Scene.h"
#include "Core/Camera/Camera.h"
#include "Debug/Assert.h"
#include "Debug/Log.h"
#include "Core/Time.h"

#include "Game/Door.h"

using namespace Galatea;
using namespace GravityGun;

#pragma region Constructors/Destructor

Door::Door() noexcept
	:	doorLeaf{ nullptr }, doorLeafRB{ nullptr }, playerRB{ nullptr }, doorOpenSound{ nullptr },
		doorCloseSound{ nullptr }, LeafOpenedPosition{ 0, 1.5f, 0 }, LeafClosedPosition{ 0, 0.f, 0 },
		openingSpeed{ 5.f }, isOpen{ false }
{}

Door::~Door() noexcept
{}

#pragma endregion

#pragma region Methods

void Door::Init() noexcept
{
	doorLeaf = owner->GetChild("DoorLeaf");
	doorLeafRB = owner->GetChild("DoorLeaf")->GetComponent<RigidBody>();
	playerRB = Scene::GetCurrentScene()->GetCurrentCamera()->owner->parent->GetComponent<RigidBody>();
	doorOpenSound = owner->GetComponents<Sound>()[0];
	doorCloseSound = owner->GetComponents<Sound>()[1];
	
	doorOpenSound->SetVolume(0.5f);
	doorOpenSound->Set3DMinMaxDistance(0.1f, 40.f);
	doorOpenSound->Set3DConeSettings(360.f, 360.f, 0.5f);

	doorCloseSound->SetVolume(0.5f);
	doorCloseSound->Set3DMinMaxDistance(0.1f, 40.f);
	doorCloseSound->Set3DConeSettings(360.f, 360.f, 0.5f);

	//if (playerRB->GetGravity().Normalized() == doorLeafRB->GetGravity().Normalized())
	//	doorLeaf->transform.position = LeafOpenedPosition;
	//else
	doorLeaf->transform.position = LeafClosedPosition;
}

void Door::Update() noexcept
{
	bool isSameGravity{ playerRB->GetGravity().Normalized() == doorLeafRB->GetGravity().Normalized() };

	if (isSameGravity && !isOpen)
	{
		doorOpenSound->Play();

		doorLeaf->isActive = false;
		doorLeafRB->Enable(false);
		isOpen = true;
	}
	else if (!isSameGravity && isOpen)
	{
		doorCloseSound->Play();

		doorLeaf->isActive = true;
		doorLeafRB->Enable(true);
		isOpen = false;
	}
	/*if (isOpen && doorLeaf->transform.position != LeafOpenedPosition)
		doorLeaf->transform.position = doorLeaf->transform.position.Lerp(LeafOpenedPosition, (float)Time::GetDeltaTime() * openingSpeed);
	else if (!isOpen && doorLeaf->transform.position != LeafClosedPosition)
		doorLeaf->transform.position = doorLeaf->transform.position.Lerp(LeafClosedPosition, (float)Time::GetDeltaTime() * openingSpeed);*/
}

#pragma endregion
