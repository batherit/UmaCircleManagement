#pragma once
#include "CView.h"
class CMainView :
    public CView
{
    virtual void OnOpen() override;
    virtual bool UpdateView() override;
};

