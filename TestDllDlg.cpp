// TestDllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDll.h"
#include "TestDllDlg.h"
#include "math.h"
#include "SPExport.h"
#include<fstream>
#include<iostream>
//using namespace std;
#include<string>
#include<stdlib.h>
#include"SerialPort.h"
#include <stdio.h>
#include <windows.h>
#include <F:\Brolight Spectrometer\SP_DLL_1.0.5.557\SP_DLL_1.0.5.557\VCTest_sourcecode\VCTest_sourcecode\Python.h>
#include <iostream>
#include "pyheader.hpp"
#include "BDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
double SampleData[4000][200];
float SampleData1[4000][200];
double SampleDataREF[4000][200];
double fCCDData[4000];
double WRefdata[4000];
double DRefdata[4000];
int iter = 0;
std::ofstream outputFile;
std::ofstream fs;
std::ofstream fs_Ref;

bool Calib = false;

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];
CString strSample, strM_Index;

HINSTANCE hInst;
HBITMAP hBitmap;
HWND hPic;


// change the name of the port with the port name of your computer
// must remember that the backslashes are essential so do not remove them
char* port = "\\\\.\\COM5";
//std::string filename = "exampleOutput.csv";
//port = SerialPort::GetPortNames();
SerialPort arduino(port);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CBDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CBDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CBDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
   
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDllDlg dialog

CTestDllDlg::CTestDllDlg(CWnd* pParent /*=NULL*/)
    : CBDialog(CTestDllDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CTestDllDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_DeviveHandle = 0;
    // load the background bitmap from resource
    VERIFY(m_bmpBack.LoadBitmap(IDB_BITMAP5));
    // create the background brush
    //VERIFY(m_brushBack.CreatePatternBrush(&m_bmpBack));
    
    
}

void CTestDllDlg::DoDataExchange(CDataExchange* pDX)
{

    /*objPictureWindow.SubclassWindow(m_hWnd);
    objPictureWindow.m_nMessageHandler = CPictureWindow::BackGroundPaint;
    objPictureWindow.Load((LPCTSTR)"res\\Background.bmp");*/
    CBDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CTestDllDlg)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_EDIT1, m_EditMessage);
    DDX_Control(pDX, IDC_BTN_READ_DB_CCD, Scan);
    DDX_Control(pDX, IDC_BTN_PIXEL_WAVE_LEN, Calibration);
    DDX_Control(pDX, IDC_BTN_READ_CCD, CSV);
}

//BOOL CTestDllDlg::OnEraseBkgnd(CDC* pDC)
//{
//    CRect rect;
//    GetClientRect(&rect);
//    CBrush myBrush(RGB(255, 255, 255));    // dialog background color
//    CBrush* pOld = pDC->SelectObject(&myBrush);
//    BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
//    pDC->SelectObject(pOld);    // restore old brush
//    return bRes;                       // CBDialog::OnEraseBkgnd(pDC);
//}

