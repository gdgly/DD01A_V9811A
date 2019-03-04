/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: RF_comm.c
**Author: maji
**date: 
**description: c code for lora RF communicate
**note: memer type  DI03B
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2017-09-06   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/
#include <MyIncludes_H.h>
/*#include "..\myInclude\myInclude.h"
#include "..\hardDriver\hardDriver.h"
#include "..\myLib\myLib.h"
#include "data.h"*/


RF_DRV_VAR gs_rf_drv_var;
uint8 *P_DL645_07_BUFF;    //ͨѶ������ָ�� //
DLT645_07_VAR gs_dlt645_07_var;



code INT8U Super_mima_DLT[4] ={0X00,0X23,0X61,0X45};  //�������룬00����456123 //



/************************************************************************************************************
* DL/T 645-2007  ���ִ���
*************************************************************************************************************/
/*******************************************************************
* uchar MeteIDCheck():
********************************************************************/
INT8U MeteIDCheck(INT8U *ptr)
{
	 register INT8U i;
	 INT8U adr[6];

	 //  //
	 mem_read(&adr[0], ADR_METER_PARAM1_RF_COMM_ID, 6, MEM_E2P1);

	 //
	 for(i=6; i>0; i--)
	 {
		 if( *(ptr-i) !=0x99)  break;
	 }
	 if(i==0)		return(TRUE); 
 
	 //
	 for(i=6; i>0; i--)
	 {
		if( ( *(ptr-i) != 0xaa ) && ( *(ptr-i) != adr[6-i] ) ) 
		{
			return(FALSE);
		} 
	 }	 
	 return(TRUE); 
}

/*****************************************************************
������
*****************************************************************/
INT8U DLT_SecurityCK(INT8U *ptr)
{
    INT8U ary[4];
	
    mem_read(&ary[0], ADR_METER_PARAM1_PW1, 4, MEM_E2P1);  //get level 1 password   //
	if ( Lib_Cmp_TwoArry( ptr+DLT_MIMAPAPtr, &ary[0], 4) ==0)  return (mmok);
	if ( Lib_Cmp_TwoArry( ptr+DLT_MIMAPAPtr, &Super_mima_DLT[0], 4) ==0)  return (mmok);
	return(mmerr);
}

