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
	
	UFUNCTION(BlueprintCallable)
	void ShowToast(const TSubclassOf<UToastWidget> WidgetClass, const FString& Message, 
		const FVector2D& Position, const FAnchors& Anchors, const FVector2D& Alignment);
	
protected:
	
	void DestroyToast(UToastWidget* Toast);
	
	UPROPERTY()
	TArray<UToastWidget*> ActiveToasts;
};
