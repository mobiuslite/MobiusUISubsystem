// 


#include "ToastSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Core/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUDRootWidget.h"
#include "Widgets/ToastWidget.h"

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

void UToastSubsystem::ShowToast(const TSubclassOf<UToastWidget> WidgetClass, const FString& Message,
	const FVector2D& Position, const FAnchors& Anchors, const FVector2D& Alignment)
{
	AGameHUD* HUD = Cast<AGameHUD>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameHUD::StaticClass()));
	if (!HUD) return;
	
	UCanvasPanel* RootPanel = HUD->GetRoot()->GetCanvasPanel();
	if (!RootPanel) return;
	
	UToastWidget* NewWidget = CreateWidget<UToastWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClass);
	NewWidget->InitializeToast(Message);
	ActiveToasts.Add(NewWidget);
	
	UCanvasPanelSlot* NewSlot = RootPanel->AddChildToCanvas(NewWidget);
	NewSlot->SetAlignment(Alignment);
	NewSlot->SetAnchors(Anchors);
	NewSlot->SetPosition(Position);
}

void UToastSubsystem::DestroyToast(UToastWidget* Toast)
{
	if (!Toast) return;
	Toast->RemoveFromParent();
}
