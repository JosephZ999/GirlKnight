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
	TFunction<void()>					 OnWaveOver;

	TFunction<void()> OnPlayerCharacterCreate;
	TFunction<void()> OnEnemyCharacterCreate;

public:
	TSharedPtr<GK_Character> GetPlayerCharacterPtr() const { return PlayerCharacterPtr; }
	TSharedPtr<GK_Character> GetEnemyCharacterPtr() const { return EnemyPtr; }

	int32 GetWaveSize() const;

	bool HasEnemy() const;

	void SetPlayerCharacter(const GK_Character& InPlayerCharacter);
	void SetEnemyWave(const TArray<GK_Character>& InEnemyWave);
	void FinishInit();
	void Clean() {}

	bool PutPlayer();
	bool PutEnemy();

public:
	bool IsEnemy(TWeakPtr<GK_Character> InCharacter);

	void ChargePlayerCharacter(float InValue);
	void ChargeEnemy(float InValue);
	void ResetCharacterPower(TWeakPtr<GK_Character> InCharacter);

private:
	void PlayerTurn();
	void EnemyTurn();

	void Attack(TSharedPtr<GK_Character> InAttacker, TSharedPtr<GK_Character> InVictim);
};
