// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"


class USWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USInteractionComponent();

	void PrimaryInteract();

	void FindBestInteractable();

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor *TargetActor);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AActor> FocusedActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USWorldUserWidget> WidgeClass;

	UPROPERTY()
	TObjectPtr<USWorldUserWidget> Widget;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
