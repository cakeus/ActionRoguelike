// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTS_CheckHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTS_CheckHealth::UpdateHealthPercent(UBehaviorTreeComponent& OwnerComp)
{
	auto Controller = OwnerComp.GetAIOwner();
	if (!(ensure(Controller)))
	{
		return;
	}

	auto SelfActor =Controller->GetPawn();
	if (!ensure(SelfActor))
	{
		return;
	}

	auto AttrComp = SelfActor->GetComponentByClass<USAttributeComponent>();

	if (!ensure(AttrComp))
	{
		return;
	}
	
	auto BB =OwnerComp.GetBlackboardComponent();
	if (!(ensure(BB)))
	{
		return;
	}
	
	float HealthPercent = AttrComp->GetHealthPercent();

	BB->SetValueAsFloat(HealthKey.SelectedKeyName,HealthPercent);
}

void USBTS_CheckHealth::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	UpdateHealthPercent(OwnerComp);;
}

void USBTS_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UpdateHealthPercent(OwnerComp);
}
