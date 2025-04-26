// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Basepawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasepawn
{
	GENERATED_BODY()

public:
	ATank();

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankMesh", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankMesh", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float _speed = 200.f;

	void Move(float value);
	
};
