// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* _projectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* _movementComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,AActor* otherActor, UPrimitiveComponent* otherComp,FVector NormalImpulse,const FHitResult& hit);
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float _damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* _hitParticle;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* _trailParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USoundBase* _launchSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USoundBase* _hitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;


};
