
// ComicRepackDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CComicRepackDlg 对话框
class CComicRepackDlg : public CDialogEx
{
// 构造
public:
	CComicRepackDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMICREPACK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	BOOL EditCopy(CString & strInfo);
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_oPath;
	afx_msg void OnBnClickedPack();
	CComboBox m_oVolNum;
	CButton m_oIgnoreFirst;
	CButton m_oPackButton;
	CStatic m_oInfo;
	CEdit m_oLog;
	afx_msg void OnBnClickedGetLog();
	CEdit m_oStartChapter;
};
