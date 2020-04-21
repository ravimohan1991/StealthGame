// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	/** 
	* Function called by server on all clients 
	*
	* @param InstigatorPawn The pawn responsible for completing the mission
	* @param bSuccess If the mission is completed successfully
	*/
	UFUNCTION(NetMulticast, Reliable)
	void MulticastMissionComplete(APawn* InstigatorPawn, bool bSuccess);
	
};
