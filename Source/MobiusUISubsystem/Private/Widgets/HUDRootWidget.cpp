// 


#include "Widgets/HUDRootWidget.h"
#include "CommonActivatableWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Core/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MLCommonActivatableWidget.h"
#include "Widgets/MLCommonActivatableWidgetStack.h"

void UHUDRootWidget::SetOwnerHUD(AGameHUD* HUD)
{
	OwnerHUD = HUD;
}

UCommonActivatableWidget* UHUDRootWidget::PushWidget(const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (!WidgetStack) return nullptr;
	
	UCommonActivatableWidget* NewWidget = WidgetStack->AddWidget(ActivatableWidgetClass);
	if (UMLCommonActivatableWidget* MLWidget = Cast<UMLCommonActivatableWidget>(NewWidget))
	{
		MLWidget->SetRoot(this);
	}
	
	AGameHUD::SetInputModeGameEnabled(GetWorld(), false, true);
	
	return NewWidget;
}

void UHUDRootWidget::PopWidget(UCommonActivatableWidget* Widget) const
{
	if (!WidgetStack) return;
	
	WidgetStack->RemoveWidget(*Widget);
	
	if (WidgetStack->GetNumActiveWidgets() == 0)
	{
		AGameHUD::SetInputModeGameEnabled(GetWorld(), true, true);
	}
}

void UHUDRootWidget::PopWidgetByClass(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
{
	if (!IsValid(WidgetClass)) return;
	if (UCommonActivatableWidget* ActiveWidget = WidgetStack->GetActiveWidgetByClass(WidgetClass))
	{
		PopWidget(ActiveWidget);
	}
}

bool UHUDRootWidget::IsWidgetActiveByClass(const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass) const
{
	if (!WidgetStack) return false;
	return WidgetStack->IsWidgetActiveByClass(ActivatableWidgetClass);
}

void UHUDRootWidget::OnLocalPlayerStateAdded(const APlayerState* PlayerState)
{
	if (UMLCommonActivatableWidget* Widget = Cast<UMLCommonActivatableWidget>(WidgetStack->GetRootContent()))
	{
		Widget->OnLocalPlayerStateReady(PlayerState);
	}
	
	const TArray<UCommonActivatableWidget*>& WidgetList = WidgetStack->GetWidgetList();
	for (int i = 0; i < WidgetList.Num(); ++i)
	{
		if (UMLCommonActivatableWidget* Widget = Cast<UMLCommonActivatableWidget>(WidgetList[i]))
		{
			Widget->OnLocalPlayerStateReady(PlayerState);
		}
	}
}

void UHUDRootWidget::RegisterActorWidget(const AActor* Actor, UTexture2D* Texture, const FVector& Offset)
{
	ensure(IsValid(ActorWidgetClass));
	
	if (!Actor || !Texture) return;
	
	UUserWidget* NewWidget = CreateWidget(this, ActorWidgetClass);
	if (!NewWidget) return;
	
	UCanvasPanelSlot* NewSlot = GetCanvasPanel()->AddChildToCanvas(NewWidget);
	NewSlot->SetAlignment(FVector2D(0.5f));
	NewSlot->SetAutoSize(true);
	
	FActorWidgetInfo Info;
	Info.Actor = Actor;
	Info.CanvasSlot = NewSlot;
	Info.Offset = Offset;
	Info.Widget = NewWidget;
	
	ActorWidgets.Add(Info);
}

void UHUDRootWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	for (int i = 0; i < ActorWidgets.Num();)
	{
		FActorWidgetInfo& Info = ActorWidgets[i];
		if (!Info.Actor)
		{
			ActorWidgets.RemoveAt(i);
			continue;
		}
		
		FVector2D ScreenPosition;
		const APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0); 
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(Controller, Info.Actor->GetActorLocation() + Info.Offset, ScreenPosition, false);
		
		Info.CanvasSlot->SetPosition(ScreenPosition);
		
		i++;
	}
}
