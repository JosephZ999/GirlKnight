// Girl Knight by MoonDi

#include "GK_Character.h"

const GK_Character GK_Character::BaseCharacter = GK_Character("BaseCharacter", FCharacterStats(10.f, 2.f, 0.f));
const GK_Character GK_Character::BaseMonster   = GK_Character("BaseCharacter", FCharacterStats(5.f, 1.f, 3.f));

float GK_Character::GetDamage() const
{
	return Stats.Damage;
}

float GK_Character::GetHealth() const
{
	return Health;
}

float GK_Character::ApplyDamage(float InDamage)
{
	float DamageAmount = InDamage;
	// calc damage amount with armor

	Health -= DamageAmount;
	return DamageAmount;
}
