// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ASProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectile();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> MovementComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UParticleSystemComponent> EffectComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UAudioComponent> AudioComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundCue> ImpactSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> ImpactFX;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> CastFX;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Impact();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
