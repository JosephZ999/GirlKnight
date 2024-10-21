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

	float Health   = 0.f;
	float Cooldown = 0.f;

public:
	float GetDamage() const;
	float GetHealth() const;
	float ApplyDamage(float InDamage);

public:
	static const GK_Character BaseCharacter;
	static const GK_Character BaseMonster;
};
