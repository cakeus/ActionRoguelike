// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASHealthPotion::ASHealthPotion()
{
	Health = 50.0f;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{	
	Super::Interact_Implementation(InstigatorPawn);
	
	if (!CanInteract(InstigatorPawn))
	{
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Health Potion interact!"));

	auto AttrComp = InstigatorPawn->GetComponentByClass<USAttributeComponent>();
	if (AttrComp)
	{
		if (AttrComp->ApplyHealthChange(InstigatorPawn,Health))
		{
			InteractSuccessful();
		}
	}
}

