// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SAttributeComponent.h"
#include "AI/SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>("PawnSense");
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSense->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
}

void ASAICharacter::OnHealthChanged(AActor* ActorInstigator, class USAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if (ActorInstigator && ActorInstigator != this)
	{
		SetTargetActor(ActorInstigator);
	}

	if (Delta < 0)
	{		
		auto MeshComp = GetMesh();
		if (ensure(MeshComp))
		{
			MeshComp->SetScalarParameterValueOnMaterials(FName("TimeToHit"), GetWorld()->TimeSeconds);	
		}
	}
	
	if (Delta < 0 && NewHealth <= 0)
	{
		auto AIC = Cast<ASAIController>(GetController());
		if (AIC)
		{
			AIC->GetBrainComponent()->StopLogic("Killed");
		}

		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName("Ragdoll");

		FVector AwayFromInstigator = (GetActorLocation() -  ActorInstigator->GetActorLocation()).GetSafeNormal();
		FVector Impulse = ( AwayFromInstigator + FVector::UpVector) * 5000.0f; // Adjust as needed

		// Apply impulse to all bodies (starting from root)
		GetMesh()->AddImpulseToAllBodiesBelow(Impulse, NAME_None, false); 
		
		SetLifeSpan(10.0f);
	}
}

void ASAICharacter::SetTargetActor(AActor* TargetActor)
{
	auto AIC = Cast<ASAIController>(GetController());
	if (AIC)
	{
		auto BBC = AIC->GetBlackboardComponent();
		BBC->SetValueAsObject("TargetActor",TargetActor);
	}

}



