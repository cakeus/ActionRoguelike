// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100.0f;
}

bool USAttributeComponent::ApplyHealthChange( AActor* Instigator, float Delta)
{
	if (Health > 0)
	{
		Health += Delta;
		
		UE_LOG(LogTemp, Display, TEXT("%s Health=%f"), *GetOwner()->GetName(), Health);
		
		OnHealthChanged.Broadcast(Instigator, this, Health, Delta);

		if (Health <= 0)
		{
			GetOwner()->Destroy();
		}
		return true;
	}


	return false;
}
