// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SActionEffect.h"

#include "Actions/SActionComponent.h"

USActionEffect::USActionEffect() 
{
	bAutoStart = true;
	Duration = 0;
	Period = 0;
}

void USActionEffect::Start_Implementation(AActor* Instigator)
{
	
	Super::Start_Implementation(Instigator);

	if (Duration > 0)
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this, &USActionEffect::Stop, Instigator);
		GetWorld()->GetTimerManager().SetTimer(DurationHandle, TimerDelegate, Duration, false);
	}

	if (Period > 0)
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this, &USActionEffect::ExecutePeriodicEffect, Instigator);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, TimerDelegate, Period, true);		
	}
}

void USActionEffect::Stop_Implementation(AActor* Instigator)
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) <= KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(Instigator);
	}
	
	Super::Stop_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);

	GetOwnerComponent()->RemoveAction(this);
	
}

void USActionEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
}

