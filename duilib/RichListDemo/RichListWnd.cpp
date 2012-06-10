#include "StdAfx.h"
#include "RichListWnd.h"

CRichListWnd::CRichListWnd(void)
{
}

CRichListWnd::~CRichListWnd(void)
{
}

void CRichListWnd::OnFinalMessage( HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	delete this;
}

DuiLib::tString CRichListWnd::GetSkinFolder()
{
#ifdef _DEBUG
	return _T("skin\\RichListRes\\");
#else
	return _T("skin\\");
#endif
	
}

DuiLib::tString CRichListWnd::GetSkinFile()
{
	return _T("duilib.xml");
}

UILIB_RESOURCETYPE CRichListWnd::GetResourceType() const
{
#ifdef _DEBUG
	return UILIB_FILE;
#else
	return UILIB_ZIP;
#endif
}

DuiLib::tString CRichListWnd::GetZIPFileName() const
{
	return _T("RichListRes.zip");
}

LPCTSTR CRichListWnd::GetWindowClassName( void ) const
{
	return _T("RichListWnd");
}

void CRichListWnd::Notify( TNotifyUI &msg )
{
	if( msg.sType == _T("click") ) 
	{
		if( msg.pSender == m_pCloseBtn ) 
		{ 
			PostQuitMessage(0); // ��Ϊactivex��ԭ��ʹ��close���ܻ���ִ���
			return; 
		}else if( msg.pSender == m_pMinBtn ) 
		{ 
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
			return; 
		}else if( msg.pSender == m_pMaxBtn ) 
		{ 
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); 
			return; 
		}else if( msg.pSender == m_pRestoreBtn ) 
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			return;
		}
		else if( msg.pSender->GetName() == _T("quitbtn") ) {
			/*Close()*/PostQuitMessage(0); // ��Ϊactivex��ԭ��ʹ��close���ܻ���ִ���
		}
		else if(msg.pSender->GetName() == _T("down_ico"))
		{                
			CControlUI *find_ctrl =m_PaintManager.FindSubControlByName(msg.pSender->GetParent()->GetParent(), _T("down_name"));

			if(find_ctrl)
			{
				MessageBox(NULL, 
					find_ctrl->GetText()+_T(" ��ʾδѡ�����еİ�ť�������������ð�ť�������ҵ�������listcontainer.."), 
					_T("DUILIB DEMO"), MB_OK);   
				((CLabelUI *)find_ctrl)->SetText(_T("�ɳ���̬���ú������..."));
			}
		}
		else if(msg.pSender->GetName() == _T("down_del"))
		{
			CListUI *down_list = 
				static_cast<CListUI*>(m_PaintManager.FindControl(_T("down_list_tab")));
			if(!down_list)
				return;

			down_list->RemoveAt(down_list->GetCurSel());                   
		}
		else if(msg.pSender->GetName() == _T("down_new"))
		{
			CListUI *down_list = static_cast<CListUI*>(m_PaintManager.FindControl(_T("down_list_tab")));
			if(!down_list)
				return;

			CListContainerElementUI *new_node = new CListContainerElementUI;
			new_node->ApplyAttributeList(_T("height=\"45\""));

			CHorizontalLayoutUI *new_h_lay = new CHorizontalLayoutUI;
			new_h_lay->ApplyAttributeList(_T("float=\"false\" ")\
				_T("childpadding=\"10\" inset=\"3,5,3,5\""));

			CButtonUI *new_btn_1 = new CButtonUI;
			new_btn_1->ApplyAttributeList(
				_T("name=\"down_ico\" float=\"false\" ")\
				_T("bordersize=\"0\" width=\"32\" maxheight=\"26\" ")\
				_T("bkimage=\"downlist_app.png\" ")\
				_T("normalimage=\"file='downlist_run.png' dest='20,14,32,26'\""));

			CVerticalLayoutUI *new_v_lay = new CVerticalLayoutUI;
			new_h_lay->Add(new_btn_1);
			new_h_lay->Add(new_v_lay);

			CLabelUI *new_label = new CLabelUI;
			new_label->ApplyAttributeList(_T("textcolor=\"#FFAAAAAA\" showhtml=\"true\""));
			new_label->SetText(_T("new added item.exe"));
			new_label->SetName(_T("down_name"));
			CProgressUI *new_progress = new CProgressUI;
			new_progress->SetMinValue(0);
			new_progress->SetMaxValue(100);
			new_progress->SetValue(1);
			new_progress->SetMaxWidth(200);
			new_progress->SetMaxHeight(7);
			new_progress->SetForeImage(_T("progress_fore.png"));
			new_progress->SetName(_T("down_progress"));
			new_v_lay->Add(new_label);
			new_v_lay->Add(new_progress);

			CLabelUI *new_label2 = new CLabelUI;
			CLabelUI *new_label3 = new CLabelUI;
			CVerticalLayoutUI *new_v_lay2 = new CVerticalLayoutUI;
			new_h_lay->Add(new_v_lay2);
			new_v_lay2->Add(new_label2);
			new_v_lay2->Add(new_label3);
			new_label2->ApplyAttributeList(
				_T("align=\"right\" text=\"\" textcolor=\"#FFAAAAAA\" showhtml=\"true\""));
			new_label3->ApplyAttributeList(
				_T("align=\"right\" text=\"0.00K/34.33M \" textcolor=\"#FFAAAAAA\" showhtml=\"true\""));

			new_node->Add(new_h_lay);
			down_list->Add(new_node);
		}              
	}
	else if(msg.sType == _T("selectchanged"))
	{
		if(msg.pSender->GetName() == _T("down_list"))
		{
			//MessageBox(NULL, _T("donw list click"), _T("DUILIB DEMO"), MB_OK);    
			static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_main")))->SelectItem(0);
		}
		else if(msg.pSender->GetName() == _T("down_his"))
		{
			//MessageBox(NULL, _T("donw his click"), _T("DUILIB DEMO"), MB_OK);    
			static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_main")))->SelectItem(1);
		}
	}
	else if(msg.sType == _T("itemclick"))
	{
		TCHAR alert_msg[64] = {0};
		int index = ((CListContainerElementUI *)msg.pSender)->GetIndex();
		wsprintf(alert_msg, _T("ѡ������%d, ���ұ����ڵ�������Ŀ��..."), index);
		MessageBox(NULL, alert_msg, _T("DUILIB DEMO"), MB_OK);            

		CControlUI *find_ctrl =m_PaintManager.FindSubControlByName(msg.pSender, _T("down_name"));

		if(find_ctrl)
		{
			MessageBox(NULL, 
				find_ctrl->GetText()+_T(" ѡ���е�������Ŀ����.."), 
				_T("DUILIB DEMO"), MB_OK);   
			((CLabelUI *)find_ctrl)->SetText(_T("�ɳ���̬���ú������..."));
		}
		else
		{
			MessageBox(NULL, _T("��������δΪ�ؼ�����name�����Ҳ���Ҫ�����Ŀؼ�"), 
				_T("DUILIB DEMO"), MB_OK);   
		}

		find_ctrl =m_PaintManager.FindSubControlByName(msg.pSender, _T("down_progress"));

		if(find_ctrl)
		{
			TCHAR alert_msg[256] = {0};
			wsprintf(alert_msg, _T("������ֵ:%d"), ((CProgressUI *)find_ctrl)->GetValue());
			MessageBox(NULL, 
				alert_msg, 
				_T("DUILIB DEMO"), MB_OK);   

			((CProgressUI *)find_ctrl)->SetValue(30);
			MessageBox(NULL, _T("�޸��˽�����ֵ"), 
				_T("DUILIB DEMO"), MB_OK);   
		}
	}
}

