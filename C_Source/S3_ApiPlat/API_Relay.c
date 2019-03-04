/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: API_Relay.c
**Author: maji
**date: 
**description: c code for �ű��̵ּ�������
**note: memer type  DI03B
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2017-09-06   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>

/*********************************************************************************************************
**  ȫ�ֱ�����
********************************************************************************************************/
RELAY_MANAGE_VAR_TYPE gs_relay_manage_var;

/*********************************************************************************************************
**  �����������
********************************************************************************************************/



/*********************************************************************************************************
**  ������   start
********************************************************************************************************/




/*****************************************************************************
** Function name    :void Drv_relay_run_check(void)
**
** Description      :�̵��������鴦��
**
** Parameters       :NONE  
**
** Returned value	:NONE
**
** Note             :1 ����������ѭ���н��е��ã�����ʵ�ֶԼ̵���״̬�ļ��
**                  :2 
**----------------------------------------------------------------------------
** V01.01  MJ  2017-09-15
******************************************************************************/
void Drv_relay_run_check(void)
{
//	if((gs_relay_manage_var.u8_CMD==CMD_RELAY_OFF)&&( gs_relay_manage_var.u8_STA !=CMD_RELAY_OFF )) 
//	{
//		//��բ���� //
//		if(gs_relay_manage_var.u8_tmr_opera == 0)
//		{
//			CTL_Relay_OFF(); 
//			gs_relay_manage_var.u8_tmr_opera = TMR_OPERA_RELAY;
//			//�ȴ��жϴ�����ʱ  //
//			while(gs_relay_manage_var.u8_tmr_opera!=0)
//			{
//				
//			}
//			CTL_Relay_FREE() ;
//			Lib_Delay_ms(20);  //�˴�����ʱ��Ϊ��ȷ����բ������ĵ�Դ�ָ��������´μ̵����������̫С���µ�Դ���� //
//			//����״̬������   //
//			gs_relay_manage_var.u8_STA = CMD_RELAY_OFF;
//			mem_db_write(ADR_METER_PARAM1_RELAY_CMD, &gs_relay_manage_var.u8_CMD, 2, MEM_E2P1);
//			api_deal_even_class_recode(ID_CLASS_I_RELAY_OFF,START);  //���ɺ�բ�¼���¼ //
//		}
//	}
//	else if((gs_relay_manage_var.u8_CMD==CMD_RELAY_ON)&&( gs_relay_manage_var.u8_STA !=CMD_RELAY_ON )) 
//	{
//		//��բ���� //
//		if(gs_relay_manage_var.u8_tmr_opera == 0)
//		{
//			CTL_Relay_ON(); 
//			gs_relay_manage_var.u8_tmr_opera = TMR_OPERA_RELAY;
//			//�ȴ��жϴ�����ʱ  //
//			while(gs_relay_manage_var.u8_tmr_opera!=0)
//			{
//				
//			}
//			CTL_Relay_FREE() ;
//			Lib_Delay_ms(20);  //�˴�����ʱ��Ϊ��ȷ����բ������ĵ�Դ�ָ��������´μ̵����������̫С���µ�Դ���� //
//			//����״̬������   //			
//			gs_relay_manage_var.u8_STA = CMD_RELAY_ON;
//			mem_db_write(ADR_METER_PARAM1_RELAY_CMD, &gs_relay_manage_var.u8_CMD, 2, MEM_E2P1);		
//			api_deal_even_class_recode(ID_CLASS_I_RELAY_ON,START);	//������բ�¼���¼ //
//		}			
//	}
//	else
//	{
//		return;
//	}

}


