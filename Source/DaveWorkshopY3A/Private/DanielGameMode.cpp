
#include "DanielGameMode.h"

#include "DanielPawn.h"
#include "DanielPlayerController.h"
#include "DanielPlayerState.h"
#include "DanielGameState.h"
#include "DanielHUD.h"


ADanielGameMode::ADanielGameMode(const FObjectInitializer& FObjectInitializer)
{
	DefaultPawnClass = ADanielPawn::StaticClass();
	GameStateClass = ADanielGameState::StaticClass();
	PlayerControllerClass = ADanielPlayerController::StaticClass();
	PlayerStateClass = ADanielPlayerState::StaticClass();
	HUDClass = ADanielHUD::StaticClass();
}
