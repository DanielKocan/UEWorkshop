

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DanielGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DAVEWORKSHOPY3A_API ADanielGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADanielGameMode(const FObjectInitializer& FObjectInitializer);

	void BeginPlay() override;
};