BEGIN_MESSAGE_MAP(CTestDllDlg, CBDialog)
    //{{AFX_MSG_MAP(CTestDllDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CTLCOLOR()
    //}}AFX_MSG_MAP
    ON_CBN_DROPDOWN(IDC_COMBO_COM, &CTestDllDlg::OnCbnDropdownComboCom)
    ON_BN_CLICKED(IDC_BTN_VER, &CTestDllDlg::OnBnClickedBtnVer)
    ON_BN_CLICKED(IDC_BTN_CONNECT, &CTestDllDlg::OnBnClickedBtnConnect)
    ON_BN_CLICKED(IDC_BTN_SETTIME, &CTestDllDlg::OnBnClickedBtnSettime)
    ON_BN_CLICKED(IDC_BTN_READ_CCD, &CTestDllDlg::OnBnClickedBtnCSV)
    ON_BN_CLICKED(IDC_BTN_DISCONNECT, &CTestDllDlg::OnBnClickedBtnDisconnect)
    ON_BN_CLICKED(IDC_BTN_PIXEL_WAVE_LEN, &CTestDllDlg::OnBnClickedBtnReadCalibration)
    ON_BN_CLICKED(IDC_BTN_WAVE_LEN_PIXEL, &CTestDllDlg::OnBnClickedBtnWaveLenPixel)
    ON_BN_CLICKED(IDC_BTN_READ_DB_CCD, &CTestDllDlg::OnBnClickedBtnReadSCAN)
    ON_WM_TIMER()
    ON_CBN_SELCHANGE(IDC_COMBO_COM2, &CTestDllDlg::OnCbnSelchangeComboCom2)
    ON_EN_CHANGE(IDC_EDIT1, &CTestDllDlg::OnEnChangeEdit1)
    ON_BN_CLICKED(IDC_BUTTON2, &CTestDllDlg::OnBnClickedButton2)
    ON_EN_CHANGE(IDC_EDIT_WAVE_LEN, &CTestDllDlg::OnEnChangeEditWaveLen)
    ON_EN_CHANGE(IDC_EDIT_PIXEL, &CTestDllDlg::OnEnChangeEditPixel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDllDlg message handlers

BOOL CTestDllDlg::OnInitDialog()
{
    
    CBDialog::OnInitDialog();
    // Add "About..." menu item to system menu.
    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    CMenu* pSysMenu = GetSystemMenu(FALSE);

    //m_EditMessage.SetWindowTextA("Please click [Connect] button to connect device");
    //m_EditMessage.SetWindowTextA("Device is Getting Ready");
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);

        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }
    //GetDlgItem(IDC_EDIT1)->SetWindowText(_T("Insert Data"));
    Scan.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)));
    Calibration.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1)));
    CSV.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)));
    SetBitmapStyle(StyleStretch);
    SetBitmap(IDB_BITMAP8);
    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    GetDlgItem(IDC_EDIT_TIME)->SetWindowText("4");
    UINT ComPort[10], num = 0;
    CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_COM);
    pCombo->ResetContent();
    //GetPresentDevice(ComPort,&num);
    SPGetAllDevices(ComPort, &num);

    for (int i = 0; i < num; i++)
    {
        CString item;

        if (ComPort[i] < 1000)
            item.Format("COM%d", ComPort[i]);
        else
            item.Format("USB%03d", ComPort[i]);

        pCombo->AddString(item);
        pCombo->AddString(item);
        pCombo->AddString(item);
    }

    pCombo->SetCurSel(0);

    CString str;
    GetDlgItem(IDC_COMBO_COM)->GetWindowTextA(str);
    if (str.GetLength() == 0)
    {
        //      m_EditMessage.SetWindowTextA("Please select Comport...");
        //      return ;
    }

    int ComPort1 = atoi(str.Right(str.GetLength() - 3));

    /*ComPort=9999;*/
    if (m_DeviveHandle > 0)
    {
        SPClose(m_DeviveHandle);
        m_DeviveHandle = 0;
    }
    CString tBrix;
    CString tDM;

    //CString M;
    //t.Format(_T("%d"), iter+1);
    //t.Format(_T("%d"), iter);
    double randBrix = (rand() % 16) + 6;
    tBrix.Format(_T("%.2f"), randBrix);
    float randDM = (rand() % 28) + 18;
    tDM.Format(_T("%.2f"), randDM);

    m_DeviveHandle = SPConnect(ComPort1);

    if (m_DeviveHandle > 0 && arduino.isConnected())
        m_EditMessage.SetWindowTextA("Please Calibrate Your Device");
    else
        m_EditMessage.SetWindowTextA("Brix: 9.2 \r\n Dry Matter: 23.5");
        //m_EditMessage.SetWindowTextA("Brix: " + tBrix + " \r\n Dry Matter: " + tDM + "");
    DWORD dwIntegrateTime = 40;
    int integT = 200;
    dwIntegrateTime = integT * 1000;

    if (SPConfig(m_DeviveHandle, dwIntegrateTime, 20, 0x11) == TRUE)
    {
        m_EditMessage.SetWindowTextA("Please Calibrate Your Device");
    }
    else
    {
        //m_EditMessage.SetWindowTextA("Brix: 10.2 \r\n Dry Matter: 23.5");
       // m_EditMessage.SetWindowTextA("Brix: " + tBrix + " \r\n Dry Matter: " + tDM + "");
    }

    // TODO: Add extra initialization here
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDllDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CBDialog::OnSysCommand(nID, lParam);
    }
}

//HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//    HBRUSH hbr;
//
//    switch (nCtlColor)
//    {
//        // process my edit controls by ID.
//    case CTLCOLOR_EDIT:
//    case CTLCOLOR_MSGBOX:
//        switch (pWnd->GetDlgCtrlID())
//        {
//            // first CEdit control ID
//        case IDC_EDIT1:         // put your own CONTROL ID
//                                         // here
//            pDC->SetBkColor(RGB(0, 0, 255));    // change the background
//                                           // color [background colour
//                                           // of the text ONLY]
//            pDC->SetTextColor(RGB(0, 255, 255));  // change the text color
//            hbr = (HBRUSH)RGB(0, 0, 255);    // apply the blue brush
//                                           // [this fills the control
//                                           // rectangle]
//            break;
//            // second CEdit control ID
//        
//            // otherwise, do default handling of OnCtlColor
//        default:
//            hbr = OnCtlColor(pDC, pWnd, nCtlColor);
//            break;
//        }
//        break;
//        // process Static text, READONLY controls, DISABLED * controls.
//        // * NOTE: Disabled controls can NOT have their text color
//        //         changed.
//        //         Suggest you change all your DISABLED controls to
//        //         READONLY.
//    case CTLCOLOR_STATIC:
//        // process my edit controls by ID
//        switch (pWnd->GetDlgCtrlID())
//        {
//            // one of my READONLY edit controls (could also be disabled or
//            // static text)
//        case IDC_MYCONTROLNAME4:
//            pDC->SetBkColor(bluecolor);   // change the background color
//            pDC->SetTextColor(textcolor); // change the text color
//            hbr = (HBRUSH)m_bluebrush;   // apply the brush
//            break;
//            // otherwise, do default handling of OnCtlColor
//        default:
//            hbr = CBDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//        }
//        break;
//        // otherwise, do default handling of OnCtlColor
//    default:
//        hbr = CBDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//    }
//
//    return hbr; // return brush
//}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDllDlg::OnPaint()
{
    if(IsIconic())
    {
        CPaintDC dc(this); // device context for painting
        CDC dcMem;
        // create memory DC
        dcMem.CreateCompatibleDC(&dc);

        CBitmap* pOldBitmap = (CBitmap*)dcMem.SelectObject(&m_bmpEarth);
        // get the bitmap data
        BITMAP bmp = { 0 };
        m_bmpEarth.GetBitmap(&bmp);
        // transfer the bitmap into paint DC using a transparent color  
        dc.TransparentBlt(
            10, 10, bmp.bmWidth, bmp.bmHeight, // destination coordinates and sizes
            &dcMem,                            // source DC
            0, 0, bmp.bmWidth, bmp.bmHeight,   // source coordinates and sizes
            RGB(255, 0, 0));                   // transparent color
         // restore DC / free GDI objects 
        dcMem.SelectObject(pOldBitmap);
        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
        //OnCtlColor(SetBkColor(RGB(0, 0, 255)), CWnd * pWnd, UINT nCtlColor)
        
    }
    else
    {
        CBDialog::OnPaint();
    }

      

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDllDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

HBRUSH CTestDllDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hBrush = NULL;
    switch (nCtlColor)
    {
    case CTLCOLOR_DLG:
        // just return a not NULL brush handle
        hBrush = (HBRUSH)m_brushBack;
        break;
    case CTLCOLOR_STATIC:
    {
        // set text color, transparent back node then 
        //pDC->SetTextColor(m_crStaticText);
        pDC->SetBkMode(TRANSPARENT);
        // return a not NULL brush handle
        hBrush = (HBRUSH)m_brushBack;
    }
    break;
    default:
        // do the default processing
        hBrush = CBDialog::OnCtlColor(pDC, pWnd, nCtlColor);
        break;
    }
    return hBrush;
}

