// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GK_GameplayTypes.h"
#include "GK_ActionWidget.generated.h"

class AGK_GameMode;
class UGK_ActionSlotWidget;
class UOverlay;

/**
 *
 */
UCLASS()
class GIRLKNIGHT_API UGK_ActionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (BindWidget))
	UOverlay* SlotOverlay;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGK_ActionSlotWidget> SlotWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Slots")
	float SlotSize = 100.f;

	UPROPERTY(EditAnywhere, Category = "Slots")
	float SpaceBetweenSlots = 20.f;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 DeprectedSlotsNum = 4;

private:
	UPROPERTY()
	AGK_GameMode* GameMode;

	UPROPERTY()
	TArray<UGK_ActionSlotWidget*> ActionSlots;

	UPROPERTY()
	int32 ActionsInPreview = 3;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void	  AddActionSlot(EPlayerActions InAction, int32 InPosition);
	FVector2D GenerateSlotPosition(int32 InPosition) const;

	void Init();
	void Clean();

	void OnRightAction();
	void OnWrongAction();

	void OnBattleStart();
};
