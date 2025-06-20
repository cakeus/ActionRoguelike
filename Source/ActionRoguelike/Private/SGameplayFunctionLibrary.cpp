// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

#include "SAttributeComponent.h"

bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageInstigator, AActor* TargetActor, float Damage)
{
	auto AttrComp = TargetActor->GetComponentByClass<USAttributeComponent>();
	if (AttrComp)
	{
		return AttrComp->ApplyHealthChange(DamageInstigator, -Damage);
	}
	return false;
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageInstigator, AActor* TargetActor, float Damage, const FHitResult& Hit)
{
	if (ApplyDamage(DamageInstigator, TargetActor, Damage))
	{		
		auto HitComp = Hit.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(Hit.BoneName))
		{
			FVector Direction = (Hit.TraceEnd - Hit.TraceStart).GetSafeNormal();
			HitComp->AddImpulseAtLocation(Direction * 300000.0f, Hit.ImpactPoint, Hit.BoneName);
		}
		return true;
	}

	return false;
}
