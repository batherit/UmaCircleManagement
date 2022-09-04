#pragma once
#include "Common.h"

class CView
{
public:
	virtual void OnOpen() {}
	virtual void OnClose() {}
	virtual bool UpdateView() PURE;
};

