#include "CViewManager.h"
#include "CView.h"
#include "CInputManager.h"

bool CViewManager::UpdateView()
{
	if (ViewPtr)
		return ViewPtr->UpdateView();
	else
		return false;
}

void CViewManager::SetNextView(const shared_ptr<CView>& InViewPtr)
{
	if (InViewPtr)
	{
		ClearView();

		if (ViewPtr)
		{
			StackedViews.push(ViewPtr);
		}

		ViewPtr = InViewPtr;

		ViewPtr->OnOpen();
	}
}

void CViewManager::ClearView() const
{
	system("cls");
}

void CViewManager::PauseView() const
{
	system("pause");
}

bool CViewManager::BackView()
{
	if (StackedViews.empty())
		return false;

	const shared_ptr<CView> topViewPtr = StackedViews.top();
	StackedViews.pop();

	ClearView();

	if (ViewPtr)
	{
		ViewPtr->OnClose();
	}

	ViewPtr = topViewPtr;

	return true;
}
