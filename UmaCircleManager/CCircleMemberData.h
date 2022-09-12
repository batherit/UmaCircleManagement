#pragma once

#include "Common.h"

class CCircleMemberData
{
public:
	CCircleMemberData()
	{}
	explicit CCircleMemberData(const string& InMemberName)
		:
		MemberName(InMemberName)
	{}
	CCircleMemberData(const string& InMemberName, int InFanNumber)
		:
		MemberName(InMemberName),
		FanNumber(InFanNumber)
	{}

	inline const string& GetMemberName() const { return MemberName; }
	inline int GetFanNumber() const { return FanNumber; }

	inline bool operator==(const CCircleMemberData& InData) const
	{
		if (IsValid() && InData.IsValid())
			return operator==(InData.GetMemberName());
		else
			return false;
	}

	inline bool operator==(const string& InMemberName) const
	{
		return MemberName == InMemberName;
	}

	inline bool operator<(const CCircleMemberData& InData) const
	{
		if(IsValid() && InData.IsValid())
			return MemberName < InData.MemberName;
		return false;
	}
	inline bool IsValid() const { return MemberName.length() > 0; }

private:
	string MemberName;
	int FanNumber = 0;
};
