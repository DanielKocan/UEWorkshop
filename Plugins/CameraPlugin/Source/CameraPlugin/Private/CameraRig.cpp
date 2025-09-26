#include "CameraRig.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACameraRig::ACameraRig(const FObjectInitializer& ObjectInitializer)
{
	// For transform
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(-250.0f, 0.0f,0.0f));
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACameraRig::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraRig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


