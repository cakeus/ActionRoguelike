// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SItemBase.h"
#include "SHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASItemBase
{
	GENERATED_BODY()
public:
	ASHealthPotion();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Health;

};
