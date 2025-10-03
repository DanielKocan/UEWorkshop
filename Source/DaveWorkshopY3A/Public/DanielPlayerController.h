#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DanielPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DAVEWORKSHOPY3A_API ADanielPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ADanielPlayerController(const FObjectInitializer& ObjectInitializer);

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RomanCore")
    TObjectPtr<class UCameraRigControllerComponent> CameraRigControllerComponent;

protected:
    void SetupInputComponent() override;
};
