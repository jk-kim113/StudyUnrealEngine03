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
	// 생성자
	ASuperSideScroller_Player();

protected:
	// 플레이어 입력 컴포넌트를 설정하기 위해 부모 캐릭터 클래스의 함수를 재정의한다.
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// 전력 질주
	void Sprint();

	// 전력 질주 정지
	void StopSprinting();

	//ThrowProjectile
	void ThrowProjectile();

private:
	// 전력 질주 중인지 확인하는 bool 변수. 안전장치.
	bool bIsSprinting;
};
