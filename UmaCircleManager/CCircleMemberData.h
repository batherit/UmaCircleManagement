#pragma once

#include "Common.h"

class CCircleMemberData
{
public:
	CCircleMemberData()
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
			return MemberName == InData.MemberName;
		else
			return false;
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
