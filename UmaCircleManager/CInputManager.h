#pragma once
#include "Common.h"

using InputString = string;

class CInputManager
{
	GENERATED_SINGLETON(CInputManager)

public:
	inline bool ProcessInput() { cin >> InputString; return true; }
	inline const InputString& GetInputString() const { return InputString; }

private:
	InputString InputString;
};

