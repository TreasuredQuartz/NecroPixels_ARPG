// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectInstance.generated.h"

class UEffectInstance_UIComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class NECROPIXELS_ARPG_API UEffectInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<UEffectInstance_UIComponent*> Components;
};
