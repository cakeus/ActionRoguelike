// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SPlayerState.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable spawning bots"), ECVF_Cheat);

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


void ASGameModeBase::OnActorKilled(AActor* Actor, AActor* Killer)
{
	auto Player = Cast<ASCharacter>(Actor);
	if (Player)
	{
		FTimerDelegate Delegate;
		Delegate.BindUObject(this,&ASGameModeBase::RespawnPlayer, Cast<APlayerController>(Player->GetController()));
		
		FTimerHandle TimerHandle_Unused;
		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_Unused, Delegate, RespawnDelay,false);

		UE_LOG(LogTemp, Display, TEXT("Player %s Killed, scheduling respawn..."), *GetNameSafe(Actor));
	}

	TryToAwardCredits(Actor,Killer);
}

void ASGameModeBase::TryToAwardCredits(AActor* KilledActor, AActor* Killer)
{
	if (auto Bot = Cast<ASAICharacter>(KilledActor))
	{
		if (Bot->CreditsAwarded <= 0)
		{
			return;
		}
	
		if (auto KillerPawn = Cast<APawn>(Killer))
		{
			if (auto KillerPlayerState = KillerPawn->GetPlayerState<ASPlayerState>())
			{
				KillerPlayerState->ApplyCreditsChange(Bot->CreditsAwarded);
			}
		}
	}
}

void ASGameModeBase::RespawnPlayer(APlayerController* Controller)
{
	UE_LOG(LogTemp, Display, TEXT("Player respawned"));
	Controller->UnPossess();
	RestartPlayer(Controller);
}


void ASGameModeBase::SpawnEnemy()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		return;
	}
	
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

void ASGameModeBase::KillAllAI()
{
	for (TActorIterator<ASAICharacter> it(GetWorld());it;++it)
	{
		auto Bot = *it;
		auto AttrComp = Bot->GetComponentByClass<USAttributeComponent>();
		if (AttrComp && AttrComp->IsAlive())
		{
			AttrComp->Kill(Bot);
		}
	}
}