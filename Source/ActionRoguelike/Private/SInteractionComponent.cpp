// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"
#include "SWorldUserWidget.h"

static TAutoConsoleVariable<bool> CVarDebugDraw(TEXT("su.DebugDraw"), false, TEXT("Enable debug drawing"), ECVF_Cheat);


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
	if (FocusedActor)
	{
		ServerInteract(FocusedActor);
	}
}

void USInteractionComponent::FindBestInteractable()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector Start;
	FRotator Rotation;

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
	{
		return;
	}
	
	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (!PlayerController)
	{
		return;
	}

	TArray<FHitResult> HitResults;
	PlayerController->GetPlayerViewPoint(Start, Rotation);
	FCollisionShape Shape;
	Shape.SetSphere(30);

	FVector End = Start + Rotation.Vector() *  1000.0f;
	GetWorld()->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, ObjectQueryParams, Shape);

	FocusedActor = nullptr;;
	for (FHitResult HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor)
	{
		if (Widget == nullptr && ensure(WidgeClass))
		{
			Widget = CreateWidget<USWorldUserWidget>(GetWorld(), WidgeClass);
		}

		if (Widget != nullptr)
		{
			Widget->AttachedActor = FocusedActor;;
			
			if (!Widget->IsInViewport())
			{
				Widget->AddToViewport();	
			}					
		}
	}
	else
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
			Widget = nullptr;
		}
	}
	
	if (CVarDebugDraw.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 10.0f);
	}
}

void USInteractionComponent::ServerInteract_Implementation(AActor *TargetActor)
{
	if (TargetActor)
	{
		ISGameplayInterface::Execute_Interact(TargetActor, Cast<APawn>(GetOwner()));
	}
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

	auto Owner = Cast<APawn>(GetOwner());
	if (Owner && Owner->IsLocallyControlled())
	{
		FindBestInteractable();
	}
}

