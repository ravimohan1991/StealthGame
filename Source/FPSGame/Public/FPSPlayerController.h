// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/**
	* Called on the completion of the mission.
	*
	* @param InstigatorPawn The pawn responsible for completing the mission
	* @param bSuccess If the mission is completed successfully
	* @see AFPSGameState::MulticastMissionComplete_Implementation
	* @see Blueprint'/Game/Blueprints/BP_PlayerController.BP_PlayerController'
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnMissionComplete(APawn* InstigatorPawn, bool bSuccess);
};
