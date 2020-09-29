#if !defined(BROLIGHT_SP_DLL_INCLUDED_)
#define BROLIGHT_SP_DLL_INCLUDED_
typedef struct {
    bool   m_bState;
    double m_dx;
    double m_dy;
    double m_dz;
    double m_dBigX;
    double m_dBigY;
    double m_dBigZ;
    double m_du;
    double m_dv;
    double m_duPrime; //           CIE1976UV - u
    double m_dvprime; //        -   CIE1976UV - v
    double m_dwprime; //        -   CIE1976UV

    double m_dPeakWavelength;
    double m_dPeakIntensity;
    double m_dDominantWavelength;
    double m_Pe;
    double m_dColorTemperature;

    double m_dRa;
    double m_dR1;
    double m_dR2;
    double m_dR3;
    double m_dR4;
    double m_dR5;
    double m_dR6;
    double m_dR7;
    double m_dR8;
    double m_dR9;
    double m_dR10;
    double m_dR11;
    double m_dR12;
    double m_dR13;
    double m_dR14;

    double Hunter_L;
    double Hunter_a;
    double Hunter_b;
    double CIE_L;
    double CIE_a;
    double CIE_b;
    double Cab;//彩度
    double Hab;//色调角
    double YI;
    double Rratio;//红色比
    double fCTA;//色容差
    double *m_dArrIrrad;
    bool bIsComplementaryColor;
} tag_Color;
/*************************************************
Function:   GetAllDevices
Description:    连接设备
Input:      Port设备通讯端口，NumOfPort有效通讯端口总数
Output:     无
Return:     成功返回TRUE，否则返回FALSE
*************************************************/
int __stdcall SPGetAllDevices(unsigned int *Port, unsigned int * NumOfPort);

/*************************************************
Function:   SPConnect
Description:    连接设备
Input:      comport 设备通讯串口
Output:     无
Return:     成功返回设备句柄，否则返回0
*************************************************/
int __stdcall SPConnect(int ComPort);

/*************************************************
Function:   SPConfig
Description: 设置CCD信号采集参数
Input:      DevID，设备句柄
            dwIntegrateTime,CCD积分时间,如果参数值为0,则不改变这个参数的原值,单位us
            BoxCar滤波参数,参数值为0，如果参数值为0,则不改变这个参数的原值
            TriggerMode 触发模式，0X11：正常模式，0x12软件触发，0x13硬件触发，0x14同步触发,传入0，则不改变参数的原值。
Return:     成功返回TRUE,失败返回FALSE
*************************************************/
int __stdcall SPConfig(int DevID, unsigned long int dwIntegrateTime, int BoxCar, int TriggerMode);



/*************************************************
Function:   SPReadWordCCD
Description:    读取CCD数据
Input:      DevID，设备句柄，SPConnect函数返回值；
Output:     CCDData，返回的数据，共7424个字节，以0x010102020303开头，0x55665566结尾的
Return:     返回读到的数据的数量
*************************************************/
int __stdcall      SPReadWordCCD(int DevID, int *CCDData);


/*************************************************
Function:   SPReadDoubleCCD
Description:    读取CCD数据
Input:      DevID，设备句柄，SPConnect函数返回值
Output:     fCCDData，返回的数据，
Return:     返回读到的数据的个数
*************************************************/
int __stdcall       SPReadDoubleCCD(int DevID, double *fCCDData);
int __stdcall       SPReadDoubleCCDAvg(int DevID, double* fCCDData, int AvgTimes);



/*************************************************
Function:   SPWaveLengthToPixel
Description:    像素序号与波长的换算
Input:      DevID，设备句柄，SPConnect函数返回值，fWaveLen，波长；
Return:     返回对应像素序号，序号从0开始
*************************************************/
int __stdcall       SPWaveLengthToPixel(int DevID, double fWaveLen);


/*************************************************
Function:   SPPixelToWaveLength
Description:    像素序号与波长的换算
Input:      DevID，设备句柄，SPConnect函数返回值；n，像素序号（序号从1开始）
Return:     波长
*************************************************/
double __stdcall SPPixelToWaveLength(int DevID, unsigned int n);



/*************************************************
Function:   SPClose
Description:    关闭设备
Input:      DevID，设备句柄，SPConnect函数返回值;
Output:     无
Return:     成功返回TRUE,否则返回FALSE
*************************************************/
int __stdcall SPClose(int DevID);


/*************************************************
Function:   GetDllVer
Description:    读取DLL版本信息
Input:      无
Output:     ver，输出版本信息
Return:     TRUE
*************************************************/
int __stdcall GetDllVer(char *ver);

