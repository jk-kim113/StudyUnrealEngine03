// Fill out your copyright notice in the Description page of Project Settings.


#include "MyThirdPersonChar.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyThirdPersonChar::AMyThirdPersonChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 캡슐 콜리전의 크기를 설정한다.
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// 컨트롤러가 회전할 때 캐릭터는 회전하지 않도록 설정한다.
	// 캐릭터가 카메라에 영향을 주도록 놔둔다.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 캐릭터 무브먼트를 설정한다.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 카메라 붐을 생성한다(충돌이 발생할 경우 플레이어 쪽으로 다가가도록 설정한다).
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// 캐릭터를 따라다닐 카메라를 생성한다.
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AMyThirdPersonChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyThirdPersonChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyThirdPersonChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

