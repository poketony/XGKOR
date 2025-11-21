// Hyperlink.h : header file
//

#define HL_BACKCOLOUR_TRANSPARENT	0xFFFFFFFF

#define MIN_TEXT_WIDTH				48

// Label positions.
#define HL_TEXTPOS_NONE			0
#define HL_TEXTPOS_ABOVE		1
#define HL_TEXTPOS_TOP			2
#define HL_TEXTPOS_MIDDLE		3
#define HL_TEXTPOS_BOTTOM		4
#define HL_TEXTPOS_BELOW		5

// Label alignments.
#define HL_TEXTALIGN_LEFT		0
#define HL_TEXTALIGN_CENTRE		1
#define HL_TEXTALIGN_RIGHT		2

// Font attributes.
#define HL_FONTBOLD				TRUE
#define HL_FONTNOTBOLD			FALSE
#define HL_FONTITALIC			TRUE
#define HL_FONTNOTITALIC		FALSE

// Highlighting styles.
#define HL_HIGHLIGHT_TEXTONLY		0
#define HL_HIGHLIGHT_IMAGEONLY		1
#define HL_HIGHLIGHT_TEXTANDIMAGE	2

/////////////////////////////////////////////////////////////////////////////
// CHyperlink window

class CHyperlink : public CWnd
{
// Construction
public:
	HCURSOR SetActiveCursor(HCURSOR hCursor);
	COLORREF GetActiveTextColour(void);
	COLORREF GetTextColour(void);
	COLORREF GetBackColour(void);
	void SetHighlightStyle(UINT uStyle);
	void GetBitmapRect(CRect& rctBitmap);
	void GetTextRect(CRect& rctText);
	void AllowModsToFont(BOOL bAllowMods = TRUE);
	void SetFontSize(int iHeight, UINT uWidth = 0);
	void SetFontAttributes(BOOL bBold, BOOL bItalic);
	void SetFontName(CString strName);
	void SetFontToUse(CFont *pFont, BOOL bAllowMods = FALSE);
	void SetTransparentBitmap(BOOL bTransparent = TRUE);
	void EnsureHyperlinkIsVisible(void);
	void CalculateRequiredSize(CRect& rctHyperlink);
	void SetTextWrapping(BOOL bWrap = TRUE);
	void SetTextPosition(UINT uPosition, UINT uAlignment);
	void SetNoBitmap(void);
	void SetBitmapFilename(CString strFilename);
	void SetBitmapID(UINT uID);
	void SetLinkTarget(CString strTarget);
	void SetActiveTextColour(COLORREF dwColour);
	void SetBackColour(COLORREF dwColour);
	void SetTextColour(COLORREF dwColour);
	CHyperlink();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperlink)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHyperlink();

	// Generated message map functions
protected:
	virtual void OnRClick(void);
	virtual void OnClick(void);
	//{{AFX_MSG(CHyperlink)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bUserCursor;
	BOOL IsTextOverImage(void);
	void AdjustPositions(CRect& rctHyperlink);
	CFont * GetFontToUse(void);
	CBitmap * GetBitmapToUse(void);

protected:
	HCURSOR m_hHandCursor;
	COLORREF m_dwBkgndColour;
	UINT m_uHighlightStyle;
	BOOL m_bAllowModsToFont;
	BOOL m_bFontItalic;
	BOOL m_bFontBold;
	CSize m_sizFontSize;
	CString m_strFontName;
	CFont * m_pFont;
	BOOL m_bTransparentImage;
	CRect m_rctImage;
	CRect m_rctText;
	BOOL m_bWrapText;
	UINT m_uTextAlignment;
	UINT m_uTextPosition;
	CString m_strBitmapFilename;
	UINT m_uBitmapID;
	CString m_strLinkTarget;
	COLORREF m_dwActiveTextColour;
	COLORREF m_dwBackColour;
	COLORREF m_dwTextColour;
	BOOL m_bMouseOver;
};

/////////////////////////////////////////////////////////////////////////////
