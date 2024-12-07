// Fill out your copyright notice in the Description page of Project Settings.


#include "AoC202401.h"

void UAoC202401::StartFirstChallenge(UObject* Outer)
{
	UDataTable* Table = UMyBlueprintFunctionLibrary::GetDayData(1, Outer);
	TArray<int32> Left;
	TArray<int32> Right;
	for (int i = 1; i <= Table->GetRowNames().Num(); i++)
	{
		FInput01* Result = UMyBlueprintFunctionLibrary::GetTableRow<FInput01>(Table, i);
		Left.Add(Result->Left);
		Right.Add(Result->Right);
	}
	Left.Sort();
	Right.Sort();

	int32 Answer = 0;
	for(int i = 0; i < Left.Num(); i++)
	{
		Answer += abs(Left[i] - Right[i]);
	}
	UE_LOG(LogTemp, Log, TEXT("Day 01 Challenge 1: %i"), Answer);
}

void UAoC202401::StartSecondChallenge(UObject* Outer)
{	
	// Get Data
	UDataTable* Table = UMyBlueprintFunctionLibrary::GetDayData(1, Outer);
	TMap<int32, int32> Left;
	TMap<int32, int32> Right;
	//For each line of the table
	for (int i = 1; i <= Table->GetRowNames().Num(); i++)
	{
		FInput01* Result = UMyBlueprintFunctionLibrary::GetTableRow<FInput01>(Table, i);
		//If the left number does not exist in the left dictionary
		if (!Left.Contains(Result->Left))
		{
			//Initialise count at 0
			Left.Add(Result->Left,0);
		}
		//If the right number does not exist in the right dictionary
		if (!Right.Contains(Result->Right))
		{
			//Initialise count at 0
			Right.Add(Result->Right, 0);
		}
		//add 1 to the count of the left number
		Left[Result->Left] = Left[Result->Left] + 1;
		//add 1 to the count of the right number
		Right[Result->Right] = Right[Result->Right] + 1;
	}
	
	// Initialise the answer at 0
	int32 Answer = 0;

	//For each element of one of the dictionary
	for (auto Element : Left)
	{
		// if both dictionaries contain that number
		if (Right.Contains(Element.Key))
		{
			// multiply the amount of times that the left number has been seen in the right column and multiply it again by number of time that the number was seen in the left column. add this amount to the answer.
			Answer = Answer + Element.Key * Element.Value * Right[Element.Key];
		}
	}
	//display answer
	UE_LOG(LogTemp, Log, TEXT("Day 01 Challenge 2: %i"), Answer);
}