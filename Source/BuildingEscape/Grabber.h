// @CGlearning

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

#define OUT

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 100.f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	void Grab();
	void ReleaseGrab();
	void FindPhysicsHandle();
	void SetupInputComponent();

	//Return the LineTranceEnd
	FVector GetPlayersReach() const;

	//Get Players Position in Worlds
	FVector GetPlayersWorldPos() const;

	//Return the first actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;
};
