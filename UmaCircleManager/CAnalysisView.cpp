#include "CAnalysisView.h"
#include "CInputManager.h"
#include "CViewManager.h"
#include "CMainView.h"
#include "CToolBox.h"

void CAnalysisView::OnOpen()
{
	CView::OnOpen();

	system("cls");
}

bool CAnalysisView::UpdateView()
{
	const CCircleMemberDatabase& databaseInst = CCircleMemberDatabase::Get();
	const CircleMemberDataKeyList& keyList = databaseInst.GetCircleMemberDataKeyList();
	
	for (const auto& key : keyList)
	{
		CircleMemberDataHistory memberHistory;
		if (!databaseInst.GetCircleMemberHistory(key, memberHistory))
		{
			continue;
		}
			
		cout << key.GetMemberName() << endl;
		PrintAnalysisFromHistory(memberHistory);
	}
    cout << "1. Main" << endl;

	CInputManager::Get().ProcessInput();

	const InputString& inputString = CInputManager::Get().GetInputString();
	if (inputString == "Main" || inputString == "1")
	{
		CViewManager::Get().SetNextView(make_shared<CMainView>());
	}

    return true;
}

void CAnalysisView::PrintAnalysisFromHistory(const CircleMemberDataHistory& InMemberHistory)
{
	if (InMemberHistory.size() > 1)
	{
		auto preIter = InMemberHistory.begin();
		auto curIter = next(preIter);
		if (preIter->second.IsValid())
			cout << left << setw(15) << preIter->first << setw(15) << CToolBox::ToNumberWithComma(preIter->second.GetFanNumber()) << endl;
		else
			cout << left << setw(15) << preIter->first << setw(15) << "Not data" << endl;

		do {
			const bool preDataValid = preIter->second.IsValid();
			const bool curDataValid = curIter->second.IsValid();
			if (preDataValid && curDataValid)
			{
				// keep
				cout << left << setw(15) << curIter->first << setw(15) << CToolBox::ToNumberWithComma(curIter->second.GetFanNumber())
					<< " /Up " << CToolBox::ToNumberWithComma(curIter->second.GetFanNumber() - preIter->second.GetFanNumber()) << endl;
			}
			else if (curDataValid)
			{
				// new
				cout << left << setw(15) << curIter->first << setw(15) << CToolBox::ToNumberWithComma(curIter->second.GetFanNumber())
					<< " new member" << endl;
			}
			else if (preDataValid)
			{
				// retired
				cout << left << setw(15) << curIter->first << "retired" << endl;
			}
			else
			{
				// not data
				cout << left << setw(15) << curIter->first << setw(15) << "Not data" << endl;
			}

			preIter = curIter;
			++curIter;
		} while (curIter != InMemberHistory.end());
	}
	else if (InMemberHistory.size() == 1)
	{
		const auto& iter = InMemberHistory.begin();
		if ((*iter).second.IsValid())
		{
			cout << setw(10) << iter->second.GetFanNumber() << " new member" << endl;
		}
		else
		{
			cout << setw(10) << " retired" << endl;
		}
	}
	else
	{
		cout << setw(10) << " No member data found." << endl;
	}
	cout << "<<" << endl;
}
