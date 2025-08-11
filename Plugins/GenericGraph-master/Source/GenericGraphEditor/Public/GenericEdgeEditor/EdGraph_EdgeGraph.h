// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EdGraph_EdgeGraph.generated.h"

/**
 * 
 */
UCLASS()
class GENERICGRAPHEDITOR_API UEdGraph_EdgeGraph : public UEdGraph
{
	GENERATED_BODY()
	
public:
	UEdGraph_EdgeGraph();
	virtual ~UEdGraph_EdgeGraph();

	virtual void RebuildEdgeGraph();

	class UGenericGraphEdge* GetGenericGraphEdge() const;

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;
	virtual void PostEditUndo() override;

};
