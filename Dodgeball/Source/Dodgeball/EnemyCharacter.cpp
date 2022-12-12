// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� �÷��̾ �����ϴ� ĳ���� ���ϱ�
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// �� ������ �÷��̾� ĳ���͸� �ٶ󺻴�.
	LookAtActor(PlayerCharacter);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::LookAtActor(AActor * TargetActor)
{
	if (TargetActor == nullptr)
	{
		return;
	}

	if (CanSeeActor(TargetActor))
	{
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		// ���� �������� �� ������ �ٶ󺸴� �� �ʿ��� ȸ�� ����ϱ�
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		// ���� ȸ���� �ռ� ���� ȸ�� ������ �����Ѵ�.
		SetActorRotation(LookAtRotation);
	}
}

bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor) const
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	// ���� Ʈ���̽��� ����� �����Ѵ�.
	FHitResult Hit;

	// ���� Ʈ���̽��� ���۰� �� ��ġ
	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();

	// �þ� �Ǵ��� ���� ���� Ʈ���̽� ä��
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	FCollisionQueryParams QueryParams;

	// �� ���� Ʈ���̽��� �����ϴ� ���͸� �����Ѵ�.
	QueryParams.AddIgnoredActor(this);

	// Ȯ���� ��� ���͸� ������ ���� ��Ͽ� �߰��Ѵ�.
	QueryParams.AddIgnoredActor(TargetActor);

	// ���� Ʈ���̽� �����ϱ�
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	/*
	// ���� Ʈ���̽����� ���Ǵ� ������ ȸ��
	FQuat Rotation = FQuat::Identity;
	// ���� Ʈ���̽����� ����ϴ� ��ü�� ����
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.f, 20.f, 20.f));
	GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape);
	*/
	

	// ���ӿ��� ���� Ʈ���̽� �����ֱ� (�ð�ȭ)
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}