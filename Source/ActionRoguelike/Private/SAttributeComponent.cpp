// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SCharacter.h"

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

bool USAttributeComponent::ApplyHealthChange( AActor* Instigator, float Delta)
{
	if (Health > 0 || Health < HealthMax)
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

			if (auto Character = Cast<ASCharacter>(GetOwner()))
			{
				Character->Die();
			}
		}
		return true;
	}


	return false;
}
