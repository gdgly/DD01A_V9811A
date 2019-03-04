#ifndef __RACCOON_H__
#define __RACCOON_H__


#ifndef  RACCOONEXT
    #define RACCOONEXT extern
#else
    #define RACCOONSELF
#endif


//=============================================================
//RACCOON ģ����ƼĴ���  ANCtrl1��ANCtrl2����Ϊ0
//=============================================================
#define   RegANCtrl0   0x0185
#define   RegANCtrl1   0X0186
#define   RegANCtrl2   0X0187

//=============================================================
//RACCOON �������üĴ���  
//=============================================================
#define   RegMTPARA0   0x0183
#define   RegMTPARA1   0x0184   // �ǲ�����Ϊ8-15λ   0x00F0  

//=============================================================
//RACCOON ϵͳ���üĴ���  
//=============================================================
#define   RegSysCtrl   0x0180

//=============================================================
//RACCOON ֱ�������Ĵ���  
//=============================================================
#define   RegDCU       0x0114
#define   RegDCI       0x0115
#define   RegDCM       0x0116
#define   RegDCIM      0x00F9
#define   RegDCVTM     0x00FB
#define   RegDCVDCM1   0x00FD
#define   RegDCVDCM2   0x00FF
#define   RegDCTM      0x0101

//=============================================================
//RACCOON Ƶ�ʼĴ���  
//=============================================================
#define   RegFREQ      0x019A
#define   RegSAFREQ    0x011D
#define   RegAFREQ     0x011E

//=============================================================
//RACCOON ��ѹ/����/Mͨ����Чֵ�Ĵ���  
//=============================================================
#define   RegARRTI     0x0105
#define   RegARRTU     0x0104
#define   RegARRTM     0x0106
#define   RegBRRTU     0x0109
#define   RegBRRTI     0x010A
#define   RegARTI      0x010E
#define   RegARTU      0x010D
#define   RegARTM      0x010F
#define   RegARTIM     0x00F8
#define   RegARVTM     0x00FA
#define   RegARVDCM1   0x00FC
#define   RegARVDCM2   0x00FE
#define   RegARTMM     0x0100
#define   RegBRTU      0x0112
#define   RegBRTI      0x0113
#define   RegAARTI     0x011C
#define   RegAARTU     0x011B
#define   RegAARTM     0x0117
#define   RegABRTU     0x0121
#define   RegABRTI     0x0122

//=============================================================
//RACCOON �й�/�޹����ʼĴ���  
//=============================================================
#define   RegRAP       0x0102
#define   RegRAQ       0x0103
#define   RegRBP       0x0107
#define   RegRBQ       0x0108
#define   RegIAP       0x010B
#define   RegIAQ       0x010C
#define   RegIBP       0x0110
#define   RegIBQ       0x0111
#define   RegAAP       0x0119
#define   RegAAQ       0x011A
#define   RegABP       0x011F
#define   RegABQ       0x0120


//=============================================================
//RACCOON �й�/�޹������ۼӡ�CF���巧�Ĵ���  
//=============================================================
#define   RegPEGY      0x01A1
#define   RegNEGY      0x01A2
#define   RegPCFCNT    0x01A3
#define   RegNCFCNT    0x01A4


//=============================================================
//RACCOON Ԥ��ֱ��ƫ��ֵ�Ĵ���  
//=============================================================
#define   RegZZDCI     0x0123
#define   RegZZDCU     0x0124

//=============================================================
//RACCOON ��ѹ/����/����ֵ��ЧֵУ���Ĵ���  
//=============================================================
#define   RegWARTI     0x012C
#define   RegWARTU     0x0132
#define   RegWARTM     0x012D
#define   RegWBRTI     0x0126
#define   RegWBRTU     0x012B

//=============================================================
//RACCOON ȫ���й�/�޹�����У���Ĵ���  
//=============================================================
#define   RegWAPT      0x012E
#define   RegWAQT      0x0130
#define   RegWWAPT     0x012F
#define   RegWWAQT     0x0131
#define   RegWBPT      0x0127
#define   RegWBQT      0x0129
#define   RegWWBPT     0x0128
#define   RegWWBQT     0x012A

//=============================================================
//RACCOON ����ֵ�Ĵ���  
//=============================================================
#define   RegEGYTH     0x0181
#define   RegCTH       0x0182
#define   RegIDETTH    0x0134

//=============================================================
//RACCOON У��ͼĴ���  
//=============================================================
#define   RegCKSUM     0x0133


//=============================================================
//RACCOON ��ͨ�˲���ϵ���Ĵ���  
//=============================================================
#define   RegBPFPARA   0x0125

