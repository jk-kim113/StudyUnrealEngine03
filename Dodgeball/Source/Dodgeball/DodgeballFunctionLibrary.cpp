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

	// ���� Ʈ���̽��� ����� �����Ѵ�.
	FHitResult Hit;

	// ���� Ʈ���̽��� ���� �� �� ��ġ
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	// �þ� �Ǵ��� ���� ���� Ʈ���̽� ä��
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	FCollisionQueryParams QueryParams;
	// ������ ���͵��� �����Ѵ�.
	QueryParams.AddIgnoredActors(IgnoreActors);

	// Ȯ���� ��� ���͸� ������ ���� ��Ͽ� �߰��Ѵ�.
	QueryParams.AddIgnoredActor(TargetActor);

	// ���� Ʈ���̽��� �����Ѵ�.
	World->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	/*
	// ���� Ʈ���̽����� ���Ǵ� ������ ȸ��
	FQuat Rotation = FQuat::Identity;
	// ���� Ʈ���̽����� ����ϴ� ��ü�� ����
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.f, 20.f, 20.f));
	GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape);
	*/


	// ���ӿ��� ���� Ʈ���̽��� �����ش�.
	DrawDebugLine(World, Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}