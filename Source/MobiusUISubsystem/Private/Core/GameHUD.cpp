// 


#include "Core/GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/HUDRootWidget.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::PauseGame_Implementation()
{
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(RootClass))
	{
		Root = CreateWidget<UHUDRootWidget>(GetOwningPlayerController(), RootClass);
		Root->SetOwnerHUD(this);
		Root->AddToViewport();
	}
}
