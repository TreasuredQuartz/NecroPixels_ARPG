// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NECROPIXELS_ARPG_API UGenericLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static TArray<class APlayerState*> GetPlayerArray(const UObject* WorldContextObject);
};
