// Girl Knight by MoonDi

#include "GK_HealthWidget.h"
#include "GK_GameMode.h"

void UGK_HealthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetWorld())
	{
		GameModePtr = GetWorld()->GetAuthGameMode<AGK_GameMode>();
	}
}

float UGK_HealthWidget::GetPlayerHealthPercent() const
{
	if (GameModePtr)
	{
		return GameModePtr->GetPlayerHealthPercent();
	}
	return 0.0f;
}

float UGK_HealthWidget::GetPlayerPowerPercent() const
{
	if (GameModePtr)
	{
		return GameModePtr->GetPlayerPowerPercent();
	}
	return 0.0f;
}

float UGK_HealthWidget::GetEnemyHealthPercent() const
{
	if (GameModePtr)
	{
		return GameModePtr->GetEnemyHealthPercent();
	}
	return 0.0f;
}

float UGK_HealthWidget::GetEnemyPowerPercent() const
{
	if (GameModePtr)
	{
		return GameModePtr->GetEnemyPowerPercent();
	}
	return 0.0f;
}
