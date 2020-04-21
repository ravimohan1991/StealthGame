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
	* @param bSuccess If the mission is completed successfully
	* @see AFPSExtractionZone::OnOverlap
	*/
	void MissionCompleted(APawn* InstigatorPawn, bool bSuccess);

private:
	/** The class of viewport actor.  Used at the end of mission */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<AActor> ViewportActor;
};



