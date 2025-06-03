// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class ASProjectile;
class USAttributeComponent;
class USInteractionComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	// Movement input handling
	void Move(const FInputActionValue& Value);

	// Look input handling
	void Look(const FInputActionValue& Value);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USAttributeComponent> AttributeComp;
	
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<ASProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<ASProjectile> SpecialProjectileClass;

	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<ASProjectile> DashProjectileClass;
	
	UPROPERTY(EditAnywhere,Category="Attack")
	TObjectPtr<UAnimMontage> AttackAnim;
	
	// Input Mapping Context (Enhanced Input System)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	// Jump Action (Enhanced Input System)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	// Interact Action (Enhanced Input System)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;
	
	// Primary attack action (Enhanced Input System)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> PrimaryAttackAction;

	// Secondary attack action (Enhanced Input System)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SecondaryAttackAction;

	// Dash attack action (Enhanced Input System)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction>DashAttackAction;
		
	// Movement action (Enhanced Input System)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	// Look action (Enhanced Input System)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	FVector TargetLocation;
	TSubclassOf<AActor> AttackProjectileClass;
	
	void AttackTimeElapsed();
	
	void PrimaryAttack();
	void SecondaryAttack();
	void DashAttack();

	void StartProjectileAttack(TSubclassOf<ASProjectile> ProjectileClass);
	
	
	void Interact();

	UFUNCTION()
	void OnHealthChanged(AActor* ActorInstigator, class USAttributeComponent* OwningComp, float NewHealth, float Delta);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void Die();
};
