#if !defined(BROLIGHT_SP_DLL_INCLUDED_)
#define BROLIGHT_SP_DLL_INCLUDED_
typedef struct {
    BOOL   m_bState;
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
    double Cab;//�ʶ�
    double Hab;//ɫ����
    double YI;
    double Rratio;//��ɫ��
    double fCTA;//ɫ�ݲ�
    double *m_dArrIrrad;
    BOOL bIsComplementaryColor;
} tag_Color_Result;
/*************************************************
Function:   GetAllDevices
Description:    �����豸
Input:      Port�豸ͨѶ�˿ڣ�NumOfPort��ЧͨѶ�˿�����
Output:     ��
Return:     �ɹ�����TRUE�����򷵻�FALSE
*************************************************/
BOOL __stdcall SPGetAllDevices(UINT *Port, unsigned int * NumOfPort);

/*************************************************
Function:   SPConnect
Description:    �����豸
Input:      comport �豸ͨѶ����
Output:     ��
Return:     �ɹ������豸��������򷵻�0
*************************************************/
int __stdcall SPConnect(int ComPort);

/*************************************************
Function:   SPConfig
Description: ����CCD�źŲɼ�����
Input:      DevID���豸���
            dwIntegrateTime,CCD����ʱ��,�������ֵΪ0,�򲻸ı����������ԭֵ,��λus
            BoxCar�˲�����,����ֵΪ0���������ֵΪ0,�򲻸ı����������ԭֵ
            TriggerMode ����ģʽ��0X11������ģʽ��0x12���������0x13Ӳ��������0x14ͬ������,����0���򲻸ı������ԭֵ��
Return:     �ɹ�����TRUE,ʧ�ܷ���FALSE
*************************************************/
BOOL __stdcall SPConfig(int DevID, DWORD dwIntegrateTime, int BoxCar, int TriggerMode);



/*************************************************
Function:   SPReadWordCCD
Description:    ��ȡCCD����
Input:      DevID���豸�����SPConnect��������ֵ��
Output:     CCDData�����ص����ݣ���7424���ֽڣ���0x010102020303��ͷ��0x55665566��β��
Return:     ���ض��������ݵ�����
*************************************************/
UINT __stdcall      SPReadWordCCD(int DevID, WORD *CCDData);


/*************************************************
Function:   SPReadDoubleCCD
Description:    ��ȡCCD����
Input:      DevID���豸�����SPConnect��������ֵ
Output:     fCCDData�����ص����ݣ�
Return:     ���ض��������ݵĸ���
*************************************************/
int __stdcall       SPReadDoubleCCD(int DevID, double *fCCDData);

/*************************************************
Function:   SPReadDoubleCCDAvg
Description:    ��ȡCCD����
Input:      DevID���豸�����SPConnect��������ֵ
            AvgTimes  ƽ������
Output:     fCCDData�����ص�����
Return:     ���ض��������ݵĸ���
*************************************************/
int __stdcall       SPReadDoubleCCDAvg(int DevID, double *fCCDData, int AvgTimes);

/*************************************************
Function:   SPWaveLengthToPixel
Description:    ��������벨���Ļ���
Input:      DevID���豸�����SPConnect��������ֵ��fWaveLen��������
Return:     ���ض�Ӧ������ţ���Ŵ�0��ʼ
*************************************************/
int __stdcall       SPWaveLengthToPixel(int DevID, double fWaveLen);


/*************************************************
Function:   SPPixelToWaveLength
Description:    ��������벨���Ļ���
Input:      DevID���豸�����SPConnect��������ֵ��n��������ţ���Ŵ�1��ʼ��
Return:     ����
*************************************************/
double __stdcall SPPixelToWaveLength(int DevID, UINT n);



/*************************************************
Function:   SPClose
Description:    �ر��豸
Input:      DevID���豸�����SPConnect��������ֵ;
Output:     ��
Return:     �ɹ�����TRUE,���򷵻�FALSE
*************************************************/
BOOL __stdcall SPClose(int DevID);


/*************************************************
Function:   GetDllVer
Description:    ��ȡDLL�汾��Ϣ
Input:      ��
Output:     ver������汾��Ϣ
Return:     TRUE
*************************************************/
BOOL __stdcall GetDllVer(char *ver);

