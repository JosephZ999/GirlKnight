// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "GK_DataTypes.h"
#include "GK_Character.h"

class GK_Character;

/**
 *
 */
class GIRLKNIGHT_API GK_Game
{
private:
	TSharedPtr<GK_Character> PlayerCharacterPtr;
	TSharedPtr<GK_Character> EnemyPtr;

	GK_Character		 PlayerCharacter;
	TArray<GK_Character> EnemyWave;

public:
	TFunction<void(const FEventAttack&)> OnAttack;
	TFunction<void()>					 OnPlayerCharacterDead;
	TFunction<void()>					 OnEnemyCharacterDead;

public:
	void SetPlayerCharacter(const GK_Character& InPlayerCharacter);
	void SetEnemyWave(const TArray<GK_Character>& InEnemyWave);
	void FinishInit();
	void Clean() {}

public:
	void PlayerTurn();
	void EnemyTurn();

private:
	void PutEnemy();
	void Attack(TSharedPtr<GK_Character> InAttacker, TSharedPtr<GK_Character> InVictim);
};
