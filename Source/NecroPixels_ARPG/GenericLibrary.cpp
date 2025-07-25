// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"

TArray<class APlayerState*> UGenericLibrary::GetPlayerArray(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameState(WorldContextObject)->PlayerArray;
}