/*****************************************************************************
** Function name    :void Drv_relay_powerup_check(void)
**
** Description      :���ܱ��ϵ��ʼ������̵�������
**
** Parameters       :NONE
**
** Returned value	:NONE
**
** Note             :1 ��ʼ�����ܱ��Ⱥ�բ����Ϊ�˿ɿ��Կ��ǣ��ڼ̵�������ʱ����ͨ�����µ�ָ�
**                  :2 ע�⣬������ֻ���ϵ��ʼ������
**----------------------------------------------------------------------------
** V01.01  MJ  2017-09-15
******************************************************************************/
void Drv_relay_powerup_check(void)
{
	//1 Ӳ��IO�ڳ�ʼ��  //
	PIN_Relay_INITLIZE();
	CTL_Relay_FREE() ;
	Lib_Delay_ms(100);  //�˴�����ʱ��Ϊ��ȷ����բ����ǰ�ĵ�Դ�ȶ���ʱ //

	//�ϵ�Ԥ��բ  //
	CTL_Relay_OFF(); 
	Lib_Delay_ms(80);	
	CTL_Relay_FREE();

	//��ر�����ʼ��  //
	mem_read( &gs_relay_manage_var.u8_CMD, ADR_METER_PARAM1_RELAY_CMD, 2, MEM_E2P1);
	gs_relay_manage_var.u8_STA =CMD_RELAY_OFF;//�ϵ�Ĭ��Ϊ��բ״̬
	//��ȡ�̵�������բ���������������ͨѶ���������բ����������ԭ������///
	//���糬���ɵ��������բ���ϵ��Զ���բ���� yang 2017-12-22////
	if((gs_relay_manage_var.u8_CMD != CMD_RELAY_OFF) &&(gs_relay_manage_var.u8_CMD != CMD_RELAY_ON))   
	{
		gs_relay_manage_var.u8_STA =CMD_RELAY_OFF;
		mem_db_write(ADR_METER_PARAM1_RELAY_CMD, &gs_relay_manage_var.u8_CMD, 2, MEM_E2P1);
	}
	gs_relay_manage_var.u8_tmr_opera =0;
	Lib_Delay_ms(100);  //�˴�����ʱ��Ϊ��ȷ����բ������ĵ�Դ�ָ��������´μ̵����������̫С���µ�Դ���� //
    CLRWDT();   // �忴�Ź�//
}




/*****************************************************************************
** Function name    :INT8U Drv_relay_COMM_CMD_operating(INT8U *ptr_cmd)
**
** Description      :ͨѶ�������ñ���������̵�������ָ��
**
** Parameters       :INT8U *ptr_cmd ͨѶ�������ڵĿ������ݣ�2�ֽ������׵�ַ   
**
** Returned value	:INT8U,����������ݼ�鲻�Ϸ�����ʧ��
**
** Note             :1 ������ֻ�޸�RAM���������ݣ����Լ̵�����ʵ�ʲ���
**                  :2 ע�⣬������ֻ��ͨѶ����������
**----------------------------------------------------------------------------
** V01.01  MJ  2017-09-15
******************************************************************************/
INT8U Drv_relay_COMM_CMD_operating(INT8U *ptr_cmd)
{
	INT8U u8_cmd,u8_sta;
	
	u8_cmd = *ptr_cmd;
	u8_sta =  *(ptr_cmd+1);

			
	//�������������ж�  //
	if(u8_cmd != u8_sta )  return FALSE;    //���ݸ�ʽ����  //

	if(u8_cmd ==CMD_RELAY_OFF )
		{
		//ͨѶ��բ����,ǿ��ϵͳ��բ	//
		gs_relay_manage_var.u8_CMD = CMD_RELAY_OFF;
		gs_relay_manage_var.u8_STA = CMD_RELAY_ON;
		gs_relay_manage_var.u8_tmr_opera = 0;
		Drv_relay_run_check();   //�̵���������  //
		}
	else if(u8_cmd ==CMD_RELAY_ON)
		{
		//ͨѶ��բ����	,ǿ��ϵͳ��բ//
		gs_relay_manage_var.u8_CMD = CMD_RELAY_ON;
		gs_relay_manage_var.u8_STA = CMD_RELAY_OFF;
		gs_relay_manage_var.u8_tmr_opera = 0;
		Drv_relay_run_check();  //�̵���������  //
		}
	else
		{
			return FALSE;	
		}
	
    CLRWDT();   // �忴�Ź�//
	return TRUE;
}



/*******************************************************************
*
*  end of file                                    
*
*******************************************************************/

