// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _projectileMesh;

	_movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	_movementComp->MaxSpeed = 1300.f;
	_movementComp->InitialSpeed = 1300.f;

	_trailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trailt"));
	_trailParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	_projectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);

	if (_launchSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, _launchSound, GetActorLocation(), 1.f, 1.f);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& hitResult)
{
	//UE_LOG(LogTemp,Warning,TEXT("Hit : %s , %s , %s"), *otherActor->GetName(), *HitComp->GetName(), *otherComp->GetName());

	auto myOwner = GetOwner();
	if (myOwner == nullptr) 
	{
		Destroy();
		return;
	} 

	auto myOwnerInstigator = myOwner->GetInstigatorController();
	auto damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor!=this && otherActor!= myOwner) 
	{
		UGameplayStatics::ApplyDamage(otherActor,_damage, myOwnerInstigator, this, damageTypeClass);
		if (_hitParticle) 
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, _hitParticle, GetActorLocation(), GetActorRotation());
		}

		if (_hitSound) 
		{
			UGameplayStatics::PlaySoundAtLocation(this, _hitSound, GetActorLocation(), 1.f, 1.f);
		}

		if (HitCameraShakeClass) 
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}

	}

	Destroy();

}

