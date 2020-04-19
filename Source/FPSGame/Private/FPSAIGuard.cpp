// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "FPSGameMode.h"
#include "Engine/World.h"
#include "AIController.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeeingPawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHearingNoise);

	if (bPatrol)
	{
		GuardController = Cast<AAIController>(GetController());

		if (GuardController)
		{
			GuardController->MoveToActor(PatrolPoint1);
			CurrentPatrolPoint = PatrolPoint1;
		}
	}

	OriginalRotation = GetActorRotation();

}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPatrolPoint == nullptr)
	{
		return;
	}

	if ((CurrentPatrolPoint->GetActorLocation() - GetActorLocation()).Size() < 100)
	{
		NextPatrolPoint();
		if (GuardController)
		{
			GuardController->MoveToActor(CurrentPatrolPoint);
		}
	}
}

void AFPSAIGuard::OnSeeingPawn(APawn* SeenPawn)
{
	if (SeenPawn == nullptr || GetWorld() == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 50.0f, 12, FColor::Red, false, 10.0f);
	
	if (GuardController)
	{
		GuardController->StopMovement();
	}

	AFPSGameMode* GM = GetWorld()->GetAuthGameMode<AFPSGameMode>();
	if (GM)
	{
		GM->MissionCompleted(SeenPawn, false);
	}
}

void AFPSAIGuard::OnHearingNoise(APawn* InstigatorPawn, const FVector& Location, float Volume)
{
	if (GetWorld() == nullptr)
	{
		return;
	}
	
	DrawDebugSphere(GetWorld(), Location, 50.0f, 12, FColor::Blue, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = Direction.Rotation();//FRotationMatrix::MakefromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	if (GuardController)
	{
		GuardController->StopMovement();
	}

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetRotation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetRotation, this, &AFPSAIGuard::ResetRotation, 3.0f, false);
}

void AFPSAIGuard::ResetRotation()
{
	SetActorRotation(OriginalRotation);

	if (GuardController)
	{
		GuardController->MoveToActor(CurrentPatrolPoint);
	}
}

void AFPSAIGuard::NextPatrolPoint()
{
	if (CurrentPatrolPoint != PatrolPoint1)
	{
		CurrentPatrolPoint = PatrolPoint1;
	}
	else
	{
		CurrentPatrolPoint = PatrolPoint2;
	}
}