//=============================================================
//RACCOON ����ֵ�Ĵ���  
//=============================================================
#define   RegDATACP    0x0189


//=============================================================
//��������:RACCOON�Ĵӻ���ַ
//
//=============================================================


//������Ϊ�˱���ͨ��

////����/�������ݼĴ���
/*
#define DATAP       0x0119
#define DATAQ       0x10d7
#define RMSU        0x011B
#define RMSI1       0x011C
#define RMSI2       0x0117

#define RAP         0x0102  //ȫ���й�����ԭʼֵ
#define RAQ         0x0103  //ȫ���޹�����ԭʼֵ
#define ARRTU       0x0104  //ȫ��������Чֵ��ԭʼֵ
#define ARRTI       0x0105  //ȫ����ѹ��Чֵ��ԭʼֵ
 
//
#define DATAFREQ    0x011D
//
*/
//������Ϊ�˱���ͨ��


#define Slave0  0
#define Slave1  1
#define Slave2  2
#define Slave3  3

#define SlaveNum    Slave0
//#define HZCONST   3200*256*10*1.0254
#define HZCONST   8192000

#define VARHZ   0x4c000

extern uint8 I_Dirct;
extern uint8 Aphy_Dly;
extern uint32 power,npower;



#define divf     3475      //8�ű�
#define divf1    3630      //8�ű�
#define divf2    3570      //8�ű�


#ifdef RACCOONSELF
uint16 const  RegAddrSoc[]=
{
    SCP,         //�й����ʱȲ�Ĵ���
    SCQ,         //�޹����ʱȲ�Ĵ���
    SCU,         //��ѹ��Чֵ�Ȳ�Ĵ���
    SCI1,        //������Чֵ�Ȳ�Ĵ���
    PARAPC,      //�й����ʶ��β����Ĵ��� 
    PARAQC,      //�޹����ʶ��β����Ĵ��� 
    PHCCtrl1,    //Iaͨ���ǲ�Ĵ���
};

uint16 const  RegAddrRac[]=
{
    RegANCtrl0,     //ģ����ƼĴ���0
    RegANCtrl1,     //ģ����ƼĴ���1
    RegANCtrl2,     //ģ����ƼĴ���2
    RegBPFPARA,     //��ͨ�˲���ϵ���Ĵ���
    RegMTPARA0,     //�������ƼĴ���0 
    
    RegMTPARA1,     //�������ƼĴ���1
    RegWARTU,       //ȫ����ѹ��Чֵ�Ȳ�Ĵ���
    RegWARTI,       //ȫ��������Чֵ�Ȳ�Ĵ��� 
    RegWAPT,        //ȫ���й����ʱȲ�Ĵ���
    RegWWAPT,       //ȫ���й����ʶ��β���ֵ�Ĵ���
    RegWWAQT,
};
#else
extern uint16 const  RegAddrSoc[];
extern uint16 const  RegAddrRac[];
#endif


//=============================================================
//�ṹ�壺У�����
//
//=============================================================
typedef struct
{
    uint32  Soc_SCP;             //�й����ʱȲ�Ĵ���
    uint32  Soc_SCQ;             //�޹����ʱȲ�Ĵ���
    uint32  Soc_SCU;             //��ѹ��Чֵ�Ȳ�Ĵ���
    uint32  Soc_SCI1;            //������Чֵ�Ȳ�Ĵ���
    uint32  Soc_PARAPC;          //�й����ʶ��β����Ĵ���                
    uint32  Soc_PARAQC;          //�޹����ʶ��β����Ĵ��� 
    uint8   Soc_PHCCtrl1;         //Iaͨ�� �ǲ�Ĵ���
}S_JBRESoc;


typedef struct
{
    uint32  Rac_MTPARA1;         //�������ƼĴ���1 �����ǲ�
    uint32  Rac_WARTU;           //ȫ����ѹ��Чֵ�Ȳ�Ĵ���
    uint32  Rac_WARTI;           //ȫ��������Чֵ�Ȳ�Ĵ���
    uint32  Rac_WAPT;            //ȫ���й����ʱȲ�Ĵ���
    uint32  Rac_WWAPT;           //ȫ���й����ʶ��β����Ĵ���                
    uint32  Rac_WWAQT;           //ȫ���޹����ʶ��β����Ĵ���                
}S_JBRERac;


typedef struct
{
    uint8  uc_80msCnt;            // С�ź��й�80MS  
    uint8  uc_80msCntRE;      //С�ź��޹�80ms
    uint8  uc_160msCnt;         //���ź��й�160ms
    uint8  uc_160msCntRE;   //���ź��޹�160ms
    uint16  uc_1280msCnt;     //��ƽ������
}S_IMPTIM;