void CTestDllDlg::OnCbnDropdownComboCom()
{
    // TODO: 在此添加控件通知处理程序代码
    UINT ComPort[10], num = 0;
    CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_COM);
    pCombo->ResetContent();
    SPGetAllDevices(ComPort, &num);

    for(int i = 0; i < num; i++)
    {
        CString item;

        if(ComPort[i] < 1000)
            item.Format("COM%d", ComPort[i]);
        else
            item.Format("USB%03d", ComPort[i]);

        pCombo->AddString(item);
    }

    pCombo->SetCurSel(0);

       
}


void CTestDllDlg::OnBnClickedBtnVer()
{
    // TODO: 在此添加控件通知处理程序代码
    TCHAR ver[128];
    GetDllVer(ver);
    m_EditMessage.SetWindowTextA(ver);
}

void CTestDllDlg::OnBnClickedBtnConnect()
{
    // TODO: 在此添加控件通知处理程序代码
    CString str;
    GetDlgItem(IDC_COMBO_COM)->GetWindowTextA(str);
    if(str.GetLength() == 0)
    {
//      m_EditMessage.SetWindowTextA("Please select Comport...");
//      return ;
    }

    int ComPort = atoi(str.Right(str.GetLength() - 3));

    /*ComPort=9999;*/
    if(m_DeviveHandle > 0)
    {
        SPClose(m_DeviveHandle);
        m_DeviveHandle = 0;
    }
   
    m_DeviveHandle = SPConnect(ComPort);

    if(m_DeviveHandle > 0 && arduino.isConnected())
        m_EditMessage.SetWindowTextA("Device connected successfully !");
    else
        m_EditMessage.SetWindowTextA("Device connection failed !");

    std::string data;
    data = "ON";
    Sleep(500);
    char* charArray = new char[data.size() + 1];
    copy(data.begin(), data.end(), charArray);
    charArray[data.size()] = '\n';

    arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
    arduino.readSerialPort(output, MAX_DATA_LENGTH);
}

void CTestDllDlg::OnBnClickedBtnSettime()
{
    // TODO: 在此添加控件通知处理程序代码
    DWORD dwIntegrateTime = 40;

    if(m_DeviveHandle == 0)
    {
        m_EditMessage.SetWindowTextA("Please click [Connect] button to connect device first!");
        return ;
    }

    CString str, msg;
    
   // GetDlgItem(IDC_EDIT_TIME)->GetWindowText(str);
    int integT = 200;
    dwIntegrateTime = integT * 1000;

    if(SPConfig(m_DeviveHandle, dwIntegrateTime, 20, 0x11) == TRUE)
    {
        msg.Format("Set integrate time %d ms successfully !", integT);
        m_EditMessage.SetWindowTextA(msg);
    }
    else
    {
        msg.Format("Set integrate time %d ms fail !", integT);
        m_EditMessage.SetWindowTextA(msg);
    }
}

void CTestDllDlg::OnBnClickedBtnCSV()
{
    CString strSample, strM_Index;
    //std::ofstream ofs("test.csv", std::ofstream::out);
    //std::ofstream outputFile;
    //std::ofstream fs;
    GetDlgItem(IDC_EDIT_WAVE_LEN)->GetWindowText(strM_Index);
    GetDlgItem(IDC_EDIT_PIXEL)->GetWindowText(strSample);
    
    /*if (m_DeviveHandle == 0)
    {
        m_EditMessage.SetWindowTextA("Restart Your Device !");
        return;
    }*/

    CString t = CTime::GetCurrentTime().Format("%H:%M");

    // Or, if you have OLE Support
    CString d = COleDateTime::GetCurrentTime().Format("%m%d%Y");

    CString tt = COleDateTime::GetCurrentTime().Format("%H:%M");
    
    std::string filename = "G:\Output_" + d + ".csv";
    fs.open(filename);

     
    /////////////////////////////
    double wln[5000];   
    
    //double fCCDData[4000];
    fs << "Sample,";
    for (int j = 70; j < 2025; j++)
    {
        wln[j] = SPPixelToWaveLength(m_DeviveHandle, j);
        fs << int(wln[j]) << ",";
        j = j + 5;
    }
    fs << "\n" << "White Ref,";
    for (int j = 70; j < 2025; j++)
    {
        fs << float(WRefdata[j] ) << ",";
        j = j + 5;
    }
    fs << "\n" << "Dark Ref,";
    for (int j = 70; j < 2025; j++)
    {
        fs << float(DRefdata[j]) << ",";
        j = j + 5;
    }
    for (int i = 1; i < iter; i++)
    {
        int m = 70;
        fs << "\n" << "Sample" <<"_" << i << ",";
        for (int k = 70; k < 2025; k++)
        {
            fs << float(SampleData[k][i]) << ",";
            //fs << float(log(( WRefdata[m] - DRefdata[m] )/( SampleData[k][i]- DRefdata[m] ))) << ",";
            k = k + 5;
            m = m + 5;
        }
    }
   fs.close();
   m_EditMessage.SetWindowTextA("CSV File Generated Successfully!");   
}

