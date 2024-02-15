// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_w_Tags.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"


// Sets default values
ACharacter_w_Tags::ACharacter_w_Tags()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TeamId = FGenericTeamId(10);
}


FGenericTeamId ACharacter_w_Tags::GetGenericTeamId() const
{
	return TeamId;
}

// Called when the game starts or when spawned
void ACharacter_w_Tags::BeginPlay()
{
	Super::BeginPlay();
	
	// Skeletal mesh lod update rates
	GetMesh()->AnimUpdateRateParams->bShouldUseLodMap = true;
	GetMesh()->AnimUpdateRateParams->bShouldUseMinLod = false;
	GetMesh()->AnimUpdateRateParams->BaseNonRenderedUpdateRate = 15;
	GetMesh()->AnimUpdateRateParams->LODToFrameSkipMap.Empty(4);
	GetMesh()->AnimUpdateRateParams->LODToFrameSkipMap.Add(0, 0);
	GetMesh()->AnimUpdateRateParams->LODToFrameSkipMap.Add(1, 0);
	GetMesh()->AnimUpdateRateParams->LODToFrameSkipMap.Add(2, 2);
	GetMesh()->AnimUpdateRateParams->LODToFrameSkipMap.Add(3, 3);
	GetMesh()->AnimUpdateRateParams->MaxEvalRateForInterpolation = 0;
}

// Called every frame
void ACharacter_w_Tags::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacter_w_Tags::Falling()
{
	Super::Falling();
	AAIController* AiController = Cast<AAIController>(GetController());
	if (AiController != nullptr)
	{
		if (UPathFollowingComponent* PathFollowingComp = AiController->GetPathFollowingComponent())
		{
			PathFollowingComp->Deactivate();
		}
	}
}

void ACharacter_w_Tags::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	AAIController* AiController = Cast<AAIController>(GetController());
	if (AiController != nullptr)
	{
		if (UPathFollowingComponent* PathFollowingComp = AiController->GetPathFollowingComponent())
		{
			PathFollowingComp->Activate();
		}
	}
}

void ACharacter_w_Tags::LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	Super::LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
	AAIController* AiController = Cast<AAIController>(GetController());
	if (AiController != nullptr)
	{
		if (UPathFollowingComponent* PathFollowingComp = AiController->GetPathFollowingComponent())
		{
			PathFollowingComp->Deactivate();
		}
	}
}

// Called to bind functionality to input
void ACharacter_w_Tags::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
