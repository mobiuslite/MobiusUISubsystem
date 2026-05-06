// 


#include "ToastSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Core/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUDRootWidget.h"
#include "Widgets/ToastWidget.h"

int UToastSubsystem::NextToastId;

TStatId UToastSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UToastSubsystem, STATGROUP_Tickables);
}

void UToastSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < ActiveToasts.Num();)
	{
		UToastWidget* Toast = ActiveToasts[i];
		
		bool bMarkedForRemoval = true;
		if (Toast)
		{
			bMarkedForRemoval = Toast->Tick(DeltaTime);
		}
		
		if (bMarkedForRemoval)
		{
			DestroyToast(Toast);
			ActiveToasts.RemoveAt(i);
		} 
		else
		{
			i++;
		}
	}
}

UToastWidget* UToastSubsystem::ShowToast(const TSubclassOf<UToastWidget> WidgetClass, const FString& Message,
	const FVector2D& Position, const FAnchors& Anchors, const FVector2D& Alignment)
{
	return AddToastToViewport(WidgetClass, Message, Position, Anchors, Alignment, false);
}

UToastWidget* UToastSubsystem::ShowManualToast(const TSubclassOf<UToastWidget> WidgetClass, const FString& Message,
	const FVector2D& Position, const FAnchors& Anchors, const FVector2D& Alignment, int& OutToastId)
{
	UToastWidget* NewWidget = AddToastToViewport(WidgetClass, Message, Position, Anchors, Alignment, true);
	
	OutToastId = ++NextToastId;
	ManualToasts.Add(OutToastId, NewWidget);
	
	return NewWidget;
}

void UToastSubsystem::HideToast(const int ToastId)
{
	if (UToastWidget** FoundToast = ManualToasts.Find(ToastId))
	{
		if (UToastWidget* Toast = *FoundToast)
		{
			Toast->SetStateToClosing();
		}
		
		ManualToasts.Remove(ToastId);
	}
}

UToastWidget* UToastSubsystem::AddToastToViewport(const TSubclassOf<UToastWidget> WidgetClass, const FString& Message,
                                                  const FVector2D& Position, const FAnchors& Anchors, const FVector2D& Alignment, const bool bIsManual)
{
	AGameHUD* HUD = Cast<AGameHUD>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameHUD::StaticClass()));
	if (!HUD) return nullptr;
	
	UCanvasPanel* RootPanel = HUD->GetRoot()->GetCanvasPanel();
	if (!RootPanel) return nullptr;
	
	UToastWidget* NewWidget = CreateWidget<UToastWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClass);
	NewWidget->InitializeToast(Message, bIsManual);
	ActiveToasts.Add(NewWidget);
	
	UCanvasPanelSlot* NewSlot = RootPanel->AddChildToCanvas(NewWidget);
	NewSlot->SetAlignment(Alignment);
	NewSlot->SetAnchors(Anchors);
	NewSlot->SetPosition(Position);
	NewSlot->SetAutoSize(true);
	
	//This stops full screen toasts with 0-1 anchors not taking up the full screen. Need to look into this more.
	if (Anchors.Minimum.IsNearlyZero() && Anchors.Maximum.X >= 1.0f && Anchors.Maximum.Y >= 1.0f)
	{
		NewSlot->SetOffsets(FMargin());
	}
	
	return NewWidget;
}

void UToastSubsystem::DestroyToast(UToastWidget* Toast)
{
	if (!Toast) return;
	Toast->RemoveFromParent();
}
