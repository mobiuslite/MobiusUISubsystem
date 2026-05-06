// 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Widgets/Layout/Anchors.h"
#include "ToastSubsystem.generated.h"

struct FAnchors;
class UToastWidget;
/**
 * 
 */
UCLASS()
class MOBIUSUISUBSYSTEM_API UToastSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual TStatId GetStatId() const override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="WidgetClass"))
	UToastWidget* ShowToast(const TSubclassOf<UToastWidget> WidgetClass, const FString& Message, 
		const FVector2D& Position, const FAnchors& Anchors, const FVector2D& Alignment);
	
	//Shows a toast that will remain on screen until HideToast is called with the ID returned by this function
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="WidgetClass"))
	UToastWidget* ShowManualToast(const TSubclassOf<UToastWidget> WidgetClass, const FString& Message, 
		const FVector2D& Position, const FAnchors& Anchors, const FVector2D& Alignment, int& OutToastId);
	UFUNCTION(BlueprintCallable)
	void HideToast(const int ToastId);
	
protected:
	
	static int NextToastId;
	
	UToastWidget* AddToastToViewport(const TSubclassOf<UToastWidget> WidgetClass, const FString& Message, 
		const FVector2D& Position, const FAnchors& Anchors, const FVector2D& Alignment, const bool bIsManual);
	
	void DestroyToast(UToastWidget* Toast);
	
	UPROPERTY()
	TArray<UToastWidget*> ActiveToasts;
	
	UPROPERTY()
	TMap<int, UToastWidget*> ManualToasts;
};
