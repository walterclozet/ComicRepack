
// ComicRepackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ComicRepack.h"
#include "ComicRepackDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <tchar.h>
#include <algorithm>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CComicRepackDlg 对话框



CComicRepackDlg::CComicRepackDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COMICREPACK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComicRepackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_oPath);
	DDX_Control(pDX, IDC_VOLNUM, m_oVolNum);
	DDX_Control(pDX, IDC_IG1, m_oIgnoreFirst);
	DDX_Control(pDX, IDC_PACK, m_oPackButton);
	DDX_Control(pDX, IDC_INFO, m_oInfo);
	DDX_Control(pDX, IDC_EDIT2, m_oLog);
	DDX_Control(pDX, IDC_START_PAGE, m_oStartChapter);
}

BEGIN_MESSAGE_MAP(CComicRepackDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CComicRepackDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_PACK, &CComicRepackDlg::OnBnClickedPack)
	ON_BN_CLICKED(IDC_GET_LOG, &CComicRepackDlg::OnBnClickedGetLog)
END_MESSAGE_MAP()


// CComicRepackDlg 消息处理程序

BOOL CComicRepackDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_oVolNum.AddString(L"1");
	m_oVolNum.AddString(L"6");
	m_oVolNum.AddString(L"10");
	m_oVolNum.SetCurSel(2);

	m_oPath.SetWindowTextW(L"y:\\d2");

	m_oStartChapter.SetWindowTextW(L"1");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CComicRepackDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CComicRepackDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CComicRepackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// select dir
void CComicRepackDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BROWSEINFO  bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.iImage = 0;
	LPCITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (!pidl)
		return;
	TCHAR  szDisplayName[255];
	SHGetPathFromIDList(pidl, szDisplayName);
	CString str(szDisplayName);
	m_oPath.SetWindowText(str);
}

bool comp(const CString & a, const CString & b)
{
	if (a.GetLength() == b.GetLength())
	{
		return a < b;
	}

	return _ttoi(a.Mid(0, a.Find(L'.')).GetBuffer()) < _ttoi(b.Mid(0, b.Find('.')).GetBuffer());
}

void CComicRepackDlg::OnBnClickedPack()
{
	char strZipBat[] = R"(@echo off
cd __res
del /f /q *.zip
for /f "delims=\n" %%i in ('dir /b /a:d') do zip -r "%%i.zip" ".\%%i")";
	char strRarBat[] = R"(@echo off
if exist "%programfiles%\winrar\rar.exe" set rar="%programfiles%\winrar\rar.exe"
if exist "%programfiles(x86)%\winrar\rar.exe" set rar="%programfiles(x86)%\winrar\rar.exe"

cd __res

del /f /q *.rar

