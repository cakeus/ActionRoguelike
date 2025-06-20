// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinPickup.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASCoinPickup::ASCoinPickup()
{
	Value = 10;
}

void ASCoinPickup::Interact_Implementation(APawn* InstigatorPawn)
{	
	Super::Interact_Implementation(InstigatorPawn);
	
	if (!CanInteract(InstigatorPawn))
	{
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Health Potion interact!"));

	if (auto PlayerState = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PlayerState->ApplyCreditsChange(Value);

		InteractSuccessful();
	}
}