RACCOONEXT S_IMPTIM gs_ipmtim;

typedef struct 
{
    uint16 ui_MeterC;           // ����
    uint16 ui_Un;               // ��Ƶ�ѹ
    uint16 ui_Ib;               // ��Ƶ���
    
    uint32  Com_EGYTH;          //�й�����ֵ�Ĵ���
    uint32  Com_REEGYTH;        //�޹�����ֵ�Ĵ���

    uint32  Rac_ANCtrl0;        //ģ����ƼĴ���0
    uint32  Rac_ANCtrl1;        //ģ����ƼĴ���1
    uint32  Rac_ANCtrl2;        //ģ����ƼĴ���2
    uint32  Rac_BPFPARA;        //��ͨ�˲���ϵ���Ĵ���
    uint32  Rac_MTPARA0;        //�������ƼĴ���0
    
    S_JBRESoc  gs_JBA;          //A��Ȳ���
    S_JBRERac  gs_JBB;          //B��Ȳ���

    uint32 ul_PG;               //A���й����ʱ���ϵ��
    uint32 ul_URmG;             //A���ѹͨ������ϵ��
    uint32 ul_I1RmG;            //A�����ͨ��1����ϵ��
    
    uint8  Soc_AnaG;             //A��ģ������(����M bit[7],U bit[6],IB bit[5:3],IA bit[2:0])

    uint16 u16_csck;            //  CS�ۼӺ�
//    uint16 ui_JbCRC;            // У�������CRC���
}S_JBPM;

RACCOONEXT S_JBPM gs_JbPm;            //У�����




//=============================================================
//��������:RACCOON�Ķ�д����
//
//=============================================================
#define APhy  0x08
#define BPhy  0x00
#define ABCPhy 0x03
#define RacRead  0x01
#define RacWrite 0x02 
#define RacBroadcast 0



#define   guc_Dy9260FOver           0x25        //ģ�⴮�ڳ�ʱ���� 370ms ͨѶ����? //


enum          //gs_RacCtrl.ucStatus����
{
  Rac_Idle=0,
  Rac_Send,
  Rac_Rev,
  Rac_WaitPro,
   
};

typedef struct 
{
  uint8 ucStatus;               
  uint8 ucSendLen;
  uint8 ucSendPoint;
  uint8 ucRevLen;
  uint8 ucRevPoint;
  uint8 ucBuf[100];
}S_RacCtrl;
RACCOONEXT S_RacCtrl gs_RacCtrl;


RACCOONEXT volatile uint8 guc_CommDelayTime;             //ͨѶ�ȴ���ʱ
RACCOONEXT volatile uint8 guc_CommDelayTime1;




typedef struct
{
    uint8 uc_Phystat;
    uint8 uc_Physendtim;
    uint8 uc_Sendstat;
    uint8 uc_Powstat;
    uint8 uc_flapara;
    uint8 uc_Uartstat;
}S_RacPhy;
RACCOONEXT S_RacPhy gs_RacPhy;
RACCOONEXT uint8 guc_cntA; //�������
RACCOONEXT uint8 guc_cntB; 

RACCOONEXT uint8 guc_powerdir;     //������
RACCOONEXT uint8 guc_start;   //��������ʼ
RACCOONEXT uint8 guc_powerdirA;     //������
RACCOONEXT uint8 guc_powerdirB;     //������
RACCOONEXT uint8 guc_powerdirAmid;     //�������м����
RACCOONEXT uint8 guc_powerdirBmid;     //�������м����



enum
{
     power_a = 0x01,
     power_b = 0x02,
     power_c = 0x04,
};


#define V9260Start_Send()       { SCON4|=BIT1; ExInt2IFG|=(BIT2); }


void Init_RacCtrl(void);
uint8 WriteRaccoon(uint32 Data,uint16 Addr,uint8 Phyadd);
uint8 ReadRaccoon(uint16 Addr,uint8 num,uint8 Phyadd);
void ReadRaccoonInt(uint16 Addr,uint8 num,uint8 Phyadd); 
void RxReset_V9260(void);
void InitRaccoon(void);
void V9260_InitDefaultPara(void);
void CheckRegSum(void);
void CheckSysErr(void);
uint8 UpdateRaccoonPara(void);
uint32 Read_Power(uint16 reg,uint8 phyadd);
void BroadcastWriteRaccoon(uint32 Data,uint16 Addr);
void UpdateRaccoonParABC(uint8 phyadd,uint8 pow);
void Accumulate_abc(void);
void  Init_9260F_EMU(void);

void ReadbackABCPhy(void);  

#endif
