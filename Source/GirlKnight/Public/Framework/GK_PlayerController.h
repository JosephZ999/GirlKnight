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

	// Blueprint Interface
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

	UFUNCTION(BlueprintImplementableEvent)
	void OnBattleStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWaveWin();

public:
	UFUNCTION(BlueprintCallable)
	void StartBattle();

private:
	// Inputs
	void OnArrowUpPressed();
	void OnArrowDownPressed();
	void OnArrowLeftPressed();
	void OnArrowRightPressed();

private:
	//-----------------------------------------------// Delegate Handles
};
