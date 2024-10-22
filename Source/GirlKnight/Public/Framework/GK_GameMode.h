// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GK_DataTypes.h"
#include "GK_GameplayTypes.h"
#include "GK_GameMode.generated.h"

class GK_Game;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterAttack, const FGK_AttackData&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterCreate, const FName&);

/**
 *
 */
UCLASS()
class GIRLKNIGHT_API AGK_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGK_GameMode();

	FOnCharacterCreate OnPlayerCharacterCreate;
	FOnCharacterCreate OnEnemyCharacterCreate;

	FSimpleMulticastDelegate OnGameStart;
	FSimpleMulticastDelegate OnBattleStart;
	FSimpleMulticastDelegate OnBattleWin;
	FSimpleMulticastDelegate OnBattleFail;

	FSimpleMulticastDelegate OnWaveWin;
	FSimpleMulticastDelegate OnPlayerDead;
	FSimpleMulticastDelegate OnEnemyDead;

	FOnCharacterAttack OnPlayerAttack;
	FOnCharacterAttack OnEnemyAttack;

	FSimpleMulticastDelegate OnRightAction;
	FSimpleMulticastDelegate OnWrongAction;

	// Game Options
	float InitialStartTimer = 3.f;
	float EnemyDecharging	= 1.f;

private:
	TSharedPtr<GK_Game> GameObject;
	bool				bBattleStarted	= false;
	bool				bNoEnemy		= false;
	bool				bEnemyWaveEmpty = false;

	TArray<EPlayerActions> ActionStack;

public:
	virtual void StartPlay() override;
	virtual void Tick(float InDeltaTime) override;

	FName GetPlayerCharacterIndex() const;
	FName GetEnemyCharacterIndex() const;

	void		   GetActionStack(TArray<EPlayerActions>& OutActions) const;
	EPlayerActions GetActionByIndex(int32 InIndex) const;

	// Gameplay
	void StartGame();
	void StartBattle();
	void SpawnEnemy();

	void DoAction(EPlayerActions InAction);

private:
	void SetBattleEnabled(bool InStarted);

	void		   ResetActionStack();
	void		   AddActionToStack();
	EPlayerActions GenerateAction();

private:
	// Game Events
	void ReceiveCharacterAttack(const FEventAttack& InParam);
	void ReceiveEnemyDead();
	void ReceivePlayerDead();
	void ReceiveWaveOver();

	void ReceivePlayerCreate();
	void ReceiveEnemyCreate();
};
