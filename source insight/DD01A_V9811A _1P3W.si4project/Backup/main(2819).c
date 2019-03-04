/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name          : main.c
**Author		: maji
**date           : 2016-04-20
**description	: main ������C�ļ�
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>

uint8  debug_tmp1;

/****************************************************************
Function:  		void main(void)   
Description: 		ϵͳ������
Input:
Parameters:     
Returns:                                
Others:         
****************************************************************/
void main(void)
{
    NOP();
    CLRWDT();     
    DisableINT();    				// disable interrupt function  //
    Proc_Initialize_systerm_reset();  
    EnableINT();
    NOP();    	


    while(1)
    {
    CLRWDT();   // �忴�Ź�//
    if(CheckPOWERUP()==TRUE)    
    {
		 //RFͨѶ����					   //
//		 api_RF_comm_deal();
//		 CLRWDT();	 // �忴�Ź�//
//		 api_RF_judge_tx();
//		 CLRWDT();	 // �忴�Ź�//
//		 api_RF_judge_tx_over_delay();
		    CLRWDT();	 // �忴�Ź�//
        if(gs_sys_run.back_fg&BIT0_FONT_FG_10MS)
        {
            gs_sys_run.back_fg &= ~BIT0_FONT_FG_10MS;
            Proc_handl_tou_10ms();
        }
		  // �ϵ�״̬�µĵ�Դ������  //	
		    Proc_judge_Power_down_process();	  
        if(gs_sys_run.back_fg&BIT1_BACK_FG_RTC)
        {
            gs_sys_run.back_fg &= ~BIT1_BACK_FG_RTC;
            Proc_handl_tou_1s();
        }
		  // �ϵ�״̬�µĵ�Դ������  //	
		Proc_judge_Power_down_process();	  
		Drv_relay_run_check();   //�̵�������״̬���  //
		CLRWDT();	// �忴�Ź�//
    }
	   	 // �ϵ�״̬�µĵ�Դ������  //   
       Proc_judge_Power_down_process();      
}

}


/***************************************************************
*    END
****************************************************************/

