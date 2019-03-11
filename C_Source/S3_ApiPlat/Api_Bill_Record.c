/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Api_Measure.c
**Author: maji
**date: 
**description: c code for ��������Ӧ�ò�
**note:  Driver code for GENERAL
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2015-10-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>


#if (BILL_MAX_NUM>0)


//*****************************************************************
//	Calculate the address of history data
//*****************************************************************
code BILL_INFO bill_info[] = 
{
    ADR_BLOCK101_BILL1_DATA_E2P, ADR_BLOCK26_BILL_VAR_PTR_E2P,  LEN_BLOCK10X_BILLX_DATA_E2P,  BILL_MAX_NUM,   MEM_E2P1,		    // 0 ���������˵�������   //
};   

uint8 d_flag ;
US_EC_DATA_UNIT 	energy_data_array[5] = {0,0,0,0,0};
NEW_MMD_DATA_UNIT st_mmd_unit_array[5] = {0,0,0,0,0};
SUM_MMD_DATA_UNIT sum_st_mmd_unit_array[5] = {0,0,0,0,0};
uint8 csck,Excsck;

//2�·�ʱ���û�ȡ����
uint8 Judage_Year(uint8 year)
{
	if((year%4==0 && year%100!=0)||(year%400==0))
    {
		return 29;//������ 29��
	}
	else
	{
		return 28;//��ƽ�� 28�� 
	}
}
//����ֵΪ�����·��ж�����
uint8 Judage_Month(uint8 month,uint8 year)
{
	if(month == 2)
		return Judage_Year(year);
	if(month < 8)
	{
		if(month%2 ==0)
		{
			return 30;
		}
		else
		{
			return 31;
		}
	}
	else
	{
	   	if(month%2 ==0)
		{
			return 31;
		}
		else
		{
			return 30;
		}
	} 
}


