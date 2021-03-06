/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Proc_Tou.c
**Author		: maji
**date			: 2016-04-20
**description	: 系统时标触发后的处理相关C代码
**note			: V9811A ，MERTER FOR DL03C
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
uint8 button_flag = 0;
uint8 button_delay = 0;
uint8 MD_flag = 0;
uint8 MD_delay = 1;
uint8 MAGN_flag = 0;
uint8 MAGN_delay = 0;
uint8 MD_dis_delay = 0;
INT8U Bill_Data;
uint8 KEY_READ_FLAG = 0;
uint8 KEY_READ_DELAY = 0;
uint8 IsModeTest = FALSE;
uint8 TestDelay = 0;



/*****************************************************************************
** Function name    :Proc_get_clock
**
** Description         :获取当前RTC 时间全局变量数据  
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

    //获取当前时间数据数据   //
    Get_RTCTime(&rtc_data_tmp);  
    if(Lib_Check_RTC_data_FORM(&rtc_data_tmp.Week) ==FALSE)
    {
        mem_read(&rtc_data_tmp.Week, ADR_METER_VAR_RTC, 7, MEM_E2P1);
        if(Lib_Check_RTC_data_FORM(&rtc_data_tmp.Week) ==FALSE)
       {
            // 默认 2016-4-20  12:30:30   WEEKDAY=3(周3) //
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
    Lib_Copy_Str_TwoArry(&gs_CurDateTime.Week, &rtc_data_tmp.Week, 7);    //数据赋值 //
}


/*****************************************************************************
** Function name    :Proc_init_tou_var
**
** Description         :获取当前RTC 时间全局变量数据  
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
void api_handl_button_pre_10ms(void)
{
	if(Judge_ERR_COVER_key() == FALSE && KEY_READ_FLAG == 0)
	{
		KEY_READ_FLAG = 1;
		KEY_READ_DELAY = 3;		 //长按3秒进入test模式
	}
	if(Judge_ERR_COVER_key() == TRUE)
	{
		KEY_READ_FLAG = 0;
		KEY_READ_DELAY = 0;
	}
	if(Judge_PG_DN_key() == TRUE && button_delay == 0)
	{
		button_flag = 1;
		button_delay = 1;
	//	api_updated_LCDDisplayItem_per_second();
	}
	if(Judge_PG_DN_key() == FALSE)
	{
		button_delay = 0;
	}
	if(Judge_MD_CLEAR_key() == TRUE && MD_delay == 0)
	{
		MD_flag = 1;
		MD_delay = 1;
	}
	if(Judge_MD_CLEAR_key() == FALSE)
	{
		MD_delay = 0;
	}
	if(Judge_MAGN_CHK_key() == TRUE && MAGN_delay == 0)
	{
		MAGN_flag = 1;
		MAGN_delay = 1;
//			api_updated_LCDDisplayItem_per_second();
	} 
	if(Judge_MAGN_CHK_key() == FALSE)
	{
		MAGN_delay = 0;
	}
}


/*****************************************************************************
** Function name    :Proc_handl_tou_10ms
**
** Description         :10ms中断产生后的程序处理        
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

	//通讯串口10ms 处理 //
	for(i=0;i<UART_CH_NUM;i++)
	{
	    Hdl_UART_10ms_run(i);
	    api_handl_COMM_pre_10ms(i);
	}
	api_handl_button_pre_10ms();
	
}



/*****************************************************************************
** Function name    :Proc_handl_tou_10ms
**
** Description         :10ms中断产生后的程序处理        
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
//	INT8U Bill_Data;

//	NEW_MMD_DATA_UNIT st_mmd_unit;
//	SUM_MMD_DATA_UNIT sum_st_mmd_unit;
	Proc_get_clock();
//	mem_db_check();
	CLRWDT();	// 清看门狗//
	if(gs_emu_run_var.delay_emu>0)
	{
		 gs_emu_run_var.delay_emu--;//emu稳定时间为3秒
		 api_Measure_ram_INIT();
	}
	//计量稳定后扫描事件
	if(gs_emu_run_var.delay_emu==0)
	{
		// 瞬时量获取//
		// OpenCF();
		api_measure_deal_pre_second();
		CLRWDT();	// 清看门狗//
		//电能脉冲秒处理 //
		api_accum_current_energy_data_pre_second();
		CLRWDT();   // 清看门狗//
		api_even_Detect_sec();
		//需量秒计算处理 //
		api_updata_md_var_min_per_second(); 
		CLRWDT();	// 清看门狗//
		//硬件短接清零检测秒处理//   
		Proc_Check_PROKEY_Pre_sec();
		//LED灯状态刷新//
		api_updated_LED_per_second();
		api_measure_VBAT_pre_min();   
	}
	if(Judge_ERR_COVER_key() == FALSE)
	{
		if(KEY_READ_DELAY > 0)
		{
			KEY_READ_DELAY--;	
		}else{
			IsModeTest = TRUE;
			TestDelay = 600;
			//液晶显示test模式  code
		}
	}else{
		if(TestDelay > 0)
		{
			TestDelay --;
		}else{
			IsModeTest = FALSE;
		}
	}
	if(MD_dis_delay == 0)//按键需量清零以后3秒全屏
	{
	 	// 显示项目每秒改变处理//        
    	api_updated_LCDDisplayItem_per_second();    
     	// 显示内容每秒更新处理//                
    	api_updated_LCDDisplayPixel_per_second();
	}
	else
	{
		MD_dis_delay -- ;
	}
     //分钟级处理  //
#if meter_type == D_1P2W

	 //无功补偿
	 TimeEventProc();
#endif
    if(gs_CurDateTime.Second == 0)
    {
		Check_EMU_AdjParam();
		CLRWDT();	// 清看门狗//
		api_updata_md_var_slid_per_minute();   
		CLRWDT();	// 清看门狗//
		//日冻结
		api_freeze_energy_Ram_pre_day();
		api_freeze_energy_pre_day(); 
//		mem_read(&Bill_Data, ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,BILL_FLAG), 1, MEM_E2P1);
		#if (BILL_MAX_NUM>0)
		if(Bill_Data == 0x30)
		{
			CLRWDT();
			api_handl_settle_per_minute();
		}
		CLRWDT();	// 清看门狗//
		#endif
		LoadPro_Rec();         
		CLRWDT();	// 清看门狗//
		#if (TARIFF_MAX_NUM>1)
		api_update_triffNo_pre_minute();
		#endif	
			 
    }

     if(gs_CurDateTime.Second == 0x25)
     {
        Handl_RTC_Adj_per_minu();   
		CLRWDT();	// 清看门狗//
     }  

  
    if(gs_CurDateTime.Second == 0x31)
     {
       api_measure_temperature_pre_min();   
	   CLRWDT();   // 清看门狗//
     } 
	
}


//-------------------------------------------------------------------------------//
//  Function:      void get_default_mem_data(INT8U index)     
//  Description:  
//  Parameters:   无  
//  Returns:        无                          
//  Others:         
//-------------------------------------------------------------------------------//
void  Proc_Auto_ClrMeter_Pre_sec(void)
{

   ;
}

//-------------------------------------------------------------------------------//
//  Function:      void get_default_mem_data(INT8U index)     
//  Description:  
//  Parameters:   无  
//  Returns:        无                          
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

