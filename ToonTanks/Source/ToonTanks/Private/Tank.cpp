// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
	SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	SpringComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	CameraComp->SetupAttachment(SpringComp);

}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &ATank::Move);

}

void ATank::Move(float value)
{
	UE_LOG(LogTemp,Warning,TEXT("Value : %f"),value);
	FVector deltaLocation = FVector::ZeroVector;
	deltaLocation.X = value*_speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(deltaLocation);
}
