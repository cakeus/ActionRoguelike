// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

ASGameModeBase::ASGameModeBase()
{
	SpawnTime = 5.0f;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	FTimerHandle TimerHandle_Unused;
	GetWorldTimerManager().SetTimer(TimerHandle_Unused, this,&ASGameModeBase::SpawnEnemy, SpawnTime, true);
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus == EEnvQueryStatus::Success)
	{
		TArray<FVector> ValidLocations;	
		if (QueryInstance->GetQueryResultsAsLocations(ValidLocations))
		{			
			FVector Loc = ValidLocations[0];
			FActorSpawnParameters SpawnParams;
			GetWorld()->SpawnActor<ASAICharacter>(EnemyPawn, Loc, FRotator::ZeroRotator, SpawnParams);
		}
		
	}
}

void ASGameModeBase::SpawnEnemy()
{
	int NumAlive = 0;
	for (TActorIterator<ASAICharacter> it(GetWorld());it;++it)
	{
		auto Bot = *it;
		auto AttrComp = Bot->GetComponentByClass<USAttributeComponent>();
		if (AttrComp && AttrComp->IsAlive())
		{
			NumAlive++;
		}
	}

	
	float MaxBots = 10;

	if (ensure(DifficultyCurve))
	{
		MaxBots =DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);		
	}

	if (NumAlive >= static_cast<int>(MaxBots))
	{
		return;		
	}
	
	auto QueryInstance = UEnvQueryManager::RunEQSQuery(GetWorld(), EnvQuery, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
}
