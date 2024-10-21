// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GK_GameMode.generated.h"

class GK_Game;

/**
 *
 */
UCLASS()
class GIRLKNIGHT_API AGK_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGK_GameMode() {}

private:
	TSharedPtr<GK_Game> GameObject;

public:
	virtual void StartPlay() override;
};
