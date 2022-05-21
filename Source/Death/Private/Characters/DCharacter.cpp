// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ADCharacter::ADCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	// Camera and friends
	CameraHelperComponent = CreateDefaultSubobject<USceneComponent>("CameraHelperComponent");
	CameraHelperComponent->SetupAttachment(RootComponent);
	
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CameraHelperComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(0.f, 10.f, 90.f)); // Camera rotated so moving forward moves us right
	SpringArmComponent->TargetArmLength = 800.f;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 5.f;
	SpringArmComponent->CameraLagMaxDistance = 100.f;	
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	FacingRightCamOffset = 500.f;
	FacingLeftCamOffset = 500.f;

	// lock the Y plane so we can only run right and left
	GetCharacterMovement()->SetPlaneConstraintEnabled(true);	
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
}


void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetViewportSize();
	InitialViewPortSize = ViewportSize;

	CameraHelperComponent->SetRelativeLocation(FVector(FacingRightCamOffset, 0.f, 0.f), true);
	
}


void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ADCharacter::MoveForward);	
}

void ADCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{		
		const FRotator YawRotator(0.f, Controller->GetControlRotation().Yaw, 0.f); 
		const FVector Direction(FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X)); // Returns: vector of the axis ( points in the Yaw direction of our controller
		AddMovementInput(Direction, Value); // Speed and acceleration is not handled here. That's handled in Character Movement component			
	}
}

FVector2D ADCharacter::GetViewportSize()
{
	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
	
	return ViewportSize;
}
