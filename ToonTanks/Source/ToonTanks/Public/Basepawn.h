// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Basepawn.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API ABasepawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasepawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector lookAtTarget);
	void Fire();



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankMesh", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankMesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankMesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankMesh", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> _projectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* _deathParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USoundBase* _deathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;



};
