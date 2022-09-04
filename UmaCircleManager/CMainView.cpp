#include "CMainView.h"
#include "CInputManager.h"
#include "CViewManager.h"
#include "CAnalysisView.h"

void CMainView::OnOpen()
{
	CView::OnOpen();

	system("cls");
}

bool CMainView::UpdateView()
{
	cout << "1. Analysis" << endl;

	CInputManager::Get().ProcessInput();
	
	const InputString& inputString = CInputManager::Get().GetInputString();
	if (inputString == "Analysis" || inputString == "1")
	{
		CViewManager::Get().SetNextView(make_shared<CAnalysisView>());
	}
	else
	{
		cout << "The command cannot be processed." << endl;
	}

	return true;
}