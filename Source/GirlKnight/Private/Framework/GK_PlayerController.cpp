// Girl Knight by MoonDi

#include "GK_PlayerController.h"
#include "GK_GameMode.h"
#include "GK_GameplayTypes.h"

#include "Engine/World.h"
#include "Components/InputComponent.h"

void AGK_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto World = GetWorld();
	if (! World) return;

	GameMode = World->GetAuthGameMode<AGK_GameMode>();
	if (! GameMode) return;

	GameMode->OnPlayerCharacterCreate.AddLambda([this](const FName& InCharIndex) { OnPlayerSpawn(InCharIndex); });
	GameMode->OnEnemyCharacterCreate.AddLambda([this](const FName& InCharIndex) { OnEnemySpawn(InCharIndex); });

	GameMode->OnBattleStart.AddLambda([this]() { OnBattleStart(); });
	GameMode->OnWaveWin.AddLambda([this]() { OnWaveWin(); });
	GameMode->OnPlayerDead.AddLambda([this]() { OnPlayerDead(); });
	GameMode->OnEnemyDead.AddLambda([this]() { OnEnemyDead(); });

	GameMode->OnPlayerAttack.AddLambda([this](const FGK_AttackData& AttackParam) { OnPlayerAttack(AttackParam); });
	GameMode->OnEnemyAttack.AddLambda([this](const FGK_AttackData& AttackParam) { OnEnemyAttack(AttackParam); });

	GameMode->OnRightAction.AddLambda([this]() { OnRightAction(); });
	GameMode->OnWrongAction.AddLambda([this]() { OnWrongAction(); });

	GameMode->StartGame();
}

void AGK_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("ArrowUp", EInputEvent::IE_Pressed, this, &ThisClass::OnArrowUpPressed);
		InputComponent->BindAction("ArrowDown", EInputEvent::IE_Pressed, this, &ThisClass::OnArrowDownPressed);
		InputComponent->BindAction("ArrowLeft", EInputEvent::IE_Pressed, this, &ThisClass::OnArrowLeftPressed);
		InputComponent->BindAction("ArrowRight", EInputEvent::IE_Pressed, this, &ThisClass::OnArrowRightPressed);
	}
}

void AGK_PlayerController::StartBattle()
{
	if (! GameMode) return;

	GameMode->StartBattle();
}

void AGK_PlayerController::GetActionList(TArray<EPlayerActions>& OutActions) const
{
	GameMode->GetActionStack(OutActions);
}

//-----------------------------------------------// Input Actions
void AGK_PlayerController::OnArrowUpPressed()
{
	if (GameMode)
	{
		GameMode->DoAction(EPlayerActions::Up);
	}
}

void AGK_PlayerController::OnArrowDownPressed()
{
	if (GameMode)
	{
		GameMode->DoAction(EPlayerActions::Down);
	}
}

void AGK_PlayerController::OnArrowLeftPressed()
{
	if (GameMode)
	{
		GameMode->DoAction(EPlayerActions::Left);
	}
}

void AGK_PlayerController::OnArrowRightPressed()
{
	if (GameMode)
	{
		GameMode->DoAction(EPlayerActions::Right);
	}
}