for /f "delims=\n" %%i in ('dir /b /a:d') do %rar% a "%%i.rar" ".\%%i")";

	CString strLog;
	CString strInfo;
	m_oPackButton.EnableWindow(FALSE);
	// TODO: 在此添加控件通知处理程序代码

	CString strBase;
	m_oStartChapter.GetWindowText(strInfo);
	int nChapterStart = _ttoi(strInfo.GetBuffer());
	m_oPath.GetWindowText(strBase);

	DeleteFile((strBase + _T("\\zipapp.bat")).GetBuffer());
	CFile oBatFile((strBase + _T("\\zipall.bat")).GetBuffer(), CFile::modeReadWrite | CFile::modeCreate);

	BYTE aBom[] = { 0xef, 0xbb, 0xbf };
	oBatFile.Write(aBom, sizeof(aBom));
	oBatFile.Write(strZipBat, strlen(strZipBat));
	oBatFile.Flush();
	oBatFile.Close(); 

	oBatFile.Open((strBase + _T("\\rarall.bat")).GetBuffer(), CFile::modeReadWrite | CFile::modeCreate);
	oBatFile.Write(aBom, sizeof(aBom));
	oBatFile.Write(strRarBat, strlen(strRarBat));
	oBatFile.Flush();
	oBatFile.Close();

	BOOL bIgnoreFirst = m_oIgnoreFirst.GetCheck() == BST_CHECKED;

	// get dirs
	CFileFind oFind;
	BOOL bSearch = oFind.FindFile(strBase + _T("\\*.*"));

	vector<CStringW> arrFolderList;
	while (bSearch)
	{
		bSearch = oFind.FindNextFileW();

		if ((oFind.IsDirectory() == TRUE) && (oFind.IsDots() != TRUE))
		{
			if (oFind.GetFileName().IsEmpty())
				continue;
			if (oFind.GetFileName()[0] == _T('.'))
				continue;

			if (CString(L"__res") != oFind.GetFileName())
				arrFolderList.push_back(oFind.GetFileName());
		}
	}

	CString strVolPath;

	CString strVolNum;
	m_oVolNum.GetWindowTextW(strVolNum);
	int nVolNum = _ttoi(strVolNum.GetBuffer());
	if (nVolNum < 0)
	{
		nVolNum = 1;
	}

	// get total vol numbers
	int m_nVolTotal = arrFolderList.size() / nVolNum;
	if (arrFolderList.size() % nVolNum)
	{
		++m_nVolTotal;
	}
	for (size_t i = 0; i < m_nVolTotal; ++i)
	{
		strVolPath.Format(_T("%s\\__res\\"), strBase.GetBuffer());
		if (_taccess(strVolPath, 0) != 0)
		{
			CreateDirectory(strVolPath, NULL);
		}
		if (nVolNum == 1)
		{
			strVolPath.Format(_T("%s\\__res\\vol_%03d\\"), strBase.GetBuffer(), i + nChapterStart);
		}
		else if (i != m_nVolTotal - 1)
		{
			strVolPath.Format(_T("%s\\__res\\vol_%03d - %03d\\"), strBase.GetBuffer(), nVolNum * i + nChapterStart, nVolNum * (i + 1) + nChapterStart - 1);
		}
		else
		{
			strVolPath.Format(_T("%s\\__res\\vol_%03d - %03d\\"), strBase.GetBuffer(), nVolNum * i + nChapterStart, nVolNum * i + nChapterStart - 1 + arrFolderList.size() % nVolNum);
		}
		if (_taccess(strVolPath, 0) != 0)
		{
			CreateDirectory(strVolPath, NULL);
		}

		// proc book i
		// start copying images
		int nImgIndex = 0;
		vector<int> arrIndex;
		vector<CStringW> arrChapters;
		for (size_t j = 0; j < nVolNum; ++j)
		{
			if (i * nVolNum + j >= arrFolderList.size())
			{
				break;
			}

			CStringW strSrc = strBase + L"\\" + arrFolderList[i * nVolNum + j];
			CStringW strChapterName = arrFolderList[i * nVolNum + j];
			if (strChapterName.Mid(0, 8) == _T("chapter_") && strChapterName[11] == _T('_'))
			{
				strChapterName = strChapterName.Mid(12);
			}

			// loading all image files to arrFileList
			vector <CString> arrFileList;
			CFileFind oFind2;
			BOOL bSearch = oFind2.FindFile(strSrc + _T("\\*.*"));

			while (bSearch)
			{
				bSearch = oFind2.FindNextFileW();

				if (oFind2.IsDots())
				{
					continue;
				}
				else if ((oFind2.IsDirectory() == TRUE))
				{
					continue;
				}

				arrFileList.push_back(oFind2.GetFileName());
			}

			// ignore empty folder
			if (arrFileList.empty())
			{
				continue;
			}

			sort(arrFileList.begin(), arrFileList.end(), comp);

			arrIndex.push_back(nImgIndex);
			arrChapters.push_back(strChapterName);

 			strInfo.Format(_T("Vol %d, Chapter %d, Total = %d\r\n"), i + 1, i * nVolNum + j, arrFileList.size());
 			strLog += strInfo;
// 			m_oLog.SetWindowTextW(strLog);
			for (size_t k = 0; k < arrFileList.size(); ++k)
			{
				if (bIgnoreFirst && k == 0)
				{
					continue;
				}
				CString strSrcFile = strSrc + _T("\\") + arrFileList[k];
				CString strDestFile;
				strDestFile.Format(_T("%sV%02d%03d%s"), strVolPath.GetBuffer(), j, nImgIndex, strSrcFile.Mid(strSrcFile.ReverseFind(L'.')));

				m_oInfo.SetWindowTextW(strDestFile);
				if (_taccess(strDestFile, 0) == 0)
				{
					// file aready exists, skip it
					strInfo.Format(_T("skip %s\r\n"), strSrcFile.GetBuffer(), strDestFile.GetBuffer());
				}
				else
				{
					BOOL bRes = CopyFile(strSrcFile, strDestFile, FALSE);
					if (!bRes)
					{
						DWORD dwErr = GetLastError();

						ASSERT(FALSE);
					}
					strInfo.Format(_T("copy %s to %s\r\n"), strSrcFile.GetBuffer(), strDestFile.GetBuffer());
				}
				strLog += strInfo;
				++nImgIndex;
			}
		}

		// creating index file
		m_oInfo.SetWindowTextW(L"Set index");
		DeleteFile((strVolPath + _T("vol-navpoint.txt")).GetBuffer());
		CFile oIndexFile((strVolPath + _T("vol-navpoint.txt")).GetBuffer(), CFile::modeReadWrite | CFile::modeCreate);

		BYTE aBom[] = { 0xef, 0xbb, 0xbf };
		oIndexFile.Write(aBom, sizeof(aBom));
		wchar_t buf[255]; 
		char buf2[255 * 3];
		for(size_t k = 0; k < arrIndex.size(); ++k)
		{
			if (arrChapters[k].IsEmpty())
			{
				swprintf_s(buf, L"Chapter %d,%03d\r\n", i * nVolNum + k + nChapterStart, arrIndex[k]);
			}
			else
			{
				swprintf_s(buf, L"%s,%03d\r\n", arrChapters[k].GetBuffer(), arrIndex[k]);
			}

			WideCharToMultiByte(CP_UTF8, 0, buf, -1, buf2, 255 * 3, NULL, NULL);
			oIndexFile.Write(buf2, strlen(buf2));
		}
		oIndexFile.Flush();
		oIndexFile.Close();

		m_oInfo.SetWindowTextW(L"1 vol finished");
	}
	m_oInfo.SetWindowTextW(L"OK");
	m_oLog.SetWindowTextW(strLog);

	m_oPackButton.EnableWindow(TRUE);
}

