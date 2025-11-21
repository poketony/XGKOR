// Hyperlink.cpp : implementation file
//

#include "stdafx.h"
#include "Hyperlink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString	g_strClickHere = _T("Click here");
BYTE	g_byHandCur16ANDMask[32] = {0xF3, 0xFF, 0xE1, 0xFF, 0xE1, 0xFF, 0xE1, 0xFF, 
									0xE1, 0xFF, 0xE0, 0x7F, 0xC0, 0x0F, 0x80, 0x03, 
									0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x80, 0x00, 0x80, 0x01, 0xC0, 0x01};
BYTE	g_byHandCur16XORMask[32] = {0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 
									0x0C, 0x00, 0x0C, 0x00, 0x0D, 0x80, 0x2D, 0xB0, 
									0x6F, 0xF4, 0x6F, 0xFC, 0x6F, 0xFE, 0x6F, 0xFE, 
									0x7F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFC, 0x1F, 0xFC};
BYTE	g_byHandCur32ANDMask[128]= {0xF3, 0xFF, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFF, 
									0xE1, 0xFF, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFF, 
									0xE1, 0xFF, 0xFF, 0xFF, 0xE0, 0x7F, 0xFF, 0xFF, 
									0xC0, 0x0F, 0xFF, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 
									0x00, 0x01, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xFF, 
									0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
									0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0xFF, 0xFF, 
									0x80, 0x01, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
									0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
BYTE	g_byHandCur32XORMask[128]= {0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
									0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
									0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
									0x0D, 0x80, 0x00, 0x00, 0x2D, 0xB0, 0x00, 0x00, 
									0x6F, 0xF4, 0x00, 0x00, 0x6F, 0xFC, 0x00, 0x00, 
									0x6F, 0xFE, 0x00, 0x00, 0x6F, 0xFE, 0x00, 0x00, 
									0x7F, 0xFE, 0x00, 0x00, 0x3F, 0xFE, 0x00, 0x00, 
									0x3F, 0xFC, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/////////////////////////////////////////////////////////////////////////////
// CHyperlink

CHyperlink::CHyperlink()
{
	m_bAllowModsToFont = FALSE ;
	m_bFontBold = FALSE ;
	m_bFontItalic = FALSE ;
	m_bMouseOver = FALSE ;
	m_bTransparentImage = FALSE ;
	m_bUserCursor = FALSE ;
	m_bWrapText = TRUE ;
	m_dwActiveTextColour = 0x0000FF00 ;
	m_dwBkgndColour = (COLORREF)-1 ;
	m_dwTextColour = 0x00000000 ;
	m_dwBackColour = HL_BACKCOLOUR_TRANSPARENT ;
	m_pFont = NULL ;
	m_sizFontSize.cx = 0 ;
	m_sizFontSize.cy = 0 ;
	m_strBitmapFilename = _T("");
	m_strFontName = _T("");
	m_strLinkTarget = _T("");
	m_uBitmapID = 0 ;
	m_uHighlightStyle = HL_HIGHLIGHT_TEXTANDIMAGE ;
	m_uTextAlignment = HL_TEXTALIGN_CENTRE ;
	m_uTextPosition = HL_TEXTPOS_BELOW ;
}

CHyperlink::~CHyperlink()
{
}

BEGIN_MESSAGE_MAP(CHyperlink, CWnd)
	//{{AFX_MSG_MAP(CHyperlink)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHyperlink message handlers

void CHyperlink::OnPaint() 
{
	CBitmap		*pBmp, *pBmpOld ;
	CDC			dcTemp ;
	CFont		*pFont, *pFntOld ;
	COLORREF	dwColour ;
	CPaintDC	dc(this);
	CPen		penBorder, *pPenOld ;
	CRect		rctHyperlink ;
	CString		strText ;
	UINT		uFlags = DT_NOPREFIX ;

// Grab the background colour. We must get the colour of a pixel within the 
// clipping area, if possible, otherwise the colour returned will be -1.
	dc.GetClipBox(&rctHyperlink);	// Gets the border AROUND the area.
	rctHyperlink.InflateRect(-1, -1);	// NOW it is the actual area.
	dwColour = dc.GetPixel(rctHyperlink.TopLeft() );
// Only set the background colour if not already set, and if a valid colour was 
// returned.
	if (m_dwBkgndColour == (COLORREF)-1 && dwColour != (COLORREF)-1)
		m_dwBkgndColour = dwColour ;

// Make sure the hyperlink will show SOMETHING.
	EnsureHyperlinkIsVisible();

// Get the positions and sizes calculated.
	CalculateRequiredSize(rctHyperlink);

// Get the image and font to use.
	pBmp = GetBitmapToUse();
	pFont = GetFontToUse();

// Draw the image.
	if (pBmp != NULL)
	{
		dcTemp.CreateCompatibleDC(NULL);
		pBmpOld = (CBitmap *)dcTemp.SelectObject(pBmp);
		dc.BitBlt(m_rctImage.left, m_rctImage.top, m_rctImage.Width(), 
					m_rctImage.Height(), &dcTemp, 0, 0, SRCCOPY);
		dcTemp.SelectObject(pBmpOld);
		dcTemp.DeleteDC();

// Draw highlight border, if required.
		if (m_bMouseOver && m_uHighlightStyle != HL_HIGHLIGHT_TEXTONLY)
		{
			penBorder.CreatePen(PS_SOLID, 1, m_dwActiveTextColour);
			pPenOld = (CPen *)dc.SelectObject(&penBorder);
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(m_rctImage);
			dc.SelectObject(pPenOld);
			penBorder.DeleteObject();
		}
	}

// Draw the text.
	GetWindowText(strText);
	if (strText != _T("") && m_uTextPosition != HL_TEXTPOS_NONE)
	{
		pFntOld = (CFont *)dc.SelectObject(pFont);

		if (m_dwBackColour == HL_BACKCOLOUR_TRANSPARENT || IsTextOverImage() )
			dc.SetBkMode(TRANSPARENT);
		else
			dc.SetBkColor(m_dwBackColour);

		if (m_bMouseOver)
			dc.SetTextColor(m_dwActiveTextColour);
		else
			dc.SetTextColor(m_dwTextColour);

		if (!m_bWrapText)
			uFlags |= DT_SINGLELINE ;
		else
			uFlags |= DT_WORDBREAK ;

		if (m_uTextAlignment == HL_TEXTALIGN_LEFT)
			uFlags |= DT_LEFT ;
		else if (m_uTextAlignment == HL_TEXTALIGN_CENTRE)
			uFlags |= DT_CENTER ;
		else if (m_uTextAlignment == HL_TEXTALIGN_RIGHT)
			uFlags |= DT_RIGHT ;

// Any underline required for highlighting is already there in the font itself, 
// because GetFontToUse() put it in.
		dc.DrawText(strText, &m_rctText, uFlags);

		dc.SelectObject(pFntOld);
	}

// Tidy up.
	if (pFont != NULL)
	{
		pFont->DeleteObject();
		delete pFont ;
	}
	if (pBmp != NULL)
	{
		pBmp->DeleteObject();
		delete pBmp ;
	}
}

void CHyperlink::OnMouseMove(UINT nFlags, CPoint point) 
{
	BOOL		bPreviousState ;

	bPreviousState = m_bMouseOver ;
	if (m_rctText.PtInRect(point) || m_rctImage.PtInRect(point) )
	{
		m_bMouseOver = TRUE ;
		::SetCursor(m_hHandCursor);
		SetCapture();
	}
	else
	{
		m_bMouseOver = FALSE ;
		::ReleaseCapture();
	}

	if (m_bMouseOver != bPreviousState)
	{
		Invalidate();
		UpdateWindow();
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CHyperlink::SetTextColour(COLORREF dwColour)
{
	m_dwTextColour = dwColour ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetBackColour(COLORREF dwColour)
{
	m_dwBackColour = dwColour ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetActiveTextColour(COLORREF dwColour)
{
	m_dwActiveTextColour = dwColour ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

BOOL CHyperlink::OnEraseBkgnd(CDC* pDC) 
{
	CBrush	brBkgnd, *pBrOld ;
	CRect	rctClient ;

	if (pDC != NULL && m_dwBkgndColour != (COLORREF)-1)
	{
		GetClientRect(&rctClient);
		brBkgnd.CreateSolidBrush(m_dwBkgndColour);
		pBrOld = (CBrush *)pDC->SelectObject(&brBkgnd);
		pDC->SelectStockObject(NULL_PEN);
		rctClient.InflateRect(1, 1);
		rctClient.right++ ;
		rctClient.bottom++ ;
		pDC->Rectangle(rctClient);
		pDC->SelectObject(pBrOld);
		brBkgnd.DeleteObject();
	}
	else
		CWnd::OnEraseBkgnd(pDC);

	return TRUE ;
}

void CHyperlink::SetLinkTarget(CString strTarget)
{
	m_strLinkTarget = strTarget ;
}

void CHyperlink::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bMouseOver)
	{
		OnClick();
		m_bMouseOver = FALSE ;
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CHyperlink::SetBitmapID(UINT uID)
{
	m_uBitmapID = uID ;
	m_strBitmapFilename = _T("");
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetBitmapFilename(CString strFilename)
{
	m_strBitmapFilename = strFilename ;
	m_uBitmapID = 0 ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

LRESULT CHyperlink::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT	lResult ;
	
	lResult = Default();
	Invalidate();
	UpdateWindow();

	return lResult ;
}

void CHyperlink::SetNoBitmap(void)
{
	m_strBitmapFilename = _T("");
	m_uBitmapID = 0 ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetTextPosition(UINT uPosition, UINT uAlignment)
{
	m_uTextPosition = uPosition ;
	m_uTextAlignment = uAlignment ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetTextWrapping(BOOL bWrap)
{
	m_bWrapText = bWrap ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::CalculateRequiredSize(CRect& rctHyperlink)
{
	BITMAP		sBmp ;
	CBitmap		*pBmp ;
	CClientDC	dc(this);
	CFont		*pFont, *pFntOld ;
	CString		strText ;
	UINT		uFlags = DT_NOPREFIX|DT_CALCRECT, uWidth, uHeight ;

// Make sure we either have an image or some text.
	EnsureHyperlinkIsVisible();

// Get the bitmap dimensions.
	pBmp = GetBitmapToUse();
	if (pBmp == NULL)
		m_rctImage.SetRectEmpty();
	else
	{
		pBmp->GetBitmap(&sBmp);
		m_rctImage.SetRect(0, 0, sBmp.bmWidth, sBmp.bmHeight);

		pBmp->DeleteObject();
		delete pBmp ;	// Since we no longer need it.
	}

// Get the text dimensions.
	GetWindowText(strText);
	pFont = GetFontToUse();
	pFntOld = (CFont *)dc.SelectObject(pFont);

	m_rctText = m_rctImage ;
	m_rctText.bottom = m_rctText.top + 1 ;	// Minimum height, will get altered.
// Establish minimum text width (if image is wider than default minimum, it 
// takes precedence).
	uWidth = MIN_TEXT_WIDTH ;
	if (pBmp != NULL && m_rctImage.Width() > (int)uWidth)
		uWidth = m_rctImage.Width();
// Make sure text is at least the minimum width.
	if (pBmp != NULL && m_rctText.Width() < (int)uWidth)
		m_rctText.right = m_rctText.left + uWidth ;
	else if (pBmp == NULL && m_rctText.Width() < 1)
	{
// Minimum width does not apply when there is no image, other than that it 
// needs to be at least 1 to work properly.
		m_rctText.right = m_rctText.left + 1 ;	// Must be at least 1 wide.
	}

	if (!m_bWrapText)
		uFlags |= DT_SINGLELINE ;
	else
		uFlags |= DT_WORDBREAK ;
	uWidth = m_rctText.Width();	// Preserve current minimum width.
	dc.DrawText(strText, &m_rctText, uFlags);
// Restore minimum width, otherwise alignment won't appear to work.
	if (m_rctText.Width() < (int)uWidth)
		m_rctText.right = m_rctText.left + uWidth ;


	dc.SelectObject(pFntOld);
	if (pFont != NULL)
	{
		pFont->DeleteObject();
		delete pFont ;
	}

// Combine the two rects as appropriate.
	uWidth = max(m_rctImage.Width(), m_rctText.Width() );
	if (m_uTextPosition == HL_TEXTPOS_ABOVE || m_uTextPosition == HL_TEXTPOS_BELOW)
		uHeight = m_rctImage.Height() + m_rctText.Height();
	else
		uHeight = max(m_rctImage.Height(), m_rctText.Height() );

	rctHyperlink.SetRect(0, 0, uWidth, uHeight);

// Now actually position the image and text correctly within this window.
	AdjustPositions(rctHyperlink);
}

CBitmap * CHyperlink::GetBitmapToUse(void)
{
// It is up to the caller to destroy and delete this CBitmap object, if not 
// NULL.

	BOOL		bGotBitmap = FALSE ;
	CBitmap		*pBmp ;
	CWnd		*pWndParent ;
	HBITMAP		hBmp = NULL ;
	HINSTANCE	hInst ;
	LPCTSTR		lpszName ;
	UINT		uFlags = LR_LOADFROMFILE ;

	pBmp = new CBitmap ;
	if (m_uBitmapID != 0)
	{
		hInst = AfxGetInstanceHandle();
		lpszName = MAKEINTRESOURCE(m_uBitmapID);
		uFlags = 0 ;
		bGotBitmap = TRUE ;
	}
	else if (m_strBitmapFilename != _T("") )
	{
		hInst = NULL ;
		lpszName = (LPCTSTR)m_strBitmapFilename ;
		bGotBitmap = TRUE ;
	}

	if (m_bTransparentImage)
	{
		uFlags |= LR_LOADTRANSPARENT ;

		pWndParent = GetParent();
		if (pWndParent != NULL)
		{
			if (pWndParent->IsKindOf(RUNTIME_CLASS(CDialog) ) || 
				pWndParent->IsKindOf(RUNTIME_CLASS(CFormView) ) )
			{
				uFlags |= LR_LOADMAP3DCOLORS ;
			}
		}
	}

	if (bGotBitmap)
	{
		hBmp = (HBITMAP)::LoadImage(hInst, lpszName, IMAGE_BITMAP, 0, 0, 
									uFlags);
		pBmp->Attach(hBmp);
	}

// No bitmap specified / image failed to load?
	if (pBmp->m_hObject == NULL)
	{
		delete pBmp ;
		pBmp = NULL ;
	}

	return pBmp ;
}

CFont * CHyperlink::GetFontToUse(void)
{
// It is up to the caller to destroy and delete this CFont object, if not NULL.

	CClientDC	dc(this);
	CFont		*pFont ;
	LOGFONT		sLF ;

	if (m_pFont != NULL)	// Set directly by user.
		pFont = m_pFont ;
	else
	{
// Select a stock font to pop out the current font.
		pFont = (CFont *)dc.SelectStockObject(ANSI_VAR_FONT);
		dc.SelectObject(pFont);	// Put the original font back.
	}

// At this point pFont is just a copy of a font. It will be created as a new 
// font below.
	pFont->GetLogFont(&sLF);

	if (m_bAllowModsToFont)
	{

		if (m_strFontName != _T("") )
			strcpy(sLF.lfFaceName,(const char *)m_strFontName);

		if (m_sizFontSize.cy != 0)
		{
			sLF.lfHeight = m_sizFontSize.cy ;
			sLF.lfWidth = m_sizFontSize.cx ;
		}

		if (m_bFontBold)
			sLF.lfWeight = FW_BOLD ;
		else
			sLF.lfWeight = FW_NORMAL ;

		sLF.lfItalic = (BYTE)m_bFontItalic ;
	}

// Always create with an underline if the mouse is over the text and the 
// highlighting style involves the text.
	if (m_bMouseOver && m_uHighlightStyle != HL_HIGHLIGHT_IMAGEONLY)
		sLF.lfUnderline = TRUE ;

// NOW we create the new font.
	pFont = new CFont ;
	pFont->CreateFontIndirect(&sLF);
	pFont->GetLogFont(&sLF);

	return pFont ;
}

void CHyperlink::EnsureHyperlinkIsVisible(void)
{
	CBitmap	*pBmp ;
	CString	strText ;

	GetWindowText(strText);

// Prevent hyperlink with no text and no image!
	pBmp = GetBitmapToUse();
	if (pBmp == NULL)	// No image, or can't create.
	{
		if (m_uTextPosition == HL_TEXTPOS_NONE)
			m_uTextPosition = HL_TEXTPOS_BELOW ;

		if (strText == _T("") )
		{
			strText = g_strClickHere ;
			SetWindowText(strText);
		}
	}
	else
	{
		pBmp->DeleteObject();
		delete pBmp ;
	}
}

void CHyperlink::SetTransparentBitmap(BOOL bTransparent)
{
	m_bTransparentImage = bTransparent ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetFontToUse(CFont *pFont, BOOL bAllowMods)
{
	m_pFont = pFont ;
	m_bAllowModsToFont = bAllowMods ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetFontName(CString strName)
{
	m_strFontName = strName ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetFontAttributes(BOOL bBold, BOOL bItalic)
{
	m_bFontBold = bBold ;
	m_bFontItalic = bItalic ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::SetFontSize(int iHeight, UINT uWidth)
{
	m_sizFontSize.cy = iHeight ;
	m_sizFontSize.cx = uWidth ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::AllowModsToFont(BOOL bAllowMods)
{
	m_bAllowModsToFont = bAllowMods ;
	if (m_hWnd != NULL)
	{
		Invalidate();
		UpdateWindow();
	}
}

void CHyperlink::GetTextRect(CRect& rctText)
{
	rctText = m_rctText ;
}

void CHyperlink::GetBitmapRect(CRect& rctBitmap)
{
	rctBitmap = m_rctImage ;
}

void CHyperlink::AdjustPositions(CRect& rctHyperlink)
{
	CBitmap	*pBmp ;
	CRect	rctClient ;
	int		iLeftImage, iTopImage, iLeftText, iTopText, iLeft, iTop ;

	pBmp = GetBitmapToUse();

	if (m_uTextAlignment == HL_TEXTALIGN_LEFT)
	{
		iLeftImage = 0 ;
		iLeftText = 0 ;
	}
	else if (m_uTextAlignment == HL_TEXTALIGN_CENTRE)
	{
		iLeftImage = (rctHyperlink.Width() - m_rctImage.Width() ) / 2 ;
		iLeftText = (rctHyperlink.Width() - m_rctText.Width() ) / 2 ;
	}
	else if (m_uTextAlignment == HL_TEXTALIGN_RIGHT)
	{
		iLeftImage = rctHyperlink.Width() - m_rctImage.Width();
		iLeftText = rctHyperlink.Width() - m_rctText.Width();
	}

	if (m_uTextPosition == HL_TEXTPOS_ABOVE)
	{
		iTopText = 0 ;
		iTopImage = m_rctText.Height();
	}
	else if (m_uTextPosition == HL_TEXTPOS_BELOW)
	{
		iTopImage = 0 ;
		iTopText = m_rctImage.Height();
	}
	else
	{
		iTopImage = 0 ;
		if (pBmp == NULL)	// No image, or can't create.
			iTopText = 0 ;
		else if (m_uTextPosition == HL_TEXTPOS_TOP)
			iTopText = 0 ;
		else if (m_uTextPosition == HL_TEXTPOS_MIDDLE)
			iTopText = (m_rctImage.Height() - m_rctText.Height() ) / 2 ;
		else if (m_uTextPosition == HL_TEXTPOS_BOTTOM)
			iTopText = m_rctImage.Height() - m_rctText.Height();
	}

// Adjust the rects for this minimum size window.
	m_rctText.OffsetRect(iLeftText, iTopText);
	m_rctImage.OffsetRect(iLeftImage, iTopImage);

// Adjust the rects for the true window size.
	GetClientRect(&rctClient);
	iLeft = (rctClient.Width() - rctHyperlink.Width() ) / 2 ;
	iTop = (rctClient.Height() - rctHyperlink.Height() ) / 2 ;
	m_rctText.OffsetRect(iLeft, iTop);
	m_rctImage.OffsetRect(iLeft, iTop);

	if (pBmp != NULL)
	{
		pBmp->DeleteObject();
		delete pBmp ;
	}
}

BOOL CHyperlink::IsTextOverImage(void)
{
	BOOL	bIsOver = FALSE ;

	if (m_uTextPosition == HL_TEXTPOS_TOP || 
		m_uTextPosition == HL_TEXTPOS_MIDDLE || 
		m_uTextPosition == HL_TEXTPOS_BOTTOM)
	{
		bIsOver = TRUE ;
	}

	return bIsOver ;
}

void CHyperlink::SetHighlightStyle(UINT uStyle)
{
	m_uHighlightStyle = uStyle ;
}

COLORREF CHyperlink::GetBackColour(void)
{
	return m_dwBackColour ;
}

COLORREF CHyperlink::GetTextColour(void)
{
	return m_dwTextColour ;
}

COLORREF CHyperlink::GetActiveTextColour(void)
{
	return m_dwActiveTextColour ;
}

void CHyperlink::OnClick(void)
{
// May be overridden...

	CString		strTarget, strMailTo = "mailto:";
	HINSTANCE	hInst ;
	HWND		hWndDesktop ;
	int			iLength ;

	hWndDesktop = ::GetDesktopWindow();
	strTarget = m_strLinkTarget ;
	if (strTarget == "")
	{
		GetWindowText(strTarget);
		iLength = strMailTo.GetLength();
		if (strTarget.Find('@') != -1 && strTarget.Left(iLength) != strMailTo)
			strTarget = strMailTo + strTarget ;
	}
	hInst = ::ShellExecute(hWndDesktop,"open", strTarget, NULL,"", SW_SHOW);
}

void CHyperlink::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bMouseOver)
	{
		OnRClick();
		m_bMouseOver = FALSE ;
	}
	
	CWnd::OnRButtonDown(nFlags, point);
}

void CHyperlink::OnRClick(void)
{
// May be overridden...
}

int CHyperlink::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	int	iCursorSize ;

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	iCursorSize = ::GetSystemMetrics(SM_CXCURSOR);
	if (iCursorSize == 32)
	{
		m_hHandCursor = ::CreateCursor(AfxGetInstanceHandle(), 8, 1, 32, 32, 
										g_byHandCur32ANDMask, g_byHandCur32XORMask);
	}
	else if (iCursorSize == 16)
	{
		m_hHandCursor = ::CreateCursor(AfxGetInstanceHandle(), 4, 0, 16, 16, 
										g_byHandCur16ANDMask, g_byHandCur16XORMask);
	}

	return 0;
}

void CHyperlink::OnDestroy() 
{
// Only destroy the existing cursor if it was our own.
	if (!m_bUserCursor)
		::DestroyCursor(m_hHandCursor);

	CWnd::OnDestroy();
}

HCURSOR CHyperlink::SetActiveCursor(HCURSOR hCursor)
{
	HCURSOR	hOldCursor = NULL ;

// Only destroy the existing cursor if it was our own.
	if (!m_bUserCursor)
		::DestroyCursor(m_hHandCursor);
	else
		hOldCursor = m_hHandCursor ;

	m_hHandCursor = hCursor ;
	m_bUserCursor = TRUE ;

	return hOldCursor ;
}
