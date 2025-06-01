// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Timer = 0;
	State = MS_Traveling;

}

void ASDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (State)
	{
	case MS_Traveling:
		Timer += DeltaTime;
		if (Timer > 0.2f)
		{
			State = MS_Stopped;
			Timer = 0;
			MovementComp->Velocity = FVector::ZeroVector;
		}
		break;
	case MS_Stopped:
		Timer += DeltaTime;
		if (Timer > 0.2f)
		{
			State = MS_Complete;
			GetInstigator()->TeleportTo(GetActorLocation(), GetActorRotation());
			Destroy();			
		}
		break;
	case MS_Complete:
		break;
	default:
		break;	
	}
}
