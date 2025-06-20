// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemBase.generated.h"

UCLASS(Abstract)
class ACTIONROGUELIKE_API ASItemBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASItemBase();

	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> MeshComp;


	UPROPERTY(EditDefaultsOnly=Item)
	TObjectPtr<USoundCue> InteractSound;
	
	UPROPERTY(EditDefaultsOnly, Category=Item)	
	int Cost;

	UPROPERTY(EditDefaultsOnly, Category=Item)	
	float Cooldown;

	virtual void InteractSuccessful();

	UFUNCTION()
	void Respawn();

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Item)
	bool bEnabled = true;

	UFUNCTION(BlueprintCallable, Category=Item)
	bool CanInteract(APawn* Interactor) const;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
