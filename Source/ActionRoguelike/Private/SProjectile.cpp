#include "SProjectile.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"


// Sets default values
ASProjectile::ASProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectile::OnOverlap);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);
	
		
}

// Called when the game starts or when spawned
void ASProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	//AudioComp->Play();
}

void ASProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Hit %s"), *OtherActor->GetName());
	
}

void ASProjectile::Impact()
{
	if (ImpactFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFX, GetActorLocation(), GetActorRotation());
	}

	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
	}
}


// Called every frame
void ASProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

