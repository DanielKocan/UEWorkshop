
#include "DanielGameMode.h"


#include "DanielPawn.h"
#include "DanielPlayerController.h"
#include "DanielPlayerState.h"
#include "DanielGameState.h"
#include "DanielHUD.h"

#include "CameraRig.h"

ADanielGameMode::ADanielGameMode(const FObjectInitializer& FObjectInitializer)
{
	DefaultPawnClass = ADanielPawn::StaticClass();
	GameStateClass = ADanielGameState::StaticClass();
	PlayerControllerClass = ADanielPlayerController::StaticClass();
	PlayerStateClass = ADanielPlayerState::StaticClass();
	HUDClass = ADanielHUD::StaticClass();
}

void ADanielGameMode::BeginPlay()  
{
    Super::BeginPlay();

    if (UWorld* World = GetWorld())
    {
        ACameraRig* CameraRig = World->SpawnActor<ACameraRig>();
        if (CameraRig)
        {
            UE_LOG(LogTemp, Warning, TEXT("CameraRig spawned and BeginPlay should be called"));
        }
    }
}