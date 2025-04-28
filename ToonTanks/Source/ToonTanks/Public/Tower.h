// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Basepawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasepawn
{
	GENERATED_BODY()

public:
	ATower();

	void HandleDestruction();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	class ATank* _tank;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float _fireRange = 300.f;

	FTimerHandle _fireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float _fireRate = 2.f;
	void CheckFireCondition();
	bool InFireRange();

};
