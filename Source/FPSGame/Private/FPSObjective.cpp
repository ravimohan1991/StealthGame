// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjective.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjective::AFPSObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);// Disable collision for static mesh
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);// Enable collision only for linetrace and overlap events
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);// Changes all ResponseToChannels container for this PrimitiveComponent
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSObjective::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSObjective::OnOverlapWithActor);
}

void AFPSObjective::PlayPickupEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupEffect, GetActorLocation());
}

// Called every frame
void AFPSObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSObjective::OnOverlapWithActor(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter)
	{
		PlayPickupEffects();
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}
}

