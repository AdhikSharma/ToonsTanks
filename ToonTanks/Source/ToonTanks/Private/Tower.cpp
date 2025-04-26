// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{

}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	_tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(_fireRateTimerHandle,this, &ATower::CheckFireCondition,_fireRate,true);
}


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(_tank->GetActorLocation());
	}

}

void ATower::CheckFireCondition()
{
	if (InFireRange()) 
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (_tank)
	{
		float distance = FVector::Dist(GetActorLocation(), _tank->GetActorLocation());
		if (distance <= _fireRange)
		{
			return true;
		}
	}

	return false;
}



