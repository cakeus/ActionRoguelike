// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SActionEffect.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"


class USAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USActionComponent();

	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddAction(TSubclassOf<USAction> ActionClass, AActor* ActionInstigator);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartAction(FName ActionName, AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopAction(FName ActionName, AActor* Instigator);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	void RemoveAction(USAction* ActionToRemove);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actions")
	FGameplayTagContainer ActiveGameplayTags;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<USAction*> Actions;

	USAction* GetActionByName(FName ActionName);

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	TArray<TSubclassOf<USAction>> StartingActions;
public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
};
