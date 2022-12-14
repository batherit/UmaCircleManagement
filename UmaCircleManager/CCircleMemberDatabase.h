#pragma once

#include "Common.h"
#include "CCircleMemberData.h"

using CircleMemberDataKey = CCircleMemberData;
using CircleMemberDataKeySet = set<CircleMemberDataKey>;
using CircleMemberDataList = vector<CCircleMemberData>;
using CircleMemberDataWithDate = pair<FileDate, CCircleMemberData>;
using CircleMemberDataHistory = map<FileDate, CCircleMemberData>;
using CircleMemberDataHistoryList = vector<CircleMemberDataHistory>;
using CircleMemberDataListWithDate = pair<FileDate, CircleMemberDataList>;
using CircleMemberDataMapWithDate = map<FileDate, CircleMemberDataList>;

struct CmdBase
{
public:
	virtual bool Process() PURE;
};

struct CmdChangeCircleMemberName : public CmdBase
{
public:
	CmdChangeCircleMemberName(const string& InSrcName, const string& InDestName)
		:
		SrcName(InSrcName),
		DestName(InDestName)
	{}

	virtual bool Process() override;

private:
	string SrcName;
	string DestName;
};

class CCircleMemberDatabase
{
	GENERATED_SINGLETON(CCircleMemberDatabase)

	friend CmdChangeCircleMemberName;

public:
	void LoadDatas();
	inline bool ProcessCommand(const shared_ptr<CmdBase>& InCmdPtr)
	{
		if (InCmdPtr)
		{
			return InCmdPtr->Process();
		}
		return false;
	}

	inline const CircleMemberDataKeySet& GetCircleMemberDataKeySet() const 
	{ 
		return MemberDataKeySet;
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
	void CreateMemberHistoryList();

	inline void ClearDatas()
	{
		MemberDataMap.clear();
		MemberHistoryList.clear();
		MemberDataKeySet.clear();
	}

private:
	// static
	const static string folderPath;

	// based
	CircleMemberDataMapWithDate MemberDataMap;

	// derived
	CircleMemberDataKeySet MemberDataKeySet;
	CircleMemberDataHistoryList MemberHistoryList;
};

