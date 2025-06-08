// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto AIController = OwnerComp.GetAIOwner();

	auto Owner = Cast<ACharacter>(AIController->GetPawn());
	if (!Owner)
	{
		return EBTNodeResult::Failed;
	}

	FVector SpawnPos = Owner->GetMesh()->GetSocketLocation("Muzzle_01");
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

	if (!TargetActor)
	{
		return EBTNodeResult::Failed;
	}

	FVector ToTarget = TargetActor->GetActorLocation() - SpawnPos;

	FTransform SpawnTM = FTransform(ToTarget.ToOrientationRotator(),SpawnPos);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Owner;
	auto Proj = GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);
	if (!Proj)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;

}
