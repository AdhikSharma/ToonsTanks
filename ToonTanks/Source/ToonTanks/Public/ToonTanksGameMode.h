// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* actorDied);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool won);


private:
	class ATank* _tank;
	class AToonTanksPlayerController* _playerController;

	UPROPERTY(EditDefaultsOnly)
	float _startDelay = 3.f;

	void HandleGameStart();

	
	int32 _targetTowers = 4;

	int32 GetTowerTargetCount();
	
};
