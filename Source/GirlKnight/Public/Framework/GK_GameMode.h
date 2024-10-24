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

	UPROPERTY(EditAnywhere, Category = "GameOptions")
	float InitialStartTimer = 2.f;

	UPROPERTY(EditAnywhere, Category = "GameOptions | Actions")
	float AddPowerRightAction = 1.f;

	UPROPERTY(EditAnywhere, Category = "GameOptions | Actions")
	float DecreasePowerWrongAction = 0.f;

	UPROPERTY(EditAnywhere, Category = "GameOptions | Actions")
	float AddEnemyPowerWrongAction = 1.f;

	UPROPERTY(EditAnywhere, Category = "GameOptions | Actions")
	float DecreaseEnemyPowerRightAction = 0.f;

	// Game Options
	UPROPERTY(EditAnywhere, Category = "GameOptions | Hit")
	float DechargePlayerOnHit = 1.f;

	UPROPERTY(EditAnywhere, Category = "GameOptions | Hit")
	float DechargeEnemyOnHit = 1.f;

	// Delegates
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

private:
	TSharedPtr<GK_Game> GameObject;
	bool				bBattleStarted	= false;
	bool				bEnemyWaveEmpty = false;

	TArray<EPlayerActions> ActionStack;

	int32 InitialWaveSize = 0;

public:
	virtual void StartPlay() override;
	virtual void Tick(float InDeltaTime) override;

	FName GetPlayerCharacterIndex() const;
	FName GetEnemyCharacterIndex() const;
	float GetPlayerHealthPercent() const;
	float GetPlayerPowerPercent() const;
	float GetEnemyHealthPercent() const;
	float GetEnemyPowerPercent() const;

	void		   GetActionStack(TArray<EPlayerActions>& OutActions) const;
	EPlayerActions GetActionByIndex(int32 InIndex) const;

	// Gameplay
	void StartGame();
	void StartBattle();
	void SpawnEnemy();

	void DoAction(EPlayerActions InAction);

	UFUNCTION(BlueprintCallable)
	float GetProgressPercent() const;

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
