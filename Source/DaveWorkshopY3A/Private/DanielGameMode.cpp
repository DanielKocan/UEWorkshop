
#include "DanielGameMode.h"

#include "DanielPawn.h"
#include "DanielPlayerController.h"
#include "DanielPlayerState.h"
#include "DanielGameState.h"


ADanielGameMode::ADanielGameMode(const FObjectInitializer& FObjectInitializer)
{
	DefaultPawnClass = ADanielPawn::StaticClass();
	PlayerControllerClass = ADanielPlayerController::StaticClass();
	PlayerStateClass = ADanielPlayerState::StaticClass();

}
