// Fill out your copyright notice in the Description page of Project Settings.


#include "MyThirdPersonChar.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyThirdPersonChar::AMyThirdPersonChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ĸ�� �ݸ����� ũ�⸦ �����Ѵ�.
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// ��Ʈ�ѷ��� ȸ���� �� ĳ���ʹ� ȸ������ �ʵ��� �����Ѵ�.
	// ĳ���Ͱ� ī�޶� ������ �ֵ��� ���д�.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// ĳ���� �����Ʈ�� �����Ѵ�.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// ī�޶� ���� �����Ѵ�(�浹�� �߻��� ��� �÷��̾� ������ �ٰ������� �����Ѵ�).
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// ĳ���͸� ����ٴ� ī�޶� �����Ѵ�.
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

