/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_Adj_H.H
**Author		: maji
**date			: 2016-05-09 
**description	: G80F92XD��EMU����ģ����·��У����C����������ļ�
**note			: MCU- G80F92XD ��MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-05-09   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#ifndef _Lnk_EMU_Adj_H
#define _Lnk_EMU_Adj_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
// �Զ�У��������������//
#define HARD_EADJ_STEP0_L_INITLIZE    0  // ���ص���У׼  //
#define HARD_EADJ_STEP1_L_100IB_100L    1  // ���ص���У׼  //
#define HARD_EADJ_STEP2_L_100IB_50L    2  // ���ص���У׼  //
#define HARD_EADJ_STEP3_L_5IB_100L    3  // ���ص���У׼  //
#define HARD_EADJ_STEP4_N_INITLIZE    4  // ���ص���У׼  //
#define HARD_EADJ_STEP5_N_100IB_100L    5  // ���ص���У׼  //
#define HARD_EADJ_STEP6_N_100IB_50L    6  // ���ص���У׼  //
#define HARD_EADJ_STEP7_N_5IB_100L    7  // ���ص���У׼  //
#define HARD_EADJ_STEP8_METER_CLR    8  // ������㴦��//

// ����У׼��ز������ο������ĵ��м������ڵ����ݽ��и�ֵ //
#define INITGATECP 		0x927C00      // 
#define INITGATECQ 		INITGATECP      //  �޹�Ǳ������ 0.1%//

#define INITGATEP  		73508912//E1���� ���������ֲ�ļ�����������*0.9 60hz����ֵ����1.2�� // 
#define INITGATEQ  		(INITGATEP*1.568)// E2�޹�����//
#define INITGATEP_10M  	(INITGATEP/10L)//��������10������Ӧ������ֵӦ��С10��  yang 2017-12-28
#define INITGATEQ_10M  	(INITGATEQ/10L)//��������10������Ӧ������ֵӦ��С10��  yang 2017-12-28

// soc  �Ĺ�������ֵ
#define REF_RMSPn          6534125L   //���ѹ�ͻ�����������й���������ֵ //  
#define REF_RMSPn_9260     6534125L   //���ѹ�ͻ�����������й���������ֵ //  


#define K_RMSP              0.003673042f  //9811�й�����ϵ�� 
#define K_RMSP2             0.003673042f  //�޹�����ϵ��

#define REF_START_Pn          ((uint32) (REF_RMSPn*0.001f))       //��������0.001 �Ļ����㹦�ʱ�׼ֵ //  
#define REF_START_REV_Pn      ((~((uint32)(REF_RMSPn*0.001f)))+1) //��������0.001 �Ļ����㹦�ʱ�׼ֵ //  



/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
typedef struct
{
    uint32 w1gain;          //ͨ��1��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    uint32 p1cal;           //ͨ��1��ѹ������λ�����Ĵ���  //
    uint32 watt1os;        //ͨ��1�й�����ƫ��  //
    uint32 irms1os;        //ͨ��1������Чֵƫ��  //
    uint32 w2gain;          //ͨ��2��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    uint32 p2cal;           //ͨ��2��ѹ������λ�����Ĵ���  //
    uint32 watt2os;        //ͨ��2�й�����ƫ��  //
    uint32 irms2os;        //ͨ��2������Чֵƫ��  //
    uint32 urmsos;        //��ѹ��Чֵƫ��  //
    float vconst_val_ch1;   //ͨ��1�����ߵ�ѹ�̶�ֵ //    
    float vconst_val_ch2;   //ͨ��2�����ߵ�ѹ�̶�ֵ //
    float vrms_xs;          //��Ϊ����ĵ�ѹ��Чֵϵ��  //
    float i1rms_xs;         //��Ϊ�����ͨ��1������Чֵϵ��  //
    float i2rms_xs;         //��Ϊ�����ͨ��2������Чֵϵ��  //
    uint16     csck;  		//У��� //
}ST_EMU_ADJ_PARAM;


typedef struct
{
    uint32 U_ref;       //�αȵ�ѹֵ������0.1V  // 
    uint32 I_ref;       //�αȵ���ֵ������0.001A  //     
    uint32 C_GATEP;    // ��������ֵ //
    uint32 C_GATECP;   // Ǳ������ֵ //
    uint32 C_PCONST;   // ����ʵ�У׼���׼ֵ//
    float   Kim_Prms;      //�й�������Чֵϵ��//
    float   Kim_Prms2;     //�޹�������Чֵϵ��//
}ST_Adjust_CONST;

typedef struct 
{
    uint8   sec_flg;  //У׼�����е���仯��ʶ//
    uint8   adj_flg;  //У�����״̬��=0X55����У������� //
} ST_EMU_ADJ_VAR;


typedef struct 
{
    uint32   *ramAdr;                            //������ַ //
    uint16    emuAdr;                            //�Ĵ�����ַ //
}EMU_CK_TAB;   

typedef struct 
{
    uint32   val;                               //��������//
    uint16    emuAdr;                      //�Ĵ�����ַ //
}EMU_CONST_CK_TAB;   



typedef struct 
{
    uint32   val_9260F;                               //��������//
    uint16    emuAdr_9260F;                      //�Ĵ�����ַ //
}EMU_CONST_CK_TAB_9260F;   

/***************************************************************
*    3    ��������       
****************************************************************/
extern const  ST_EMU_ADJ_PARAM  code   default_adj_emu_param_tab;
extern const  ST_Adjust_CONST  code   cst_adj_const;
extern const  EMU_CK_TAB  code   cst_emu_selfchck_tab[];
extern const  EMU_CONST_CK_TAB  code   cst_emu_constchck_tab[];

extern ST_EMU_ADJ_PARAM  gs_adj_emu_param;
extern ST_EMU_ADJ_VAR      gs_emu_adj_var;


extern const  EMU_CONST_CK_TAB_9260F  code   cst_emu_constchck_tab_9260f[];
/***************************************************************
*    4     ��������        
****************************************************************/
extern void Get_EMU_AdjParam(void);
extern void Check_EMU_AdjParam(void);
extern void Hardware_AdjustDiv_Sub(void);
extern void Save_EMU_AdjParam(void);

extern void Measure_Electric_Err_Gain(INT8U *sptr);
extern void Calibration_Power(float f_err_data);
extern void Calibration_Current(INT32U Current,INT32U Voltage);
extern void Calibration_Angular(float f_err_data);
extern void Calibration_small_signal(float f_err_data);

extern uint32 CalculateSChz(int16 error,int32 LastSC);
/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/



/***************************************************************
*    END
****************************************************************/
#endif

