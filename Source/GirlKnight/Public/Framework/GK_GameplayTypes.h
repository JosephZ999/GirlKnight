#pragma once

#include "CoreMinimal.h"
#include "GK_GameplayTypes.generated.h"

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