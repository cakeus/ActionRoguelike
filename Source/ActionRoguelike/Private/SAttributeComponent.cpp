// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SCharacter.h"
#include "SGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Multiply all damage"), ECVF_Cheat);


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100.0f;
	HealthMax = 100.0f;
	bWantsInitializeComponent = true;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	if (Actor == nullptr)
	{
		return false;
	}

	auto AttrComp = Actor->FindComponentByClass<USAttributeComponent>();
	if (AttrComp == nullptr)
	{
		return false;
	}

	return AttrComp->IsAlive();
}


bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

void USAttributeComponent::InitializeComponent()
{
	Super::InitializeComponent();
	Health = HealthMax;
	UE_LOG(LogTemp, Warning, TEXT("USAttributeComponent::InitializeComponent Actor=%s HealthMax=%f"), *GetOwner()->GetName(), HealthMax);
}

float USAttributeComponent::GetHealthPercent() const
{
	return Health / HealthMax;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

void USAttributeComponent::Kill(AActor* Instigator)
{
	ApplyHealthChange(Instigator, -GetHealthMax());
}

bool USAttributeComponent::ApplyHealthChange( AActor* Instigator, float Delta)
{
	if (Delta < 0 && !GetOwner()->CanBeDamaged())
	{
		return false;
	}

	if (Delta < 0)
	{
		Delta *= CVarDamageMultiplier.GetValueOnGameThread();
	}
	
	if (Health > 0)
	{
		Health = FMath::Clamp(Health+ Delta,0,HealthMax);
		
		UE_LOG(LogTemp, Display, TEXT("%s Health=%f"), *GetOwner()->GetName(), Health);
		if (Delta != 0)
		{
			OnHealthChanged.Broadcast(Instigator, this, Health, Delta);
		}
		
		if (Health <= 0)
		{
			if (GetOwner()->GetRootComponent()->IsSimulatingPhysics())
			{
				GetOwner()->Destroy();
			}

			// if (auto Character = Cast<ASCharacter>(GetOwner()))
			// {
			// 	Character->Die();
			// }

			auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
			if (GameMode != nullptr)
			{
				GameMode->OnActorKilled(GetOwner(), Instigator);
			}
			
			return true;
		}
	}


	return false;
}
