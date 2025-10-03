#include "Components/CameraRigControllerComponent.h"
#include "Actors/CameraRig.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Log.h"

//--------------------------------------------------------------------------
UCameraRigControllerComponent::UCameraRigControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	EnsureCameraRig();

	// Add the camera mapping context on the local player
	if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
			{
				if (CameraDefaultMappingContext)
				{
					Subsys->AddMappingContext(CameraDefaultMappingContext, /*Priority*/0);
					UE_LOG(LogOmniCameraCore, Log, TEXT("Default Camera Mapping Context Added"));
				}
			}
		}
	}
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemovePanningMapping();

	if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
			{
				if (CameraDefaultMappingContext)
				{
					Subsys->RemoveMappingContext(CameraDefaultMappingContext);
					UE_LOG(LogOmniCameraCore, Log, TEXT("Default Camera Mapping Context Removed"));
				}
			}
		}
	}

	Super::EndPlay(EndPlayReason);
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::BindInput(UEnhancedInputComponent* EnhancedIC)
{
	if (!ensure(EnhancedIC)) { return; }

	// Zoom / Rotate
	if (CameraZoomAction)    EnhancedIC->BindAction(CameraZoomAction,    ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_ZoomCamera);
	if (CameraRotateAction)
	{
		EnhancedIC->BindAction(CameraRotateAction, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_RotateCamera);
		EnhancedIC->BindAction(CameraRotateAction, ETriggerEvent::Canceled,  this, &UCameraRigControllerComponent::Input_RotateCamera);
		EnhancedIC->BindAction(CameraRotateAction, ETriggerEvent::Completed, this, &UCameraRigControllerComponent::Input_RotateCamera);
	}

	// Pan (keys/joystick)
	if (CameraPanKeyXAction)      EnhancedIC->BindAction(CameraPanKeyXAction,      ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanKeyX);
	if (CameraPanKeyYAction)      EnhancedIC->BindAction(CameraPanKeyYAction,      ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanKeyY);
	if (CameraPanJoystickXAction) EnhancedIC->BindAction(CameraPanJoystickXAction, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanJoystickX);
	if (CameraPanJoystickYAction) EnhancedIC->BindAction(CameraPanJoystickYAction, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanJoystickY);
	if (CameraPanJoystickStart)
	{
		EnhancedIC->BindAction(CameraPanJoystickStart, ETriggerEvent::Triggered, this, &UCameraRigControllerComponent::Input_PanJoystickPressed);
		EnhancedIC->BindAction(CameraPanJoystickStart, ETriggerEvent::Completed, this, &UCameraRigControllerComponent::Input_PanJoystickReleased);
		EnhancedIC->BindAction(CameraPanJoystickStart, ETriggerEvent::Canceled,  this, &UCameraRigControllerComponent::Input_PanJoystickReleased);
	}
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::EnsureCameraRig()
{
	if (CameraRigActor && !CameraRigActor->IsPendingKillPending()) { return; }

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	APawn* Pawn = PC->GetPawn();

	if (!Pawn)
	{
		UE_LOG(LogOmniCameraCore, Warning, TEXT("CameraRigInputComponent: No Pawn possessed yet; deferring CameraRig spawn until it is."));
		return;
	}

	FVector SpawnLoc = Pawn->GetActorLocation();
	FRotator SpawnRot = FRotator::ZeroRotator;

	if (CameraRigTemplate)
	{
		CameraRigActor = GetWorld()->SpawnActor<ACameraRig>(CameraRigTemplate, SpawnLoc, SpawnRot);
	}
	else
	{
		// If you ever place a CameraRig in level and want to re-use it:
		for (TActorIterator<ACameraRig> It(GetWorld()); It; ++It)
		{
			CameraRigActor = *It;
			break;
		}
	}

	if (CameraRigActor)
	{
		PC->SetViewTarget(CameraRigActor);
	}
	else
	{
		UE_LOG(LogOmniCameraCore, Warning, TEXT("CameraRigInputComponent: Failed to create/find ACameraRig."));
	}
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::AddPanningMapping()
{
	if (bPanningContextActive || !CameraPanningMappingContext) { return; }

	if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
			{
				Subsys->AddMappingContext(CameraPanningMappingContext, /*Priority*/1);
				bPanningContextActive = true;
				UE_LOG(LogOmniCameraCore, Log, TEXT("Panning Camera Mapping Context Added"));
			}
		}
	}
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::RemovePanningMapping()
{
	if (!bPanningContextActive || !CameraPanningMappingContext) { return; }

	if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
			{
				Subsys->RemoveMappingContext(CameraPanningMappingContext);
				bPanningContextActive = false;
				UE_LOG(LogOmniCameraCore, Log, TEXT("Panning Camera Mapping Context Removed"));
			}
		}
	}
}

//--------------------------------------------------------------------------
void UCameraRigControllerComponent::Input_RotateCamera(const FInputActionValue& Value)
{
	if (CameraRigActor) { CameraRigActor->AddRotationInput(Value.Get<float>()); }
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::Input_ZoomCamera(const FInputActionValue& Value)
{
	if (CameraRigActor) { CameraRigActor->AddZoomInput(Value.Get<float>()); }
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::Input_PanKeyX(const FInputActionValue& Value)
{
	if (CameraRigActor) { CameraRigActor->AddPanKeyXInput(Value.Get<float>()); }
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::Input_PanKeyY(const FInputActionValue& Value)
{
	if (CameraRigActor) { CameraRigActor->AddPanKeyYInput(Value.Get<float>()); }
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::Input_PanJoystickX(const FInputActionValue& Value)
{
	if (CameraRigActor) { CameraRigActor->AddPanJoystickXInput(Value.Get<float>()); }
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::Input_PanJoystickY(const FInputActionValue& Value)
{
	if (CameraRigActor) { CameraRigActor->AddPanJoystickYInput(Value.Get<float>()); }
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::Input_PanJoystickPressed(const FInputActionValue& Value)
{
	if (Value.Get<bool>() && CameraRigActor)
	{
		CameraRigActor->StartJoystickPan();
		AddPanningMapping();
	}
}
//--------------------------------------------------------------------------
void UCameraRigControllerComponent::Input_PanJoystickReleased(const FInputActionValue& Value)
{
	if (!Value.Get<bool>() && CameraRigActor)
	{
		CameraRigActor->EndJoystickPan();
		RemovePanningMapping();
	}
}
