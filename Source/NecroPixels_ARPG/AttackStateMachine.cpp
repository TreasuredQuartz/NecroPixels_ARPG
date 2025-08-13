// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackStateMachine.h"
#include "GenericGraph.h"
#include "GenericGraphNode.h"
#include "Engine/DamageEvents.h"

// Sets default values
AAttackStateMachine::AAttackStateMachine()
{

}

void AAttackStateMachine::InitializeState()
{
	InitializeState_BP();

	if (!AttackStateGraph || AttackStateGraph->RootNodes.IsEmpty()) return;

	CurrentNode = Cast<UNodeAttackState>(AttackStateGraph->RootNodes[0]);
}

// Called every frame
void AAttackStateMachine::EvaluateStateMachine(float DeltaTime)
{
	EvaluateStateMachine_BP(DeltaTime);

	if (!CurrentNode) {
		InitializeState();
		return;
	}

	CurrentNode->ExecuteState(DeltaTime);

	if (UNodeAttackState* NextNode = CurrentNode->CheckTransitions(TriggerAttackType))
	{
		CurrentNode->OnExitState();
		NextNode->OnEnterState();
		CurrentNode = NextNode;
	}
}

void UNodeAttackState::OnEnterState()
{
	TimeInState = 0.0f;
}

void UNodeAttackState::OnExitState()
{
	TimeInState = 0.0f;
}

void UNodeAttackState::ExecuteState(float DeltaTime)
{
	TimeInState += DeltaTime;

	PreExecuteState();

	PostExecuteState();
}

void UNodeAttackState::PreExecuteState()
{
}

void UNodeAttackState::PostExecuteState()
{
}

UNodeAttackState* UNodeAttackState::CheckTransitions(uint8 TransitionAttackType)
{
	TArray<UGenericGraphNode*> EdgeKeys;
	Edges.GetKeys(EdgeKeys);
	for(UGenericGraphNode* EdgeKey : EdgeKeys)
	{
		if (UAttackTransition* CurEdge = Cast<UAttackTransition>(Edges[EdgeKey]))
		{
			// Are we within the transition period?
			const FVector2D Period = CurEdge->TransitionPeriod;
			if (Period.X <= TimeInState && (Period.Y >= Period.X || TimeInState <= Period.Y))
			{
				// Have we been given input on how to continue the combo?
				// The Graph should always have an end edge that transitions
				// Back to the root node.
				if (CurEdge->RequiredAttackType == 0 || CurEdge->RequiredAttackType == TransitionAttackType)
				{
					return Cast<UNodeAttackState>(EdgeKey);
				}
			}
		}
	}

	return nullptr;
}

AAttackInstance::AAttackInstance()
{
	SetCanBeDamaged(false);
}

bool AAttackInstance::ShouldImpactActor(AActor* InActor) const
{
	if (!InActor->CanBeDamaged()) return false;

	if (!bShouldSelfHarm)
	{
		if (GetOwner() == InActor) return false;
	}

	if (!bShouldMultiHitActor)
	{
		if (ImpactedActors.Contains(InActor)) return false;
	}

	if (ImpactedActors.Num() >= MaxImpactedActors)
	{
		return false;
	}

	return true;
}

void AAttackInstance::ImpactActor(AActor* Victim)
{
	ImpactActor_BP(Victim);

	const float DamageAmount = CalcDamage();
	const FDamageEvent DamageEvent = FDamageEvent(DamageTypeClass);
	Victim->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), GetOwner());

	ImpactedActors.Add(Victim);

	// This is simply the way things are called in the prototype blueprint.
	//
	// They would not work here, as the components are blueprint only.

	/*
	
	if (HitstopDuration > 0.0f)
	{
		ApplyHitstop(GetOwner());
		ApplyHitstop(Victim);
		ApplyHitFlash(Victim);
	}

	if (KnockbackForce)
	{
		ApplyKnockback(Victim);
	}

	SpawnImpactParticle(Victim);
	ApplyCameraShake();

	*/
}