/*****************************************************************************
** Function name    :api_get_bill_record_addr
**
** Description         : ��ȡָ���˵����¼�ľ��Ե�ַ(������Ե�ַλ��)    
**
** Parameters         :INT16U addr: ������Ե�ַλ��       
**
** Returned value   :INT16U addr: ������Ե�ַλ��  
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
INT16U api_get_bill_record_addr( INT16U addr )
{
 INT8U i,ptr,temp ,num;
 INT16U hist_addr,len;

	for( i=0; i<(sizeof(bill_info)/sizeof(BILL_INFO)); i++ )
	{
		hist_addr = bill_info[i].head_adr;
		len = bill_info[i].data_size* (INT16U)bill_info[i].ptr_num;
		if( addr>=hist_addr && addr<(hist_addr+len) ) break;
	}

	mem_read(&ptr, bill_info[i].ptr_adr, 1, bill_info[i].mem_type);
	if( ptr>= bill_info[i].ptr_num)
	{
	    ptr = 0;
	}
	
	hist_addr = addr - bill_info[i].head_adr;
	temp = hist_addr / bill_info[i].data_size;
	num = hist_addr - temp*bill_info[i].data_size;
	if ( ptr < temp ) 
	{
	    ptr = ptr + ( bill_info[i].ptr_num -temp);    
	}
	else
	{
	    ptr = ptr - temp; 
	}
	addr = bill_info[i].head_adr+ ptr*(INT16U)bill_info[i].data_size +num;

	return	addr;
}



/*****************************************************************************
** Function name    :api_write_bill_data
**
** Description         : д���˵����¼������
**
** Parameters         :INT8U id: �˵�ʱ����    
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_write_bill_data(INT8U id)
{
INT16U adr_tmp;
INT8U  ptr_tmp;
INT8U buff_int8u[BILL_BUFF_MAX_LEN];


    Lib_Clr_String(&buff_int8u[0],BILL_BUFF_MAX_LEN);

    // 1.������¼���ݵ�ָ�����ݲ�������ݴ洢���׵�ַ  //
    mem_read(&ptr_tmp, bill_info[id].ptr_adr, 1, MEM_E2P1);
    ptr_tmp++;
    if(ptr_tmp>(bill_info[id].ptr_num-1))   ptr_tmp = 0;  
    adr_tmp = bill_info[id].head_adr+ptr_tmp* bill_info[id].data_size;
    mem_db_write(bill_info[id].ptr_adr,&ptr_tmp, 1,  MEM_E2P1);

    // 2.��ȡ�������¼���¼�Ļ�����  //
    switch(id)
    {
        case BILL_ID0_MOTTH_SETTL:
            buff_int8u[0]= gs_CurDateTime.Year;
            buff_int8u[1]= gs_CurDateTime.Month;
            buff_int8u[2]= gs_CurDateTime.Day;
            buff_int8u[3]= gs_CurDateTime.Hour;
            buff_int8u[4]= gs_CurDateTime.Minute;
            buff_int8u[5]= gs_CurDateTime.Second;
            mem_db_write(ADR_BLOCK26_BILL_VAR_DATETTIME_E2P,&buff_int8u[0], 6,  MEM_E2P1); //��ǰ���1�ν����ʱ�����ڼ�¼      //
            Lib_Copy_Str_TwoArry(&buff_int8u[6], &gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT); 	// ����
            mem_read(((&buff_int8u[6])+LEN_EC_CURRENT), ADR_BLOCK01_MMD_L0_E2P, LEN_MMD_CURRENT, MEM_E2P1);  // ���� 
            mem_db_write(adr_tmp,&buff_int8u[0], bill_info[id].data_size-2,MEM_E2P1);
            //��ǰ��������  //
 //           api_clr_current_MD_data();
        break;

        default:
            sys_err();	
        break;
    }
    

}


/*****************************************************************************
** Function name    :api_handl_settle_per_minute
**
** Description         :ÿ���ӵ��õ��½��㺯������ǰʱ�ӵ���ʱʱ��ͽ���������ʱ�����½��㴦��
**
** Parameters         :NONE    
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-05-3
******************************************************************************/
void api_handl_settle_per_minute(void)
{
	uint8 param_settel[2];   //���1�ν���ʱ��� ������ʱ���� //
	ST_U16_U08 u16_hour_A,u16_hour_B;

    if(gs_CurDateTime.Minute != 0)   return;   //���Ӻ��붼Ϊ0��ʱ���� //

    mem_read(&param_settel[0], ADR_METER_PARAM1_SETL_DDHH, 2, MEM_E2P1);  //��ȡ����������( �գ�ʱ)//
    u16_hour_A.u16= Lib_bcd_byte(param_settel[0])*24 + Lib_bcd_byte(param_settel[1]);    //�����ȡ�������Сʱ��λ���� //
    u16_hour_B.u16 = Lib_bcd_byte(gs_CurDateTime.Day)*24 + Lib_bcd_byte(gs_CurDateTime.Hour);     //�����ȡ��ǰʱ�ӵ���ʱ���ֵ�Сʱ��λ���� //	

    if((u16_hour_B.u16 - u16_hour_A.u16)==0)    //�������� //
    {
        api_write_bill_data(BILL_ID0_MOTTH_SETTL);	//��������//
		api_clr_current_MD_data();	
    }
}

/*****************************************************************************
** Function name    :api_handl_settle_per_minute
**
** Description         :ÿ���ӵ��õ��½��㺯������ǰʱ�ӵ���ʱʱ��ͽ���������ʱ�����½��㴦��
**
** Parameters         :NONE    
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-05-3
******************************************************************************/
void api_freeze_energy_pre_day(void)
{
//		INT8U Bill_Data;
		if(d_flag == 1){
			d_flag = 0;
			mem_write(ADR_BLOCK_4Energy_L0_E2P, &energy_data_array[0].buf[0], 5*LEN_EC_UNIT,MEM_E2P1);
			mem_write(ADR_BLOCK_4MMD_L0_E2P,&st_mmd_unit_array[0].buf[0],5*LEN_NEW_MMD_UNIT,MEM_E2P1);
			mem_write(ADR_BLOCK_4MMD_sum_L0_E2P,&sum_st_mmd_unit_array[0].buf[0],5*LEN_SUM_MMD_UNIT,MEM_E2P1);		
			

			if(gs_CurDateTime.Second == 0)
			{
				//�ն���
				if(gs_CurDateTime.Minute == 0)
				{
					if(gs_CurDateTime.Hour == 0)
					{
//						mem_read(&Bill_Data, ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,BILL_FLAG), 1, MEM_E2P1);
						if(Bill_Data == 0x01)
						{
							//�������ݵ�������  2019-01-30
							CLRWDT();
							api_write_bill_data(BILL_ID0_MOTTH_SETTL);
							api_clr_current_MD_data();
			//				sum_st_mmd_unit_array[0].val.val_count--;
						}
			 		}
			 	}
			 }
		
		}
		

}

