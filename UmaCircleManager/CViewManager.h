#pragma once
#include"Common.h"

class CView;

class CViewManager
{
	GENERATED_SINGLETON(CViewManager)

public:
	bool UpdateView();
	void SetNextView(const shared_ptr<CView>& InViewPtr);
	void ClearView() const;
	void PauseView() const;
	bool BackView();

private:
	shared_ptr<CView> ViewPtr;
	stack<shared_ptr<CView>> StackedViews;
};

