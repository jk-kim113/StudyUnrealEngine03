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

	// 현재 플레이어가 제어하는 캐릭터 구하기
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// 매 프레임 플레이어 캐릭터를 바라본다.
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
		// 시작 지점에서 끝 지점을 바라보는 데 필요한 회전 계산하기
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		// 적의 회전을 앞서 구한 회전 값으로 설정한다.
		SetActorRotation(LookAtRotation);
	}
}

bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor) const
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	// 라인 트레이스의 결과를 저장한다.
	FHitResult Hit;

	// 라인 트레이스의 시작과 끝 위치
	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();

	// 시야 판단을 위해 비교할 트레이스 채널
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	FCollisionQueryParams QueryParams;

	// 이 라인 트레이스를 실행하는 액터를 무시한다.
	QueryParams.AddIgnoredActor(this);

	// 확인할 대상 액터를 무시할 액터 목록에 추가한다.
	QueryParams.AddIgnoredActor(TargetActor);

	// 라인 트레이스 실행하기
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	/*
	// 스윕 트레이스에서 사용되는 모형의 회전
	FQuat Rotation = FQuat::Identity;
	// 스윕 트레이스에서 사용하는 객체의 모형
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.f, 20.f, 20.f));
	GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape);
	*/
	

	// 게임에서 라인 트레이스 보여주기 (시각화)
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}