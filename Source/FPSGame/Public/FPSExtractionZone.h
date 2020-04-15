// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** The box component */
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* BoxComp;

	/** Sound to be played when pawn overlaps extraction zone without objective */
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ObjectiveMissingSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Function called when an actor overlaps this actor
	*
	* @param OverlappedComp PrimitiveComponent of the ExtractionZone actor
	* @param OtherActor The actor overlapping this actor
	* @param OtherComp The PrimitiveComponent of the overlapping actor
	* @param OtherBodyIndex
	* @param bFromSweep
	* @param SweepResult
	*/
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
