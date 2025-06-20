// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction.h"

#include "Actions/SActionComponent.h"

void USAction::Start_Implementation(AActor* Instigator)
{
	UE_LOG( LogTemp, Warning, TEXT("USAction::Start_Implementation"));

	auto ActionComp = GetOwnerComponent();
	ActionComp->ActiveGameplayTags.AppendTags(GrantsTags);

	bRunning = true;
}

void USAction::Stop_Implementation(AActor* Instigator)
{
	UE_LOG( LogTemp, Warning, TEXT("USAction::Stop_Implementation"));

	ensureAlways(bRunning);
	
	auto ActionComp = GetOwnerComponent();
	ActionComp->ActiveGameplayTags.RemoveTags(GrantsTags);
	
	bRunning = false;
}

UWorld* USAction::GetWorld() const
{
	auto ActionComp = Cast<USActionComponent>(GetOuter());
	if (ActionComp)
	{
		return ActionComp->GetWorld();
	}

	return nullptr;
}

bool USAction::CanStart(AActor* Instigator) const
{	
	auto ActionComp = GetOwnerComponent();
	if (bRunning)
	{
		return false;
	}
	
	if (ActionComp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

bool USAction::IsRunning() const
{
	return bRunning;
}

USActionComponent* USAction::GetOwnerComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}
