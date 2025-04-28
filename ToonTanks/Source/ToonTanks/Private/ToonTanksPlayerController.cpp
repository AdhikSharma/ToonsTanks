// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"


void AToonTanksPlayerController::SetPlayerEnabledState(bool enabled)
{
	if (enabled) 
	{
		GetPawn()->EnableInput(this);
	}
	else 
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = enabled;

}
