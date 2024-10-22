// Girl Knight by MoonDi

#include "GK_ActionWidget.h"
#include "GK_ActionSlotWidget.h"
#include "GK_GameMode.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void UGK_ActionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (! GetWorld()) return;

	GameMode = GetWorld()->GetAuthGameMode<AGK_GameMode>();
	if (GameMode)
	{
		GameMode->OnRightAction.AddUObject(this, &ThisClass::OnRightAction);
		GameMode->OnWrongAction.AddUObject(this, &ThisClass::OnWrongAction);
		GameMode->OnBattleStart.AddUObject(this, &ThisClass::OnBattleStart);
		Clean();
		Init();
	}
}

void UGK_ActionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (auto& SlotWidget : ActionSlots)
	{
		const FVector2D CurrentPos = SlotWidget->RenderTransform.Translation;
		const FVector2D DesiredPos = GenerateSlotPosition(SlotWidget->Index);
		const float		InterPosX  = FMath::FInterpTo(CurrentPos.X, DesiredPos.X, InDeltaTime, 50.f);
		SlotWidget->SetRenderTranslation(FVector2D(InterPosX, 0.f));
	}
}

void UGK_ActionWidget::AddActionSlot(EPlayerActions InAction, int32 InPosition)
{
	auto NewSlotWidget = CreateWidget<UGK_ActionSlotWidget>(GetWorld(), SlotWidgetClass);
	if (NewSlotWidget)
	{
		auto OverlaySlot = Cast<UOverlaySlot>(SlotOverlay->AddChild(NewSlotWidget));
		if (OverlaySlot)
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		}

		NewSlotWidget->ReceiveSetIcon(InAction);
		NewSlotWidget->Index = InPosition;
		NewSlotWidget->SetRenderTranslation(GenerateSlotPosition(InPosition));
		NewSlotWidget->ReceiveFadeIn();
		ActionSlots.Add(NewSlotWidget);
	}
	else
	{
		check(false);
	}
}

FVector2D UGK_ActionWidget::GenerateSlotPosition(int32 InPosition) const
{
	return FVector2D((SlotSize + SpaceBetweenSlots) * (float)InPosition, 0.f);
}

void UGK_ActionWidget::Init()
{
	for (int32 i = 0; i < ActionsInPreview; ++i)
	{
		AddActionSlot(GameMode->GetActionByIndex(i), i);
	}
}

void UGK_ActionWidget::Clean()
{
	for (auto& SlotWidget : ActionSlots)
	{
		SlotWidget->RemoveFromParent();
	}
	ActionSlots.Empty();
}

void UGK_ActionWidget::OnRightAction()
{
	check(GameMode);

	bool		SlotSwapped		= false;
	const float LastActionIndex = ActionsInPreview - 1;
	for (int32 i = 0; i < ActionSlots.Num(); ++i)
	{
		if (--ActionSlots[i]->Index < (-DeprectedSlotsNum))
		{
			SlotSwapped			  = true;
			ActionSlots[i]->Index = LastActionIndex;
			ActionSlots[i]->SetRenderTranslation(GenerateSlotPosition(LastActionIndex));
			ActionSlots[i]->ReceiveSetIcon(GameMode->GetActionByIndex(LastActionIndex));
			ActionSlots[i]->ReceiveFadeIn();
		}
		else if (ActionSlots[i]->Index == (-DeprectedSlotsNum))
		{
			ActionSlots[i]->ReceiveFadeOut();
		}
	}

	if (! SlotSwapped)
	{
		AddActionSlot(GameMode->GetActionByIndex(LastActionIndex), LastActionIndex);
	}
}

void UGK_ActionWidget::OnWrongAction()
{
	// play some animation
}

void UGK_ActionWidget::OnBattleStart()
{
	Clean();
	Init();
}
