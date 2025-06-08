// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTS_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USBTS_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector SelfLocationKey;

	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector TargetLocationKey;

	
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector ToTargetDirKey;
	
	
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector AttackRangeKey;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
