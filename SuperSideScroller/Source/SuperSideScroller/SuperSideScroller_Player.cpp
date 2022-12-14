// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	UE_LOG(LogTemp, Warning, TEXT("THROW PROJECTILE!"));
}