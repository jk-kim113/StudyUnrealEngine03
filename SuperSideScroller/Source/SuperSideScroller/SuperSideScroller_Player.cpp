// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "PlayerProjectile.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"

ASuperSideScroller_Player::ASuperSideScroller_Player()
{
	// bIsSprinting 값을 기본적으로 false로 설정
	bIsSprinting = false;

	// MaxWalkSpeed 값을 300.0f으로 설정
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASuperSideScroller_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// 항상 필요하지는 않지만, Super 키워드를 사용해 부모 클래스의 함수를 호출하는 것이 좋다.
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Sprint 입력이 눌렸을 때 Sprint 함수를 호출하도록 바인딩(연결) 하기
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASuperSideScroller_Player::Sprint);
	// Sprint 입력이 해제됐을 때 StopSprint 함수를 호출하도록 바인딩(연결) 하기
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASuperSideScroller_Player::StopSprinting);

	//Bind pressed action ThrowProjectile to your ThrowProjectile function
	PlayerInputComponent->BindAction("ThrowProjectile", IE_Pressed, this, &ASuperSideScroller_Player::ThrowProjectile);
}

void ASuperSideScroller_Player::Sprint()
{
	if (!bIsSprinting)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void ASuperSideScroller_Player::StopSprinting()
{	
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void ASuperSideScroller_Player::ThrowProjectile()
{
	if (ThrowMontage)
	{
		bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if (!bIsMontagePlaying)
		{
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 2.0f);
		}
	}
}

void ASuperSideScroller_Player::SpawnProjectile()
{
	if (PlayerProjectile)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FVector SpawnLocation = this->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
			FRotator Rotation = GetActorForwardVector().Rotation();

			APlayerProjectile* Projectile = World->SpawnActor<APlayerProjectile>(PlayerProjectile, SpawnLocation, Rotation, SpawnParams);
			if (Projectile)
			{
				Projectile->CollisionComp->MoveIgnoreActors.Add(SpawnParams.Owner);
			}
		}
	}
}