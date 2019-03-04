/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Api_Energy.C
**Author		: maji
**date			: 2016-04-20 
**description	: ���ܼ���Ӧ�ò���غ���C�ļ�
**note			: MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#include <MyIncludes_H.h>




ENERGY_USER_DATA    gs_energy_user_data;            //��ǰ����RAM������  //
ENERGY_USER_DATA    gs_energy_user_data_back;   //��ǰ����RAM�������� //
ENERGY_VAR		      gs_energy_var;                 // ������������������ݣ��ϵ��ʼ��Ϊ0  //


/*****************************************************************************
** Function name    :api_init_current_energy_data_ram
**
** Description         :��ʼ����ǰ����RAM�����ݣ�����λ��ʼ������        
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_init_current_energy_data_ram(void)
{
//�������
	uint8 Bill_Data;
	uint8 i;
	ST_U16_U08 u16_month_A,u16_month_B;
	ST_U16_U08 u16_day_A,u16_day_B;
	uint8 last_rec_dateTime[6];//���һ�ζ���ʱ��
	uint8 max_dateTime;
////////
    Lib_Set_String(&gs_energy_user_data.us_val[0][0].buf[0],0,sizeof(ENERGY_USER_DATA));
    Lib_Set_String(&gs_energy_user_data_back.us_val[0][0].buf[0],0,sizeof(ENERGY_USER_DATA));
    api_check_current_energy_data(); 


	//У��Ͳ��Ծʹ�EEP��ȡ����
	mem_read(&energy_data_array[0].buf[0],ADR_BLOCK_4Energy_L0_E2P,  5*LEN_EC_UNIT,MEM_E2P1);
	mem_read(&st_mmd_unit_array[0].buf[0],ADR_BLOCK_4MMD_L0_E2P,5*LEN_NEW_MMD_UNIT,MEM_E2P1);
	mem_read(&sum_st_mmd_unit_array[0].buf[0],ADR_BLOCK_4MMD_sum_L0_E2P,5*LEN_SUM_MMD_UNIT,MEM_E2P1);
	d_flag = 0;

	//У���ն���RAM���� 2019-01-25
//	Excsck = 0;
//	Excsck += Lib_get_csck_int16u_num(&energy_data_array[0].buf[0],5*LEN_EC_UNIT,CHECKWORD); 
//	Excsck += Lib_get_csck_int16u_num(&st_mmd_unit_array[0].buf[0],5*LEN_NEW_MMD_UNIT,CHECKWORD);
//	Excsck += Lib_get_csck_int16u_num(&sum_st_mmd_unit_array[0].buf[0],5*LEN_SUM_MMD_UNIT,CHECKWORD);
//	if(csck == Excsck)
//	{
//		mem_read(&last_rec_dateTime[0],ADR_BLOCK_4MMD_L0_E2P+4,5,MEM_E2P1);//������ʱ��
//		//2019-01-25 cxy  ����ǰ����������д��RAM��
//		mem_read(&energy_data_array[0].buf[0],&gs_energy_user_data_back.us_val[0][0].buf[0], LEN_EC_CURRENT, MEM_RAM);
//		//2019-01-25 cxy  �ϵ罫RAM���ն�������д��EEP	
//		mem_write(ADR_BLOCK_4Energy_L0_E2P,&energy_data_array[0].buf[0],5*LEN_EC_UNIT,MEM_E2P1);
//		mem_write(ADR_BLOCK_4MMD_L0_E2P,&st_mmd_unit_array[0].buf[0],5*LEN_NEW_MMD_UNIT,MEM_E2P1);
//		mem_write(ADR_BLOCK_4MMD_sum_L0_E2P,&sum_st_mmd_unit_array[0].buf[0],5*LEN_SUM_MMD_UNIT,MEM_E2P1);
//		
//		//���������˼������
		mem_read(&last_rec_dateTime[0],ADR_BLOCK161_EVENII_PWN_E2P+6,5,MEM_E2P1);//������ʱ��
		u16_month_A.u16 = Lib_bcd_byte(last_rec_dateTime[0])*12+ Lib_bcd_byte(last_rec_dateTime[1]);//������
		u16_month_B.u16 = Lib_bcd_byte(gs_CurDateTime.Year)*12 + Lib_bcd_byte(gs_CurDateTime.Month);
		CLRWDT();
		if(u16_month_B.u16 >= u16_month_A.u16)
		{
			if(u16_month_B.u16 - u16_month_A.u16 > 1)
			{
				 max_dateTime = 6;
			}
			else
			{
				if(u16_month_B.u16 - u16_month_A.u16 == 1)
					max_dateTime = Judage_Month(last_rec_dateTime[1],last_rec_dateTime[0])-last_rec_dateTime[2]+gs_CurDateTime.Day;
				else
					max_dateTime = gs_CurDateTime.Day -last_rec_dateTime[2];
			}
			//��ȡ���㷽ʽ  2019-01-30
			mem_read(&Bill_Data, ADR_BLOCK20_METER_PARAM1_E2P+ST_MB_OFFSET(E2P_METER_PARAM1_MAP,BILL_FLAG), 1, MEM_E2P1);
	
			if(Bill_Data == 0x01)
			{
				if(max_dateTime > 0 && max_dateTime <=12)
				{
					CLRWDT();
					for(i=0;i<max_dateTime ;i++)
					{
						api_write_bill_data(BILL_ID0_MOTTH_SETTL);
						CLRWDT();
					}
					CLRWDT();
					api_clr_current_MD_data();
	//				sum_st_mmd_unit_array[0].val.val_count--;  //���һ��
					CLRWDT();
				}
			}
//			if(Bill_Data == 0x30)
//			{
//				//���½���
//				#if (BILL_MAX_NUM>1)
//					api_handl_settle_when_powerUp();   
//				#endif
//			}
		}
//	}
//	else
//	{	

//  }

	// ��������//
    gs_energy_var.pluse[0] = 0;
}

/*****************************************************************************
** Function name    :api_check_current_energy_data
**
** Description         :��ǰ�������ݵļ�鴦�������ۼƺ�������
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_check_current_energy_data(void)
{   
    INT16U csck_tmp;
 
    //�������ݻ�ȡ  //   
    csck_tmp = Lib_get_csck_int16u_num(&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);
    if(csck_tmp != gs_energy_user_data.u16_csck) 
    {
        csck_tmp = Lib_get_csck_int16u_num(&gs_energy_user_data_back.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);        
		if(csck_tmp != gs_energy_user_data_back.u16_csck) 
        {
            mem_read(&gs_energy_user_data_back.us_val[0][0].buf[0], ADR_BLOCK00_EC_L0_E2P, LEN_EC_CURRENT, MEM_E2P1);
            gs_energy_user_data_back.u16_csck = Lib_get_csck_int16u_num(&gs_energy_user_data_back.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);
			/*
			mem_read(&gs_energy_user_data_back.us_val[0][0].buf[0], ADR_BLOCK00_EC_L0_E2P, (LEN_EC_CURRENT+2), MEM_E2P1);
			csck_tmp= Lib_get_csck_int16u_num(&gs_energy_user_data_back.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);
			if(csck_tmp != gs_energy_user_data_back.u16_csck)
			{
				Lib_Set_String(&gs_energy_user_data.us_val[0][0].buf[0],0,sizeof(ENERGY_USER_DATA));
				Lib_Set_String(&gs_energy_user_data_back.us_val[0][0].buf[0],0,sizeof(ENERGY_USER_DATA));
			}
			*/
        }
        Lib_Copy_Str_TwoArry(&gs_energy_user_data.us_val[0][0].buf[0],&gs_energy_user_data_back.us_val[0][0].buf[0],LEN_EC_CURRENT);
        gs_energy_user_data.u16_csck = gs_energy_user_data_back.u16_csck;       
    }
}

