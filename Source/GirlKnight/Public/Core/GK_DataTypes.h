#pragma once

#include "CoreMinimal.h"

struct FCharacterStats
{
	FCharacterStats() {}
	FCharacterStats(float InHealth, float InDamage, float InCooldown)
		: Health(InHealth)
		, Damage(InDamage)
		, Cooldown(InCooldown)
	{}

	float Health   = 1.f;
	float Damage   = 1.f;
	float Cooldown = 0.f;

	// add create rate, crit damage
};

struct FEventAttack
{
	TWeakPtr<class GK_Character> Attacker;
	TWeakPtr<class GK_Character> Victim;

	float DamageAmount = 0.f;
	bool  Crited	   = false;
	bool  Killed	   = false;
};