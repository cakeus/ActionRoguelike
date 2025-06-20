// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USActionEffect : public USAction
{
	GENERATED_BODY()

	USActionEffect();
	
public:
	virtual void Start_Implementation(AActor* Instigator) override;
	virtual void Stop_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effect)
	float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effect)
	float Period;

	FTimerHandle DurationHandle;
	FTimerHandle PeriodHandle;

	UFUNCTION(BlueprintNativeEvent,  Category = "Actions")
	void ExecutePeriodicEffect(AActor* Instigator);
	
};
