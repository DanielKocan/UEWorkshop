
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraRig.generated.h"

UCLASS()
class CAMERAPLUGIN_API ACameraRig : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraRig(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DanielCore")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DanielCore")
	TObjectPtr<class UCameraComponent> Camera;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
