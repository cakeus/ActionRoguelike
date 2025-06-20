// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SProjectile.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USActionEffect;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere, Category="Projectile")
	FGameplayTag ParryTag;
	
	UPROPERTY(EditAnywhere, Category="Projectile")
	float Damage;

	UPROPERTY(EditAnywhere,Category="Projectile")
	TSubclassOf<USActionEffect> ApplyEffectClass;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
