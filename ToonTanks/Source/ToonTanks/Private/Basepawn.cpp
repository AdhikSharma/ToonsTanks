// Fill out your copyright notice in the Description page of Project Settings.


#include "Basepawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

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
	DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnPoint->GetComponentLocation(),
		20.f,
		12,
		FColor::Blue,
		true,
		3.f);
}
