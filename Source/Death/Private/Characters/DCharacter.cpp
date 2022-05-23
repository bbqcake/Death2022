// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DCharacter.h"

#include <cwchar>

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"


ADCharacter::ADCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	// Dont rotate along with the controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	
	// Camera and friends
	CameraHelperComponent = CreateDefaultSubobject<USceneComponent>("CameraHelperComponent");
	CameraHelperComponent->SetupAttachment(RootComponent);	
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CameraHelperComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(0.f, 10.f, 90.f)); // Camera rotated so moving forward moves us right
	SpringArmComponent->TargetArmLength = 800.f;
	//SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->SetUsingAbsoluteRotation(true);
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
	GetCharacterMovement()->bOrientRotationToMovement = true; // turn and face Direction we are moving
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.f); // Turn speed

	// movement
	
	GetCharacterMovement()->bNotifyApex = true;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
	GetCharacterMovement()->MaxAcceleration = 1024.f;	
	GetCharacterMovement()->BrakingFriction = 0.2f;
	// jumping, gravity
	JumpMaxHoldTime = 0.3f;
	GetCharacterMovement()->JumpZVelocity = 1100.f;
	GetCharacterMovement()->GravityScale = 3.f;
	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->AirControlBoostMultiplier = 2.f;
	GetCharacterMovement()->AirControlBoostVelocityThreshold = 900000000000000000000000000.f;
	
	GetCharacterMovement()->bUseSeparateBrakingFriction = true;	
	
	
}


void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetViewportSize();
	InitialViewPortSize = ViewportSize;
	
}


void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ADCharacter::MoveForward);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ADCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ADCharacter::StopJumping);
	
}

void ADCharacter::Jump()
{
	Super::Jump();
	UE_LOG(LogTemp, Warning, TEXT("Jumping"));
}

void ADCharacter::StopJumping()
{
	Super::StopJumping();
	FVector Velocity = GetCharacterMovement()->GetLastUpdateVelocity();	
	//NotifyJumpApex(); // Doesn't do anything ? I'm leaving it here because I can
	
	
	if (Velocity.Z > 0.f)
	{		
		UE_LOG(LogTemp, Warning, TEXT("Stop our jump now!"));
	}
		
}

void ADCharacter::StopTestJump()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop our test jump now!"));
}

void ADCharacter::MoveForward(float Value)
{
	AddMovementInput(FVector(1.f,0.f,0.f), Value);	
}

FVector2D ADCharacter::GetViewportSize()
{
	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
	
	return ViewportSize;
}
