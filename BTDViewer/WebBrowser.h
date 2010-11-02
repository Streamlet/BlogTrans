//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   WebBrowser.h
//    Author:      Streamlet
//    Create Time: 2010-11-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __WEBBROWSER_H_FD0A3E73_BC52_4E71_8329_F1A766705836_INCLUDED__
#define __WEBBROWSER_H_FD0A3E73_BC52_4E71_8329_F1A766705836_INCLUDED__


#include <exdisp.h>
#include <mshtml.h>
#include <mshtmhst.h>


class WebBrowser : public IDispatch,
                   public IOleClientSite,
                   public IOleInPlaceSite,
                   public IOleInPlaceFrame,
                   public IDocHostUIHandler
{
public:
    WebBrowser();
    ~WebBrowser();

public:
    // IUnknown methods
    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject);

    virtual ULONG STDMETHODCALLTYPE AddRef( void);

    virtual ULONG STDMETHODCALLTYPE Release( void);

    // IDispatch Methods
    virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( 
        /* [out] */ __RPC__out UINT *pctinfo);

    virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( 
        /* [in] */ UINT iTInfo,
        /* [in] */ LCID lcid,
        /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo);

    virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames( 
        /* [in] */ __RPC__in REFIID riid,
        /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
        /* [range][in] */ __RPC__in_range(0,16384) UINT cNames,
        /* [in] */ LCID lcid,
        /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId);

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke( 
        /* [in] */ DISPID dispIdMember,
        /* [in] */ REFIID riid,
        /* [in] */ LCID lcid,
        /* [in] */ WORD wFlags,
        /* [out][in] */ DISPPARAMS *pDispParams,
        /* [out] */ VARIANT *pVarResult,
        /* [out] */ EXCEPINFO *pExcepInfo,
        /* [out] */ UINT *puArgErr);

    // IOleClientSite methods
    virtual HRESULT STDMETHODCALLTYPE SaveObject( void);

    virtual HRESULT STDMETHODCALLTYPE GetMoniker( 
        /* [in] */ DWORD dwAssign,
        /* [in] */ DWORD dwWhichMoniker,
        /* [out] */ __RPC__deref_out_opt IMoniker **ppmk);

    virtual HRESULT STDMETHODCALLTYPE GetContainer( 
        /* [out] */ __RPC__deref_out_opt IOleContainer **ppContainer);

    virtual HRESULT STDMETHODCALLTYPE ShowObject( void);

    virtual HRESULT STDMETHODCALLTYPE OnShowWindow( 
        /* [in] */ BOOL fShow);

    virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout( void);


    // IOleWindow methods
    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow( 
        /* [out] */ __RPC__deref_out_opt HWND *phwnd);

    virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp( 
        /* [in] */ BOOL fEnterMode);


    // IOleInPlaceSite methods
    virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate( void);

    virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate( void);

    virtual HRESULT STDMETHODCALLTYPE OnUIActivate( void);

    virtual HRESULT STDMETHODCALLTYPE GetWindowContext( 
        /* [out] */ __RPC__deref_out_opt IOleInPlaceFrame **ppFrame,
        /* [out] */ __RPC__deref_out_opt IOleInPlaceUIWindow **ppDoc,
        /* [out] */ __RPC__out LPRECT lprcPosRect,
        /* [out] */ __RPC__out LPRECT lprcClipRect,
        /* [out][in] */ __RPC__inout LPOLEINPLACEFRAMEINFO lpFrameInfo);

    virtual HRESULT STDMETHODCALLTYPE Scroll( 
        /* [in] */ SIZE scrollExtant);

    virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate( 
        /* [in] */ BOOL fUndoable);

    virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate( void);

    virtual HRESULT STDMETHODCALLTYPE DiscardUndoState( void);

    virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo( void);

    virtual HRESULT STDMETHODCALLTYPE OnPosRectChange( 
        /* [in] */ __RPC__in LPCRECT lprcPosRect);

    // IOleInPlaceUIWindow methods
    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetBorder( 
        /* [out] */ __RPC__out LPRECT lprectBorder);

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE RequestBorderSpace( 
        /* [unique][in] */ __RPC__in_opt LPCBORDERWIDTHS pborderwidths);

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetBorderSpace( 
        /* [unique][in] */ __RPC__in_opt LPCBORDERWIDTHS pborderwidths);

    virtual HRESULT STDMETHODCALLTYPE SetActiveObject( 
        /* [unique][in] */ __RPC__in_opt IOleInPlaceActiveObject *pActiveObject,
        /* [unique][string][in] */ __RPC__in_opt_string LPCOLESTR pszObjName);

    // IOleInPlaceFrame methods
    virtual HRESULT STDMETHODCALLTYPE InsertMenus( 
        /* [in] */ __RPC__in HMENU hmenuShared,
        /* [out][in] */ __RPC__inout LPOLEMENUGROUPWIDTHS lpMenuWidths);

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetMenu( 
        /* [in] */ __RPC__in HMENU hmenuShared,
        /* [in] */ __RPC__in HOLEMENU holemenu,
        /* [in] */ __RPC__in HWND hwndActiveObject);

    virtual HRESULT STDMETHODCALLTYPE RemoveMenus( 
        /* [in] */ __RPC__in HMENU hmenuShared);

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetStatusText( 
        /* [unique][in] */ __RPC__in_opt LPCOLESTR pszStatusText);

    virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
        /* [in] */ BOOL fEnable);

    virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
        /* [in] */ __RPC__in LPMSG lpmsg,
        /* [in] */ WORD wID);

    // IDocHostUIHandler methods
    virtual HRESULT STDMETHODCALLTYPE ShowContextMenu( 
        /* [in] */ DWORD dwID,
        /* [in] */ POINT *ppt,
        /* [in] */ IUnknown *pcmdtReserved,
        /* [in] */ IDispatch *pdispReserved);

    virtual HRESULT STDMETHODCALLTYPE GetHostInfo( 
        /* [out][in] */ DOCHOSTUIINFO *pInfo);

    virtual HRESULT STDMETHODCALLTYPE ShowUI( 
        /* [in] */ DWORD dwID,
        /* [in] */ IOleInPlaceActiveObject *pActiveObject,
        /* [in] */ IOleCommandTarget *pCommandTarget,
        /* [in] */ IOleInPlaceFrame *pFrame,
        /* [in] */ IOleInPlaceUIWindow *pDoc);

    virtual HRESULT STDMETHODCALLTYPE HideUI( void);

    virtual HRESULT STDMETHODCALLTYPE UpdateUI( void);

