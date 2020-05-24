
// _02ImageFormatDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "_02ImageFormat.h"
#include "_02ImageFormatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02ImageFormatDlg 대화 상자



CMy02ImageFormatDlg::CMy02ImageFormatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD__02IMAGEFORMAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	FilterList_.Add(_T("All Files (*.*) | *.*; |"));
	FilterList_.Add(_T("BMP Files (*.bmp) | *.bmp; |"));
	FilterList_.Add(_T("JPG Files (*.jpg, *.jpeg) | *.jpg; *.jpeg; |"));
	FilterList_.Add(_T("PNG Files (*.png) | *.png; |"));
	FilterList_.Add(_T("ICO Files(*.ico) | *.ico; |"));


	FileExtList_.Add(_T(".bmp"));
	FileExtList_.Add(_T(".jpg"));
	FileExtList_.Add(_T(".png"));
	FileExtList_.Add(_T(".ico"));
	FileExtList_.Add(nullptr);
}

void CMy02ImageFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy02ImageFormatDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMy02ImageFormatDlg::OnBnClickedBtnOpen)
	ON_WM_ACTIVATE()
	ON_WM_NCACTIVATE()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMy02ImageFormatDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CMy02ImageFormatDlg 메시지 처리기

BOOL CMy02ImageFormatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	if (pImageFormatCB_ == nullptr)
		pImageFormatCB_ = static_cast<CComboBox*>(GetDlgItem(IDC_CB_IMAGE_FORMAT));

	if (pSaveBTN_ == nullptr)
		pSaveBTN_ = static_cast<CButton*>(GetDlgItem(IDC_BTN_SAVE));
	
	if (pPathROEDIT_ == nullptr)
		pPathROEDIT_ = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_RO_PATH));
	
	
	this->SetWindowText(_T("진빼이 프로그램"));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMy02ImageFormatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMy02ImageFormatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CMy02ImageFormatDlg::FindImageFileExtCompareIdx(CString fileExt)
{
	if (fileExt.GetLength() == 0)
		return -1;

	

	for (int i = 0, j = FileExtList_.GetCount(); i < j; ++i)
	{
		if (fileExt.CompareNoCase(FileExtList_.GetAt(i)) == 0)
		{
			return i;
		}
	}
	return -1;
}

void CMy02ImageFormatDlg::OnBnClickedBtnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	

	CString filter = FilterList_.GetAt(0) + FilterList_.GetAt(1) + FilterList_.GetAt(2) + FilterList_.GetAt(3) + FilterList_.GetAt(4) + _T("|");
	CFileDialog fileDlg(FALSE, 0 ,0, 0, filter, this);
	INT_PTR result = fileDlg.DoModal();

	if (result == IDOK)
	{
		SelectFileFPath_ = fileDlg.GetPathName();
		CString fileExt = PathFindExtension(SelectFileFPath_);
		if (fileExt.CompareNoCase(_T(".JPEG")) == 0)
		{
			fileExt = _T(".jpg");
		}


		INT selectFileExtIdx = FindImageFileExtCompareIdx(fileExt);
		if (selectFileExtIdx == -1)
		{
			if (pImageFormatCB_->IsWindowEnabled() == TRUE)
				pImageFormatCB_->EnableWindow(FALSE);

			if (pSaveBTN_->IsWindowEnabled() == TRUE)
				pSaveBTN_->EnableWindow(FALSE);

			pPathROEDIT_->SetWindowTextW(_T(""));
			MessageBox(_T("이 파일은 변환할 수 없습니다."), _T("오류"), MB_ICONERROR | MB_OK);
		}
		else
		{
			if (pImageFormatCB_->IsWindowEnabled() == FALSE)
				pImageFormatCB_->EnableWindow(TRUE);

			if (pSaveBTN_->IsWindowEnabled() == FALSE)
				pSaveBTN_->EnableWindow(TRUE);
			
			pPathROEDIT_->SetWindowTextW(SelectFileFPath_);
			ImageFormatSelectIdx_ = selectFileExtIdx;

			LPCTSTR szImageFormatTextList[] = {
				_T("BMP"),
				_T("JPG"),
				_T("PNG"),
				_T("ICO")
			};
			pImageFormatCB_->ResetContent();
			for (int i = 0; i < _countof(szImageFormatTextList); ++i)
			{
				CString str;
				if (i == selectFileExtIdx)
					continue;

				str.Format(_T("*.%s 확장명으로 변환하기"), szImageFormatTextList[i]);
				pImageFormatCB_->AddString(str);
			}
		}
	}
	else
	{
		return;
	}
}



BOOL CMy02ImageFormatDlg::OnNcActivate(BOOL bActive)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	{
		if (m_nFlags & WF_STAYACTIVE)
		{
			bActive = TRUE;
		}
		return(BOOL)DefWindowProc(WM_NCACTIVATE, bActive, 0L);
	}
	return CDialogEx::OnNcActivate(bActive);
}


void CMy02ImageFormatDlg::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (pImageFormatCB_->GetCurSel() == CB_ERR)
	{
		MessageBox(_T("포맷을 선택해주세요"), _T("오류"), MB_OK | MB_ICONERROR);
	}
	else
	{
		int select = pImageFormatCB_->GetCurSel();
		if (select >= ImageFormatSelectIdx_)
		{
			select += 1;
		}

		CString fileName = PathFindFileName(SelectFileFPath_);
		PathRemoveExtensionW(fileName.GetBuffer());

		CFileDialog fileDlg(FALSE, FileExtList_.GetAt(select), fileName, 0, FilterList_.GetAt(select +1) + _T("|"));
		if (fileDlg.DoModal() == IDOK)
		{

			using namespace Gdiplus;
			const GUID ImageFormatList[] = {
				ImageFormatBMP,
				ImageFormatJPEG,
				ImageFormatPNG,
				ImageFormatIcon
			};

			CImage image;
			image.Load(SelectFileFPath_);
			image.Save(fileDlg.GetPathName(), ImageFormatList[ImageFormatSelectIdx_]);
			image.Destroy();
			pImageFormatCB_->SetCurSel(-1);
		}
		else
		{
			return;
		}
	}
}
