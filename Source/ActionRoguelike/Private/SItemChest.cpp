// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	bReplicates = true;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	bLidOpen = !bLidOpen;
	OnRep_LidOpen();
}

void ASItemChest::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASItemChest, bLidOpen);
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASItemChest::OnRep_LidOpen()
{
	float Pitch = bLidOpen ? 110.0f : 0;
	LidMesh->SetRelativeRotation(FRotator(Pitch,0.0f,0.0f));
}

