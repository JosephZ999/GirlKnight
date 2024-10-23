// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GK_HealthWidget.generated.h"

class AGK_GameMode;
/**
 *
 */
UCLASS()
class GIRLKNIGHT_API UGK_HealthWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AGK_GameMode* GameModePtr;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	float GetPlayerHealthPercent() const;

	UFUNCTION(BlueprintCallable)
	float GetPlayerPowerPercent() const;

	UFUNCTION(BlueprintCallable)
	float GetEnemyHealthPercent() const;

	UFUNCTION(BlueprintCallable)
	float GetEnemyPowerPercent() const;
};
