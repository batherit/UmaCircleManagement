#pragma once
#include "CView.h"
#include "CCircleMemberDatabase.h"
class CEditView : public CView
{
public:
    virtual void OnOpen() override;
    virtual bool UpdateView() override;
};

