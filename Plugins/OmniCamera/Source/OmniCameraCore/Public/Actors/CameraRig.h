#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CameraRig.generated.h"

UCLASS()
class OMNICAMERACORE_API ACameraRig : public AActor
{
    GENERATED_BODY()

public:
    ACameraRig();

public:
    /** Components **/
    UPROPERTY(VisibleAnywhere, Category = "OmniCameraCore")
    TObjectPtr<class USpringArmComponent>       SpringArm;

    UPROPERTY(VisibleAnywhere, Category = "OmniCameraCore")
    TObjectPtr<class UCameraComponent>          Camera;

    UPROPERTY(VisibleAnywhere, Category = "OmniCameraCore")
    TObjectPtr<class UCameraRigZoomComponent>   CameraZoom;
    UPROPERTY(VisibleAnywhere, Category = "OmniCameraCore")
    TObjectPtr<class UCameraRigPanComponent>    CameraPan;
    UPROPERTY(VisibleAnywhere, Category = "OmniCameraCore")
    TObjectPtr<class UCameraRigRotateComponent> CameraRotate;

public:
    /** Called every frame by controller to rotate camera. */
    void AddRotationInput(float Value);
    /** Called by controller when mouse wheel moves. */
    void AddZoomInput(float Value);
    /** Called each frame while the controller is streaming mouse X for panning. */
    void AddPanKeyXInput(float Value);
    /** Called each frame while the controller is streaming mouse Y for panning. */
    void AddPanKeyYInput(float Value);

    /** Called each frame while the controller is streaming mouse X for panning. */
    void AddPanJoystickXInput(float Value);
    /** Called each frame while the controller is streaming mouse Y for panning. */
    void AddPanJoystickYInput(float Value);
    /** Called when the controller sees PanToggle pressed. */
    void StartJoystickPan();
    /** Called when the controller sees PanToggle released. */
    void EndJoystickPan();
};