// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int, NewCredits, int, Delta );


/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=Credits)
	void ApplyCreditsChange(int Delta);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Credits)
	int Credits;
	
	UPROPERTY(BlueprintAssignable, Category=Credits)
	FOnCreditsChanged OnCreditsChanged;
};
