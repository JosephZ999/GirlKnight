// Girl Knight by MoonDi

#include "GK_Character.h"

const GK_Character GK_Character::BaseCharacter = GK_Character("BaseCharacter", FCharacterStats(10.f, 2.f, 3.f));
const GK_Character GK_Character::BaseMonster   = GK_Character("BaseMonster", FCharacterStats(5.f, 5.f, 5.f));

float GK_Character::GetDamage() const
{
	return Stats.Damage;
}

float GK_Character::GetHealth() const
{
	return Health;
}

float GK_Character::GetPowerPercent() const
{
	if (Stats.Cooldown > 0.f)
	{
		return FMath::Clamp(Power / Stats.Cooldown, 0.f, 1.f);
	}
	return 1.f;
}

float GK_Character::ApplyDamage(float InDamage)
{
	float DamageAmount = InDamage;
	// calc damage amount with armor

	Health -= DamageAmount;
	return DamageAmount;
}

bool GK_Character::IsAttackReady() const
{
	return Power >= Stats.Cooldown;
}

void GK_Character::ChargePower(float InPower)
{
	Power += InPower;
}

void GK_Character::SetPower(float InPower)
{
	Power = InPower;
}