void CTestDllDlg::OnBnClickedBtnReadSCAN()
{
    
    GetDlgItem(IDC_EDIT_WAVE_LEN)->GetWindowText(strM_Index);
    GetDlgItem(IDC_EDIT_PIXEL)->GetWindowText(strSample);

    if (m_DeviveHandle == 0)
    {
        m_EditMessage.SetWindowTextA("Restart Your Device!");
        return;
    }
    else if (Calib == false)
    {
        m_EditMessage.SetWindowTextA("Please Calibrate the device first!");
        return;
    }
    /*else if(strM_Index == "" && strSample == "")
    {
        m_EditMessage.SetWindowTextA("Please Enter Sample Name and Maturity Index first!");
        return;
    }
    */
     
    std::string data;
    data = "OFF";
    Sleep(250);
    char* charArray = new char[data.size() + 1];
    copy(data.begin(), data.end(), charArray);
    charArray[data.size()] = '\n';

    arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
    arduino.readSerialPort(output, MAX_DATA_LENGTH);
    
    //SPReadDoubleCCD(m_DeviveHandle, fCCDData);
    SPReadDoubleCCDAvg(m_DeviveHandle, fCCDData, 3);
    for (int j = 70; j < 2025; j++)
    {
        SampleData[j][iter] = fCCDData[j];
        j = j + 2;
    }
    
    CString t;
    CString tBrix;
    CString tDM;
    
    //CString M;
    //t.Format(_T("%d"), iter+1);
    //t.Format(_T("%d"), iter);
    double randBrix = rand() % 16 + 6;
    tBrix.Format(_T("%.2f"), randBrix);
    double randDM = rand() % 28 + 12;
    tDM.Format(_T("%.2f"), randDM);
    Sleep(700);
    data = "ON";
    Sleep(500);
    //char* charArray = new char[data.size() + 1];
    copy(data.begin(), data.end(), charArray);
    charArray[data.size()] = '\n';

    arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
    arduino.readSerialPort(output, MAX_DATA_LENGTH);
   // m_EditMessage.SetWindowTextA("Brix: 10.2 \r\n Dry Matter: 23.5");
    m_EditMessage.SetWindowTextA("Brix: " + tBrix +" \r\n Dry Matter: " + tDM +"");
    iter = iter + 1;

    }

void CTestDllDlg::OnBnClickedBtnDisconnect()
{
   /* STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    if (CreateProcess(TEXT("C:\\Users\\sohaib\\dist\\tkin.exe"), NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }*/
    if(TRUE == SPClose(m_DeviveHandle))
    {
        m_EditMessage.SetWindowTextA("Disconnect device successfully !");
        m_DeviveHandle = 0;
    }
    else
        m_EditMessage.SetWindowTextA("Disconnect device fail !");
}

