// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class DODGEBALL_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 닷지볼이 플레이어 캐릭터에게 입힐 데미지
	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 34.0f;

	// 닷지볼이 표면에 튕길 때 재생할 사운드
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* BounceSound;

	// 이전 사운드의 사운드 감쇄(sound attenuation)
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundAttenuation* BounceSoundAttenuation;

	// The sound the dodgeball will make when it hits the player
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* DamageSound;

	// 플레이어에 맞았을 때 닷지볼이 생성할 파티클 시스템
	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* HitParticles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const
	{
		return ProjectileMovement;
	}

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

};