/*****************************************************************
DLT645 C=0X11 ��������سɹ�������������Ѿ���д�÷�������
*****************************************************************/
INT8U DLT645_07_CTL0X11_read(INT8U *ptr)
{
	INT8U u8_returnLen,mem_type;
	INT8U i;
	INT8U  *ptr_adr;
	INT8U  data_buff[70],profile_adr[9];
	ST_U32_U08	long_tmp;
	INT16U ctmp1;
	//���ݿ���ID,����Ϊ��λ��ǰ��C51          U32����Ϊ���ģʽ  //
	gs_dlt645_07_var.u32_DI.BYTE[0] = ptr[DLT_CmdDI3Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[1] = ptr[DLT_CmdDI2Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[2] = ptr[DLT_CmdDI1Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[3] = ptr[DLT_CmdDI0Ptr];
	
   if(get_IEC_comm_var(gs_dlt645_07_var.u32_DI.UDWORD) == 0 )  return(RS_State_IVID);
   if( ( comm_data.Info.u16& EN_R) == 0 )  return(RS_State_IVData);
   //  ��ȡ���ݵĴ洢���� //
   mem_type = (comm_data.Info.B08[0]>>3)&0x07;	   
    //���������㲢���÷��ͳ���
   // Lib_Set_String((sptr+2), '0', comm_data.len_asc);  
    ptr_adr = comm_data.addr;

	//���ڱ����ID���� ��������ID 
	if((gs_dlt645_07_var.u32_DI.UDWORD>=0x06010001)&&(gs_dlt645_07_var.u32_DI.UDWORD<=0x06010168))
	{
		ctmp1 = (INT16U)(gs_dlt645_07_var.u32_DI.UDWORD - 0x06010001);
		if(ctmp1 < LPRunPa.Num[0])	// ��ȡID С�����Ѽ�¼��
		{
			comm_data.len = LPRec_Read_1(&profile_adr[0], ctmp1);
			comm_data.len_asc = 2*comm_data.len;	
			Lib_Asc_BCDA( &data_buff[0], &profile_adr[0], comm_data.len_asc);  
			for(i=0;i<comm_data.len;i++)
			{
				ptr[DLT_ReadDataPtr+i]=data_buff[comm_data.len-1-i];
			}
			u8_returnLen =comm_data.len;		
		}
		else
		{
			comm_data.len = LPRec_Read_1(profile_adr, ctmp1);
			comm_data.len_asc = 2*comm_data.len;	
			for(i=0;i<comm_data.len;i++)
			{
				ptr[DLT_ReadDataPtr+i]=0xFF;
			}
			u8_returnLen =comm_data.len;		
		}

		//�����ɹ������ݴ���  //	
		gs_dlt645_07_var.u8_lenOfData =u8_returnLen;		//�������ݳ��ȶ��帳ֵ  //
		ptr[DLT_CtlPtr] += 0X80;
		ptr[DLT_LenPtr] =gs_dlt645_07_var.u8_lenOfData+4;	 //4Ϊ�̶�ID���� //		
		return(RS_State_OK);	
	}
	
	switch (gs_dlt645_07_var.u32_DI.UDWORD)
	{	
		case 0x02010000:	//��ѹ Դ����ΪHEX32��0.1V���٣���Ҫת��ΪBCD���ʽ,XXX.XV //
		case 0x02010100:	//��ѹ Դ����ΪHEX32��0.1V���٣���Ҫת��ΪBCD���ʽ,XXX.XV //
			Lib_long_bcd4(&long_tmp.B08[0],gs_measure_var_data.gs_really[0].dw_u_val.u32);
			Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[2], 2);
			ptr[DLT_ReadDataPtr] = data_buff[1];
			ptr[DLT_ReadDataPtr+1] = data_buff[0];
			u8_returnLen =2;		
			break;
			
		case 0x02020000:	//���� Դ����ΪHEX32��0.0001A���٣���Ҫת��ΪBCD���ʽ,XXX.XXXA //
		case 0x02020100:	//���� Դ����ΪHEX32��0.0001A���٣���Ҫת��ΪBCD���ʽ,XXX.XXXA //
			Lib_long_bcd4(&long_tmp.B08[0],(gs_measure_var_data.gs_really[0].dw_i_val.u32));
			Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[1], 3);
			ptr[DLT_ReadDataPtr] = data_buff[2];
			ptr[DLT_ReadDataPtr+1] = data_buff[1];
			ptr[DLT_ReadDataPtr+2] = data_buff[0];
			u8_returnLen =3;			
			break;

		case 0x02800001:	//���ߵ��� Դ����ΪHEX32��0.0001A���٣���Ҫת��ΪBCD���ʽ,XXX.XXXA //
			Lib_long_bcd4(&long_tmp.B08[0],(gs_measure_var_data.dw_i_n_val.u32));
			Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[1], 3);
			ptr[DLT_ReadDataPtr] = data_buff[2];
			ptr[DLT_ReadDataPtr+1] = data_buff[1];
			ptr[DLT_ReadDataPtr+2] = data_buff[0];
			u8_returnLen =3;			
			break;

		case 0x02030000:	//����Դ����ΪHEX32��0.0001KW���٣���Ҫת��ΪBCD���ʽ,XX.XXXXkW //
		case 0x02030100:	//����Դ����ΪHEX32��0.0001KW���٣���Ҫת��ΪBCD���ʽ,XX.XXXXkW //
			Lib_long_bcd4(&long_tmp.B08[0],(gs_measure_var_data.gs_really[0].dw_p_val.u32));
			Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[1], 3);
			ptr[DLT_ReadDataPtr] = data_buff[2];
			ptr[DLT_ReadDataPtr+1] = data_buff[1];
			ptr[DLT_ReadDataPtr+2] = data_buff[0];
			u8_returnLen =3;
			break;
			
		case 0x02030200:	//N����Դ����ΪHEX32��0.0001KW���٣���Ҫת��ΪBCD���ʽ,XX.XXXXkW //
			Lib_long_bcd4(&long_tmp.B08[0],(gs_measure_var_data.dw_p_n_val.u32));
			Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[1], 3);
			ptr[DLT_ReadDataPtr] = data_buff[2];
			ptr[DLT_ReadDataPtr+1] = data_buff[1];
			ptr[DLT_ReadDataPtr+2] = data_buff[0];
			break;
			
		case 0x02060000:	//������������ΪHEX16��0.001����Ҫת��ΪBCD���ʽ0.001 //
		case 0x02060100:	//������������ΪHEX16��0.001����Ҫת��ΪBCD���ʽ0.001 //
			Lib_word_bcd2(&long_tmp.B08[0],(gs_measure_var_data.gs_really[0].dw_pf_val.u16));
			Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[0], 2);
			ptr[DLT_ReadDataPtr] = data_buff[1];
			ptr[DLT_ReadDataPtr+1] = data_buff[0];
			u8_returnLen =2;			
			break;

		case 0x02800002:	//����Ƶ������ΪHEX16��0.01Hz����Ҫת��ΪBCD���ʽxx.xx //
			Lib_word_bcd2(&long_tmp.B08[0],(gs_measure_var_data.gs_really[0].w_freq_val.u16));
			Lib_Copy_Str_TwoArry(&data_buff[0], &long_tmp.B08[0], 2);
			ptr[DLT_ReadDataPtr] = data_buff[1];
			ptr[DLT_ReadDataPtr+1] = data_buff[0];
			u8_returnLen =2;			
			break;

		case 0x04000100://���ڼ�����(����0����������)YYMMDDWWhhmmss
			Lib_Copy_Str_TwoArry(&data_buff[0], ptr_adr, comm_data.len);
			data_buff[7] = data_buff[0];	//ww
			data_buff[0] = data_buff[1];	//YY
			data_buff[1] = data_buff[2];	//MM
			data_buff[2] = data_buff[3];	//DD
			data_buff[3] = data_buff[7];	//WW
			data_buff[4] = data_buff[4];	//hh
			data_buff[5] = data_buff[5];	//mm
			data_buff[6] = data_buff[6];	//ss
			ptr[DLT_ReadDataPtr] = data_buff[6];
			ptr[DLT_ReadDataPtr+1] = data_buff[5];
			ptr[DLT_ReadDataPtr+2] = data_buff[4];
			ptr[DLT_ReadDataPtr+3] = data_buff[3];
			ptr[DLT_ReadDataPtr+4] = data_buff[2];
			ptr[DLT_ReadDataPtr+5] = data_buff[1];
			ptr[DLT_ReadDataPtr+6] = data_buff[0];
			u8_returnLen =7;			
			break;

		case 0x04000401://���ַ ��� NNNNNNNNNNNN
			mem_read(&data_buff[0], (INT16U)comm_data.addr,  comm_data.len,  mem_type );
			comm_data.len_asc = get_meter_id_asclen(&data_buff[0], 16);
			comm_data.len = comm_data.len_asc/2;
			for(i=0;i<comm_data.len;i++)
			{
				ptr[DLT_ReadDataPtr+i]=data_buff[comm_data.len-1-i];
			}
			u8_returnLen =comm_data.len;			
			break;

		case 0x04800001: //����汾�� ����ASC��
			Lib_Copy_Str_TwoArry(&data_buff[0], ptr_adr, comm_data.len);
			for(i=0;i<comm_data.len;i++)
			{
				ptr[DLT_ReadDataPtr+i]=data_buff[comm_data.len-1-i];
			}
			u8_returnLen =comm_data.len;			
			break;		
		case 0x80805001:	//��ǰ���ܵ���+�̵���״̬+�������ʱ�� //
			//��ǰ���ܵ���
			mem_read(&data_buff[10], (INT16U)&gs_energy_user_data.us_val[0][0].buf[0], LEN_EC_UNIT, MEM_RAM);	  //��ȡ��ǰ���� //
			api_get_energy_LCD(&data_buff[10], 0x62,&data_buff[0]);
			for(i=0;i<4;i++)
			{
				ptr[DLT_ReadDataPtr+i]=data_buff[4-1-i];
			}
			//�̵���״̬
			mem_read(&data_buff[0], (INT16U)ADR_METER_PARAM1_RELAY_CMD, 2, MEM_E2P1);	  //��ȡ��ǰ���� //
			for(i=0;i<2;i++)
			{
				ptr[DLT_ReadDataPtr+i+4]=data_buff[2-1-i];
			}
			Lib_Copy_Str_TwoArry(&data_buff[0], &gs_CurDateTime.Year, 6);
			for(i=0;i<6;i++)
			{
				ptr[DLT_ReadDataPtr+i+4+2]=data_buff[6-1-i];
			}
			u8_returnLen =comm_data.len;			
		break;
		default:
