// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class ASAICharacter;
class UEnvQuery;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASGameModeBase();
	
	virtual void StartPlay() override;

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	virtual void OnActorKilled(AActor *Actor, AActor *Killer);
	void TryToAwardCredits(AActor* KilledActor, AActor* Killer);

protected:
	UFUNCTION()
	void SpawnEnemy();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCurveFloat> DifficultyCurve;
	
	UPROPERTY(EditDefaultsOnly,Category="AI")
	TSubclassOf<ASAICharacter> EnemyPawn;

	UPROPERTY(EditDefaultsOnly,Category="AI")
	TObjectPtr<UEnvQuery> EnvQuery;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTime;

	UFUNCTION(Exec)
	void KillAllAI();

	UFUNCTION()
	void RespawnPlayer(APlayerController *Controller);
};
