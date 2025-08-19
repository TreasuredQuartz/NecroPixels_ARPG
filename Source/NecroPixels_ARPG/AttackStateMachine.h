// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericGraphEdge.h"
#include "GenericGraphNode.h"
#include "AttackStateMachine.generated.h"

class UGenericGraph;
class UNodeAttackState;

UCLASS(Blueprintable)
class NECROPIXELS_ARPG_API AAttackStateMachine : public AInfo
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAttackStateMachine();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackStateMachine", meta = (ExposeOnSpawn = true))
	AActor* AvatarActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackStateMachine")
	UGenericGraph* AttackStateGraph;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackStateMachine")
	TObjectPtr<UNodeAttackState> CurrentNode;

	// 0 is none or invalid.
	// Use any other number to denote your type of attack ie:
	// - 1 = Heavy Attack
	// - 2 = Light Attack
	// - 3 = Arieal Attack
	// etc.
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "AttackStateMachine")
	uint8 TriggerAttackType;

public:	
	// Should call at start
	UFUNCTION(BlueprintCallable, Category = "AttackStateMachine")
	void InitializeState();

	// Called from C++ at start
	UFUNCTION(BlueprintImplementableEvent, Category = "AttackStateMachine")
	void InitializeState_BP();

	// Should call every frame that is active
	UFUNCTION(BlueprintCallable, Category = "AttackStateMachine")
	void EvaluateStateMachine(float DeltaTime);

	// Called from C++ every frame that is active
	UFUNCTION(BlueprintImplementableEvent, Category = "AttackStateMachine")
	void EvaluateStateMachine_BP(float DeltaTime);

	// Should be called when the owner wants to attack
	UFUNCTION(BlueprintCallable, Category = "AttackStateMachine")
	void SetAttack(uint8 NewAttackType) { TriggerAttackType = NewAttackType; };

	// Should be called when the owner wants to stop attacking
	// You can also use TriggerAttackType with an invalid type: 0
	UFUNCTION(BlueprintCallable, Category = "AttackStateMachine")
	void ResetAttack() { TriggerAttackType = 0; };
};

UCLASS(Blueprintable)
class NECROPIXELS_ARPG_API AAttackInstance : public AActor
{
	GENERATED_BODY()

	/////////////
	// Members //
	/////////////

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	uint8 bShouldSelfHarm : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	uint8 bShouldMultiHitActor : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	uint8 MaxImpactedActors;

	/*
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	float DamageModifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	float KnockbackForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	float HitstopDuration;

	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	TArray<AActor*> ImpactedActors;

	/*
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	class UNiagaraSystem* ImpactParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInstance")
	TSubclassOf<class UCameraShake> ImpactCameraShake;

	*/

	/////////////
	// Methods //
	/////////////

public:
	// Constructor
	AAttackInstance();

	UFUNCTION(BlueprintPure)
	virtual float CalcDamage() const { return CalcDamage_BP(); };

	UFUNCTION(BlueprintImplementableEvent)
	float CalcDamage_BP() const;

	UFUNCTION(BlueprintPure)
	bool ShouldImpactActor(AActor* Actor) const;

	UFUNCTION(BlueprintCallable)
	virtual void ImpactActor(AActor* Victim);

	UFUNCTION(BlueprintImplementableEvent)
	void ImpactActor_BP(AActor* Victim);

	// Why are these functions commented here?

	// They are simply the functions called in the
	// Blueprint prototype of this class.
	// They reference blueprint only components so they
	// cannot be replicated here.

	/*

	void ApplyHitstop() const;

	void ApplyHitFlash() const;

	void ApplyKnockback() const;

	void SpawnImpactParticle() const;

	void ApplyCameraShake() const;

	*/
};

UCLASS()
class NECROPIXELS_ARPG_API UAttackTransition : public UGenericGraphEdge
{
	GENERATED_BODY()

public:
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "AttackTransition")
	uint8 RequiredAttackType;
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "AttackTransition")
	FVector2D TransitionPeriod;
};

UCLASS(ClassGroup = (Common), meta = (BlueprintSpawnableComponent))
class NECROPIXELS_ARPG_API UNodeAttackState : public UGenericGraphNode
{
	GENERATED_BODY()

private:
	float TimeInState;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeAttackState")
	TSubclassOf<AAttackInstance> AttackInstanceClass;

public:
	UFUNCTION(BlueprintCallable, Category = "NodeAttackState")
	void OnEnterState();
	UFUNCTION(BlueprintCallable, Category = "NodeAttackState")
	void OnExitState();
	UFUNCTION(BlueprintCallable, Category = "NodeAttackState")
	void ExecuteState(float DeltaTime);

	void PreExecuteState();
	void PostExecuteState();

	UFUNCTION(BlueprintCallable, Category = "NodeAttackState")
	UNodeAttackState* CheckTransitions(uint8 TransitionAttackType);
};