/****************************************************************************************
@ Function: SPGetDeviceModelName
@ Desc:      读取设备的型号
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ ModelName: 读到的设备型号
@ return     TRUE/FALSE
****************************************************************************************/
int __stdcall SPGetDeviceModelName(int DevID, char*ModelName);

/****************************************************************************************
@ Function:  SPGetSN
@ Desc:      读取设备的序列号
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ SN:        读到的设备的序列号
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetSN(int DevID, char *SN);

/****************************************************************************************
@ Function:  SPGetCalData(old)
@ Desc:      读取保存在下位机中的波长标定系数
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ C:         数组，波长标定系数依次保存C0，C1，C2，C3
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetCalData(int DevID, double C[4]);

/****************************************************************************************
@ Function:  SPGetFirmWareVer
@ Desc:      读取保存在下位机中的固件版本
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ Firmware:  读取的固件版本信息
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetFirmWareVer(int DevID, char* Firmware);

/****************************************************************************************
@ Function:  SPGetCCDInfo
@ Desc:      读取光谱仪CCD的相关信息
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ nPixels:   总的像素，如3651
@ nStartPos: 起始有效像素的序号
@ BackLightIntensity:    背光亮度值
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetCCDInfo(int DevID, int*nPixels, int *nStartPos, int *BackLightIntensity);

/****************************************************************************************
@ Function:  SPGetWaveLengthRange
@ Desc:      读取光谱仪CCD的波长范围
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ min:       最小波长，单位nm
@ max:       最大波长，单位nm
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetWaveLengthRange(int DevID, double *min, double *max);

/****************************************************************************************
@ Function:  SPGetResolution
@ Desc:      读取光谱仪的分辨率
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ Resolution: 分辨率，单位nm
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetResolution(int DevID, char* Resolution);

/****************************************************************************************
@ Function:  SPGetResolution
@ Desc:      读取光谱仪的狭缝宽度
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ slit:      狭缝宽度信息字符串
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetSlit(int DevID, char* slit);

/****************************************************************************************
@ Function:  SPGetComProtocol
@ Desc:      读取光谱仪的通讯协议版本
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ return     通讯协议版本号
****************************************************************************************/
int __stdcall SPGetComProtocol(int DevID);

/****************************************************************************************
@ Function:  SPReadDevDesc
@ Desc:      读取光谱仪的参数信息
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ Desc：    参数信息字符串，字符格式请见通讯协议
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPReadDevDesc(int DevID, char*Desc);


/****************************************************************************************
@ Function:  SPWriteDevDesc
@ Desc:      写入光谱仪的参数信息
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ Desc：    参数信息字符串，字符格式请见通讯协议
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPWriteDevDesc(int DevID, char*Desc, int len);

/****************************************************************************************
@ Function:  SPSetCalData
@ Desc:      写入波长标定参数
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ C：       波长标定参数数组，C[0]位0次方系数，C[3]为3次方系数
@ strCalDate：标定日期YYYYMMDD
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPSetCalData(int DevID, double C[4], char * strCalDate);

/****************************************************************************************
@ Function:  SPReadCalData (New)
@ Desc:      读取波长标定参数
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ C：       波长标定参数数组，C[0]位0次方系数，C[3]为3次方系数
@ strCalDate：标定日期YYYYMMDD
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPReadCalData(int DevID, double C[4], char * strCalDate);

/****************************************************************************************
@ Function:  SPReadCalData
@ Desc:      读取设备类型
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ type：    设备类型
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetDeviceType(int DevID, int *type);

/****************************************************************************************
@ Function:  SPReset
@ Desc:      复位设备
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPReset(int DevID);


/****************************************************************************************
@ Function:  SPGetIntegrateTimeRange
@ Desc:      获取设备支持的积分时间范围，单位us
@ DevID:     DevID，设备句柄，SPConnect函数返回值;
@ return     TRUE/FALSE
****************************************************************************************/
bool __stdcall SPGetIntegrateTimeRange(int DevID, unsigned int*min, unsigned int *max);
int __stdcall SPGetADDigits(int DevID);
unsigned long int  __stdcall SPGetState(int DevID);
void  __stdcall  SPSetState(int DevID, unsigned long int state);
bool  __stdcall SPSetStandardLampSpectrum(int DevID, double *wave, double *pow, int cnt, double T);
tag_Color __stdcall SPProcessSpectrum(int DevID, double *wave, double *pow, int cnt);
#endif




