#include "CEditCircleNameView.h"
#include "CInputManager.h"
#include "CViewManager.h"
#include "CCircleMemberDatabase.h"

void CEditCircleNameView::OnOpen()
{
	CView::OnOpen();
}

bool CEditCircleNameView::UpdateView()
{
	cout << "Input src name : ";
	CInputManager::Get().ProcessInput();
	const string srcName = CInputManager::Get().GetInputString();

	cout << "Input dest name : ";
	CInputManager::Get().ProcessInput();
	const string destName = CInputManager::Get().GetInputString();

	cout << "Do you agree to change? (y/n) : ";
	CInputManager::Get().ProcessInput();
	const string isOk = CInputManager::Get().GetInputString();

	if (isOk == "Y" || isOk == "y")
	{
		// TODO : change src name to dest name
		CCircleMemberDatabase::Get().ProcessCommand(make_shared<CmdChangeCircleMemberName>(srcName, destName));

		CViewManager::Get().ClearView();
		cout << "Completed." << endl;
		CViewManager::Get().PauseView();
		CViewManager::Get().ClearView();
	}

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

	return true;
}