////////////////���������⴦��/////////////////////////////
			if(gs_dlt645_07_var.u32_DI.BYTE[0]==0x00)
			{
				comm_data.len = LEN_EC_UNIT;   // �޸Ļ�ȡ����//
			}
///////////////////////////////////////////////////////////////////

			if((comm_data.Info.u16&CM_ALL) == CM_BILL)
			{
				mem_read(&data_buff[0], api_get_bill_record_addr((INT16U)comm_data.addr), comm_data.len,  mem_type );
			}
			else 
			{
				if(mem_type==MEM_RAM)
				{
					Lib_Copy_Str_TwoArry(&data_buff[0], ptr_adr, comm_data.len);
				}
				else
				{
					mem_read(&data_buff[0], (INT16U)comm_data.addr, comm_data.len, mem_type );
				}
			}

////////////////���������⴦��/////////////////////////////
			if(gs_dlt645_07_var.u32_DI.BYTE[0]==0x00)
			{
				Lib_Copy_Str_TwoArry(&data_buff[10], &data_buff[0], LEN_EC_UNIT);
				api_get_energy_LCD(&data_buff[10], 0x62, &data_buff[0]) ;
				comm_data.len=4;
			}
///////////////////////////////////////////////////////////////////

////////////////����������⴦��/////////////////////////////
			if(gs_dlt645_07_var.u32_DI.BYTE[0]==0x01)
			{  
				Lib_Copy_Str_TwoArry(&long_tmp.B08[0], &data_buff[0], 4);
				Lib_long_bcd4(&data_buff[0],long_tmp.u32);
			}