//     virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
//         /* [in] */ BOOL fEnable);

    virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate( 
        /* [in] */ BOOL fActivate);

    virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate( 
        /* [in] */ BOOL fActivate);

    virtual HRESULT STDMETHODCALLTYPE ResizeBorder( 
        /* [in] */ LPCRECT prcBorder,
        /* [in] */ IOleInPlaceUIWindow *pUIWindow,
        /* [in] */ BOOL fRameWindow);

    virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
        /* [in] */ LPMSG lpMsg,
        /* [in] */ const GUID *pguidCmdGroup,
        /* [in] */ DWORD nCmdID);

    virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath( 
        /* [annotation][out] */ 
        __out  LPOLESTR *pchKey,
        /* [in] */ DWORD dw);

    virtual HRESULT STDMETHODCALLTYPE GetDropTarget( 
        /* [in] */ IDropTarget *pDropTarget,
        /* [out] */ IDropTarget **ppDropTarget);

    virtual HRESULT STDMETHODCALLTYPE GetExternal( 
        /* [out] */ IDispatch **ppDispatch);

    virtual HRESULT STDMETHODCALLTYPE TranslateUrl( 
        /* [in] */ DWORD dwTranslate,
        /* [annotation][in] */ 
        __in __nullterminated  OLECHAR *pchURLIn,
        /* [annotation][out] */ 
        __out  OLECHAR **ppchURLOut);

    virtual HRESULT STDMETHODCALLTYPE FilterDataObject( 
        /* [in] */ IDataObject *pDO,
        /* [out] */ IDataObject **ppDORet);

protected:
    ULONG   m_ulRef;
    HWND    m_hWnd;
    BOOL    m_bInPlaced;

    IStorage            *m_pStorage;
    IOleObject          *m_pOleObj; 
    IOleInPlaceObject   *m_pInPlaceObj;
    IWebBrowser2        *m_pWB2;
    IHTMLDocument2      *m_pHtmlDoc2;
    IHTMLDocument3      *m_pHtmlDoc3;
    IHTMLWindow2        *m_pHtmlWnd2;
    IHTMLEventObj       *m_pHtmlEvent;


public:
    BOOL Create(HWND hWnd);
    void Destroy();
    void Navigate(LPCTSTR lpUrl);
};



#endif // #ifndef __WEBBROWSER_H_FD0A3E73_BC52_4E71_8329_F1A766705836_INCLUDED__
