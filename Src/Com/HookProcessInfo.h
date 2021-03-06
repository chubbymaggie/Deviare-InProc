﻿/*
 * Copyright (C) 2010-2014 Nektra S.A., Buenos Aires, Argentina.
 * All rights reserved.
 *
 **/

#pragma once

#include "resource.h"       // main symbols
#if _MSC_VER >= 1700
  #ifdef _WIN64
    #include "DeviareLiteCOM_i64_vs2012.h"
  #else //_WIN64
    #include "DeviareLiteCOM_i_vs2012.h"
  #endif //_WIN64
#elif  _MSC_VER >= 1600
  #ifdef _WIN64
    #include "DeviareLiteCOM_i64_vs2010.h"
  #else //_WIN64
    #include "DeviareLiteCOM_i_vs2010.h"
  #endif //_WIN64
#else
  #ifdef _WIN64
    #include "DeviareLiteCOM_i64_vs2008.h"
  #else //_WIN64
    #include "DeviareLiteCOM_i_vs2008.h"
  #endif //_WIN64
#endif
#include "CustomRegistryMap.h"
#include "DllMain.h"
#include "..\..\Include\NktHookLib.h"

//-----------------------------------------------------------

extern HINSTANCE hDllInst;

//-----------------------------------------------------------

// CNktHookProcessInfoImpl
class ATL_NO_VTABLE CNktHookProcessInfoImpl : public CComObjectRootEx<CComMultiThreadModel>,
                                              public CComCoClass<CNktHookProcessInfoImpl, &CLSID_NktHookProcessInfo>,
                                              public IObjectSafetyImpl<CNktHookProcessInfoImpl,
                                                                       INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
                                              public IDispatchImpl<INktHookProcessInfo, &IID_INktHookProcessInfo,
                                                                   &LIBID_DeviareLite, 1, 0>
{
public:
  CNktHookProcessInfoImpl() : CComObjectRootEx<CComMultiThreadModel>(),
                       CComCoClass<CNktHookProcessInfoImpl, &CLSID_NktHookProcessInfo>(),
                       IObjectSafetyImpl<CNktHookProcessInfoImpl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>(),
                       IDispatchImpl<INktHookProcessInfo, &IID_INktHookProcessInfo, &LIBID_DeviareLite, 1, 0>()
    {
    memset(&sProcInfo, 0, sizeof(sProcInfo));
    return;
    };

  ~CNktHookProcessInfoImpl()
    {
    if (sProcInfo.hThread != NULL)
      ::CloseHandle(sProcInfo.hThread);
    if (sProcInfo.hProcess != NULL)
      ::CloseHandle(sProcInfo.hProcess);
    return;
    };

  DECLARE_REGISTRY_RESOURCEID_EX(IDR_INTERFACEREGISTRAR, L"DeviareLite.NktHookProcessInfo", L"1",
                                 L"NktHookProcessInfo Class", CLSID_NktHookProcessInfo, LIBID_DeviareLite, L"Neutral")

  BEGIN_COM_MAP(CNktHookProcessInfoImpl)
    COM_INTERFACE_ENTRY(INktHookProcessInfo)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IObjectSafety)
    COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, cUnkMarshaler.p)
  END_COM_MAP()

  // ISupportsErrorInfo
  STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  DECLARE_GET_CONTROLLING_UNKNOWN()

  HRESULT FinalConstruct()
    {
    return ::CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &(cUnkMarshaler.p));
    };

  void FinalRelease()
    {
    cUnkMarshaler.Release();
    return;
    };

public:
  STDMETHOD(get_ProcessHandle)(__out my_ssize_t *procHandle);
  STDMETHOD(get_ThreadHandle)(__out my_ssize_t *threadHandle);
  STDMETHOD(get_ProcessId)(__out LONG *pid);
  STDMETHOD(get_ThreadId)(__out LONG *tid);

private:
  friend class CNktHookLibImpl;

  PROCESS_INFORMATION sProcInfo;
  //----
  CComPtr<IUnknown> cUnkMarshaler;
};

//-----------------------------------------------------------

OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(__uuidof(NktHookProcessInfo), CNktHookProcessInfoImpl)
