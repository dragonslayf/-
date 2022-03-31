#include<afxwin.h>
class CMyFrameWnd:public CFrameWnd {
	DECLARE_MESSAGE_MAP()
public:
	int OnCreate(LPCREATESTRUCT pcs);
	void OnPaint();
	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg LRESULT OnMyMessage(WPARAM, LPARAM);
private:
	int m_mouse_x, m_mouse_y;
};
 
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

afx_msg LRESULT CMyFrameWnd::OnMyMessage(WPARAM wParam, LPARAM lParam) {
	CString str;
	str.Format("wParam=%d, lParam=%d", wParam, lParam);
	AfxMessageBox(str);
	return 0;
}
int CMyFrameWnd::OnCreate(LPCREATESTRUCT pcs) {
	return CFrameWnd::OnCreate(pcs);
}


afx_msg void CMyFrameWnd::OnMouseMove(UINT i, CPoint pos) {
	m_mouse_x = pos.x;
	m_mouse_y = pos.y;
	::InvalidateRect(this->m_hWnd, NULL, TRUE);
}

void CMyFrameWnd::OnPaint(void) {
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(hdc, m_mouse_x, m_mouse_y, "Hello", 5);
	::EndPaint(m_hWnd, &ps);
}


class CMyWinApp :public CWinApp {
public:
	virtual BOOL InitInstance();
};

BOOL CMyWinApp::InitInstance() {
	CMyFrameWnd* pwd = new CMyFrameWnd;
	pwd->Create(NULL, "mainWnd");
	m_pMainWnd = pwd;
	pwd->ShowWindow(SW_SHOW);
	return CWinApp::InitInstance();

}
CMyWinApp theApp;