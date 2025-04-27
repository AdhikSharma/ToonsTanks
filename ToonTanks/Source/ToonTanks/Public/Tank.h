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

	void HandleDestruction();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlayerController* GetTankPlayerController() const { return _playerControllerRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankMesh", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankMesh", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float _speed = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float _rotationSpeed = 100.f;

	APlayerController* _playerControllerRef;

private:
	void Move(float value);
	void Turn(float value);
	
};
