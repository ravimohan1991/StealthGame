// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "FPSPlayerController.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::MissionCompleted(APawn* InstigatorPawn, bool bSuccess)
{
	if (InstigatorPawn == nullptr)
	{
		return;
	}
	
	AActor* VPActor = UGameplayStatics::GetActorOfClass(this, ViewportActor);
	if (VPActor)
	{
		for (TActorIterator<AFPSPlayerController>It(GetWorld()); It; ++It)
		{
			AFPSPlayerController* PC = *It;
			if (PC)
			{
				PC->SetViewTargetWithBlend(VPActor, 0.5f, VTBlend_Cubic);
			}
		}
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->MulticastMissionComplete(InstigatorPawn, bSuccess);
	}
}
