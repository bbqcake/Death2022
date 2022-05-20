// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

UCLASS()
class DEATH_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	ADCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:	
	virtual void BeginPlay() override;

private:
	

	
public:	


};