/*****************************************************************************
** Function name    :lnk_inc_energy_pluse
**
** Description         :��ǰ�й�������������������װ�����ͨ�������ۼ�    
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
uint8 lnk_add_fac_energy_pluse(void)
{

  uint8 chg_fg=FALSE; 
  uint8 u8_tmp,i;
	
  for (i=0; i<EC_CH_NUM; i++)
  {        
	  if(gs_energy_var.pluse[i]>0)
	  {
		  DisableINT();    				// disable interrupt function  //
		  u8_tmp = gs_energy_var.pluse[i];
		  gs_energy_var.pluse[i] =0;  //�й��������㴦�� //
		  EnableINT();
		
		  gs_energy_user_data.us_val[i][0].val.decim_hex16 += u8_tmp;  // ���ۼ�	��ϲ��ۼ�//
		  #if (TARIFF_MAX_NUM>1)
		  gs_energy_user_data.us_val[i][EN_TRIFF_no].val.decim_hex16 += u8_tmp; //  ��ϲ��ۼ�//
		  #endif
		  chg_fg = TRUE;
	  }
	}
	
	 return (chg_fg);
}



/*****************************************************************************
** Function name    :lnk_inc_energy_pluse
**
** Description         :��ǰ�޹���������������������װ�����ͨ�������ۼ�    
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
uint8 lnk_add_rac_energy_pluse(void)
{

uint8 chg_fg=FALSE;
	/*
	uint8 u8_tmp;

	//����ģʽ�ֻ�ȡ�����಻�ж�����ֻ�ж�������  0x0FΪ1234���� ������
	mem_read(&gs_sys_globaL_var.Rac_energy[0], ADR_METER_PARAM1_REC_ENERGY, 2, MEM_E2P1);   
	if(gs_energy_var.pluse[1]>0)
	{
		DisableINT();    				// disable interrupt function  //
		u8_tmp = gs_energy_var.pluse[1];
		gs_energy_var.pluse[1] =0;  //�й��������㴦�� //
		EnableINT();

        if((gs_sys_globaL_var.Rac_energy[1]&0x0F)==0x06) //2��3���ۼ� 1��4 �����ۼ� �����ۼ�
		{
		  if((gs_emu_run_var.net_flg&REV_TT_RACPOWER)==0)
		  {
		   gs_energy_user_data.us_val[EC_CH_RE_PT_TT][0].val.decim_hex16 += u8_tmp;  // ���ۼ�  ��ϲ��ۼ�//
		   #if (TARIFF_MAX_NUM>1)
	 	   gs_energy_user_data.us_val[EC_CH_RE_PT_TT][EN_TRIFF_no].val.decim_hex16 += u8_tmp; //  ��ϲ��ۼ�//
		   #endif
		  }
		 chg_fg = TRUE;
		}
		else if((gs_sys_globaL_var.Rac_energy[1]&0x0F)==0x09)  //1��4���޲��ۼӡ�2��3�����ۼ�  �����ۼ�//
		{
		  if(gs_emu_run_var.net_flg&REV_TT_RACPOWER)
		  {
		   gs_energy_user_data.us_val[EC_CH_RE_PT_TT][0].val.decim_hex16 += u8_tmp;  // ���ۼ�  ��ϲ��ۼ�//
		   #if (TARIFF_MAX_NUM>1)
	 	   gs_energy_user_data.us_val[EC_CH_RE_PT_TT][EN_TRIFF_no].val.decim_hex16 += u8_tmp; //  ��ϲ��ۼ�//
		   #endif
		  }
		 chg_fg = TRUE;
		}
		else //Ĭ����  ���������ۼ�
		{
		   gs_energy_user_data.us_val[EC_CH_RE_PT_TT][0].val.decim_hex16 += u8_tmp;  // ���ۼ�  ��ϲ��ۼ�//
		   #if (TARIFF_MAX_NUM>1)
	 	   gs_energy_user_data.us_val[EC_CH_RE_PT_TT][EN_TRIFF_no].val.decim_hex16 += u8_tmp; //  ��ϲ��ۼ�//
		   #endif
		   chg_fg = TRUE;
		}
		
		if(gs_emu_run_var.net_flg&REV_TT_RACPOWER)
		{
		 	  gs_energy_user_data.us_val[EC_REV_REC_NUM][0].val.decim_hex16 += u8_tmp; // �����ۼ�
		   #if (TARIFF_MAX_NUM>1)
		      gs_energy_user_data.us_val[EC_REV_REC_NUM][EN_TRIFF_no].val.decim_hex16 += u8_tmp; // �����ۼ�
		   #endif
		}
		else 
		{
		  	  gs_energy_user_data.us_val[EC_FOR_REC_NUM][0].val.decim_hex16 += u8_tmp;//�����ۼ�
		   #if (TARIFF_MAX_NUM>1)
		      gs_energy_user_data.us_val[EC_FOR_REC_NUM][EN_TRIFF_no].val.decim_hex16 += u8_tmp;//�����ۼ�
		   #endif
		}
	}
*/
	 return (chg_fg);
}

