// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballFunctionLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

bool UDodgeballFunctionLibrary::CanSeeActor(const UWorld* World, FVector Location, const AActor * TargetActor, TArray<const AActor*> IgnoreActors)
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	// 라인 트레이스의 결과를 저장한다.
	FHitResult Hit;

	// 라인 트레이스의 시작 및 끝 위치
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	// 시야 판단을 위해 비교할 트레이스 채널
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	FCollisionQueryParams QueryParams;
	// 지정한 액터들을 무시한다.
	QueryParams.AddIgnoredActors(IgnoreActors);

	// 확인할 대상 액터를 무시할 액터 목록에 추가한다.
	QueryParams.AddIgnoredActor(TargetActor);

	// 라인 트레이스를 실행한다.
	World->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	/*
	// 스윕 트레이스에서 사용되는 모형의 회전
	FQuat Rotation = FQuat::Identity;
	// 스윕 트레이스에서 사용하는 객체의 모형
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.f, 20.f, 20.f));
	GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape);
	*/


	// 게임에서 라인 트레이스를 보여준다.
	DrawDebugLine(World, Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}