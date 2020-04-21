// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSCharacter.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastMissionComplete_Implementation(APawn* InstigatorPawn, bool bSuccess)
{
	UWorld* MyWorld = GetWorld();
	for (TActorIterator<AFPSCharacter> At(MyWorld); At; ++At)
	{
		ACharacter* MyCharacter = *At;
		if (MyCharacter && MyCharacter->IsLocallyControlled())
		{
			MyCharacter->DisableInput(nullptr);
			AFPSPlayerController* PC = Cast<AFPSPlayerController>(MyCharacter->GetController());
			if (PC)
			{
				PC->OnMissionComplete(InstigatorPawn, bSuccess);
			}
		}
	}
}
