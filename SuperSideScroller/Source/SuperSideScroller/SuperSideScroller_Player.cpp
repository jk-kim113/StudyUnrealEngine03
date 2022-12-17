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
	// bIsSprinting ���� �⺻������ false�� ����
	bIsSprinting = false;

	// MaxWalkSpeed ���� 300.0f���� ����
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASuperSideScroller_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// �׻� �ʿ������� ������, Super Ű���带 ����� �θ� Ŭ������ �Լ��� ȣ���ϴ� ���� ����.
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Sprint �Է��� ������ �� Sprint �Լ��� ȣ���ϵ��� ���ε�(����) �ϱ�
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASuperSideScroller_Player::Sprint);
	// Sprint �Է��� �������� �� StopSprint �Լ��� ȣ���ϵ��� ���ε�(����) �ϱ�
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