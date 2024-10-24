// Girl Knight by MoonDi

#include "GK_Game.h"

DEFINE_LOG_CATEGORY_STATIC(__GK_Game, All, All);

int32 GK_Game::GetWaveSize() const
{
	return EnemyWave.Num();
}

bool GK_Game::HasEnemy() const
{
	return EnemyPtr.IsValid() ? EnemyPtr->GetHealth() > 0.f : false;
}

void GK_Game::SetPlayerCharacter(const GK_Character& InPlayerCharacter)
{
	PlayerCharacter = InPlayerCharacter;
}

void GK_Game::SetEnemyWave(const TArray<GK_Character>& InEnemyWave)
{
	EnemyWave = InEnemyWave;
}

bool GK_Game::PutPlayer()
{
	PlayerCharacterPtr = MakeShared<GK_Character>(PlayerCharacter);
	if (PlayerCharacterPtr && ! PlayerCharacterPtr->GetIndex().IsNone())
	{
		if (OnPlayerCharacterCreate)
		{
			OnPlayerCharacterCreate();
		}
		return true;
	}
	return false;
}

bool GK_Game::PutEnemy()
{
	if (EnemyWave.Num() == 0)
	{
		if (OnWaveOver)
		{
			OnWaveOver();
		}
		UE_LOG(__GK_Game, Display, TEXT("No enemies in wave"));
		return false;
	}

	EnemyPtr = MakeShared<GK_Character>(EnemyWave[0]);
	EnemyWave.RemoveAt(0);
	if (OnEnemyCharacterCreate)
	{
		OnEnemyCharacterCreate();
	}
	return true;
}

void GK_Game::Attack(TSharedPtr<GK_Character> InAttacker, TSharedPtr<GK_Character> InVictim)
{
	check(InAttacker);
	check(InVictim);
	if (! InAttacker || ! InVictim) return;

	const float Damage		 = InAttacker->GetDamage();
	const float CritDamage	 = 2.f;
	const bool	Crit		 = false;
	const float DamageAmount = InVictim->ApplyDamage(Crit ? Damage * CritDamage : Damage);

	if (OnAttack) // Callback
	{
		FEventAttack AttackParam;
		AttackParam.Attacker	 = InAttacker;
		AttackParam.Victim		 = InVictim;
		AttackParam.DamageAmount = DamageAmount;
		AttackParam.Crited		 = Crit;
		AttackParam.Killed		 = InVictim->GetHealth() <= 0.f;
		OnAttack(AttackParam);
	}
}

void GK_Game::PlayerTurn()
{
	check(PlayerCharacterPtr);
	check(EnemyPtr);

	Attack(PlayerCharacterPtr, EnemyPtr);

	if (EnemyPtr->GetHealth() <= 0.f)
	{
		if (OnEnemyCharacterDead)
		{
			OnEnemyCharacterDead();
		}
	}
}

void GK_Game::EnemyTurn()
{
	check(EnemyPtr);
	check(PlayerCharacterPtr);

	Attack(EnemyPtr, PlayerCharacterPtr);

	if (PlayerCharacterPtr->GetHealth() <= 0.f)
	{
		if (OnPlayerCharacterDead)
		{
			OnPlayerCharacterDead();
		}
	}
}

bool GK_Game::IsEnemy(TWeakPtr<GK_Character> InCharacter)
{
	return EnemyPtr == InCharacter;
}

void GK_Game::ChargePlayerCharacter(float InValue)
{
	if (! PlayerCharacterPtr) return;
	if (PlayerCharacterPtr->GetPowerPercent() >= 1.f)
	{
		// We Attacked already
		return;
	}

	PlayerCharacterPtr->ChargePower(InValue);
	if (PlayerCharacterPtr->IsAttackReady())
	{
		PlayerTurn();
	}
}

void GK_Game::ChargeEnemy(float InValue)
{
	if (! EnemyPtr) return;
	if (EnemyPtr->GetPowerPercent() >= 1.f)
	{
		// We Attacked already
		return;
	}

	EnemyPtr->ChargePower(InValue);
	if (EnemyPtr->IsAttackReady())
	{
		EnemyTurn();
	}
}

void GK_Game::ResetCharacterPower(TWeakPtr<GK_Character> InCharacter)
{
	if (InCharacter.IsValid())
	{
		InCharacter.Pin()->SetPower(0.f);
	}
}
