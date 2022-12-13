// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DodgeballFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API UDodgeballFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	// 전달된 액터를 볼 수 있는지 확인
	static bool CanSeeActor(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoreActors = TArray<const AActor*>());

};
