// 


#include "Widgets/ToastWidget.h"

void UToastWidget::InitializeToast(const FString& Message, const bool bIsManualToast)
{
	State = EToastState::Opening;
	OnStateChange(State);
	
	StateTimer = TransitionTime;
	
	SetToastMessage(Message);
	
	bIsManual = bIsManualToast;
}

bool UToastWidget::Tick(const float DeltaTime)
{
	//Don't tick manual toasts after they appear
	if (State == Idle && bIsManual)
	{
		return false;
	}
	
	bool bRemove = false;
	
	if ((StateTimer -= DeltaTime) < 0.0f)
	{
		switch (State)
		{
		case EToastState::Opening:
			{
				State = Idle;
				StateTimer = Lifespan;
			}
			break;
		case EToastState::Idle:
			{
				State = Closing;
				StateTimer = TransitionTime;
			}
			break;
		case EToastState::Closing:
			{
				State = None;
				bRemove = true;
			}
			break;
		}
		
		OnStateChange(State);
	}
	
	return bRemove;
}

void UToastWidget::SetStateToClosing()
{
	State = Closing;
	StateTimer = TransitionTime;
	
	OnStateChange(State);
}

void UToastWidget::SetToastMessage_Implementation(const FString& Message)
{
	ToastMessage = Message;
}

void UToastWidget::OnStateChange_Implementation(EToastState NewState)
{
}
