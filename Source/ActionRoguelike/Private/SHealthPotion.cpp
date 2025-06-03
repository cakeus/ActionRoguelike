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
	if (!bEnabled)
	{
		return;
	}
	
	Super::Interact_Implementation(InstigatorPawn);
	
	UE_LOG(LogTemp, Display, TEXT("Health Potion interact!"));

	auto AttrComp = InstigatorPawn->GetComponentByClass<USAttributeComponent>();
	if (AttrComp)
	{
		if (AttrComp->ApplyHealthChange(InstigatorPawn,Health))
		{
			if (InteractSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());
			}

			MeshComp->SetVisibility(false);
			bEnabled = false;

			FTimerHandle TimerHandle_Unused;
			GetWorldTimerManager().SetTimer(TimerHandle_Unused, this,&ASHealthPotion::Respawn, 10.0f);
		}
	}
}

void ASHealthPotion::Respawn()
{
	UE_LOG(LogTemp, Display, TEXT("Health Potion Respawn!"));
	bEnabled = true;
	MeshComp->SetVisibility(true);
}
