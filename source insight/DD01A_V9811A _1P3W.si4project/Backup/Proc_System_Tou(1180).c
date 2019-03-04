/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_Tou.c
**Author		: maji
**date			: 2016-04-20
**description	: ϵͳʱ�괥����Ĵ������C����
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>



RTC_TYPE gs_CurDateTime;
TOU_VAR  gs_tou_var;
AUTO_ClrMeter_VAR  gs_auto_clrMeter_var;



/*****************************************************************************
** Function name    :Proc_get_clock
**
** Description         :��ȡ��ǰRTC ʱ��ȫ�ֱ�������  
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void Proc_get_clock(void)
{
 RTC_TYPE rtc_data_tmp;

    //��ȡ��ǰʱ����������   //
    Get_RTCTime(&rtc_data_tmp);  
    if(Lib_Check_RTC_data_FORM(&rtc_data_tmp.Week) ==FALSE)
    {
        mem_read(&rtc_data_tmp.Week, ADR_METER_VAR_RTC, 7, MEM_E2P1);
        if(Lib_Check_RTC_data_FORM(&rtc_data_tmp.Week) ==FALSE)
       {
            // Ĭ�� 2016-4-20  12:30:30   WEEKDAY=3(��3) //
            rtc_data_tmp.Week= 3;       
            rtc_data_tmp.Year = 0x16;
            rtc_data_tmp.Month = 0x04;
            rtc_data_tmp.Day= 0x20;
            rtc_data_tmp.Hour= 0x12;
            rtc_data_tmp.Minute= 0x30;
            rtc_data_tmp.Second= 0x30;
            mem_db_write(ADR_METER_VAR_RTC, &rtc_data_tmp.Week, 7, MEM_E2P1);
        }
        Set_RTCTime(&rtc_data_tmp);   
    }
    Lib_Copy_Str_TwoArry(&gs_CurDateTime.Week, &rtc_data_tmp.Week, 7);    //���ݸ�ֵ //
}


/*****************************************************************************
** Function name    :Proc_init_tou_var
**
** Description         :��ȡ��ǰRTC ʱ��ȫ�ֱ�������  
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void Proc_init_tou_var(void)
{
    Proc_get_clock();
      
}


/*****************************************************************************
** Function name    :Proc_handl_tou_10ms
**
** Description         :10ms�жϲ�����ĳ�����        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void Proc_handl_tou_10ms(void)
{
 uint8 i;
    
    //ͨѶ����10ms ���� //
    for(i=0;i<UART_CH_NUM;i++)
    {
        Hdl_UART_10ms_run(i);
        api_handl_COMM_pre_10ms(i);
    }
     
}



/*****************************************************************************
** Function name    :Proc_handl_tou_10ms
**
** Description         :10ms�жϲ�����ĳ�����        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void Proc_handl_tou_1s(void)
{
//	int i;

//	NEW_MMD_DATA_UNIT st_mmd_unit;
//	SUM_MMD_DATA_UNIT sum_st_mmd_unit;
	Proc_get_clock();
//	mem_db_check();
	CLRWDT();	// �忴�Ź�//
	if(gs_emu_run_var.delay_emu>0)
	{
		 gs_emu_run_var.delay_emu--;//emu�ȶ�ʱ��Ϊ3��
		 api_Measure_ram_INIT();
	}
	//�����ȶ���ɨ���¼�
	if(gs_emu_run_var.delay_emu==0)
	{
		// ˲ʱ����ȡ//
		// OpenCF();
		api_measure_deal_pre_second();
		CLRWDT();	// �忴�Ź�//
		//���������봦�� //
		api_accum_current_energy_data_pre_second();
		CLRWDT();   // �忴�Ź�//
		api_even_Detect_sec();
		//��������㴦�� //
		api_updata_md_var_min_per_second(); 
		CLRWDT();	// �忴�Ź�//
		//Ӳ���̽��������봦��//   
		Proc_Check_PROKEY_Pre_sec();
		//LED��״̬ˢ��//
		api_updated_LED_per_second();
		api_measure_VBAT_pre_min();   
	}
	 // ��ʾ��Ŀÿ��ı䴦��//        
    api_updated_LCDDisplayItem_per_second();    
     // ��ʾ����ÿ����´���//                
    api_updated_LCDDisplayPixel_per_second();
     //���Ӽ�����  //
    if(gs_CurDateTime.Second == 0)
    {
		Check_EMU_AdjParam();
		CLRWDT();	// �忴�Ź�//
		api_updata_md_var_slid_per_minute();   
		CLRWDT();	// �忴�Ź�//
        #if (BILL_MAX_NUM>0)
        api_handl_settle_per_minute();
		CLRWDT();	// �忴�Ź�//
        #endif
		LoadPro_Rec();         
		CLRWDT();	// �忴�Ź�//
        #if (TARIFF_MAX_NUM>1)
        api_update_triffNo_pre_minute();  
        #endif
		api_freeze_energy_Ram_pre_day();
		api_freeze_energy_pre_day(); 	
			 
    }

     if(gs_CurDateTime.Second == 0x25)
     {
        Handl_RTC_Adj_per_minu();   
		CLRWDT();	// �忴�Ź�//
     }  

  
    if(gs_CurDateTime.Second == 0x31)
     {
       api_measure_temperature_pre_min();   
	   CLRWDT();   // �忴�Ź�//
     } 

	
}


//-------------------------------------------------------------------------------//
//  Function:      void get_default_mem_data(INT8U index)     
//  Description:  
//  Parameters:   ��  
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
void  Proc_Auto_ClrMeter_Pre_sec(void)
{

   ;
}

//-------------------------------------------------------------------------------//
//  Function:      void get_default_mem_data(INT8U index)     
//  Description:  
//  Parameters:   ��  
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//


void  Initlize_Auto_ClrMeter_Var(void)
{

	gs_auto_clrMeter_var.u8_sec_cnt=0;
	gs_auto_clrMeter_var.u8_flg = 0;

}





/***************************************************************
*    END
****************************************************************/

