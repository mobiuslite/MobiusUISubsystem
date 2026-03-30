// 


#include "Widgets/MLCommonActivatableWidget.h"

#include "Core/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUDRootWidget.h"
#include "GameFramework/PlayerState.h"

void UMLCommonActivatableWidget::GoBack()
{
	if (const AGameHUD* HUD = Cast<AGameHUD>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameHUD::StaticClass())))
	{
		HUD->GetRoot()->PopWidget(this);
	}
}

void UMLCommonActivatableWidget::SetRoot(class UHUDRootWidget* RootWidget)
{
	Root = RootWidget;
}

bool UMLCommonActivatableWidget::NativeOnHandleBackAction()
{
	bool bResult = false;
	
	if (bIsBackHandler)
	{
		DeactivateWidget();
		GoBack();
		bResult = true;
	}
	
	return bResult;
}

void UMLCommonActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (const APlayerController* OwningController = GetOwningPlayer())
	{
		OnLocalPlayerStateReady(OwningController->GetPlayerState<APlayerState>());
	}
}

void UMLCommonActivatableWidget::OnLocalPlayerStateReady(const APlayerState* PlayerState)
{
	if (!PlayerState) return;
	
	if (bStateReadySent) return;
	bStateReadySent = true;
	BP_OnLocalPlayerStateReady(PlayerState);
}
