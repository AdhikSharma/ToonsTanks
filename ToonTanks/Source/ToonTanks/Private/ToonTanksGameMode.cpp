// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
}



void AToonTanksGameMode::HandleGameStart()
{
	_targetTowers = GetTowerTargetCount();
	_tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	_playerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (_playerController) 
	{
		_playerController->SetPlayerEnabledState(false);

		FTimerHandle playerEnableTimerHandle;
		FTimerDelegate playerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			_playerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(playerEnableTimerHandle,
			playerEnableTimerDelegate,
			_startDelay,
			false
		);

	}
}

void AToonTanksGameMode::ActorDied(AActor* actorDied)
{
	if (_tank && actorDied==_tank)
	{
		_tank->HandleDestruction();
		if (_playerController)
		{
			_playerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* destroyedTower = Cast<ATower>(actorDied)) 
	{	
		destroyedTower->HandleDestruction();
		--_targetTowers;
		if (_targetTowers==0) 
		{
			GameOver(true);
		}
	}
}

int32 AToonTanksGameMode::GetTowerTargetCount()
{
	TArray<AActor*> towers;

	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);

	return towers.Num();
}