void api_freeze_energy_Ram_pre_day(void)
{
	int8 i;
	
//ֻ��RAM������
	if(gs_CurDateTime.Second == 0)
	{
		//�ն���
		if(gs_CurDateTime.Minute == 0)
		{
			if(gs_CurDateTime.Hour == 0)
			{
			//����
				d_flag = 1;
				mem_read(&energy_data_array[0].buf[0], (INT16U)&gs_energy_user_data.us_val[EC_CH_AC_PT_TT][0].buf[0], LEN_EC_UNIT, MEM_RAM);
				for(i=4;i>0;i--)
				{
					mem_write(&energy_data_array[i].buf[0], &energy_data_array[i-1].buf[0], LEN_EC_UNIT,MEM_RAM);
				}
				
			//����
				st_mmd_unit_array[0].val.date_rtc[0] = gs_CurDateTime.Year;
				st_mmd_unit_array[0].val.date_rtc[1] = gs_CurDateTime.Month;
				st_mmd_unit_array[0].val.date_rtc[2] = gs_CurDateTime.Day;
				st_mmd_unit_array[0].val.date_rtc[3] = gs_CurDateTime.Hour;
				st_mmd_unit_array[0].val.date_rtc[4] = gs_CurDateTime.Minute;
				for(i=4;i>0;i--)
				{
					mem_write(&st_mmd_unit_array[i].buf[0],&st_mmd_unit_array[i-1].buf[0],LEN_NEW_MMD_UNIT,MEM_RAM);
				}
				
			//�ۼ�����
				for(i=4;i>0;i--)
				{
					mem_write(&sum_st_mmd_unit_array[i].buf[0],&sum_st_mmd_unit_array[i-1].buf[0],LEN_SUM_MMD_UNIT,MEM_RAM);
				}


				
//				if(Bill_Data == 0x30)
//				{
//					#if (BILL_MAX_NUM>0)
//					if(Bill_Data == 0x30)
//					{
//						CLRWDT();
//						api_handl_settle_per_minute();
//					}
//					CLRWDT();	// �忴�Ź�//
//					#endif
//				}

				//RAMУ��
				csck = 0;
				csck += Lib_get_csck_int16u_num(&energy_data_array[0].buf[0],5*LEN_EC_UNIT,CHECKWORD); 
				csck += Lib_get_csck_int16u_num(&st_mmd_unit_array[0].buf[0],5*LEN_NEW_MMD_UNIT,CHECKWORD);
				csck += Lib_get_csck_int16u_num(&sum_st_mmd_unit_array[0].buf[0],5*LEN_SUM_MMD_UNIT,CHECKWORD);

			}
		}
	}	
}


/*****************************************************************************
** Function name    :api_handl_settle_when_powerUp
**
** Description         :�ϵ粹�½���Ӧ�ú���
**
** Parameters         :NONE   
**
** Returned value   :NONE
**
** NOTE                :ע���ڵ��ñ�����ǰ��Ҫȷ��ϵͳ��ȡ��RTC���ݺ͵�ǰ��������
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-05-03
******************************************************************************/
void api_handl_settle_when_powerUp(void)
{
  uint8 last_rec_dateTime[6];   //���1�ν���ʱ��� ������ʱ���� //
  uint8 param_settel[2];   //���1�ν���ʱ��� ������ʱ���� //
  ST_U16_U08 u16_month_A,u16_month_B;
  ST_U16_U08 u16_hour_A,u16_hour_B;
  uint16  months_no_settled;
  INT8U i,j; 


/////////////////////////////////////////////////////////
// ��ȡ�µ�ʱ�����µ�ʱ��Ƚ�???//
//����ģʽ�ᵼ��ʱ��ǰ�ĺ�ˢ�����м�¼
//////////////////////////////////////////////////////////
//    mem_read(&last_rec_dateTime[0], ADR_BLOCK26_BILL_VAR_DATETTIME_E2P, 6, MEM_E2P1); //��ȡ�ϴν���ʱ��(������ʱ���� )
	mem_read(&last_rec_dateTime[0],ADR_BLOCK161_EVENII_PWN_E2P+6,5,MEM_E2P1);//������ʱ��
    u16_month_A.u16 = Lib_bcd_byte(last_rec_dateTime[0])*12 + Lib_bcd_byte(last_rec_dateTime[1]);	    //���1�ν�����µ�λ���� //
    u16_month_B.u16 = Lib_bcd_byte(gs_CurDateTime.Year)*12 + Lib_bcd_byte(gs_CurDateTime.Month);	
    mem_read(&param_settel[0], ADR_METER_PARAM1_SETL_DDHH, 2, MEM_E2P1);  //��ȡ����������( �գ�ʱ)//
    u16_hour_A.u16 = Lib_bcd_byte(param_settel[0])*24 + Lib_bcd_byte(param_settel[1]);
    u16_hour_B.u16 = Lib_bcd_byte(gs_CurDateTime.Day)*24 + Lib_bcd_byte(gs_CurDateTime.Hour);
///����ʱ��Ϊ0��������Ĳ��� yang 2018-1-5////
	/*
	if(u16_month_A.u16 ==0)
	{
		return;       //��¼�Ľ���ʱ����Ϊ0ʱ�����в�������� //
	}
	*/
    if( u16_month_A.u16 > u16_month_B.u16) 
	{
		months_no_settled =1;
	}
	else
	{
		months_no_settled = u16_month_B.u16- u16_month_A.u16;  // ��Ҫ�����¸���//
	}
    j=0;//������ļ�¼��������  //
    for(i=0;i<(MAX_Fill_SETTLED_MONTHS+1);i++) // 0-12
    {
        if(j>= MAX_Fill_SETTLED_MONTHS)  break;
        if(months_no_settled==0)   break;
        if(months_no_settled==1)    
        {
            if(u16_hour_B.u16>= u16_hour_A.u16)
            {
                api_write_bill_data(BILL_ID0_MOTTH_SETTL);	//�½���//		
                CLRWDT();
                j++;
                months_no_settled--;
            }
            else
            {
                break;
            }
        } 
        else
        {
            api_write_bill_data(BILL_ID0_MOTTH_SETTL);	//�½���//		
            CLRWDT();
            j++;
            months_no_settled--;  
        } 
    }    
}



