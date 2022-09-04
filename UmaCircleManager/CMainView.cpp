#include "CMainView.h"
#include "CInputManager.h"
#include "CViewManager.h"
#include "CAnalysisView.h"
#include "CEditView.h"

void CMainView::OnOpen()
{
	CView::OnOpen();

	system("cls");
}

bool CMainView::UpdateView()
{
	cout << "1. Analysis / 2. Edit" << endl;

	CInputManager::Get().ProcessInput();
	
	const InputString& inputString = CInputManager::Get().GetInputString();
	if (inputString == "Analysis" || inputString == "1")
	{
		CViewManager::Get().SetNextView(make_shared<CAnalysisView>());
	}
	else if (inputString == "Edit" || inputString == "2")
	{
		CViewManager::Get().SetNextView(make_shared<CEditView>());
	}
	else
	{
		cout << "The command cannot be processed." << endl;
	}

	return true;
}