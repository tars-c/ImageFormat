
// _02ImageFormatDlg.h: 헤더 파일
//

#pragma once


// CMy02ImageFormatDlg 대화 상자
class CMy02ImageFormatDlg : public CDialogEx
{
// 생성입니다.
public:
	CMy02ImageFormatDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD__02IMAGEFORMAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox* pImageFormatCB_ = nullptr;
	CButton* pSaveBTN_ = nullptr;
	CEdit* pPathROEDIT_ = nullptr;
	CStringArray FilterList_;
	CStringArray FileExtList_;

	CString SelectFileFPath_;
	int ImageFormatSelectIdx_;

	int FindImageFileExtCompareIdx(CString fileExt);
	afx_msg void OnBnClickedBtnOpen();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnBnClickedBtnSave();
};
