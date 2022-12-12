// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DODGEBALL_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SightSource;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 전달된 액터를 바라보도록 캐릭터의 회전을 변경한다.
	// 전달된 액터를 볼 수 있는지 여부를 반환한다.
	bool LookAtActor(AActor* TargetActor);

	// 전달된 액터를 볼 수 있는지 확인
	bool CanSeeActor(const AActor* TargetActor) const;

	void ThrowDodgeball();

	// 적 캐릭터가 이번 프레임에 플레이어를 볼 수 있는지 여부
	bool bCanSeePlayer = false;
	// 적 캐릭터가 이전 프레임에 플레이어를 볼 수 있었는지 여부
	bool bPreviousCanSeePlayer = false;

	FTimerHandle ThrowTimerHandle;

	float ThrowingInterval = 2.0f;
	float ThrowingDelay = 0.5f;

	// dodgeball 오브젝트를 생성하는 데 사용하는 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball)
	TSubclassOf<class ADodgeballProjectile> DodgeballClass;
};
