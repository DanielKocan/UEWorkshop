#pragma once

#include "CoreMinimal.h"
#include "Components/CameraRigComponent.h"

#include "CameraRigZoomComponent.generated.h"

UCLASS()
class OMNICAMERACORE_API UCameraRigZoomComponent : public UCameraRigComponent
{
    GENERATED_BODY()

public:
    UCameraRigZoomComponent();

public:
    UPROPERTY(EditAnywhere, Category = "OmniCameraCore")
    float ZoomSpeed;
    UPROPERTY(EditAnywhere, Category = "OmniCameraCore")
    float MinArmLength;
    UPROPERTY(EditAnywhere, Category = "OmniCameraCore")
    float MaxArmLength;

public:
    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

public:
    void OnZoomCamera(float Value);
};