/****************************************************************************************
@ Function: SPGetDeviceModelName
@ Desc:      ��ȡ�豸���ͺ�
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ ModelName: �������豸�ͺ�
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetDeviceModelName(int DevID, char*ModelName);

/****************************************************************************************
@ Function:  SPGetSN
@ Desc:      ��ȡ�豸�����к�
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ SN:        �������豸�����к�
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetSN(int DevID, char *SN);

/****************************************************************************************
@ Function:  SPGetCalData(old)
@ Desc:      ��ȡ��������λ���еĲ����궨ϵ��
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ C:         ���飬�����궨ϵ�����α���C0��C1��C2��C3
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetCalData(int DevID, double C[4]);

/****************************************************************************************
@ Function:  SPGetFirmWareVer
@ Desc:      ��ȡ��������λ���еĹ̼��汾
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ Firmware:  ��ȡ�Ĺ̼��汾��Ϣ
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetFirmWareVer(int DevID, char* Firmware);

/****************************************************************************************
@ Function:  SPGetCCDInfo
@ Desc:      ��ȡ������CCD�������Ϣ
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ nPixels:   �ܵ����أ���3651
@ nStartPos: ��ʼ��Ч���ص����
@ BackLightIntensity:    ��������ֵ
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetCCDInfo(int DevID, int*nPixels, int *nStartPos, int *BackLightIntensity);

/****************************************************************************************
@ Function:  SPGetWaveLengthRange
@ Desc:      ��ȡ������CCD�Ĳ�����Χ
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ min:       ��С��������λnm
@ max:       ��󲨳�����λnm
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetWaveLengthRange(int DevID, double *min, double *max);

/****************************************************************************************
@ Function:  SPGetResolution
@ Desc:      ��ȡ�����ǵķֱ���
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ Resolution: �ֱ��ʣ���λnm
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetResolution(int DevID, char* Resolution);

/****************************************************************************************
@ Function:  SPGetResolution
@ Desc:      ��ȡ�����ǵ�������
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ slit:      ��������Ϣ�ַ���
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetSlit(int DevID, char* slit);

/****************************************************************************************
@ Function:  SPGetComProtocol
@ Desc:      ��ȡ�����ǵ�ͨѶЭ��汾
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ return     ͨѶЭ��汾��
****************************************************************************************/
WORD __stdcall SPGetComProtocol(int DevID);

/****************************************************************************************
@ Function:  SPReadDevDesc
@ Desc:      ��ȡ�����ǵĲ�����Ϣ
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ Desc��    ������Ϣ�ַ������ַ���ʽ���ͨѶЭ��
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPReadDevDesc(int DevID, char*Desc);


/****************************************************************************************
@ Function:  SPWriteDevDesc
@ Desc:      д������ǵĲ�����Ϣ
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ Desc��    ������Ϣ�ַ������ַ���ʽ���ͨѶЭ��
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPWriteDevDesc(int DevID, char*Desc, int len);

/****************************************************************************************
@ Function:  SPSetCalData
@ Desc:      д�벨���궨����
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ C��       �����궨�������飬C[0]λ0�η�ϵ����C[3]Ϊ3�η�ϵ��
@ strCalDate���궨����YYYYMMDD
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPSetCalData(int DevID, double C[4], char * strCalDate);

/****************************************************************************************
@ Function:  SPReadCalData (New)
@ Desc:      ��ȡ�����궨����
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ C��       �����궨�������飬C[0]λ0�η�ϵ����C[3]Ϊ3�η�ϵ��
@ strCalDate���궨����YYYYMMDD
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPReadCalData(int DevID, double C[4], char * strCalDate);

/****************************************************************************************
@ Function:  SPGetDeviceType
@ Desc:      ��ȡ�豸����
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ type��    �豸����
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetDeviceType(int DevID, int *type);

/****************************************************************************************
@ Function:  SPReset
@ Desc:      ��λ�豸
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPReset(int DevID);


/****************************************************************************************
@ Function:  SPGetIntegrateTimeRange
@ Desc:      ��ȡ�豸֧�ֵĻ���ʱ�䷶Χ����λus
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetIntegrateTimeRange(int DevID, UINT*min, UINT *max);

/****************************************************************************************
@ Function:  SPGetADDigits
@ Desc:      ��ȡA/Dת���ֱ��ʣ��������źŵ�λ��
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ return     �����źŵ�λ������16
****************************************************************************************/
int __stdcall SPGetADDigits(int DevID);
/****************************************************************************************
@ Function:  SPGetState
@ Desc:      ��ȡ�����ǵ�״̬
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ return     �����ǵ�״̬
****************************************************************************************/
DWORD  __stdcall SPGetState(int DevID);

