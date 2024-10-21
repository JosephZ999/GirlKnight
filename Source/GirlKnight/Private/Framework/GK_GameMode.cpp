// Girl Knight by MoonDi

#include "GK_GameMode.h"
#include "Core/GK_Game.h"
#include "Core/GK_Character.h"

void AGK_GameMode::StartPlay()
{
	Super::StartPlay();

	GameObject = MakeShared<GK_Game>();
	if (GameObject)
	{
		FVector::OneVector;
		GameObject->SetPlayerCharacter(GK_Character::BaseCharacter);
		GameObject->SetEnemyWave({GK_Character::BaseMonster, GK_Character::BaseMonster});
		GameObject->FinishInit();
	}
}
