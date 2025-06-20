// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SItemBase.h"
#include "SCoinPickup.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoinPickup : public ASItemBase
{
	GENERATED_BODY()
public:
	ASCoinPickup();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Value;

};
