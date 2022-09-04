#pragma once

#include "Common.h"
#include "CCircleMemberData.h"

using CircleMemberDataKeyList = set<CCircleMemberData>;
using CircleMemberDataList = vector<CCircleMemberData>;
using CircleMemberDataWithDate = pair<FileDate, CCircleMemberData>;
using CircleMemberDataHistory = map<FileDate, CCircleMemberData>;
using CircleMemberDataHistoryList = vector<CircleMemberDataHistory>;
using CircleMemberDataListWithDate = pair<FileDate, CircleMemberDataList>;
using CircleMemberDataMapWithDate = map<FileDate, CircleMemberDataList>;

class CCircleMemberDatabase
{
	GENERATED_SINGLETON(CCircleMemberDatabase)

public:
	void LoadDatas();

	inline const CircleMemberDataKeyList& GetCircleMemberDataKeyList() const 
	{ 
		return MemberDataKeyList;
	}

	inline const CircleMemberDataHistoryList& GetCircleMemberDataHistoryList() const
	{
		return MemberHistoryList;
	}

	bool GetCircleMembersInfoByOldestData(OUT FileDate& OutDate, OUT CircleMemberDataList& OutInfo) const
	{
		const auto& iter = MemberDataMap.begin();

		if (iter == MemberDataMap.end())
		{
			return false;
		}
		else
		{
			OutDate = (*iter).first;
			OutInfo = (*iter).second;
			return true;
		}
	}

	bool GetCircleMembersInfoByLatestDate(OUT FileDate& OutDate, OUT CircleMemberDataList& OutInfo) const
	{
		const auto& iter = MemberDataMap.rbegin();

		if (iter == MemberDataMap.rend())
		{
			return false;
		}
		else
		{
			OutDate = (*iter).first;
			OutInfo = (*iter).second;
			return true;
		}
	}

	bool GetCircleMembersInfoByDate(const FileDate InDate, OUT CircleMemberDataList& OutInfo) const
	{
		const auto& iter = MemberDataMap.find(InDate);

		if (iter == MemberDataMap.end())
		{
			return false;
		}
		else
		{
			OutInfo = (*iter).second;
			return true;
		}
	}

	bool GetCircleMembersInfoByPreDate(const FileDate InDate, OUT FileDate& OutPrevData, OUT CircleMemberDataList& OutInfo) const
	{
		auto iter = MemberDataMap.find(InDate);

		if (MemberDataMap.begin() != iter)
			--iter;
		else
			return false;

		OutPrevData = (*iter).first;
		OutInfo = (*iter).second;
		return true;
	}

	bool GetCircleMemberHistory(const CCircleMemberData& InData, OUT CircleMemberDataHistory& OutMemberHistory) const
	{
		for (const CircleMemberDataHistory& memberHistory : MemberHistoryList)
		{
			for (const auto& iter : memberHistory)
			{
				if (iter.second == InData)
				{
					OutMemberHistory = memberHistory;
					return true;
				}
				else
					continue;
			}
		}
		return false;
	}

private:
	inline void ClearDatas()
	{
		MemberDataMap.clear();
		MemberHistoryList.clear();
		MemberDataKeyList.clear();
	}

private:
	CircleMemberDataMapWithDate MemberDataMap;
	CircleMemberDataHistoryList MemberHistoryList;
	CircleMemberDataKeyList MemberDataKeyList;
};

