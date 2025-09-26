#include "CameraRigControllerComponent.h"
#include "CameraRig.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "Logging/LogMacros.h"

// Sets default values for this component's properties
UCameraRigControllerComponent::UCameraRigControllerComponent(const FObjectInitializer& ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCameraRigControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCameraRigControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Nothing to implement yet
}

void UCameraRigControllerComponent::EnsureCameraRig()
{
	if (SpawnedCameraRig && !SpawnedCameraRig->IsPendingKillPending())
	{
		return;
	}

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	APawn* Pawn = PC->GetPawn();

	if (!Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("CameraRigControllerComponent: No Pawn possessed yet; deferring CameraRig spawn until it is."));
		return;
	}

	FVector SpawnLoc = Pawn->GetActorLocation();
	FRotator SpawnRot = FRotator::ZeroRotator;

	if (CameraRigTemplate)
	{
		SpawnedCameraRig = GetWorld()->SpawnActor<ACameraRig>(CameraRigTemplate, SpawnLoc, SpawnRot);
	}
	else
	{
		// If you ever place a CameraRig in level and want to re-use it:
		for (TActorIterator<ACameraRig> It(GetWorld()); It; ++It)
		{
			SpawnedCameraRig = *It;
			break;
		}
	}

	if (SpawnedCameraRig)
	{
		PC->SetViewTarget(SpawnedCameraRig);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CameraRigControllerComponent: Failed to create/find ACameraRig."));
	}
}

