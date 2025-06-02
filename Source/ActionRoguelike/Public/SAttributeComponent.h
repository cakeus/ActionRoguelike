// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, Instigator, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USAttributeComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	virtual void InitializeComponent() override;
protected:
	
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	float Health;
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Attributes")
	float HealthMax;

public:
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange( AActor* Instigator, float Delta);
};
