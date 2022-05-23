// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USceneComponent;

UCLASS()
class DEATH_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	ADCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;
	virtual void StopJumping() override;
	void StopTestJump();

protected:	
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* SpringArmComponent;
	/* Show more of right or left of screen depending on what way the player is facing/moving */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	USceneComponent* CameraHelperComponent;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FacingRightCamOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FacingLeftCamOffset;
	
private:
	
	FVector2D InitialViewPortSize;
	FVector2D ViewportSize;

	FVector2D GetViewportSize();
	//void AdjustCamera();
	
	

	
public:	


};
