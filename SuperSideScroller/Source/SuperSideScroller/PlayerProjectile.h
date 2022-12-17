// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.generated.h"

UCLASS()
class SUPERSIDESCROLLER_API APlayerProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// 구체 콜리전 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	void ExplodeProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* DestroyEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* DestroySound;

private:

	// 프로젝타일 무브먼트 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	// 스태틱 메시 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Sound)
	class UAudioComponent* ProjectileMovementSound;

	UPROPERTY(VisibleDefaultsOnly, Category = Particle)
	class UParticleSystemComponent* ProjectileEffect;
};
