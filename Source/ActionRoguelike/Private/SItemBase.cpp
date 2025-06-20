// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemBase.h"

#include "SPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

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

void ASItemBase::InteractSuccessful()
{
	if (InteractSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());
	}

	if (Cooldown > 0)
	{
		MeshComp->SetVisibility(false);
		bEnabled = false;
		FTimerHandle TimerHandle_Unused;
		GetWorldTimerManager().SetTimer(TimerHandle_Unused, this,&ASItemBase::Respawn, Cooldown);	
	}
	else
	{
		Destroy();
	}
	
}

void ASItemBase::Respawn()
{
	UE_LOG(LogTemp, Display, TEXT("%s Respawn!"), *GetNameSafe(this));
	bEnabled = true;
	MeshComp->SetVisibility(true);
}

bool ASItemBase::CanInteract(APawn *Interactor) const
{
	if (!bEnabled)
	{
		return false;
	}

	if (Cost > 0)
	{
		if (auto PlayerState = Cast<ASPlayerState>(Interactor->GetPlayerState()))
		{
			if (PlayerState->Credits < Cost)
			{
				return false;
			}
		}
	}

	return true;
}

// Called every frame
void ASItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

