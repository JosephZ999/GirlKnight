// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GK_GameplayTypes.h"
#include "GK_PlayerController.generated.h"

class AGK_GameMode;

/**
 *
 */
UCLASS()
class GIRLKNIGHT_API AGK_PlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AGK_GameMode* GameMode = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Main
	UFUNCTION(BlueprintImplementableEvent)
	void OnGameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBattleStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBattleWin();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBattleFail();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWaveWin();

	// Characters handling
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerSpawn(const FName& InCharIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnemySpawn(const FName& InCharIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerAttack(const FGK_AttackData& InAttackParam);

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnemyAttack(const FGK_AttackData& InAttackParam);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerDead();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnemyDead();

	// Player Actions
	UFUNCTION(BlueprintImplementableEvent)
	void OnRightAction();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWrongAction();

public:
	UFUNCTION(BlueprintCallable)
	void StartBattle();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void GetActionList(TArray<EPlayerActions>& OutActions) const;

private:
	// Inputs
	void OnArrowUpPressed();
	void OnArrowDownPressed();
	void OnArrowLeftPressed();
	void OnArrowRightPressed();

private:
	//-----------------------------------------------// Delegate Handles
};
