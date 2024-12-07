// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Input01.h"
#include "AoC202401.generated.h"

/**
 * 
 */
UCLASS()
class AOC2024_API UAoC202401 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "AOC2024-01")
	static void StartFirstChallenge(UObject* Outer);

	UFUNCTION(BlueprintCallable, Category = "AOC2024-01")
	static void StartSecondChallenge(UObject* Outer);
	
};
