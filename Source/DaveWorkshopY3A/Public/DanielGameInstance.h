#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DanielGameInstance.generated.h"

UCLASS()
class DAVEWORKSHOPY3A_API ADanielGameInstance : public AGameState
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADanielGameInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