/****************************************************************************************
@ Function:  SPSetState
@ Desc:      ��ǹ����ǵ�״̬
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ state:     �����ǵ�״̬;
@ return     ��
****************************************************************************************/
void  __stdcall  SPSetState(int DevID, DWORD state);

/****************************************************************************************
@ Function:  SPSetStandardLampSpectrum
@ Desc:      �����׼��Դ�Ĺ�������
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ wave:      ��׼��Դ�Ĳ�����������;
@ pow:       ��׼��Դ�Ĺ�ǿ��������;
@ cnt:       �����С;
@ T:         ��׼��Դ��ɫ��
@ return     TRUE/FALSE
****************************************************************************************/
BOOL  __stdcall SPSetStandardLampSpectrum(int DevID, double *wave, double *pow, int cnt, double T);

/****************************************************************************************
@ Function:  SPProcessSpectrum
@ Desc:      ������Թ�Դ�Ĺ�������
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ wave:      ���Թ�Դ�Ĳ�����������;
@ pow:       ���Թ�Դ�Ĺ�ǿ��������;
@ cnt:       �����С;
@ return     ɫ�ȷ��������
****************************************************************************************/
tag_Color_Result __stdcall SPProcessSpectrum(int DevID, double *wave, double *pow, int cnt);
BOOL __stdcall SPReadDepCalData(int DevID, WORD *nStart, WORD*nEnd, float *fData);
BOOL __stdcall SPWriteDepCalData(int DevID, WORD nStart, WORD nEnd, float *fData);
/****************************************************************************************
@ Function:  SPSetTriggerPulse
@ Desc:      ����ͬ����������ź�
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ DevID:     wHighLevelWidth������ߵ�ƽ����ʱ�䣬��λms;
@ DevID:     wLowLevelWidth�� ����͵�ƽ����ʱ�䣬��λms;
@ DevID:     PulseNumber����һ�������������������������;
@ DevID:     EnableTiggerPulseOutput��ֵΪ0ʱ���رմ������������ֵΪ1ʱ���򿪴�����������Ĺ���;
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPSetTriggerPulse(int DevID, WORD wHighLevelWidth, WORD wLowLevelWidth, BYTE PulseNumber, BYTE EnableTiggerPulseOutput);

/****************************************************************************************
@ Function:  SPGetGratting
@ Desc:      ��ȡ���ù�դ��Ϣ
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ Filter:    ��դ��Ϣ;
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetGratting(int DevID, char* Gratting);

/****************************************************************************************
@ Function:  SPGetLens
@ Desc:      ��ȡ������͸����Ϣ
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ Filter:    ��͸����Ϣ;
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetLens(int DevID, char* Lens);

/****************************************************************************************
@ Function:  SPGetFilter
@ Desc:      ��ȡ�����˹�Ƭ��Ϣ
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ Filter:    �˹�Ƭ��Ϣ;
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPGetFilter(int DevID, char* Filter);

/****************************************************************************************
@ Function:  SPReadNLCalData
@ Desc:      ��ȡ��������ϵ��
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ Data:      ��������ϵ������;
@ cnt��      ��������ϵ������
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPReadNLCalData(int DevID, double *Data, int *cnt);

/****************************************************************************************
@ Function:  SPWriteNLCalData
@ Desc:      д����������������������
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ DataStr:   ��������ϵ���ַ���
@ len :      �ַ�������
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPWriteNLCalData(int DevID, char *DataStr, int len);

/****************************************************************************************
@ Function:  SPCheckNonLinearCorrection
@ Desc:      �򿪹ر���������
@ DevID:     DevID���豸�����SPConnect��������ֵ;
@ ONOFF:     0:�ر�����������1:����������;
@ return     TRUE/FALSE
****************************************************************************************/
BOOL __stdcall SPCheckNonLinearCorrection(int DevID,int ONOFF);
#endif




