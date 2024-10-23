// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "GK_DataTypes.h"

/**
 *
 */
class GIRLKNIGHT_API GK_Character
{
public:
	GK_Character() {}
	GK_Character(FName InIndex, const FCharacterStats& InStats = FCharacterStats())
		: Index(InIndex)
		, Stats(InStats)
	{
		Health = Stats.Health;
	}

private:
	FName			Index;
	FCharacterStats Stats;

	float Health = 0.f;
	float Power	 = 0.f;

public:
	FName GetIndex() const { return Index; }
	float GetDamage() const;
	float GetHealth() const;
	float GetHealthPercent() const;
	float GetPowerPercent() const;


	float ApplyDamage(float InDamage);

	bool IsAttackReady() const;
	void ChargePower(float InPower);
	void SetPower(float InPower);

public:
	static const GK_Character BaseCharacter;
	static const GK_Character BaseMonster;
};
