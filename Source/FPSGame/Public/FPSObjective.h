// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjective.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Effects to be played when picked up by Pawn */
	UFUNCTION()
	void PlayPickupEffects();

private:
	/** Static mesh for the actor */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	/** For overlap detection */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	/** Pickup effects */
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* PickupEffect;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Function called when an actor overlaps this actor */
	UFUNCTION()
	void OnOverlapWithActor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
