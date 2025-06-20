// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction_ProjectileAttack.h"

#include "SCharacter.h"
#include "SProjectile.h"
#include "Kismet/GameplayStatics.h"

void USAction_ProjectileAttack::Start_Implementation(AActor* Instigator)
{
	Super::Start_Implementation(Instigator);

	auto ActionInstigator = Cast<ASCharacter>(Instigator);
	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Instigator);
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);	
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	
	auto CastFX =ProjectileClass->GetDefaultObject<ASProjectile>()->CastFX;
	if (CastFX)
	{
		UGameplayStatics::SpawnEmitterAttached(CastFX,ActionInstigator->GetMesh(),FName("Muzzle_01"));
	}

	APlayerController* PlayerController = Cast<APlayerController>(ActionInstigator->GetController());
	if (!PlayerController) return;


	
	FVector CameraLocation = ActionInstigator->GetPawnViewLocation();
	FRotator CameraRotation = ActionInstigator->GetControlRotation();
	
	FVector Start = CameraLocation;
	FRotator Rotation = CameraRotation;
	FVector End = Start + Rotation.Vector() *  10000.0f;
	if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectQueryParams, Params))
	{
		TargetLocation = HitResult.Location;
	}
	else
	{
		TargetLocation = End;
	}	
	
	ActionInstigator->PlayAnimMontage(AttackAnim);
	
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &USAction_ProjectileAttack::AttackTimeElapsed, ActionInstigator);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack, Delegate, 0.2f, false);
}

void USAction_ProjectileAttack::AttackTimeElapsed(ASCharacter* ActionInstigator)
{
	auto Character = Cast<ASCharacter>(ActionInstigator);

	FVector HandPos = Character->GetMesh()->GetSocketLocation("Muzzle_01");

	FVector TargetDir = (TargetLocation - HandPos).GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("TargetLocation: %s"), *TargetLocation.ToString());
	FTransform SpawnTM = FTransform(TargetDir.ToOrientationRotator(),HandPos);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Character;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);

	Stop(ActionInstigator);
}
