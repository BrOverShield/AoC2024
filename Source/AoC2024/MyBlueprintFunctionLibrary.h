// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Input01.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AOC2024_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static TArray<FString> GetCSVFile(FString Path);
	static UDataTable* GetDayData(int32 DayNumber, UObject* Outer);
	static FString PaddedNumber(int32 Number, int32 Length);
	static UScriptStruct* GetTableRowBase(int32 DayNumber);
	
	template <typename T>
	static T* GetTableRow(UDataTable* Table, int32 RowNumber);

	
};

template <typename T>
T* UMyBlueprintFunctionLibrary::GetTableRow(UDataTable* Table, int32 RowNumber)
{
	FString DesiredRowName = FString::FromInt(RowNumber); // row name that we are looking for
	T* Result = Table->FindRow<T>(*DesiredRowName, *DesiredRowName, true);
	return Result;
}