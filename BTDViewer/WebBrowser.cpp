//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   WebBrowser.cpp
//    Author:      Streamlet
//    Create Time: 2010-11-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "WebBrowser.h"
#include <Loki/ScopeGuard.h>

WebBrowser::WebBrowser()
    : m_ulRef(0u), m_hWnd(NULL), m_bInPlaced(FALSE),
      m_pStorage(NULL), m_pOleObj(NULL), m_pInPlaceObj(NULL),
      m_pWB2(NULL), m_pHtmlDoc2(NULL), m_pHtmlDoc3(NULL), m_pHtmlWnd2(NULL), m_pHtmlEvent(NULL)
{

}

WebBrowser::~WebBrowser()
{
    Destroy();
}


// IUnknown methods
HRESULT STDMETHODCALLTYPE WebBrowser::QueryInterface( 
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
{
    *ppvObject = NULL;

    if (riid == IID_IUnknown ||
        riid == IID_IDispatch ||
        riid == IID_IOleClientSite ||
        riid == IID_IOleWindow ||
        riid == IID_IOleInPlaceSite ||
        riid == IID_IOleInPlaceUIWindow ||
        riid == IID_IDocHostUIHandler)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }
    
    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE WebBrowser::AddRef( void)
{
    return (ULONG)InterlockedIncrement(&m_ulRef);
}


ULONG STDMETHODCALLTYPE WebBrowser::Release( void)
{
    ULONG ulRef = (ULONG)InterlockedDecrement(&m_ulRef);

//     if (ulRef == 0)
//     {
//         delete this;
//     }

    return ulRef;
}

// IDispatch Methods
HRESULT STDMETHODCALLTYPE WebBrowser::GetTypeInfoCount( 
    /* [out] */ __RPC__out UINT *pctinfo)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetTypeInfo( 
    /* [in] */ UINT iTInfo,
    /* [in] */ LCID lcid,
    /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetIDsOfNames( 
    /* [in] */ __RPC__in REFIID riid,
    /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
    /* [range][in] */ __RPC__in_range(0,16384) UINT cNames,
    /* [in] */ LCID lcid,
    /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
    return E_NOTIMPL;
}

/* [local] */ HRESULT STDMETHODCALLTYPE WebBrowser::Invoke( 
    /* [in] */ DISPID dispIdMember,
    /* [in] */ REFIID riid,
    /* [in] */ LCID lcid,
    /* [in] */ WORD wFlags,
    /* [out][in] */ DISPPARAMS *pDispParams,
    /* [out] */ VARIANT *pVarResult,
    /* [out] */ EXCEPINFO *pExcepInfo,
    /* [out] */ UINT *puArgErr)
{
    return E_NOTIMPL;
}

// IOleClientSite methods
HRESULT STDMETHODCALLTYPE WebBrowser::SaveObject( void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetMoniker( 
    /* [in] */ DWORD dwAssign,
    /* [in] */ DWORD dwWhichMoniker,
    /* [out] */ __RPC__deref_out_opt IMoniker **ppmk)
{
    *ppmk = NULL;
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetContainer( 
    /* [out] */ __RPC__deref_out_opt IOleContainer **ppContainer)
{
    *ppContainer = NULL;
    return E_FAIL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::ShowObject( void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::OnShowWindow( 
    /* [in] */ BOOL fShow)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::RequestNewObjectLayout( void)
{
    return S_OK;
}


// IOleWindow methods
/* [input_sync] */ HRESULT STDMETHODCALLTYPE WebBrowser::GetWindow( 
    /* [out] */ __RPC__deref_out_opt HWND *phwnd)
{
    *phwnd = m_hWnd;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::ContextSensitiveHelp( 
    /* [in] */ BOOL fEnterMode)
{
    return E_NOTIMPL;
}


// IOleInPlaceSite methods
HRESULT STDMETHODCALLTYPE WebBrowser::CanInPlaceActivate( void)
{
    if (m_bInPlaced)
    {
        return S_FALSE;
    }
    
    m_bInPlaced = TRUE;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::OnInPlaceActivate( void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::OnUIActivate( void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetWindowContext( 
    /* [out] */ __RPC__deref_out_opt IOleInPlaceFrame **ppFrame,
    /* [out] */ __RPC__deref_out_opt IOleInPlaceUIWindow **ppDoc,
    /* [out] */ __RPC__out LPRECT lprcPosRect,
    /* [out] */ __RPC__out LPRECT lprcClipRect,
    /* [out][in] */ __RPC__inout LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
    *ppFrame = (IOleInPlaceFrame*)this;
    AddRef();

    *ppDoc = NULL;

    GetClientRect(m_hWnd, lprcPosRect);
    GetClientRect(m_hWnd, lprcClipRect);

    lpFrameInfo->cb = sizeof(OLEINPLACEFRAMEINFO);
    lpFrameInfo->fMDIApp = FALSE;
    lpFrameInfo->hwndFrame = GetParent(m_hWnd);
    lpFrameInfo->haccel = NULL;
    lpFrameInfo->cAccelEntries = 0u;
    
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::Scroll( 
    /* [in] */ SIZE scrollExtant)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::OnUIDeactivate( 
    /* [in] */ BOOL fUndoable)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::OnInPlaceDeactivate( void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::DiscardUndoState( void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::DeactivateAndUndo( void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::OnPosRectChange( 
    /* [in] */ __RPC__in LPCRECT lprcPosRect)
{
    return S_OK;
}

// IOleInPlaceUIWindow methods
/* [input_sync] */ HRESULT STDMETHODCALLTYPE WebBrowser::GetBorder( 
    /* [out] */ __RPC__out LPRECT lprectBorder)
{
    GetClientRect(m_hWnd, lprectBorder);

    return S_OK;
}

/* [input_sync] */ HRESULT STDMETHODCALLTYPE WebBrowser::RequestBorderSpace( 
    /* [unique][in] */ __RPC__in_opt LPCBORDERWIDTHS pborderwidths)
{
    return S_OK;
}

/* [input_sync] */ HRESULT STDMETHODCALLTYPE WebBrowser::SetBorderSpace( 
    /* [unique][in] */ __RPC__in_opt LPCBORDERWIDTHS pborderwidths)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebBrowser::SetActiveObject( 
    /* [unique][in] */ __RPC__in_opt IOleInPlaceActiveObject *pActiveObject,
    /* [unique][string][in] */ __RPC__in_opt_string LPCOLESTR pszObjName)
{
    return S_OK;
}

// IOleInPlaceFrame methods
HRESULT STDMETHODCALLTYPE WebBrowser::InsertMenus( 
    /* [in] */ __RPC__in HMENU hmenuShared,
    /* [out][in] */ __RPC__inout LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
    return E_NOTIMPL;
}

/* [input_sync] */ HRESULT STDMETHODCALLTYPE WebBrowser::SetMenu( 
    /* [in] */ __RPC__in HMENU hmenuShared,
    /* [in] */ __RPC__in HOLEMENU holemenu,
    /* [in] */ __RPC__in HWND hwndActiveObject)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::RemoveMenus( 
    /* [in] */ __RPC__in HMENU hmenuShared)
{
    return E_NOTIMPL;
}

/* [input_sync] */ HRESULT STDMETHODCALLTYPE WebBrowser::SetStatusText( 
    /* [unique][in] */ __RPC__in_opt LPCOLESTR pszStatusText)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::EnableModeless( 
    /* [in] */ BOOL fEnable)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::TranslateAccelerator( 
    /* [in] */ __RPC__in LPMSG lpmsg,
    /* [in] */ WORD wID)
{
    return E_NOTIMPL;
}

// IDocHostUIHandler methods
HRESULT STDMETHODCALLTYPE WebBrowser::ShowContextMenu( 
    /* [in] */ DWORD dwID,
    /* [in] */ POINT *ppt,
    /* [in] */ IUnknown *pcmdtReserved,
    /* [in] */ IDispatch *pdispReserved)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetHostInfo( 
    /* [out][in] */ DOCHOSTUIINFO *pInfo)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::ShowUI( 
    /* [in] */ DWORD dwID,
    /* [in] */ IOleInPlaceActiveObject *pActiveObject,
    /* [in] */ IOleCommandTarget *pCommandTarget,
    /* [in] */ IOleInPlaceFrame *pFrame,
    /* [in] */ IOleInPlaceUIWindow *pDoc)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::HideUI( void)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::UpdateUI( void)
{
    return E_NOTIMPL;
}

// HRESULT STDMETHODCALLTYPE WebBrowser::EnableModeless( 
//     /* [in] */ BOOL fEnable)
// {
//     return E_NOTIMPL;
// }


HRESULT STDMETHODCALLTYPE WebBrowser::OnDocWindowActivate( 
    /* [in] */ BOOL fActivate)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::OnFrameWindowActivate( 
    /* [in] */ BOOL fActivate)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::ResizeBorder( 
    /* [in] */ LPCRECT prcBorder,
    /* [in] */ IOleInPlaceUIWindow *pUIWindow,
    /* [in] */ BOOL fRameWindow)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::TranslateAccelerator( 
    /* [in] */ LPMSG lpMsg,
    /* [in] */ const GUID *pguidCmdGroup,
    /* [in] */ DWORD nCmdID)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetOptionKeyPath( 
    /* [annotation][out] */ 
    __out  LPOLESTR *pchKey,
    /* [in] */ DWORD dw)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetDropTarget( 
    /* [in] */ IDropTarget *pDropTarget,
    /* [out] */ IDropTarget **ppDropTarget)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::GetExternal( 
    /* [out] */ IDispatch **ppDispatch)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::TranslateUrl( 
    /* [in] */ DWORD dwTranslate,
    /* [annotation][in] */ 
    __in __nullterminated  OLECHAR *pchURLIn,
    /* [annotation][out] */ 
    __out  OLECHAR **ppchURLOut)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebBrowser::FilterDataObject( 
    /* [in] */ IDataObject *pDO,
    /* [out] */ IDataObject **ppDORet)
{
    return E_NOTIMPL;
}

BOOL WebBrowser::Create(HWND hWnd)
{
    if (m_hWnd != NULL)
    {
        return FALSE;
    }

    Destroy();

    m_hWnd = hWnd;

    Loki::ScopeGuard sgDestroy = Loki::MakeObjGuard(*this, &WebBrowser::Destroy);

    HRESULT hr = S_OK;

    hr = OleInitialize(NULL);

    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = StgCreateDocfile(NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE, 0, &m_pStorage);

    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = OleCreate(CLSID_WebBrowser, IID_IOleObject, OLERENDER_DRAW, NULL, this, m_pStorage, (LPVOID *)&m_pOleObj);

    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = m_pOleObj->QueryInterface(IID_IOleInPlaceObject, (LPVOID *)&m_pInPlaceObj);

    if (FAILED(hr))
    {
        return FALSE;
    }

    RECT rect = {};
    GetClientRect(hWnd, &rect);
    hr = m_pOleObj->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, this, 0, m_hWnd, &rect);

    if (FAILED(hr))
    {
        return FALSE;
    }
    
    hr = m_pOleObj->QueryInterface(IID_IWebBrowser2, (LPVOID *)&m_pWB2);

    if (FAILED(hr))
    {
        return FALSE;
    }

    m_hWnd = hWnd;

    sgDestroy.Dismiss();

    return TRUE;
}

void WebBrowser::Destroy()
{
    if (m_pWB2 != NULL)
    {
        m_pWB2->Release();
        m_pWB2 = NULL;
    }

    if (m_pInPlaceObj != NULL)
    {
        m_pInPlaceObj->Release();
        m_pInPlaceObj = NULL;
    }

    if (m_pOleObj != NULL)
    {
        m_pOleObj->Release();
        m_pOleObj = NULL;
    }

    if (m_pStorage != NULL)
    {
        m_pStorage->Release();
        m_pStorage = NULL;
    }

    m_hWnd = NULL;

    OleUninitialize();
}

void WebBrowser::Navigate(LPCTSTR lpUrl)
{

}
