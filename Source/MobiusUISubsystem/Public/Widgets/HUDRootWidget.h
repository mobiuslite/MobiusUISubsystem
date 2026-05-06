// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDRootWidget.generated.h"

class AGameHUD;
class UCommonActivatableWidget;
class UMLCommonActivatableWidgetStack;
class UCanvasPanel;
class UCanvasPanelSlot;

USTRUCT()
struct FActorWidgetInfo
{
	GENERATED_BODY()
	
	UPROPERTY()
	const AActor* Actor;
	
	FVector Offset;
	
	UPROPERTY()
	UUserWidget* Widget;
	UPROPERTY()
	UCanvasPanelSlot* CanvasSlot;
};

UCLASS()
class MOBIUSUISUBSYSTEM_API UHUDRootWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UCanvasPanel* GetCanvasPanel() const { return RootCanvas; } 
	
	void SetOwnerHUD(AGameHUD* HUD);
	
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="ActivatableWidgetClass"))
	UCommonActivatableWidget* PushWidget(const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	UFUNCTION(BlueprintCallable)
	void PopWidget(UCommonActivatableWidget* Widget) const;
	UFUNCTION(BlueprintCallable)
	void PopWidgetByClass(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsWidgetActiveByClass(const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass) const;
	
	void OnLocalPlayerStateAdded(const APlayerState* PlayerState);
	
	//Adds a widget that will always be in the same place as the actor
	UFUNCTION(BlueprintCallable)
	void RegisterActorWidget(const AActor* Actor, UTexture2D* Texture, const FVector& Offset);
	
protected:
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* RootCanvas;
	
	UPROPERTY(BlueprintReadOnly)
	AGameHUD* OwnerHUD;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMLCommonActivatableWidgetStack* WidgetStack;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ActorWidgetClass;
	
private:
	
	UPROPERTY()
	TArray<FActorWidgetInfo> ActorWidgets;
};
