// @CGlearning
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	FindPressurePlate();
	FindAudioComponent();
}

void UOpenDoor::FindPressurePlate()
{
	if (!PressurePlate)
	{
		//Actor Name has the open door component attach on it, but no PressurePlate is setup.
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component attach on it, but no PressurePlate is setup!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing audio component"), *GetOwner()->GetName())
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float YourFloat = TotalMassOfActors();

	if (TotalMassOfActors() > ThresholdMass)
	{
		OpenDoor(DeltaTime);
		//DoorLastOpened when the door was opened
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else 
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) 
{
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	//Set Actor Rotation
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSound = false;
	if (!AudioComponent) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	//Set Actor Rotation
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSound = false;
	if (!AudioComponent) { return; }
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float Totalmass = 0.f;

	//Find All Overlapping Actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return Totalmass; }
	PressurePlate->GetOverlappingActors(OverlappingActors);

	//Add up their masses
	for (AActor* AActor : OverlappingActors)
	{
		Totalmass += AActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return Totalmass;
}
