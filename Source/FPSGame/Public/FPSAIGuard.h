// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** AI component for the sense of hearing and seeing */
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPawnSensingComponent* PawnSensingComp;

	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetRotation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Called when we see a pawn */
	UFUNCTION()
	void OnSeeingPawn(APawn* SeenPawn);

	/** Called when we hear some noise from a Pawn's PawnNoiseEmitterComponent */
	UFUNCTION()
	void OnHearingNoise(APawn* InstigatorPawn, const FVector& Location, float Volume);

	/** Called by timer to reset the rotation of the actor */
	UFUNCTION()
	void ResetRotation();
};
