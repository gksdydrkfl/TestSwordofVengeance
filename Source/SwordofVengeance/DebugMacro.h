#pragma once

#include "CoreMinimal.h"

class SWORDOFVENGEANCE_API Debug
{
public:
	static void Log(int32 InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
	}
	static void Log(float InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
	}
	static void Log(double InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
	}
	static void Log(const FString& InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
		UE_LOG(LogTemp, Log, TEXT("%s"), *InValue);
	}
	static void Log(const FVector& InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
	}
	static void Log(const FRotator& InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
	}
	static void Log(const UObject* InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		FString str;

		if (!InValue) return;

		if (!!InValue)
			str.Append(InValue->GetName());

		str.Append(!!InValue ? " Not Null" : "Null");

		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, str);
	}
	static void Print(const FString& InFileName, const FString& InFuncName, int32 InLineNumber)
	{
		int32 index = 0, length = 0;
		InFileName.FindLastChar(L'\\', index);

		length = InFileName.Len() - 1;
		FString fileName = InFileName.Right(length - index);


		FString str;
		str.Append(fileName);
		str.Append(", ");
		str.Append(InFuncName);
		str.Append(", ");
		str.Append(FString::FromInt(InLineNumber));

		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, str);
	}
};
