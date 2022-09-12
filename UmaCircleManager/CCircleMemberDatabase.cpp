#include "CCircleMemberDatabase.h"
#include "CToolBox.h"
#include "CInputManager.h"

const string CCircleMemberDatabase::folderPath = ".\\CircleMemberDatabase\\";

void CCircleMemberDatabase::LoadDatas()
{
	ClearDatas();

    _finddata_t fd;

    char filePath[256];
    sprintf_s(filePath, sizeof(filePath), "%s%s", folderPath.c_str(), "*.*");

    intptr_t hFind = _findfirst(filePath, &fd);

    if (hFind != -1)
    {
        do
        {
            if (!(fd.attrib & FILE_ATTRIBUTE_DIRECTORY))
            {
                const string fileName = fd.name; // Ex fileName : 20220815.txt
                ifstream fileStream(folderPath + fileName);
                if (!fileStream)
                {
                    cout << "That file " << fileName.c_str() << " doesn't exist." << endl;
                    fileStream.close();
                    break;
                }
                
                const size_t findIndex = fileName.find(".");
                const string fileNameNotExtension = fileName.substr(0, findIndex);
                const FileDate fileDate = stoi(fileNameNotExtension);                
                CircleMemberDataList& dataList = MemberDataMap[fileDate];
                dataList.clear();

                char dataLine[1024];
                while (!fileStream.eof())
                {
                    fileStream.getline(dataLine, sizeof(dataLine));
                    const string dataLineString(CToolBox::UTF8ToANSI(dataLine));
                    const size_t findIndex = dataLineString.find(" ");
                    const string name = dataLineString.substr(0, findIndex);
                    const int fanNum = stoi(dataLineString.substr(findIndex + 1, dataLineString.size()));
                    dataList.push_back(CCircleMemberData(name, fanNum));
                }

                fileStream.close();
            }
        } while (_findnext(hFind, &fd) != -1);
        _findclose(hFind);

        // map은 기본적으로 오름차순 정렬.
    }

    CreateMemberHistoryList();
}

void CCircleMemberDatabase::CreateMemberHistoryList()
{
    MemberDataKeySet.clear();
    MemberHistoryList.clear();

    if (MemberDataMap.empty())
    {
        cout << "Can't create member history list because member data map is empty." << endl;
        return;
    }

    FileDate fileDate;
    CircleMemberDataList circleMemberDataList;
    CircleMemberDataMapWithDate circleMemberDataMap;
    if (GetCircleMembersInfoByLatestDate(fileDate, circleMemberDataList))
    {
        do {
            circleMemberDataMap[fileDate] = circleMemberDataList;
        } while (GetCircleMembersInfoByPreDate(fileDate, fileDate, circleMemberDataList));

        for (const auto& circleMemberDataWithDate : circleMemberDataMap)
        {
            MemberDataKeySet.insert(circleMemberDataWithDate.second.begin(), circleMemberDataWithDate.second.end());
        }

        for (const auto& memberDataKey : MemberDataKeySet)
        {
            CircleMemberDataHistory memberHistory;
            for (const auto& circleMemberDataWithDate : circleMemberDataMap)
            {
                const auto& iter = find(circleMemberDataWithDate.second.begin(), circleMemberDataWithDate.second.end(), memberDataKey);

                if (iter != circleMemberDataWithDate.second.end())
                {
                    memberHistory[circleMemberDataWithDate.first] = *iter;
                }
                else
                {
                    memberHistory[circleMemberDataWithDate.first] = CCircleMemberData();
                }
            }
            MemberHistoryList.push_back(memberHistory);
        }
    }
}

// cmd
bool CmdChangeCircleMemberName::Process()
{
    CCircleMemberDatabase& dataBaseInst = CCircleMemberDatabase::Get();

    for (auto& circleMemberDataWithDate : dataBaseInst.MemberDataMap)
    {
        const auto& beginIter = circleMemberDataWithDate.second.begin();
        const auto& endIter = circleMemberDataWithDate.second.end();
        const auto& srcIter = find(beginIter, endIter, SrcName);
        const auto& destIter = find(beginIter, endIter, DestName);

        if (srcIter != endIter && destIter != endIter)
        {
            cout << "[Collision]" << endl;
            cout << "The src fan number of " << srcIter->GetMemberName() << " is " << srcIter->GetFanNumber() << "." << endl;
            cout << "The dest fan number of " << destIter->GetMemberName() << " is " << destIter->GetFanNumber() << "." << endl;
            cout << "What fan number data will you merge into? (src/dest) :";

            while (true)
            {
                CInputManager::Get().ProcessInput();
                const string& inputString = CInputManager::Get().GetInputString();

                if (inputString == "src")
                {
                    const CCircleMemberData memberData = CCircleMemberData(DestName, srcIter->GetFanNumber());
                    circleMemberDataWithDate.second.erase(srcIter);
                    circleMemberDataWithDate.second.push_back(memberData);
                    break;
                }
                else if (inputString == "dest")
                {
                    const CCircleMemberData memberData = CCircleMemberData(DestName, destIter->GetFanNumber());
                    circleMemberDataWithDate.second.erase(srcIter);
                    circleMemberDataWithDate.second.push_back(memberData);
                    break;
                }
                else
                {
                    cout << "Please re-enter. (src/dest) : " << endl;
                }
            }
            
        }
        else if (srcIter != endIter)
        {
            const CCircleMemberData memberData = CCircleMemberData(DestName, srcIter->GetFanNumber());
            circleMemberDataWithDate.second.erase(srcIter);
            circleMemberDataWithDate.second.push_back(memberData);
        }
    }

    dataBaseInst.CreateMemberHistoryList();

    return true;
}
