
#include "DanielPlayerController.h"

#include "Components/CameraRigControllerComponent.h"
#include "EnhancedInputComponent.h"

ADanielPlayerController::ADanielPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    CameraRigControllerComponent = CreateDefaultSubobject<UCameraRigControllerComponent>(TEXT("CameraRigControllerComponent"));
}

void ADanielPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (CameraRigControllerComponent)
    {
        UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
        if (ensureMsgf(EnhancedInputComponent, TEXT("ADanielPlayerController::SetupInputComponent: InputComponent is not a UEnhancedInputComponent!")))
        {
            CameraRigControllerComponent->BindInput(EnhancedInputComponent);
        }
    }
}


