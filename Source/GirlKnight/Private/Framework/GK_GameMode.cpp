// Girl Knight by MoonDi

#include "GK_GameMode.h"
#include "GK_Game.h"
#include "GK_Character.h"

#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(__GK_GameMode, All, All);

AGK_GameMode::AGK_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGK_GameMode::StartPlay()
{
	GameObject = MakeShared<GK_Game>();
	if (GameObject)
	{
		GameObject->OnAttack				= [this](const FEventAttack& InParam) { ReceiveCharacterAttack(InParam); };
		GameObject->OnEnemyCharacterDead	= [this]() { ReceiveEnemyDead(); };
		GameObject->OnPlayerCharacterDead	= [this]() { ReceivePlayerDead(); };
		GameObject->OnWaveOver				= [this]() { ReceiveWaveOver(); };
		GameObject->OnPlayerCharacterCreate = [this]() { ReceivePlayerCreate(); };
		GameObject->OnEnemyCharacterCreate	= [this]() { ReceiveEnemyCreate(); };

		GameObject->SetPlayerCharacter(GK_Character::BaseCharacter);
		GameObject->SetEnemyWave({GK_Character::BaseMonster, GK_Character::BaseMonster, GK_Character::BaseMonster,
			GK_Character::BaseMonster, GK_Character::BaseMonster});
	}
	Super::StartPlay();
}

void AGK_GameMode::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	// Handle Battle
	if (! GameObject) return;

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

float AGK_GameMode::GetPlayerHealthPercent() const
{
	if (GameObject)
	{
		auto CharPtr = GameObject->GetPlayerCharacterPtr();
		if (CharPtr)
		{
			return CharPtr->GetHealthPercent();
		}
	}
	return 0.0f;
}

float AGK_GameMode::GetPlayerPowerPercent() const
{
	if (GameObject)
	{
		auto CharPtr = GameObject->GetPlayerCharacterPtr();
		if (CharPtr)
		{
			return CharPtr->GetPowerPercent();
		}
	}
	return 0.0f;
}

float AGK_GameMode::GetEnemyHealthPercent() const
{
	if (GameObject)
	{
		auto CharPtr = GameObject->GetEnemyCharacterPtr();
		if (CharPtr)
		{
			return CharPtr->GetHealthPercent();
		}
	}
	return 0.0f;
}

float AGK_GameMode::GetEnemyPowerPercent() const
{
	if (GameObject)
	{
		auto CharPtr = GameObject->GetEnemyCharacterPtr();
		if (CharPtr)
		{
			return CharPtr->GetPowerPercent();
		}
	}
	return 0.0f;
}

void AGK_GameMode::GetActionStack(TArray<EPlayerActions>& OutActions) const
{
	OutActions = ActionStack;
}

EPlayerActions AGK_GameMode::GetActionByIndex(int32 InIndex) const
{
	if (ActionStack.IsValidIndex(InIndex))
	{
		return ActionStack[InIndex];
	}
	return EPlayerActions::None;
}

void AGK_GameMode::StartGame()
{
	if (! GetWorld()) return;

	check(GameObject);

	GameObject->PutPlayer();
	InitialWaveSize = GameObject->GetWaveSize();

	FTimerHandle StartGameTimer;
	auto		 StartFunc = [this]() { //
		OnGameStart.Broadcast();
	};
	GetWorldTimerManager().SetTimer(StartGameTimer, StartFunc, InitialStartTimer, false);
}

void AGK_GameMode::StartBattle()
{
	SetBattleEnabled(true);
	ResetActionStack();
	OnBattleStart.Broadcast();
}

void AGK_GameMode::SpawnEnemy()
{
	if (! GameObject->HasEnemy() && ! bEnemyWaveEmpty)
	{
		if (GameObject->PutEnemy())
		{
			if (GameObject->GetWaveSize() == 0)
			{
				OnPutLastEnemy.Broadcast();
			}
		}
	}
}

void AGK_GameMode::SetBattleEnabled(bool InStarted)
{
	bBattleStarted = InStarted;
}

void AGK_GameMode::DoAction(EPlayerActions InAction)
{
	if (! bBattleStarted || ! GameObject->HasEnemy()) return;
	if (ActionStack.Num() == 0) return;
	check(GameObject);

	if (InAction == ActionStack[0])
	{
		GameObject->ChargePlayerCharacter(AddPowerRightAction);
		GameObject->ChargeEnemy(DecreaseEnemyPowerRightAction * -1.f);
		ActionStack.RemoveAt(0);
		AddActionToStack();
		OnRightAction.Broadcast();
	}
	else
	{
		GameObject->ChargePlayerCharacter(DecreasePowerWrongAction * -1.f);
		GameObject->ChargeEnemy(AddEnemyPowerWrongAction);
		OnWrongAction.Broadcast();
	}
}

float AGK_GameMode::GetProgressPercent() const
{
	if (GameObject)
	{
		const int32 CurrentWaveSize = GameObject->GetWaveSize();
		return 1.f - (float(CurrentWaveSize + 1) / float(InitialWaveSize));
	}
	return 0.0f;
}

void AGK_GameMode::ResetActionStack()
{
	ActionStack.Empty();
	for (int32 i = 0; i < 4; ++i)
	{
		AddActionToStack();
	}
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
	TArray<EPlayerActions> ActionArr = {
		{EPlayerActions::Up, EPlayerActions::Down, EPlayerActions::Left, EPlayerActions::Right}, {} //
	};
	return ActionArr[FMath::RandRange(0, ActionArr.Num() - 1)];
}

//-----------------------------------------------// Callback functions
void AGK_GameMode::ReceiveCharacterAttack(const FEventAttack& InParam)
{
	check(GameObject);
	GameObject->ResetCharacterPower(InParam.Attacker);
	if (GameObject->IsEnemy(InParam.Attacker))
	{
		// Player Hit
		GameObject->ChargePlayerCharacter(-(DechargePlayerOnHit));

		FGK_AttackData AttackData;
		AttackData.AttackerIndex = InParam.Attacker.Pin()->GetIndex();
		AttackData.DamageAmount	 = InParam.DamageAmount;
		AttackData.bCrit		 = InParam.Crited;
		OnEnemyAttack.Broadcast(AttackData);
	}
	else
	{
		// Enemy Hit
		GameObject->ChargeEnemy(-(DechargeEnemyOnHit));

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
	OnEnemyDead.Broadcast();
	OnBattleWin.Broadcast();
}

void AGK_GameMode::ReceivePlayerDead()
{
	SetBattleEnabled(false);
	OnPlayerDead.Broadcast();
	OnBattleFail.Broadcast();
}

void AGK_GameMode::ReceiveWaveOver()
{
	bEnemyWaveEmpty = true;
	OnWaveWin.Broadcast();
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
