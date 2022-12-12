// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DodgeballCharacter.h"

// Sets default values
ADodgeballProjectile::ADodgeballProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.0f);
	SphereComponent->SetCollisionProfileName(FName("Dodgeball"));
	SphereComponent->SetSimulatePhysics(true);
	// �ùķ��̼��� Hit �̺�Ʈ�� �߻���Ų��.
	SphereComponent->SetNotifyRigidBodyCollision(true);
	// �߰��� �Լ����� ���ε��� ���� OnComponentHit �̺�Ʈ�� �޵��� �����Ѵ�.
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeballProjectile::OnHit);

	// �� Sphere ������Ʈ�� Root ������Ʈ�� �����Ѵ�.
	// �̷��� �������� ������ �浹(�ݸ���)�� ����� �������� ���� �� �ִ�.
	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1500.f;
}

// Called when the game starts or when spawned
void ADodgeballProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(5.0f);
}

// Called every frame
void ADodgeballProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADodgeballProjectile::OnHit(UPrimitiveComponent * HitComp,
	AActor * OtherActor,
	UPrimitiveComponent * OtherComp,
	FVector NormalImpulse,
	const FHitResult & Hit)
{
	if (Cast<ADodgeballCharacter>(OtherActor) != nullptr)
	{
		Destroy();
	}
}