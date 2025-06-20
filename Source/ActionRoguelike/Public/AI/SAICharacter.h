// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USActionComponent;
class USWorldUserWidget;
class USAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int CreditsAwarded;
	
protected:	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<UPawnSensingComponent> PawnSense;

	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<USActionComponent> ActionComp;
	
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
	void ConvertToRagdoll(AActor* ActorInstigator);
	void Die(AActor* ActorInstigator);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USAttributeComponent> AttributeComp;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY()
	TObjectPtr<USWorldUserWidget> HealthBarWidget;
	
	UFUNCTION()
	void OnHealthChanged(AActor* ActorInstigator, class USAttributeComponent* OwningComp, float NewHealth, float Delta);

	void SetTargetActor(AActor* TargetActor);


};
