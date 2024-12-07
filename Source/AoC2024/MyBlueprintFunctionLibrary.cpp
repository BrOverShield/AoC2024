// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

TArray<FString> UMyBlueprintFunctionLibrary::GetCSVFile(FString Path)
{
	TArray<FString> Lines;
	FString CsvFile = FPaths::ProjectContentDir() + Path;
	if (FPaths::FileExists(CsvFile))
	{
		UE_LOG(LogTemp, Log, TEXT("File %s exists"), *CsvFile);
		FFileHelper::LoadANSITextFileToStrings(*CsvFile, NULL, Lines);
	}

	return Lines;
}

UDataTable* UMyBlueprintFunctionLibrary::GetDayData(int32 DayNumber, UObject* Outer)
{
	if (DayNumber >= 1 && DayNumber <= 25)
	{
		FString PaddedDayNumber = PaddedNumber(DayNumber, 2);
		UClass* DataTableClass = UDataTable::StaticClass(); // get a reference to the type of object we are going to use, in this case the basic DataTable, but you can have your own
		UDataTable* InputDataTable = NewObject<UDataTable>(Outer, DataTableClass, FName(TEXT("Input01DataTable"))); // create a new data table object
		UScriptStruct* Base = GetTableRowBase(DayNumber);
		if (Base != nullptr)
		{
			InputDataTable->RowStruct = Base; // set what kind of row structure we are going to use for our table, we assume that you included the example row structure here
			TArray<FString> CSVLines = GetCSVFile("/CSVData/input" + PaddedDayNumber + ".csv"); // assuming you follow our example, load the csv as an array of strings
			FInput01 Row; // set the type of row we are going to use
			// iterate the csv lines and populate the row with the values from the csv
			for (int i = 1; i < CSVLines.Num(); i++)
			{
				FString aString = CSVLines[i];
				TArray<FString> stringArray = {};
				aString.ParseIntoArray(stringArray, TEXT(","), false);
				if (stringArray.Num() == 0) { continue; }
				FString LineLabel = stringArray[0];
				if ((LineLabel.Len() == 0) || LineLabel.StartsWith("\";") || LineLabel.StartsWith(";"))
				{
					continue;	// Skip comments or lines with no label
				}
				Row.Left = FCString::Atoi(*stringArray[1]);
				Row.Right = FCString::Atoi(*stringArray[2]);

				// add the row to the table
				InputDataTable->AddRow(FName(*stringArray[0]), Row);
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Day %i does not have any data table row structure added."), DayNumber);
		}
		return InputDataTable;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Day %i is out of range of accepted numbers."), DayNumber);
		return nullptr;
	}
}

FString UMyBlueprintFunctionLibrary::PaddedNumber(int32 Number, int32 Length)
{
	FString StringNumber = FString::FromInt(Number);
	int32 NumberLength = StringNumber.Len();
	FString PaddedNumber = "";
	for (int32 i = 0; i < Length - NumberLength; i++)
	{
		PaddedNumber += "0";
	}
	return PaddedNumber += StringNumber;
}

UScriptStruct* UMyBlueprintFunctionLibrary::GetTableRowBase(int32 DayNumber)
{
	UScriptStruct* Base;
	switch (DayNumber)
	{
	case 1:
		Base = FInput01::StaticStruct();
		break;
	default:
		Base = nullptr;
	}
	return Base;
}