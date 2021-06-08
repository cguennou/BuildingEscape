// @CGlearning

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/AudioComponent.h"
#include "OpenDoor.generated.h"

#define OUT


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void FindPressurePlate();

private:

	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere);
	float ThresholdMass = 50.f;

	UPROPERTY(EditAnywhere);
	float OpenAngle;

	UPROPERTY(EditAnywhere);
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere);
	float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere);
	float DoorOpenSpeed = 0.8f;

	UPROPERTY(EditAnywhere);
	float DoorCloseSpeed = 2.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

};
