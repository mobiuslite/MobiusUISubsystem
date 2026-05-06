// 


#include "Core/GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
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
		
		if (QueuedPlayerState)
		{
			Root->OnLocalPlayerStateAdded(QueuedPlayerState);
			QueuedPlayerState = nullptr;
		}
	}
}

void AGameHUD::SetInputModeGameEnabled(const UObject* WorldContextObject, const bool bGameOnlyEnabled,
	const bool bFlushInput)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (bGameOnlyEnabled)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController, bFlushInput);
		}
		else
		{
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, nullptr, EMouseLockMode::DoNotLock, bFlushInput);
			
			FVector2D ScreenSize;
			GEngine->GameViewport->GetViewportSize(ScreenSize);
			
			PlayerController->SetMouseLocation(ScreenSize.X * 0.5f, ScreenSize.Y * 0.5f);
		}
		
		PlayerController->bShowMouseCursor = !bGameOnlyEnabled;
	}
}

AGameHUD* AGameHUD::GetGameHUD(const AController* Controller)
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		return PlayerController->GetHUD<AGameHUD>();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Unable to get controller to retrieve GameHUD"))
	return nullptr;
}

void AGameHUD::OnPlayerStateAdded_Implementation(const APlayerState* PlayerState)
{
	if (Root)
	{
		Root->OnLocalPlayerStateAdded(PlayerState);
	}
	else
	{
		QueuedPlayerState = PlayerState;
	}
}
