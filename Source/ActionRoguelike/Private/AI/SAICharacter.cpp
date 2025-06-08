// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "SAttributeComponent.h"
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
	auto AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		auto BBC = AIC->GetBlackboardComponent();
		BBC->SetValueAsObject("TargetActor",Pawn);
	}
}

void ASAICharacter::OnHealthChanged(AActor* ActorInstigator, class USAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
}



