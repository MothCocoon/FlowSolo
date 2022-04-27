#pragma once

#include "EnhancedInputComponent.h"
#include "SoloInputComponent.generated.h"

UCLASS()
class FLOWSOLO_API USoloInputComponent final : public UEnhancedInputComponent
{
	GENERATED_UCLASS_BODY()

	template<class UserClass, class FuncType, typename... VarTypes>
	void BindClick(const UInputAction* Action, const ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, VarTypes... Vars)
	{
		if (Action)
		{
			BindAction(Action, TriggerEvent, Object, Func, Vars...);
		}
	}

	void BindValue(const UInputAction* Action)
	{
		if (Action)
		{
			BindActionValue(Action);
		}
	}
	
	template<class UserClass, class FuncType>
	void BindAxis(const UInputAction* Action, UserClass* Object, FuncType Func)
	{
		if (Action)
		{
			BindActionValue(Action);
			BindAction(Action, ETriggerEvent::Triggered, Object, Func, Action);
		}
	}
};