BOOL CComicRepackDlg::EditCopy(CString & strInfo)
{
	LPTSTR  lptstrCopy;
	HGLOBAL hglbCopy;

	// Open the clipboard, and empty it. 

	if (!OpenClipboard())
		return FALSE;
	EmptyClipboard();

	// Get a pointer to the structure for the selected label. 

	// If text is selected, copy it using the CF_TEXT format. 

	// Allocate a global memory object for the text. 

	hglbCopy = GlobalAlloc(GMEM_MOVEABLE,
		(strInfo.GetLength() + 1) * sizeof(TCHAR));
	if (hglbCopy == NULL)
	{
		CloseClipboard();
		return FALSE;
	}

	// Lock the handle and copy the text to the buffer. 

	lptstrCopy = (LPTSTR)GlobalLock(hglbCopy);
	memcpy(lptstrCopy, strInfo.GetBuffer(),
		strInfo.GetLength() * sizeof(TCHAR));
	lptstrCopy[strInfo.GetLength()] = (TCHAR)0;    // null character 
	GlobalUnlock(hglbCopy);

	// Place the handle on the clipboard. 

#ifdef UNICODE
	SetClipboardData(CF_UNICODETEXT, hglbCopy);
#else
	SetClipboardData(CF_TEXT, hglbCopy);
#endif

	// Close the clipboard. 
	CloseClipboard();

	return TRUE;
}

void CComicRepackDlg::OnBnClickedGetLog()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strLog;
	m_oLog.GetWindowTextW(strLog);
	
	EditCopy(strLog);
}
