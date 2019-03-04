/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: SYS_Config_H.H
**Author		: maji
**date			: 2016-04-26
**description	: define for main config 
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/



#ifndef 	_SYS_Config_H
#define	_SYS_Config_H

// ϵͳ��Ƶ //
#define	  FSYSCLK_800k		 819200			  //ϵͳ������Ƶ819.2KHZ // 
#define	  FSYSCLK_1M6		 (FSYSCLK_800k*2	)		 //ϵͳ������Ƶ819.2KHZ // 
#define	  FSYSCLK_3M2		 (FSYSCLK_800k*4	)		 //ϵͳ������Ƶ819.2KHZ // 
#define	  FSYSCLK_6M5		 (FSYSCLK_800k*8	)		 //ϵͳ������Ƶ819.2KHZ // 
#define	  FSYSCLK_13M		 (FSYSCLK_800k*16)		 //ϵͳ������Ƶ819.2KHZ // 
#define	  FSYSCLK_26M		 (FSYSCLK_800k*32)		 //ϵͳ������Ƶ819.2KHZ // 


#define	  FSYSCLK			 FSYSCLK_3M2//FSYSCLK_6M5			 //ϵͳƵ��6M5  //


//#define _DEBUGE_FUNCTION    // ����Ҫ����ʱ���α��� mj 2016-8-1 //

//******************************************************************
//	���ݴ�С�˶��壬
//   C51Ϊ��ˣ�32λ���ݸ�8λ�ֽڴ洢�ڵ�ַ[0]	//
//   MDK�е�M0ΪС�ˣ�32λ���ݵ�8λ�ֽڴ洢�ڵ�ַ[0]	
//******************************************************************
//#define LITTLE_END      // ������ЧΪС��ģʽ,����ע�͵�Ϊ���ģʽ//

// ���ܱ����//
#define METER_CONST  1000UL
#define METER_CONST_1KWH  METER_CONST
#define METER_CONST_10WH  ((uint8)(METER_CONST/100UL))
#define METER_CONST_10WH_BCD  0X10

#define       C_Un             240U                //���ѹ  //
#define       C_Ib             10U                  //����� //
#define       C_Fq             60U                  //�Ƶ�� //

//  ���ܱ�����//
#define PHASE	1  // ���� //
#define WIRE    2      // ���� //
#if (PHASE>1)
#define PHASE_MAX_UNM	PHASE+1  // �����ר�� //
#else
#define PHASE_MAX_UNM	PHASE     // �����ר�� //
#endif
//#endif

#define PHASE_TT  0   //����ͨ��  //
#define WIRE_L1  1	  //����� L1��//
#define WIRE_L2  2	  //����� L2��//
#define WIRE_L3  3	  //����� L3��//
#define WIRE_N   4	  // N��//


//�����������Χ//
#define MAX_ENERGY_INtEGER   99999999    // �����������Ϊ99999999 //


//  ���ܼ���ͨ����ض���  //
#define EC_CH_NUM   		 2      //  ���ܼ�����ͨ���� //
#define EC_CH_AC_PT_TT  	 0     //����0��  �������й�����//
#define EC_CH_RE_PT_TT       1     //����1��  �������޹�����
//#define EC_FOR_AC_NUM   	 1     //�й�����
//#define EC_REV_AC_NUM        2     // �й�����
//#define EC_CH_RE_PT_TT       3     //����3��  �������޹�����
//#define EC_FOR_REC_NUM   	 4     //�޹�����
//#define EC_REV_REC_NUM       5     //�޹�������

//  �����������ͨ����ض���  //
#define MD_CH_NUM   1   //  �����������ͨ�� //
#define MD_CH_AC_PT_TT   0   //����0��  �������й�����//
#define MD_CH_RE_PT_TT   1   //����0��  �޹�//

// ������������� //
#define BILL_MAX_NUM  6 // =0Ϊ�޽��㹦�ܣ�= 12Ϊ��12���½��� //



#define OTHER_EMU   1 //  ���EMU ����  1 ����� 0��soc

// ������ض��� //
#define TARIFF_MAX_NUM  4  // ������ //
#define TARIFF_T 0  // �ܷ���//
#define TARIFF1  1  //����1 //
#define TARIFF2  2  //����2 //
#define TARIFF3  3  //����3 //
#define TARIFF4  4  //����4 //


// ���ɼ�¼����



//16λ�ۼ�У��ͳ�ʼֵ  //
#define  CHECKWORD          0xa55a         // ˫�ֽ��ۼƺ�У�����   //


/***************************************************************
*    END
****************************************************************/

#endif

