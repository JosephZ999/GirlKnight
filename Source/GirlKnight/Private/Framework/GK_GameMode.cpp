// Girl Knight by MoonDi

#include "GK_GameMode.h"
#include "Core/GK_Game.h"
#include "Core/GK_Character.h"

#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(__GK_GameMode, All, All);

AGK_GameMode::AGK_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGK_GameMode::StartPlay()
{
	Super::StartPlay();

	GameObject = MakeShared<GK_Game>();
	if (GameObject)
	{
		GameObject->OnAttack				= [this](const FEventAttack& InParam) { ReceiveCharacterAttack(InParam); };
		GameObject->OnEnemyCharacterDead	= [this]() { ReceiveEnemyDead(); };
		GameObject->OnPlayerCharacterDead	= [this]() { ReceivePlayerDead(); };
		GameObject->OnWaveOver				= [this]() { ReceiveWaveOver(); };
		GameObject->OnPlayerCharacterCreate = [this]() { ReceivePlayerCreate(); };
		GameObject->OnPlayerCharacterCreate = [this]() { ReceiveEnemyCreate(); };

		GameObject->SetPlayerCharacter(GK_Character::BaseCharacter);
		GameObject->SetEnemyWave({GK_Character::BaseMonster, GK_Character::BaseMonster});
	}
}

void AGK_GameMode::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	// Handle Battle
	if (! GameObject) return;

	// Put Enemies
	if (bNoEnemy && ! bEnemyWaveEmpty)
	{
		GameObject->PutEnemy();
	}

	// Battle
	if (bBattleStarted)
	{
		GameObject->ChargeEnemy(InDeltaTime);
	}
}

FName AGK_GameMode::GetPlayerCharacterIndex() const
{
	TWeakPtr<GK_Character> Character = GameObject->GetPlayerCharacterPtr();
	if (Character.IsValid())
	{
		return Character.Pin()->GetIndex();
	}
	return FName();
}

FName AGK_GameMode::GetEnemyCharacterIndex() const
{
	TWeakPtr<GK_Character> Character = GameObject->GetEnemyCharacterPtr();
	if (Character.IsValid())
	{
		return Character.Pin()->GetIndex();
	}
	return FName();
}

void AGK_GameMode::StartGame()
{
	if (! GetWorld()) return;

	check(GameObject);

	GameObject->PutPlayer();
	GameObject->PutEnemy();

	FTimerHandle StartGameTimer;
	GetWorldTimerManager().SetTimer(StartGameTimer, this, &ThisClass::StartBattle, InitialStartTimer, false);
}

void AGK_GameMode::StartBattle()
{
	SetBattleEnabled(true);
	OnGameStart.Broadcast();
}

void AGK_GameMode::SetBattleEnabled(bool InStarted)
{
	bBattleStarted = InStarted;
}

void AGK_GameMode::DoAction(EPlayerActions InAction)
{
	if (! bBattleStarted || bNoEnemy) return;
	if (ActionStack.Num() == 0) return;
	check(GameObject);

	if (InAction == ActionStack[0])
	{
		GameObject->ChargePlayerCharacter(1.f);
		ActionStack.RemoveAt(0);
		AddActionToStack();
		// right action
	}
	else
	{
		GameObject->ChargeEnemy(1.f);
		// wrong action
	}
}

void AGK_GameMode::ResetActionStack()
{
	ActionStack.Empty();
	// broadcast delegate
}

void AGK_GameMode::AddActionToStack()
{
	EPlayerActions NewAction = GenerateAction();
	ActionStack.Add(NewAction);
	// broadcast delegate
}

EPlayerActions AGK_GameMode::GenerateAction()
{
	return EPlayerActions();
}

//-----------------------------------------------// Callback functions
void AGK_GameMode::ReceiveCharacterAttack(const FEventAttack& InParam)
{
	check(GameObject);
	GameObject->ResetCharacterPower(InParam.Attacker);
	if (GameObject->IsEnemy(InParam.Attacker))
	{
		FGK_AttackData AttackData;
		AttackData.AttackerIndex = InParam.Attacker.Pin()->GetIndex();
		AttackData.DamageAmount	 = InParam.DamageAmount;
		AttackData.bCrit		 = InParam.Crited;
		OnEnemyAttack.Broadcast(AttackData);
	}
	else
	{
		GameObject->ChargeEnemy(-(EnemyDecharging));

		FGK_AttackData AttackData;
		AttackData.AttackerIndex = InParam.Attacker.Pin()->GetIndex();
		AttackData.DamageAmount	 = InParam.DamageAmount;
		AttackData.bCrit		 = InParam.Crited;
		OnPlayerAttack.Broadcast(AttackData);
	}
}

void AGK_GameMode::ReceiveEnemyDead()
{
	SetBattleEnabled(false);
	bNoEnemy = true;
	OnEnemyDead.Broadcast();
}

void AGK_GameMode::ReceivePlayerDead()
{
	SetBattleEnabled(false);
	OnGameOver.Broadcast();
}

void AGK_GameMode::ReceiveWaveOver()
{
	bEnemyWaveEmpty = true;
	OnGameWin.Broadcast();
}

void AGK_GameMode::ReceivePlayerCreate()
{
	check(GameObject);

	OnPlayerCharacterCreate.Broadcast(GetPlayerCharacterIndex());
}

void AGK_GameMode::ReceiveEnemyCreate()
{
	check(GameObject);

	OnEnemyCharacterCreate.Broadcast(GetEnemyCharacterIndex());
}
