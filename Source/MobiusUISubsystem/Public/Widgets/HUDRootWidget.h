// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDRootWidget.generated.h"

class AGameHUD;
class UCommonActivatableWidget;
class UMLCommonActivatableWidgetStack;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class MOBIUSUISUBSYSTEM_API UHUDRootWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UCanvasPanel* GetCanvasPanel() const { return RootCanvas; } 
	
	void SetOwnerHUD(AGameHUD* HUD);
	
	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushWidget(const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	UFUNCTION(BlueprintCallable)
	void PopWidget(UCommonActivatableWidget* Widget) const;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* RootCanvas;
	
	UPROPERTY(BlueprintReadOnly)
	AGameHUD* OwnerHUD;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMLCommonActivatableWidgetStack* WidgetStack;
};