/*****************************************************************************
** Function name    :api_clr_current_energy_data
**
** Description         :��ǰ�������ݵ����㴦��
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_clr_bill_data(void)
{
    E2P_BILL_VAR_MAP  tmp_bill_var;
    BILL_DATA_UNIT    tmp_bill_unit;
    CLRWDT();
    Lib_Clr_String(&tmp_bill_var.bill_var.ptrNo,LEN_BILL_EXRAM_VAR);
    Lib_Clr_String(&tmp_bill_unit.u8_RTC_record[0],LEN_BILL_DATA_UNIT);
	
    mem_db_write(ADR_BLOCK26_BILL_VAR_E2P,&tmp_bill_var.bill_var.ptrNo, LEN_BILL_EXRAM_VAR,  MEM_E2P1); //���ָ���¼ // 
    CLRWDT();
	
    mem_fill(ADR_BLOCK101_BILL1_DATA_E2P,LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK102_BILL2_DATA_E2P,LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK103_BILL3_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK104_BILL4_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK105_BILL5_DATA_E2P,LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
    mem_fill(ADR_BLOCK106_BILL6_DATA_E2P, LEN_BLOCK10X_BILLX_DATA_E2P-2, 0x00, MEM_E2P1);
    CLRWDT();
	/* 
	mem_db_write(ADR_BLOCK107_BILL7_DATA_E2P,&tmp_bill_unit.u8_RTC_record[0], LEN_BILL_DATA_UNIT, MEM_E2P1);
	CLRWDT();
	mem_db_write(ADR_BLOCK108_BILL8_DATA_E2P, &tmp_bill_unit.u8_RTC_record[0], LEN_BILL_DATA_UNIT, MEM_E2P1);
	CLRWDT();
	mem_db_write(ADR_BLOCK109_BILL9_DATA_E2P,&tmp_bill_unit.u8_RTC_record[0], LEN_BILL_DATA_UNIT, MEM_E2P1);
	CLRWDT();
	mem_db_write(ADR_BLOCK110_BILL10_DATA_E2P,&tmp_bill_unit.u8_RTC_record[0], LEN_BILL_DATA_UNIT, MEM_E2P1);
	CLRWDT();
	mem_db_write(ADR_BLOCK111_BILL11_DATA_E2P,&tmp_bill_unit.u8_RTC_record[0], LEN_BILL_DATA_UNIT, MEM_E2P1);
	CLRWDT();
	mem_db_write(ADR_BLOCK112_BILL12_DATA_E2P, &tmp_bill_unit.u8_RTC_record[0], LEN_BILL_DATA_UNIT, MEM_E2P1);
	CLRWDT();
	*/
    
}




#endif

/***************************************************************
*    END
****************************************************************/