/////////////////////////////////////////////////////////////////// 		   
			for(i=0;i<comm_data.len;i++)
			{
				ptr[DLT_ReadDataPtr+i]=data_buff[comm_data.len-1-i];
			}
			u8_returnLen =comm_data.len;			
			break;	
	}


	//�����ɹ������ݴ���  //	
	gs_dlt645_07_var.u8_lenOfData =u8_returnLen;        //�������ݳ��ȶ��帳ֵ  //
	ptr[DLT_CtlPtr] += 0X80;
	ptr[DLT_LenPtr] =gs_dlt645_07_var.u8_lenOfData+4;    //4Ϊ�̶�ID���� //		
	return(RS_State_OK); 	
}

/*****************************************************************
DLT645 C=0X14 ��������سɹ�������������Ѿ���д�÷�������
*****************************************************************/
INT8U DLT645_07_CTL0X14_write(INT8U *ptr)
{
	//INT8U u8_returnLen;
	INT8U i,MeterID_LenTmp;
	INT8U mem_type;
	INT8U u8_buff[100];

	// 0  �������жϴ���          //
	if(DLT_SecurityCK(ptr) != mmok )  
	{
		//�������  //
		gs_dlt645_07_var.u8_lenOfData =1;		//�������ݳ��ȶ��帳ֵ  //
		return(RS_State_PswE); 		
	}

	// 1 ���ݿ���ID,����Ϊ��λ��ǰ��C51		  U32����Ϊ���ģʽ	//
	gs_dlt645_07_var.u32_DI.BYTE[0] = ptr[DLT_CmdDI3Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[1] = ptr[DLT_CmdDI2Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[2] = ptr[DLT_CmdDI1Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[3] = ptr[DLT_CmdDI0Ptr];
	
	if(get_IEC_comm_var(gs_dlt645_07_var.u32_DI.UDWORD) == 0 )	return(RS_State_IVID);
	if( ( comm_data.Info.u16& EN_W) == 0 )	return(RS_State_IVData);
	//	��ȡ���ݵĴ洢���� //
	mem_type = (comm_data.Info.B08[0]>>3)&0x07; 	
    //���������㲢�����յ����ݳ��ȺϷ��� //
    Lib_Set_String(&u8_buff[0], 0x00, comm_data.len); 
    if(gs_dlt645_07_var.u32_DI.UDWORD== 0x04000401) //�����ñ����.����Ҫ�Ա����ݳ���
    {
        if((ptr[DLT_LenPtr] > (12+comm_data.len))||(ptr[DLT_LenPtr] < 12))	   
		{
			//���ݺϷ����ж�  //
			gs_dlt645_07_var.u8_lenOfData =1;		//�������ݳ��ȶ��帳ֵ  //
			return(RS_State_IVData); 
		}
    }
    else
    {
        if(ptr[DLT_LenPtr] != (12+comm_data.len))	   
		{
			//���ݺϷ����ж�  //
			gs_dlt645_07_var.u8_lenOfData =1;		//�������ݳ��ȶ��帳ֵ  //
			return(RS_State_IVData); 
		}
    }
	// 2 д�������жϴ���          //	
	switch (gs_dlt645_07_var.u32_DI.UDWORD)
		{
			case 0x04800003:
				//�޸ļ̵���״̬�������̵�������բ //
				for(i=0;i<comm_data.len;i++)
				{
					u8_buff[i]=ptr[DLT_WriteDataPtr+i];
				}
				if(Drv_relay_COMM_CMD_operating(&u8_buff[0])==FALSE)  
				{
					//���ݺϷ����ж�  //
					gs_dlt645_07_var.u8_lenOfData =1;		//�������ݳ��ȶ��帳ֵ  //
					return(RS_State_IVData); 
				}
				break;

			case 0x04000100://���ڼ�����(����0����������)YYMMDDWWhhmmss  
				gs_CurDateTime.Year= ptr[DLT_WriteDataPtr];
				gs_CurDateTime.Month= ptr[DLT_WriteDataPtr+1];
				gs_CurDateTime.Day= ptr[DLT_WriteDataPtr+2];
				gs_CurDateTime.Week= ptr[DLT_WriteDataPtr+3];
				gs_CurDateTime.Hour= ptr[DLT_WriteDataPtr+4];
				gs_CurDateTime.Minute= ptr[DLT_WriteDataPtr+5];
				gs_CurDateTime.Second= ptr[DLT_WriteDataPtr+6];
				EA=0;
				Set_RTCTime(&gs_CurDateTime);
				EA=1;
				mem_db_write((INT16U)ADR_METER_VAR_RTC, &gs_CurDateTime.Week, 7, MEM_E2P1);
				api_init_md_data_ram();
				#if (TARIFF_MAX_NUM>0)
				api_update_triffNo_pre_minute();
				#endif
				break;

			//������⴦��
			case 0x04000401://���ַ ��� 16���ֽ� ����Ӧ,������������ǰ��0
				MeterID_LenTmp = (ptr[DLT_LenPtr]-12);	//��Ч���	����
				Lib_Set_String(&u8_buff[0], 0xFF, 16);
				for(i=0;i<MeterID_LenTmp;i++)
				{
					u8_buff[i]=ptr[DLT_WriteDataPtr+i];
				}
				mem_db_write((INT16U)comm_data.addr, &u8_buff[0], comm_data.len, mem_type);		//д��Ӧ����16�ֽڣ����������õĳ���
				break;

			case 0x04000B01://������DDHH 4
					for(i=0;i<comm_data.len;i++)
					{
						u8_buff[i]=ptr[DLT_WriteDataPtr+i];
					}
					if((u8_buff[0]<0x01)||(u8_buff[0]>0x28)||(u8_buff[1]>0x23))		//�����ж�
					{
						return(RS_State_IVData);
					}
					mem_db_write((INT16U)comm_data.addr, &u8_buff[0], comm_data.len, mem_type);
					break;
					
			case 0x04000103://�������� PERIOD : SLID   4  //�޸ĺ��������¼��� //
					for(i=0;i<comm_data.len;i++)
					{
						u8_buff[i]=ptr[DLT_WriteDataPtr+i];
					}
					if(((u8_buff[0]%u8_buff[1]) !=0)||(u8_buff[0]>30)||(u8_buff[0]==0)||(u8_buff[1]==0))		//�����ж�//
					{
						return(RS_State_IVData);
					}
					mem_db_write((INT16U)comm_data.addr, &u8_buff[0], comm_data.len, mem_type);
					api_init_md_data_ram();
					break;

			case 0x08020200://NN=00���������ͨ����//
				for(i=0;i<comm_data.len;i++)
				{
					u8_buff[i]=ptr[DLT_WriteDataPtr+i];
				}
				if(u8_buff[0]==0x00)
				{
					api_clr_even_by_comm(); 
					CLRWDT();
				}
				else
				{
					return(RS_State_IVData);
				}
				break;
				
			case 0x08020100://ֻ�嵱ǰ��������//
				for(i=0;i<comm_data.len;i++)
				{
					u8_buff[i]=ptr[DLT_WriteDataPtr+i];
				}
				if(u8_buff[0]!=0)
				return(RS_State_IVData);
				api_clr_current_MD_data();
				CLRWDT();
			break;
			
		case 0x08020300:
			for(i=0;i<comm_data.len;i++)
			{
				u8_buff[i]=ptr[DLT_WriteDataPtr+i];
			}
			if(u8_buff[0]==0x00)
			{
				LoadProRst();
				CLRWDT();
			}
			else
			{
				return(RS_State_IVData);
			}
			break;
		case 0x08020400://��������(�������(����+����)) //
			for(i=0;i<comm_data.len;i++)
			{
				u8_buff[i]=ptr[DLT_WriteDataPtr+i];
			}
			if((u8_buff[0]!=0)||(u8_buff[1]!=0)||(u8_buff[2]!=0)||(u8_buff[3]!=0))
				return(RS_State_IVData);
			api_clr_current_energy_data();
			CLRWDT();
			api_clr_current_MD_data();
			CLRWDT();
#if (BILL_MAX_NUM>0)
			api_clr_bill_data();
#endif
			CLRWDT();
			LoadProRst();
			CLRWDT();
			api_clr_even_by_comm(); 
			CLRWDT();
			api_chg_LCDDisplay_adj_item(DIS_DATA_CLR);	 // Һ����ʾ //
			break;
		default:
			for(i=0;i<comm_data.len;i++)
			{
				u8_buff[i]=ptr[DLT_WriteDataPtr+i];
			}
			
			 if(mem_type == MEM_RAM)
			 {
				   mem_write((INT16U)comm_data.addr,&u8_buff[0], comm_data.len, mem_type);
			 }
			 else
			 {
				   mem_db_write((INT16U)comm_data.addr, &u8_buff[0], comm_data.len, mem_type);
			 }
			 
			break;	
		}
	/////////////////������ʾ��������Ҫ����///////
		if((gs_dlt645_07_var.u32_DI.UDWORD == 0x04000302)||(gs_dlt645_07_var.u32_DI.UDWORD == 0x04000303)||(gs_dlt645_07_var.u32_DI.UDWORD == 0x04040100))
		{
			mem_read(&gs_dis_param.auto_sec, ADR_BLOCK21_DIS_PARAM_E2P, LEN_BLOCK21_DIS_PARAM_E2P, MEM_E2P1);
		}	
	//�����ɹ������ݴ���  //	
	gs_dlt645_07_var.u8_lenOfData =0;		//�����ɹ��������ݳ��ȶ��帳ֵ  //
	ptr[DLT_CtlPtr] += 0X80;
	ptr[DLT_LenPtr] =gs_dlt645_07_var.u8_lenOfData;		
	return(RS_State_OK); 
}

/*****************************************************************
DLT645 C=0X18 �����޸�����,���سɹ�������������Ѿ���д�÷�������
*****************************************************************/
INT8U DLT645_07_CTL0X18_chgMIMA(INT8U *ptr)
{
	INT8U i;
	
	// 0  �������жϴ���          //
	if(DLT_SecurityCK(ptr) != mmok )  
	{
		//�������  //
		gs_dlt645_07_var.u8_lenOfData =1;		//�������ݳ��ȶ��帳ֵ  //
		return(RS_State_PswE); 		
	}

	// 1 ���ݿ���ID,����Ϊ��λ��ǰ��C51		  U32����Ϊ���ģʽ	//
	gs_dlt645_07_var.u32_DI.BYTE[0] = ptr[DLT_CmdDI3Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[1] = ptr[DLT_CmdDI2Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[2] = ptr[DLT_CmdDI1Ptr];
	gs_dlt645_07_var.u32_DI.BYTE[3] = ptr[DLT_CmdDI0Ptr];

	// 2  ID�жϴ���  //
	if((gs_dlt645_07_var.u32_DI.UDWORD<0X04000C01) || (gs_dlt645_07_var.u32_DI.UDWORD >0X04000C02) )
	{
		return(RS_State_IVID);
	}

	// 3  ���ݳ��ȺϷ����жϴ���  //
	if(ptr[DLT_LenPtr] != 12 )           //12Ϊ�̶����ȣ�4ID��4�����룬4������  //
	{
		//���ݺϷ����ж�  //
		gs_dlt645_07_var.u8_lenOfData =1;		//�������ݳ��ȶ��帳ֵ  //
		return(RS_State_IVData); 
	}	

	//ID��ȷ��������޸Ĵ���  //	
	mem_db_write(ADR_METER_PARAM1_PW1, &ptr[DLT_WriterC0Ptr], 4, MEM_E2P1);

	//�����ɹ������ݴ���  //	
	gs_dlt645_07_var.u8_lenOfData =4;		//�����ɹ��������ݳ��ȶ��帳ֵ  //
	ptr[DLT_CtlPtr] += 0X80;
	ptr[DLT_LenPtr] =gs_dlt645_07_var.u8_lenOfData;
	for(i=0;i<gs_dlt645_07_var.u8_lenOfData;i++)
	{
		ptr[DLT_Cmd+i] = ptr[DLT_WriterC0Ptr+i];
	}	
	return(RS_State_OK); 
}


/*****************************************************************************
** Function name    :INT8U Lnk_SX127X_rx_data(INT8U *rx_ptr)
**
** Description          :�жϲ���ȡRFģʽ�������ݲ������RAM��
**
** Parameters           :NONE
**
** Returned value       :INT8U  ���շ��س��ȣ�0����δ���յ�����
**
** Note                 :
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-12-07
******************************************************************************/
void api_DLT645_07_protocol_analysis(void)
{
	INT8U start_index;
	INT8U i;
	INT8U result_analysis;
	INT8U offset_cs;

    //ǰ���ֽں� ֡ͷ�жϴ���//
    for(start_index=0;start_index<5;start_index++)
    {
        if((P_DL645_07_BUFF[start_index]==0X68)&&(P_DL645_07_BUFF[start_index+DLT_Head0Ptr]==0X68))  break;
    } 
    if(start_index>4)
    {
        //���յ�����֡���󣬸�λ����      //
        api_RF_commRAM_RESET();
        return;
    }

    //CSУ��ʹ���//
    offset_cs = DLT_Cmd+P_DL645_07_BUFF[start_index+DLT_LenPtr];
    if(P_DL645_07_BUFF[start_index+offset_cs] !=(INT8U)( Lib_get_csck_int16u_num( &(P_DL645_07_BUFF[start_index]), (INT8U)(offset_cs),0 )))
    { 
        //���յ�����֡���󣬸�λ����      //
        api_RF_commRAM_RESET();
        return;
    } 

    //�����ַ�����//
    if(P_DL645_07_BUFF[start_index+offset_cs+1] !=0x16)
    { 
        //���յ�����֡���󣬸�λ����      //
        api_RF_commRAM_RESET();
        return;
    } 

    //��ż���ж�//
    if(MeteIDCheck(&P_DL645_07_BUFF[start_index+DLT_Head0Ptr])!=TRUE )
    { 
        //���յ�����֡���󣬸�λ����      //
        api_RF_commRAM_RESET();
        return;
    } 

	//data  subtract 0x33 process   //
    for(i=0; i<P_DL645_07_BUFF[start_index+DLT_LenPtr]; i++ )
    {
        P_DL645_07_BUFF[start_index+DLT_Cmd+i] -= 0x33;
    }

	//������C��֧����  //
	switch (P_DL645_07_BUFF[start_index+DLT_CtlPtr]& 0x1F)
	{
		case DLT_CTL_Read:
			result_analysis = DLT645_07_CTL0X11_read(&P_DL645_07_BUFF[start_index] );
			break;

		case DLT_CTL_Write:
			result_analysis = DLT645_07_CTL0X14_write(&P_DL645_07_BUFF[start_index] );
			break;

		case DLT_CTL_ChgPswd:
			result_analysis = DLT645_07_CTL0X18_chgMIMA(&P_DL645_07_BUFF[start_index] );
			break;

		case DLT_CTL_Broadcast:
			result_analysis = RS_State_Broadcast;
			break;
			
		default:
			//���տ�������󣬲�Ӧ��//
			api_RF_commRAM_RESET();
			return;
	}
	//��Է��ؽ���ķ�֧���� //
	if(result_analysis==RS_State_OK)
		{		
		}
	else if((result_analysis==RS_State_IVData)||(result_analysis==RS_State_IVID))
		{
			P_DL645_07_BUFF[start_index+DLT_CtlPtr] +=0XC0;
			P_DL645_07_BUFF[start_index+DLT_LenPtr] =1;
			P_DL645_07_BUFF[start_index+DLT_Cmd] =BIT0;
		}	
	else if(result_analysis==RS_State_PswE)
		{
			P_DL645_07_BUFF[start_index+DLT_CtlPtr] +=0XC0;
			P_DL645_07_BUFF[start_index+DLT_LenPtr] =1;
			P_DL645_07_BUFF[start_index+DLT_Cmd] =BIT2;
		}
	else if(result_analysis==RS_State_Broadcast)
		{
			api_chg_LCDDisplay_adj_item(DIS_DATA_BROADCAST);   // Һ����ʾ //
			//ֱ�Ӹ�λRFͨѶ�ӿڣ��޷�������  //
			api_RF_commRAM_RESET();
			return;
		}
	else
		{
			//ֱ�Ӹ�λRFͨѶ�ӿڣ��޷�������	//
			api_RF_commRAM_RESET();
			return;
		}


	/////////////////////////////////////////////////////////
	//����������֡
	////////////////////////////////////////////////////////

	// 1 ��ȡ�������  //
	mem_read(&P_DL645_07_BUFF[start_index+DLT_AddrPtr], ADR_METER_PARAM1_RF_COMM_ID, 6, MEM_E2P1);

	// 2 data  add 0x33 process   //
    for(i=0; i<P_DL645_07_BUFF[start_index+DLT_LenPtr]; i++ )
    {
        P_DL645_07_BUFF[start_index+DLT_Cmd+i] += 0x33;
    }

	// 3 CS У��ͻ�ȡ //
    offset_cs = DLT_Cmd+P_DL645_07_BUFF[start_index+DLT_LenPtr];
    P_DL645_07_BUFF[start_index+offset_cs] =(INT8U)( Lib_get_csck_int16u_num( &(P_DL645_07_BUFF[start_index]), (INT8U)(offset_cs),0 ));	

	// 4 ��������ȡ //
	P_DL645_07_BUFF[start_index+offset_cs+1] =0x16;


	/////////////////////////////////////////////////////////
	//���÷���ǰ׼��
	////////////////////////////////////////////////////////
	gs_dlt645_07_var.start_index = start_index;
	gs_dlt645_07_var.tx_frame_len= start_index+12+P_DL645_07_BUFF[start_index+DLT_LenPtr];   // ��ȡ���ݷ���֡�ܳ��� //
	gs_dlt645_07_var.tx_delay_flg = TRUE;
	gs_dlt645_07_var.tx_ready_10ms =8;         //��ʱ80ms //

}


/*****************************************************************************
** Function name    :INT8U Lnk_SX127X_rx_data(INT8U *rx_ptr)
**
** Description          :�жϲ���ȡRFģʽ�������ݲ������RAM��
**
** Parameters           :NONE
**
** Returned value       :INT8U  ���շ��س��ȣ�0����δ���յ�����
**
** Note                 :
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-12-07
******************************************************************************/
void api_RF_tx_data(INT8U *txbuf,INT8U tx_len)
{
    if(tx_len==0)   return;
    G_LoRaConfig.PayloadLength= tx_len;   
    SX1276_TxPacket(txbuf);
    gs_rf_drv_var.status = RF_STATUS_TX;   
    gs_rf_drv_var.tmr_tx_max_wait = 0;
}


/*****************************************************************************
** Function name    :INT8U Lnk_SX127X_rx_data(INT8U *rx_ptr)
**
** Description          :�жϲ���ȡRFģʽ�������ݲ������RAM��
**
** Parameters           :NONE
**
** Returned value       :INT8U  ���շ��س��ȣ�0����δ���յ�����
**
** Note                 :
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-12-07
******************************************************************************/
void api_RF_commRAM_RESET(void)
{
	gs_rf_drv_var.status = RF_STATUS_RX;
	gs_rf_drv_var.data_len = 0;
	Lib_Clr_String(&gs_rf_drv_var.buff[0],RF_BUFF_MAX_SIZE);
	gs_rf_drv_var.tmr_tx_max_wait = 0;
	Lib_Clr_String(&gs_dlt645_07_var.u8_result,sizeof(DLT645_07_VAR));
	
	Lnk_SX2176_Intilize();	
}

/*****************************************************************************
** Function name    :INT8U Lnk_SX127X_rx_data(INT8U *rx_ptr)
**
** Description          :�жϲ���ȡRFģʽ�������ݲ������RAM��
**
** Parameters           :NONE
**
** Returned value       :INT8U  ���շ��س��ȣ�0����δ���յ�����
**
** Note                 :
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-12-07
******************************************************************************/
INT8U api_RF_judge_rx(INT8U **p_buf)
{
    if(gs_rf_drv_var.status == RF_STATUS_TX)   return(0);       //����״̬��������� //
    
    // ���ػ�������ַ //
    *p_buf = &gs_rf_drv_var.buff[0] ;
 	// RF ͨ���Ƿ���յ����� //
	gs_rf_drv_var.data_len = Lnk_sx1276_rx_data(&gs_rf_drv_var.buff[0]);

	return (gs_rf_drv_var.data_len);
}


/*****************************************************************************
** Function name    :INT8U Lnk_SX127X_rx_data(INT8U *rx_ptr)
**
** Description          :�жϲ���ȡRFģʽ�������ݲ������RAM��
**
** Parameters           :NONE
**
** Returned value       :INT8U  ���շ��س��ȣ�0����δ���յ�����
**
** Note                 :
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-12-07
******************************************************************************/
void api_RF_judge_tx(void)
{
	if((gs_dlt645_07_var.tx_ready_10ms ==0)&&(gs_dlt645_07_var.tx_delay_flg ==TRUE))
		{
        P_DL645_07_BUFF = &gs_rf_drv_var.buff[0];
        api_RF_tx_data(&P_DL645_07_BUFF[0], gs_dlt645_07_var.tx_frame_len);   // ���ݷ��ͣ���ǰ�� //   
        gs_dlt645_07_var.tx_delay_flg =FALSE;
		}
}

/*****************************************************************************
** Function name    :INT8U Lnk_SX127X_rx_data(INT8U *rx_ptr)
**
** Description          :�жϲ���ȡRFģʽ�������ݲ������RAM��
**
** Parameters           :NONE
**
** Returned value       :INT8U  ���շ��س��ȣ�0����δ���յ�����
**
** Note                 :
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-12-07
******************************************************************************/
void api_RF_judge_tx_over_delay(void)
{
    if(gs_rf_drv_var.status != RF_STATUS_TX)    return ;           //���Ƿ���״̬���˳� //

	//RFģ�鷢�ͳ�ʱ������TRUE,������λ����ͨѶͨ�� //
    if((gs_rf_drv_var.tmr_tx_max_wait>=RF_TX_WAIT_MAX_TRM))
    {      
		api_RF_commRAM_RESET();    		
		return; 
    }

	// RF ͨ���Ƿ��������� //
   if(LSD_RF_READ_DIO0()==0) return;
   Lib_Delay_2us(5);
   if(LSD_RF_READ_DIO0() ==0) return ;   

   api_RF_commRAM_RESET();		   
   return; 
}


/*****************************************************************************
** Function name    :INT8U Lnk_SX127X_rx_data(INT8U *rx_ptr)
**
** Description          :�жϲ���ȡRFģʽ�������ݲ������RAM��
**
** Parameters           :NONE
**
** Returned value       :INT8U  ���շ��س��ȣ�0����δ���յ�����
**
** Note                 :
**
**----------------------------------------------------------------------------
** V01.01  MJ  2016-12-07
******************************************************************************/
void api_RF_comm_deal(void)
{
	INT8U buff_size;

    if(gs_rf_drv_var.status == RF_STATUS_TX)   return;       //����״̬��������� //
	CLRWDT();	// �忴�Ź�//
	buff_size = api_RF_judge_rx(&P_DL645_07_BUFF); 

    if(buff_size==0) return;    // ÿ��ѭ����ȡһ�ν������ݳ��ȣ�=0���˳� //	

	gs_rf_drv_var.data_len = buff_size;
	CLRWDT();	// �忴�Ź�//
	api_DLT645_07_protocol_analysis();

}



/*******************************************************************
*
*  end of file                                    
*
*******************************************************************/

