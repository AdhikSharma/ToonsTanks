// Fill out your copyright notice in the Description page of Project Settings.


#include "Basepawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ABasepawn::ABasepawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasepawn::HandleDestruction()
{
	//TODO : Visual and sound effects
	if (_deathParticle) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, _deathParticle, GetActorLocation(), GetActorRotation());
	}

	if (_deathParticle) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, _deathSound, GetActorLocation(), 1.f, 1.f);
	}

	if (DeathCameraShakeClass) 
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}

}

void ABasepawn::RotateTurret(FVector lookAtTarget)
{
	FVector toTarget = lookAtTarget - TurretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, toTarget.Rotation().Yaw, 0.f);
	
	TurretMesh->SetWorldRotation
		(FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			lookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			20.f)
		);

}

void ABasepawn::Fire()
{
	FVector location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto projectile = GetWorld()->SpawnActor<AProjectile>(_projectileClass, location,rotation);
	projectile->SetOwner(this);
}