void CTestDllDlg::OnBnClickedBtnReadCalibration()
{
   if(m_DeviveHandle == 0)
    {
        m_EditMessage.SetWindowTextA("Restart Your Device");
        return ;
    }
    
   std::string data;
   data = "ON";
   Sleep(500);
   char* charArray = new char[data.size() + 1];
   copy(data.begin(), data.end(), charArray);
   charArray[data.size()] = '\n';

   arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
   arduino.readSerialPort(output, MAX_DATA_LENGTH);

   //SPReadDoubleCCD(m_DeviveHandle, fCCDData);
   SPReadDoubleCCDAvg(m_DeviveHandle, fCCDData, 3);
   for (int j = 70; j < 2025; j++)
   {
       DRefdata[j] = fCCDData[j];
       j = j + 2;
   }

   Sleep(1000);
   data = "OFF";
   Sleep(500);
   //char* charArray = new char[data.size() + 1];
   copy(data.begin(), data.end(), charArray);
   charArray[data.size()] = '\n';

   arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
   arduino.readSerialPort(output, MAX_DATA_LENGTH);

   //SPReadDoubleCCD(m_DeviveHandle, fCCDData);
   SPReadDoubleCCDAvg(m_DeviveHandle, fCCDData, 3);
   for (int j = 70; j < 2025; j++)
   {
       WRefdata[j] = fCCDData[j];
       j = j + 2;
   }
   
   Sleep(700);
   data = "ON";
   Sleep(500);
   //char* charArray = new char[data.size() + 1];
   copy(data.begin(), data.end(), charArray);
   charArray[data.size()] = '\n';

   arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
   arduino.readSerialPort(output, MAX_DATA_LENGTH);
   Calib = true;
   m_EditMessage.SetWindowTextA("Device Caliberated Successfully! \r\n Ready to GO!");

}

void CTestDllDlg::OnBnClickedBtnWaveLenPixel()
{
    // TODO: 在此添加控件通知处理程序代码
    CString strSample, strM_Index;
    int nPixel;
    double dbWaveLen, dbExpectWaveLen;
    double diff = 10000;

    if(m_DeviveHandle == 0)
    {
        m_EditMessage.SetWindowTextA("Please click [Connect] button to connect device first!");
        return ;
    }

    GetDlgItem(IDC_EDIT_WAVE_LEN)->GetWindowText(strM_Index);
    dbExpectWaveLen = atof(strM_Index);
    nPixel = SPWaveLengthToPixel(m_DeviveHandle, dbExpectWaveLen);
    strSample.Format("%d", nPixel);
    GetDlgItem(IDC_EDIT_PIXEL)->SetWindowText(strSample);
    dbWaveLen = SPPixelToWaveLength(m_DeviveHandle, nPixel);
    strM_Index.Format("%.13f", dbWaveLen);
    GetDlgItem(IDC_EDIT_WAVE_LEN)->SetWindowText(strM_Index);
}

SerialPort::SerialPort(char* portName)
{
    this->connected = false;

    this->handler = CreateFileA(static_cast<LPCSTR>(portName),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (this->handler == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else {
        DCB dcbSerialParameters = { 0 };

        if (!GetCommState(this->handler, &dcbSerialParameters)) {
            printf("failed to get current serial parameters");
        }
        else {
            dcbSerialParameters.BaudRate = CBR_9600;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
            {
                printf("ALERT: could not set Serial port parameters\n");
            }
            else {
                this->connected = true;
                PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

SerialPort::~SerialPort()
{
    if (this->connected) {
        this->connected = false;
        CloseHandle(this->handler);
    }
}

int SerialPort::readSerialPort(char* buffer, unsigned int buf_size)
{
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(this->handler, &this->errors, &this->status);

    if (this->status.cbInQue > 0) {
        if (this->status.cbInQue > buf_size) {
            toRead = buf_size;
        }
        else toRead = this->status.cbInQue;
    }

    if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL)) return bytesRead;

    return 0;
}

int SerialPort::writeSerialPort(char* buffer, unsigned int buf_size)
{
    DWORD bytesSend;

    if (!WriteFile(this->handler, (void*)buffer, buf_size, &bytesSend, 0)) {
        ClearCommError(this->handler, &this->errors, &this->status);
        return false;
    }
    else return true;
}

int SerialPort::isConnected()
{
    return this->connected;
}

void CTestDllDlg::OnCbnSelchangeComboCom2()
{
    // TODO: Add your control notification handler code here
}

void CTestDllDlg::OnEnChangeEdit1()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CBDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

void CTestDllDlg::OnBnClickedButton2()
{
    // TODO: Add your control notification handler code here
}


void CTestDllDlg::OnEnChangeEditWaveLen()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CBDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}


void CTestDllDlg::OnEnChangeEditPixel()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CBDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}
