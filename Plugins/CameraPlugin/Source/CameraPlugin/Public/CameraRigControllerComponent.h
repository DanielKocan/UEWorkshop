

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraRigControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMERAPLUGIN_API UCameraRigControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraRigControllerComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	void EnsureCameraRig();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OmniCameraCore")
	TSubclassOf<class ACameraRig> CameraRigTemplate;

	UPROPERTY(Transient)
	TObjectPtr<class ACameraRig> SpawnedCameraRig;
};
