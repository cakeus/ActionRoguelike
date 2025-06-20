// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"
#include "SWorldUserWidget.h"
#include "Actions/SActionComponent.h"
#include "AI/SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>("PawnSense");
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Enabled on mesh to react to incoming projectiles
	USkeletalMeshComponent* SkelMesh = GetMesh();
	SkelMesh->SetGenerateOverlapEvents(true);
	// Skip performing overlap queries on the Physics Asset after animation (17 queries in case of our MinionRangedBP)
	SkelMesh->bUpdateOverlapsOnAnimationFinalize = false;

	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");
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



void ASAICharacter::ConvertToRagdoll(AActor* ActorInstigator)
{
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
}

void ASAICharacter::Die(AActor* ActorInstigator)
{
	auto AIC = Cast<ASAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Killed");
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
		
	ConvertToRagdoll(ActorInstigator);

	if (HealthBarWidget)
	{
		HealthBarWidget->RemoveFromParent();
	}
		
	SetLifeSpan(10.0f);
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

		if (HealthBarWidget == nullptr)
		{
			if (ensure(HealthBarWidgetClass))
			{
				HealthBarWidget = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
				HealthBarWidget->AttachedActor = OwningComp->GetOwner();
				HealthBarWidget->AddToViewport();
			}
		}
	}
	
	if (Delta < 0 && NewHealth <= 0)
	{
		Die(ActorInstigator);
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



