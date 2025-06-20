// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"

class USWorldUserWidget;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASAIController : public AAIController
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

};
