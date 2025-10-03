#include "Components/CameraRigZoomComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/CameraRig.h"

//--------------------------------------------------------------------------
UCameraRigZoomComponent::UCameraRigZoomComponent()
{
    ZoomSpeed = 200.f;
    MinArmLength = 300.f;
    MaxArmLength = 1500.f;
}

//--------------------------------------------------------------------------
void UCameraRigZoomComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Nothing to implement
}

//--------------------------------------------------------------------------
void UCameraRigZoomComponent::OnZoomCamera(float Value)
{
    if(CameraRig == nullptr)
    {
        return;
    }

    if (FMath::IsNearlyZero(Value)) 
    {
        return;
    }

    float Desired = CameraRig->SpringArm->TargetArmLength - Value * ZoomSpeed;
    Desired = FMath::Clamp(Desired, MinArmLength, MaxArmLength);
    CameraRig->SpringArm->TargetArmLength = Desired;
}