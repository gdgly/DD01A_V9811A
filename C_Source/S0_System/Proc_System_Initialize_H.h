/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_System_Initialize_H.H
**Author		: maji
**date			: 2016-04-20 
**description	: ϵͳ��λ��ʼ���������C����������ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#ifndef _Proc_System_Initialize_H
#define _Proc_System_Initialize_H

/***************************************************************
*    1     ������Ԥ����   
****************************************************************/
#define POWER_OFF  0
#define POWER_ON   1
#define POWER_RESET 2

/***************************************************************
*    2     ���ݽṹ����     
****************************************************************/
// struct define of realy clock time //




/***************************************************************
*    3    ��������       
****************************************************************/




/***************************************************************
*    4     ��������        
****************************************************************/
extern void Proc_Initialize_INRam(void);
extern void Proc_sleep_when_reset(void);
extern void Proc_Initialize_systerm_normal_mode(void);
extern void Proc_Initialize_systerm_reset(void);
extern void Proc_judge_Power_down_process(void);
extern void sys_err(void);
extern void Proc_handle_when_systerm_reset(void);


/***************************************************************
*    5     �������ݣ�����αָ���       
****************************************************************/



/***************************************************************
*    END
****************************************************************/

#endif