LRESULT CRichListWnd::OnMouseWheel( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	// ���ie�ؼ��ղ���������Ϣ������
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	::ScreenToClient(m_PaintManager.GetPaintWindow(), &pt);
	CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("ie")));
	if( pControl && pControl->IsVisible() ) {
		RECT rc = pControl->GetPos();
		if( ::PtInRect(&rc, pt) ) {
			return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		}
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CRichListWnd::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
	if( wParam == SC_CLOSE ) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if( ::IsZoomed(*this) != bZoomed ) {
		if( !bZoomed ) {
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
			if( pControl ) pControl->SetVisible(true);
		}
		else {
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
			if( pControl ) pControl->SetVisible(false);
		}
	}
	return lRes;
}

void CRichListWnd::Init()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("restorebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("minbtn")));
}

LRESULT CRichListWnd::OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	CControlUI* pHover = m_PaintManager.FindControl(pt);
	if( pHover == NULL ) return 0;
	/*��ʾ��ͣ�������б��ͼ����ʱ����̬�任����ͼ��״̬��ʾ*/
	if(pHover->GetName() == _T("down_ico"))
	{
		MessageBox(NULL, _T("�����ĳ�ؼ����簴ť����ͣ�󣬶�Ŀ��ؼ�����������ı���״̬ͼ���С"), _T("DUILIB DEMO"), MB_OK);
		((CButtonUI *)pHover)->ApplyAttributeList(
			_T("normalimage=\"file='downlist_pause.png' dest='15,9,32,26'\""));                
	}
	return 0;
}

LRESULT CRichListWnd::OnChar( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	/*��ʾ������Ϣ�Ĵ���*/
	TCHAR press_char = (TCHAR)wParam;
	if(press_char == VK_BACK)
	{
		MessageBox(NULL, _T("�����˻��˼�"), _T("DUILIB DEMO"), MB_OK);
	}
	else
	{
		bHandled = FALSE;
	}
	return 0;
}
