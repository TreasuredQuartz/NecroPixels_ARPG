// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericEdgeEditor/EdGraph_EdgeGraph.h"

UEdGraph_EdgeGraph::UEdGraph_EdgeGraph()
{
}

UEdGraph_EdgeGraph::~UEdGraph_EdgeGraph()
{
}

void UEdGraph_EdgeGraph::RebuildEdgeGraph()
{
}

UGenericGraphEdge* UEdGraph_EdgeGraph::GetGenericGraphEdge() const
{
	return nullptr;
}

bool UEdGraph_EdgeGraph::Modify(bool bAlwaysMarkDirty)
{
	return false;
}

void UEdGraph_EdgeGraph::PostEditUndo()
{
}
