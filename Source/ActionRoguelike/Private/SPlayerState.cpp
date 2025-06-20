// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

void ASPlayerState::ApplyCreditsChange(int Delta)
{
	if (Credits+Delta < 0)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("PlayerState add credits %d -> %d"), Credits, Credits+Delta);
	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}
