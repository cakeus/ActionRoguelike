// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "SAction.generated.h"

class USActionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void Start(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent,  Category = "Actions")
	void Stop(AActor* Instigator);

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FName ActionName;
	
	virtual UWorld* GetWorld() const override;
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool CanStart(AActor* Instigator) const;


	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsRunning() const;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actions")
	bool bAutoStart;
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Actions")
	USActionComponent* GetOwnerComponent() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actions")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actions")
	FGameplayTagContainer BlockedTags;

	
	
	bool bRunning;

};
