// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ATank::ATank()
{
	SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	SpringComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	CameraComp->SetupAttachment(SpringComp);

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	_playerControllerRef = Cast<APlayerController>(GetController());
	
	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_playerControllerRef)
	{
		FHitResult hitResult;
		_playerControllerRef->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			hitResult);

		RotateTurret(hitResult.ImpactPoint);
	}
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed ,this, &ATank::Fire);

}

void ATank::Move(float value)
{
	//UE_LOG(LogTemp,Warning,TEXT("Value : %f"),value);
	FVector deltaLocation = FVector::ZeroVector;
	deltaLocation.X = value*_speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(deltaLocation,true);
}

void ATank::Turn(float value)
{
	FRotator deltaRotation = FRotator::ZeroRotator;
	deltaRotation.Yaw = value * _rotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(deltaRotation,true);
}
