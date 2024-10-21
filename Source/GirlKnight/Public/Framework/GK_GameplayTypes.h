#pragma once

#include "CoreMinimal.h"
#include "GK_GameplayTypes.generated.h"

USTRUCT(BlueprintType)
struct FGK_AttackData
{
	GENERATED_BODY()

	FName AttackerIndex;
	// FName VictimIndex;

	float DamageAmount = 0.f;
	bool  bCrit		   = false;
};

UENUM(BlueprintType)
enum class EPlayerActions : uint8
{
	None,
	// Arrows
	Up,
	Down,
	Left,
	Right,

	Max,
};