#include "CEditView.h"
#include "CInputManager.h"
#include "CViewManager.h"
#include "CEditCircleNameView.h"

void CEditView::OnOpen()
{
    CView::OnOpen();
}

bool CEditView::UpdateView()
{
	cout << "1. Change circle member name / 2. Back" << endl;

	CInputManager::Get().ProcessInput();
	const InputString& inputString = CInputManager::Get().GetInputString();
	
	if (inputString == "1")
	{
		CViewManager::Get().SetNextView(make_shared<CEditCircleNameView>());
	}
	else if (inputString == "2" || inputString == "Back")
	{
		return CViewManager::Get().BackView();		
	}

	return true;
}
