// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SActionComponent.h"

#include "Actions/SAction.h"


// Sets default values for this component's properties
USActionComponent::USActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USActionComponent::AddAction(TSubclassOf<USAction> ActionClass, AActor* ActionInstigator)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	auto ActionInstance = NewObject<USAction>(this,ActionClass);
	if (ensure(ActionClass))
	{
		Actions.Add(ActionInstance);

		if (ActionInstance->bAutoStart)
		{
			if (ensure(ActionInstance->CanStart(ActionInstigator)))
			{
				ActionInstance->Start(ActionInstigator);
			}
			
		}
	}

	
}

bool USActionComponent::StartAction(FName ActionName, AActor* Instigator)
{
	auto Action = GetActionByName(ActionName);
	if (Action && Action->CanStart(Instigator))
	{
		Action->Start(Instigator);
		return true;
	}
	return false;
}

bool USActionComponent::StopAction(FName ActionName, AActor* Instigator)
{
	auto Action = GetActionByName(ActionName);
	if (Action && Action->IsRunning())
	{
		Action->Stop(Instigator);
		return true;
	}
	return false;
}

void USActionComponent::RemoveAction(USAction* ActionToRemove)
{
	if (ensure(ActionToRemove) && ensure(!ActionToRemove->IsRunning()))
	{
		Actions.Remove(ActionToRemove);
	}
}


// Called when the game starts
void USActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (auto Action : StartingActions)
	{
		AddAction(Action, GetOwner());
	}
}


USAction* USActionComponent::GetActionByName(FName ActionName)
{
	for (USAction* Action : Actions)
	{
		if (Action->ActionName == ActionName)
		{
			return Action;
		}
	}
	
	return nullptr;
}


// Called every frame
void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = FString::Printf(TEXT("%s : %s"), *GetNameSafe(GetOwner()), *ActiveGameplayTags.ToStringSimple());
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::White, DebugMsg);
	// ...
}

