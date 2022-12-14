// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSideScroller_Player.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Player : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()
	
public:
	// ������
	ASuperSideScroller_Player();

protected:
	// �÷��̾� �Է� ������Ʈ�� �����ϱ� ���� �θ� ĳ���� Ŭ������ �Լ��� �������Ѵ�.
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// ���� ����
	void Sprint();

	// ���� ���� ����
	void StopSprinting();

	//ThrowProjectile
	void ThrowProjectile();

private:
	// ���� ���� ������ Ȯ���ϴ� bool ����. ������ġ.
	bool bIsSprinting;
};
