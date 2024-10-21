// Girl Knight by MoonDi

#include "GK_Game.h"

DEFINE_LOG_CATEGORY_STATIC(__GK_Game, All, All);

void GK_Game::SetPlayerCharacter(const GK_Character& InPlayerCharacter)
{
	PlayerCharacter = InPlayerCharacter;
}

void GK_Game::SetEnemyWave(const TArray<GK_Character>& InEnemyWave)
{
	EnemyWave = InEnemyWave;
}

void GK_Game::FinishInit()
{
	PlayerCharacterPtr = MakeShared<GK_Character>(PlayerCharacter);
	PutEnemy();
}

void GK_Game::PutEnemy()
{
	if (EnemyWave.Num() == 0)
	{
		UE_LOG(__GK_Game, Display, TEXT("No enemies in wave"));
		return;
	}

	EnemyPtr = MakeShared<GK_Character>(EnemyWave[0]);
	EnemyWave.RemoveAt(0);
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