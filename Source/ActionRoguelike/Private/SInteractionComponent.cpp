// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector Start;
	FRotator Rotation;
	GetOwner()->GetActorEyesViewPoint(Start,Rotation);

	FVector End = Start + Rotation.Vector() *  1000.0f;
	GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectQueryParams);

	if (AActor* HitActor = HitResult.GetActor())
	{
		if (HitActor->Implements<USGameplayInterface>())
		{
			ISGameplayInterface::Execute_Interact(HitActor, Cast<APawn>(GetOwner()));
		}
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 10.0f);
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

