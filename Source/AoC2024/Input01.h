// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input01.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct AOC2024_API FInput01 : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Left;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Right;

	FInput01();
	~FInput01();
};