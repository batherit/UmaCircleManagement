#include "CCircleMemberDatabase.h"
#include "CToolBox.h"

const string CCircleMemberDatabase::folderPath = ".\\CircleMemberDatabase\\";

void CCircleMemberDatabase::LoadDatas()
{
	ClearDatas();

	// create data map
	//string folderPath(".\\CircleMemberDatabase\\");

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
                const string fileName = fd.name;
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


	// create member history list

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
			MemberDataKeyList.insert(circleMemberDataWithDate.second.begin(), circleMemberDataWithDate.second.end());
		}

		for (const auto& memberDataKey : MemberDataKeyList)
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


    return false;
}
