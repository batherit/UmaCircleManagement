#pragma once
#include "CView.h"
#include "CCircleMemberDatabase.h"

class CAnalysisView :
    public CView
{
public:
    virtual void OnOpen() override;
    virtual bool UpdateView() override;

private:
    static void PrintAnalysisFromHistory(const CircleMemberDataHistory& InMemberHistory);
};

