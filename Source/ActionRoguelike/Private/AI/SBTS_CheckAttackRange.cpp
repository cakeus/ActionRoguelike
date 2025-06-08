// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTS_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTS_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto BB =OwnerComp.GetBlackboardComponent();
	if (!(ensure(BB)))
	{
		return;
	}
	auto TargetActor = Cast<AActor>(BB->GetValueAsObject("TargetActor"));
	if (!TargetActor)
	{
		return;
	}

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

	
	BB->SetValueAsVector(SelfLocationKey.SelectedKeyName, SelfActor->GetActorLocation());
	BB->SetValueAsVector(TargetLocationKey.SelectedKeyName, TargetActor->GetActorLocation());

	FVector ToTargetDir = (TargetActor->GetActorLocation() - SelfActor->GetActorLocation() ).GetSafeNormal();
	BB->SetValueAsVector(ToTargetDirKey.SelectedKeyName, ToTargetDir);
	
	bool bLoS = Controller->LineOfSightTo(TargetActor);
	
	float dist = FVector::Distance(SelfActor->GetActorLocation(), TargetActor->GetActorLocation());

	BB->SetValueAsBool(AttackRangeKey.SelectedKeyName, dist < 2000.0f && bLoS);
}