/*****************************************************************************
** Function name    :api_accum_current_energy_data_pre_second
**
** Description         :��ǰ���������ۼƴ���ÿ�����
**
** Parameters         :NONE          
**
** Returned value   :NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-04-23
******************************************************************************/
void api_accum_current_energy_data_pre_second(void)
{
	uint8 save_fg=FALSE;
	uint8 i,chg_fg1;

    //if(CheckPOWERUP() !=TRUE)   return;  
	// �������ݺϷ��Լ�� //
	api_check_current_energy_data();
	//�й����������������� //
	chg_fg1 =lnk_add_fac_energy_pluse(); 

	if(chg_fg1==FALSE) return; 
	
	save_fg=FALSE;
	for(i=0;i<EC_CH_NUM;i++)
	{
		if(gs_energy_user_data.us_val[i][0].val.decim_hex16>=METER_CONST_1KWH)
		{
 		 	if(i==0) 	save_fg = TRUE;   //��ʱ��֧���޹����ȵĴ�ȡ   ����ͨ��1�ĵ�������������λʱ���ô洢��ʶ //
			gs_energy_user_data.us_val[i][0].val.decim_hex16 -= METER_CONST_1KWH;
			gs_energy_user_data.us_val[i][0].val.integ_hex32++;
			if(gs_energy_user_data.us_val[i][0].val.integ_hex32 > MAX_ENERGY_INtEGER)
			{
				gs_energy_user_data.us_val[i][0].val.integ_hex32 = 0;  // �������Χ������ //
			}
		}
		#if (TARIFF_MAX_NUM>0)
		if(gs_energy_user_data.us_val[i][EN_TRIFF_no].val.decim_hex16>=METER_CONST_1KWH)
		{
			gs_energy_user_data.us_val[i][EN_TRIFF_no].val.decim_hex16 -= METER_CONST_1KWH;
			gs_energy_user_data.us_val[i][EN_TRIFF_no].val.integ_hex32++;
			if(gs_energy_user_data.us_val[i][EN_TRIFF_no].val.integ_hex32 > MAX_ENERGY_INtEGER)
			{
				gs_energy_user_data.us_val[i][EN_TRIFF_no].val.integ_hex32 = 0;  // �������Χ������ //
			}
		}		
		#endif
		
	}
	
	// ����RAM������У��ͺͱ���������//
	gs_energy_user_data.u16_csck = Lib_get_csck_int16u_num(&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);  
	Lib_Copy_Str_TwoArry(&gs_energy_user_data_back.us_val[0][0].buf[0],&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_E2P);

	// �������ݱ��� //
	if(save_fg == TRUE)
	{
		mem_db_write(ADR_BLOCK00_EC_L0_E2P,&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,MEM_E2P1);
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
void api_clr_current_energy_data(void)
{
	// �����ǰ�������ݵ�RAM�������� //
	Lib_Set_String(&gs_energy_user_data.us_val[0][0].buf[0],0,LEN_EC_CURRENT);
	gs_energy_user_data.u16_csck = Lib_get_csck_int16u_num(&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_CURRENT,CHECKWORD);  
	// �����ǰ�������ݵ�RAM���������� //
	Lib_Copy_Str_TwoArry(&gs_energy_user_data_back.us_val[0][0].buf[0],&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_E2P);
	// �����ǰ�������ݵ�E2P������ //
	mem_db_write(ADR_BLOCK00_EC_L0_E2P,&gs_energy_user_data.us_val[0][0].buf[0],LEN_EC_E2P-2,MEM_E2P1);
}


/***************************************************************
*    END
****************************************************************/

