#include "CEditCircleNameView.h"
#include "CInputManager.h"
#include "CViewManager.h"

void CEditCircleNameView::OnOpen()
{
	CView::OnOpen();
}

bool CEditCircleNameView::UpdateView()
{
	cout << "Input src name : " << endl;
	CInputManager::Get().ProcessInput();
	const string srcName = CInputManager::Get().GetInputString();

	cout << "Input dest name : " << endl;
	CInputManager::Get().ProcessInput();
	const string destName = CInputManager::Get().GetInputString();

	cout << "The command will change the source name to the dead name. Do you agree? (Y/N) : " << endl;
	CInputManager::Get().ProcessInput();
	const string isOk = CInputManager::Get().GetInputString();

	if (isOk == "Y" || isOk == "y")
	{
		// TODO : change src name to dest name
		CViewManager::Get().ClearView();
		cout << "Completed." << endl;
		CViewManager::Get().PauseView();
		CViewManager::Get().ClearView();
	}
	else
	{
		cout << "1. Continue / 2. Back" << endl;
		CInputManager::Get().ProcessInput();
		const string input = CInputManager::Get().GetInputString();

		if (input == "Continue" || input == "1")
		{
			CViewManager::Get().ClearView();
		}
		else
		{
			return CViewManager::Get().BackView();
		}
	}

	return true;
}