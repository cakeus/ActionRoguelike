// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemBase.h"

// Sets default values
ASItemBase::ASItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

