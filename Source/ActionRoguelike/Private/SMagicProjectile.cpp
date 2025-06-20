// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "Actions/SActionComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	Damage = 30;	
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ASMagicProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	Super::OnOverlap(OverlappedComponent, OtherActor,OtherComp,OtherBodyIndex,bFromSweep,SweepResult);
	
	if (OtherActor && OtherActor != GetInstigator() && !OtherActor->IsA(ASProjectile::StaticClass()))
	{

		auto OtherActionComp = OtherActor->GetComponentByClass<USActionComponent>();
		if (OtherActionComp && OtherActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MovementComp->Velocity = -MovementComp->Velocity;
			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		if (OtherActionComp && ApplyEffectClass)
		{
			OtherActionComp->AddAction(ApplyEffectClass, GetInstigator());
		}
		
		USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, SweepResult);
		
		Impact();
		
		Destroy();
	}
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

