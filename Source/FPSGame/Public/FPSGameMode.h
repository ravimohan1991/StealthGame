// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	/**
	* Called on the completion of the mission. Disables input of the instigator
	* pawn and calls a blueprint function.
	*
	* @param InstigatorPawn The pawn responsible for completing the mission
	* @see AFPSExtractionZone::OnOverlap
	*/
	void MissionCompleted(APawn* InstigatorPawn);

	/**
	* Called on the completion of the mission.
	*
	* @param InstigatorPawn The pawn responsible for completing the mission
	* @see AFPSGameMode::MissionCompleted
	* @see Blueprint'/Game/Blueprints/BP_GameMode.BP_GameMode'
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn);

private:
	/** The class of viewport actor.  Used at the end of mission */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<AActor> ViewportActor;
};



