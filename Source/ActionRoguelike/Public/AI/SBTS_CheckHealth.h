// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTS_CheckHealth.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USBTS_CheckHealth : public UBTService
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector HealthKey;

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void UpdateHealthPercent(UBehaviorTreeComponent& OwnerComp);
};
