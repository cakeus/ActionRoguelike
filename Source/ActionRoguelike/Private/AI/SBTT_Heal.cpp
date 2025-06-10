// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTT_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTT_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto AIController = OwnerComp.GetAIOwner();
	
	auto Owner = Cast<ACharacter>(AIController->GetPawn());
	if (!Owner)
	{
		return EBTNodeResult::Failed;
	}

	if (!USAttributeComponent::IsActorAlive(Owner))
	{
		return EBTNodeResult::Failed;
	}

	auto AttrComp = Owner->GetComponentByClass<USAttributeComponent>();
	if (!AttrComp)
	{
		return EBTNodeResult::Failed;
	}

	AttrComp->ApplyHealthChange(Owner, AttrComp->GetHealthMax());
	return EBTNodeResult::Succeeded;
}
