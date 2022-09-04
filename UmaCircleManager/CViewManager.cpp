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
		if(ViewPtr)
			ViewPtr->OnClose();
		ViewPtr = InViewPtr;
		ViewPtr->OnOpen();
	}
}
