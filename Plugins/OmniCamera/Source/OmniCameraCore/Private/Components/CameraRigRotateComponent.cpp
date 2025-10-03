#include "Components/CameraRigRotateComponent.h"

//--------------------------------------------------------------------------
UCameraRigRotateComponent::UCameraRigRotateComponent()
{
    CurrentRotationInput = 0.f;
    RotationSpeed = 45.f;
}

//--------------------------------------------------------------------------
void UCameraRigRotateComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (FMath::Abs(CurrentRotationInput) > KINDA_SMALL_NUMBER)
    {
        float DeltaYaw = CurrentRotationInput * RotationSpeed * DeltaTime;
        GetOwner()->AddActorLocalRotation(FRotator(0.f, DeltaYaw, 0.f));
    }
}

//--------------------------------------------------------------------------
void UCameraRigRotateComponent::OnRotateCamera(float Value)
{
    CurrentRotationInput = Value;
}