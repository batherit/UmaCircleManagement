#pragma once
#include"Common.h"

class CView;

class CViewManager
{
	GENERATED_SINGLETON(CViewManager)

public:
	bool UpdateView();
	void SetNextView(const shared_ptr<CView>& InViewPtr);

private:
	shared_ptr<CView> ViewPtr;
};

