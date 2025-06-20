// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "UObject/Object.h"
#include "SAction_ProjectileAttack.generated.h"

class USActionEffect;
class ASProjectile;
class ASCharacter;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()

public:
	virtual void Start_Implementation(AActor* Instigator) override;
	
protected:		
	void AttackTimeElapsed(ASCharacter* ActionInstigator);
		
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<ASProjectile> ProjectileClass;

	FVector TargetLocation;

	UPROPERTY(EditAnywhere,Category="Attack")
	TObjectPtr<UAnimMontage> AttackAnim;

};
