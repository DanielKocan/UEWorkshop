#include "DanielGameInstance.h"
#include "Actors/CameraRig.h"

// Sets default values
ADanielGameInstance::ADanielGameInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADanielGameInstance::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<ACameraRig>(); //Why it dosent work?
}

// Called every frame
void ADanielGameInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


