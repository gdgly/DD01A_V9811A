/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Lnk_EMU_Adj.c
**Author		: maji
**date			: 2016-04-20 
**description	: G80F92XD��EMU����ģ����·��У����C����
**note			: MCU- G80F92XD ��MERTER FOR DL06A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-20   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>



ST_EMU_ADJ_PARAM  gs_adj_emu_param;
ST_EMU_ADJ_VAR      gs_emu_adj_var;


/*********************************************************************************************************
**  У����ز�����ʼ��Ĭ������
********************************************************************************************************/
const  ST_EMU_ADJ_PARAM   code   default_adj_emu_param_tab = 
{
    0,  //uint32 w1gain;         //ͨ��1��������Ĵ���(�й��޹�ʹ��ͬһ��)  //0xFF,0x3B,0x66,0x28,
    0,  //uint32 p1cal;           //ͨ��1��ѹ������λ�����Ĵ���  //
    0,  //uint32 watt1os;      //ͨ��1�й�����ƫ��  //
    0,  //uint32 irms1os;      //ͨ��1������Чֵƫ��  //
    0,  //uint32 w2gain;         //ͨ��2��������Ĵ���(�й��޹�ʹ��ͬһ��)  //0xFF3B6628
    0,  //uint32 p2cal;           //ͨ��2��ѹ������λ�����Ĵ���  //
    0,  //uint32 watt2os;      //ͨ��2�й�����ƫ��  //
    0,  //uint32 irms2os;      //ͨ��2������Чֵƫ��  //
	0,  //uint32 urmsos       //��ѹ��Чֵƫ��  //
    0.075138056,  //uint32 vconst_val_ch1;   //ͨ��1�����ߵ�ѹ�̶�ֵ //    
    0.112707084,  //uint32 vconst_val_ch2;   //ͨ��2�����ߵ�ѹ�̶�ֵ //
    1.07355e-005,  //float vrms_xs;          //��Ϊ����ĵ�ѹ��Чֵϵ��  //9.19946e-006
    //2019-01-17�޸ĵ�����Чֵϵ��
	0.000163094,//0.000153309,  //float i1rms_xs;         //��Ϊ�����ͨ��1������Чֵϵ��  //
    0.000163094,//0.000153309,  //float i2rms_xs;         //��Ϊ�����ͨ��2������Чֵϵ��  //8.279879e-005   1.14993e-007
    0,  //uint16     csck;  //У��� //
};

const  ST_Adjust_CONST  code   cst_adj_const = 
{
    C_Un*10,        //uint32 U_ref;       //�αȵ�ѹֵ������0.1V  // 
    C_Ib*1000,     //uint32 I_ref;       //�αȵ���ֵ������0.001A  //     
    INITGATEP,     //uint32 GATEP;       // ��������ֵ //
    INITGATECP,   //uint32 C_GATECP;     // Ǳ������ֵ //
    REF_RMSPn,    // uint32 C_PCONST;    // ����ʵ�У׼���׼ֵ//
    K_RMSP,         //float   Kim_Prms;  //�й�������Чֵϵ��//  
    K_RMSP2,   		// �޹�������Чֵϵ��
};


const  EMU_CK_TAB  code   cst_emu_selfchck_tab[] = 
{
    &gs_adj_emu_param.w1gain,            SCP,    //ͨ��1��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    &gs_adj_emu_param.w2gain,            SCQ,    //ͨ��2��������Ĵ���(�й��޹�ʹ��ͬһ��)  //
    &gs_adj_emu_param.p1cal,            PHCCtrl1,    //ͨ��1��ѹ������λ�����Ĵ���  //
    &gs_adj_emu_param.p2cal,            PHCCtrl2,    //ͨ��2��ѹ������λ�����Ĵ���  //
    &gs_adj_emu_param.watt1os,            PARAPC,    //ͨ��1�й�����ƫ��  // 
    &gs_adj_emu_param.watt2os,            PARAQC,    //ͨ��2�й�����ƫ��  //
	&gs_adj_emu_param.irms1os,			  SCI1,	 //ͨ��1������Чֵƫ��  // 
	&gs_adj_emu_param.irms2os,			  SCI2,	 //ͨ��1������Чֵƫ��    // 
	&gs_adj_emu_param.urmsos,			  SCU,	 //��ѹ��Чֵƫ��  //
};


const  EMU_CONST_CK_TAB  code   cst_emu_constchck_tab[] = 
{
    INITGATECP,           GATECP,    //uint32 C_GATECP;   // Ǳ������ֵ //
    INITGATECQ,           GATECQ,    //uint32 C_GATECP;   // Ǳ������ֵ //
};


//9260F �̶������//
const  EMU_CONST_CK_TAB_9260F code   cst_emu_constchck_tab_9260f[] = 
{
    0x1D0004C3,          RegANCtrl0,    //0x185  BIT0-BIT1 I���� 00 x32 01 x16 10 x8  11 x1
	0x30000000,          RegANCtrl1,    //0x185 ����I:32��U:1��M:4 �¶�ϵ����ȫ�ֵ���ƫ��
    0x00000000,          RegANCtrl2,     //0x187  
    0x811D2BA7,          RegBPFPARA,    //0x0125 ��ͨ�˲���ϵ�� 0x811D2BA7
    0x00000000,          RegMTPARA0,    //0x183 CF����ʱ��3.2MHz ʹ��CF����������ۼӣ���Ǳ����������Դ��ƽ��ȫ���й�
    0,                   RegWARTU,     // U32  ��ѹ��Чֵ�Ȳ�У��ֵ //
    0,                   RegWARTI,     // U32  I1 ������Чֵ�Ȳ�У��ֵ//
};

/*********************************************************************************************************
** ��������: Save_EMU_AdjParam
** ��������: EMU��ز����޸ĺ�ı�����´���
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Save_EMU_AdjParam(void)
{
    gs_adj_emu_param.csck =Lib_get_csck_int16u_num((uint8 *)&gs_adj_emu_param.w1gain,(LEN_BLOCK70_EMU_PARAM_E2P-2),CHECKWORD);
    mem_db_write(ADR_BLOCK70_EMU_PARAM_E2P, (uint8 *)&gs_adj_emu_param.w1gain,(LEN_BLOCK70_EMU_PARAM_E2P-2),MEM_E2P1); 
}



/*********************************************************************************************************
** ��������: Save_EMU_AdjParam
** ��������: EMU��ز����޸ĺ�ı�����´���
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Get_EMU_AdjParam(void)
{
   uint16  csck_u16;

    //RAM ���ݼ��  //
    csck_u16 =Lib_get_csck_int16u_num((uint8 *)&gs_adj_emu_param.w1gain,(LEN_BLOCK70_EMU_PARAM_E2P-2),CHECKWORD);
    if(csck_u16 != gs_adj_emu_param.csck)
    {
        mem_read((uint8 *)&gs_adj_emu_param.w1gain, ADR_BLOCK70_EMU_PARAM_E2P, LEN_BLOCK70_EMU_PARAM_E2P, MEM_E2P1);
    }
}


/*********************************************************************************************************
** ��������: Check_EMU_AdjParam
** ��������: EMU�Ĵ���У��
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Check_EMU_AdjParam(void)
{
   ST_U32_U08 regval;
   uint8 i;
   EMU_CK_TAB tmp_tab;
   EMU_CONST_CK_TAB  tmp_const_tab;
   uint32 ucSum=0;
   uint8  u8_tmp;

    // ���RAM�ڵ�У��������ݣ����У�鲻��ȷ���EEPROM�ڻ�ȡ //
    Get_EMU_AdjParam();   

	///����������Ƶ��־���Ա������ȷ������ֵ yang 2017-12-28///
	mem_read(&u8_tmp, ADR_METER_PARAM1_CONST_FAST_FLG, 1, MEM_E2P1); 	
	if(u8_tmp==0x3C)
	{
			  //��Ƶ10��  //
		SetMeterCfgACK(INITGATEP_10M,GATEP);		//����I1ͨ������������
		SetMeterCfgACK(INITGATEP_10M,GATEQ);		//����I2ͨ������������ 				
	}
	else
	{
		SetMeterCfgACK(INITGATEP,GATEP);		//����I1ͨ������������
		SetMeterCfgACK(INITGATEP,GATEQ);		//����I2ͨ������������ 
	}


    // �̶�ֵ���õ�У��������ݼ�� //    
    for(i=0;i<(dim(cst_emu_constchck_tab));i++)
    {
        tmp_const_tab.emuAdr = cst_emu_constchck_tab[i].emuAdr;
        tmp_const_tab.val = cst_emu_constchck_tab[i].val;
        regval.u32 = 0;
        regval.u32 = ReadMeterParaACK(tmp_const_tab.emuAdr);     //��������ֵ���  //
        if(regval.u32 != tmp_const_tab.val)
        {
            regval.u32 = tmp_const_tab.val;
            SetMeterCfgACK(regval.u32,tmp_const_tab.emuAdr);
        }  
    }
    // ��ȡ�洢оƬ�ڵ�У�����ݽ��м�� //
    for(i=0;i<(dim(cst_emu_selfchck_tab));i++)
    {
        tmp_tab.emuAdr = cst_emu_selfchck_tab[i].emuAdr;
        tmp_tab.ramAdr = cst_emu_selfchck_tab[i].ramAdr;
        regval.u32 = 0;
        regval.u32= ReadMeterParaACK(tmp_tab.emuAdr);
        if((tmp_tab.emuAdr==PHCCtrl1)||(tmp_tab.emuAdr==PHCCtrl2))
        {
            if(regval.B08[3] != (uint8)(*tmp_tab.ramAdr))
            {
                regval.u32 = (uint8)(*tmp_tab.ramAdr);
                SetMeterCfgACK(regval.u32,tmp_tab.emuAdr);
            }      
        }
        else
        {
            if(regval.u32 != *tmp_tab.ramAdr)
            {
                regval.u32 = *tmp_tab.ramAdr;
                SetMeterCfgACK(regval.u32,tmp_tab.emuAdr);
            }
        }    
     }

}

/*********************************************************************************************************
** ��������: Get_Original_Power
** ��������: ��ȡԭʼ����ֵ
** ��ڲ���: avr_times-ƽ������ 
** ���ڲ���: ��		
********************************************************************************************************/
uint32 Get_Original_Power(uint8 avr_times,uint8 ch)
{
    uint32 val;
    uint8  i;
    uint32 aery_old;
    uint32 aery_val;
    uint32 avr_aery;
    ST_U32_U08 TempValue;
    CLRWDT();

    avr_aery=0;
    gs_emu_adj_var.sec_flg=FALSE; 
    for (i=0;i<avr_times;i++)
    {
        CLRWDT();
        while(gs_emu_adj_var.sec_flg==FALSE);
        gs_emu_adj_var.sec_flg=FALSE; 
        CLRWDT(); 
        if(ch==EMU_CH_L)
        {
            val=ReadMeterParaACK(DATAIQ);	  //DATAP 2017-1-12 ZWK
        }
        else
        {
           // val=ReadMeterParaACK(DATAIQ);  // RegIAP ȫ������˲ʱֵ
	   if(ReadRaccoon(RegIAP,1,BPhy)==TRUE)   //RegAAP 2017-1-12 ZWK   // ��� 200ms��ȡ�ȴ�    //  ����ʱ��76ms
	   {
		memcpy((uint8*)TempValue.B08,gs_RacCtrl.ucBuf+3,4); //�й���ƽ������
		Lib_Rev_Copy_Arry(&TempValue.B08[0],4);// ���ֽ���ǰ  ����//
		val = TempValue.u32;
	   }
	   else // ��ȡʧ�ܣ� 
	   {
		gs_sys_run.font_fg |= BIT4_FONT_FG_EnyBottom;
	   }
        }

       if(val>=0x80000000)
       {
          val=~val+1;  
       }

       aery_old=val;
       avr_aery=avr_aery+aery_old;
    }   

    aery_val=avr_aery/avr_times;
    CLRWDT();
    NOP();
    return(aery_val);
}	 	



/*********************************************************************************************************
** ��������: Get_Original_Irms
** ��������: ��ȡԭʼ������Чֵ����
** ��ڲ���: avr_times-ƽ������ 
** ���ڲ���: ��		
********************************************************************************************************/
uint32 Get_Original_Irms(uint8 avr_times,uint8 ch)
{
    uint32 val;
    uint8  i;
    uint32 aery_old;
    uint32 aery_val;
    uint32 avr_aery;
    ST_U32_U08 TempValue;
    CLRWDT();

    avr_aery=0;
    gs_emu_adj_var.sec_flg=FALSE; 
    for (i=0;i<avr_times;i++)
    {
        CLRWDT();
        while(gs_emu_adj_var.sec_flg==FALSE);
        gs_emu_adj_var.sec_flg=FALSE; 
        CLRWDT(); 
        if(ch==EMU_CH_L)
        {
            val=ReadMeterParaACK(RMSII1);	 
        }
        else
        {
           // val=ReadMeterParaACK(DATAIQ); //RegIAP ȫ������˲ʱֵ
	   if(ReadRaccoon(RegARTI,1,BPhy)==TRUE)     // ��� 200ms��ȡ�ȴ�    //  ����ʱ��15ms
	   {
		memcpy((uint8*)TempValue.B08,gs_RacCtrl.ucBuf+3,4); //�й���ƽ������
		Lib_Rev_Copy_Arry(&TempValue.B08[0],4);// ���ֽ���ǰ  ����//
	       val = TempValue.u32;
	   }
	   else // ��ȡʧ�ܣ� ���¶�ȡһ��// 
	   {
		gs_sys_run.font_fg |= BIT4_FONT_FG_EnyBottom;
	   }
        }

       if(val>=0x80000000)
       {
          val=~val+1;  
       }

       aery_old=val;
       avr_aery=avr_aery+aery_old;
    }   

    aery_val=avr_aery/avr_times;
    CLRWDT();
    NOP();
    return(aery_val);
}	 


/*=========================================================================================\n
* @function_name: CalculateSC
* @function_file: EnergyBottom.c
* @����: �Ȳ���㹫ʽ
* 
* 
* @����: 
* @param:CurValue  :����й�����ֵ
* @param:TarValue  :��׼���й�����ֵ
* 
* @����: 
* @return: uint32 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
INT32U CalculateSC(INT32U CurValue,INT32U TarValue)
{
    //  2016-5-20  mj //                
    INT32S s32_tmp0;
    double f_CurValue,f_TarValue,f_Error;
    double f_s32_tmp0,f_s32_tmp1,f_s32_tmp2,f_s32_tmp3;

    // ��ȡ��ǰ���  ((CurValue-TarValue)/TarValue )*100% //    
    f_CurValue = (double)CurValue;
    f_TarValue = (double)TarValue;
    f_Error = (f_CurValue-TarValue)*1.0/f_TarValue;

	f_s32_tmp0 = 1.0/(1+f_Error);

	f_s32_tmp1 = f_s32_tmp0 - 1.0;
	
	f_s32_tmp2 = f_s32_tmp1* 0x80000000;
	
	f_s32_tmp3 = floor(f_s32_tmp2);     // ����ȡ�� //
	s32_tmp0 = (INT32S)f_s32_tmp3;	
	return (s32_tmp0);
}

/*=========================================================================================\n
* @function_name: CalculateAC
* @function_file: EnergyBottom.c
* @����: �ǲ���㹫ʽ
* 
* 
* @����: 
* @param:CurValue   ������� 
* @param:TarValue   ����׼����
* 
* @����: 
* @return: uint8    
* @����:   lwb (2012-06-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
INT8U CalculateAC(INT32U CurValue,INT32U TarValue)
{
    //���㹫ʽ����,���ı�2011��7��14��//
    INT16U Error;                    
    INT8U Result;
	INT8U JCFH;
	
	JCFH = 0;
	if(TarValue < 50)   return 0;
	
	if(TarValue>CurValue)  
	{
		// ����� //
		Error=(TarValue-CurValue)*1000/TarValue;            //�������ֵ��������1000
		JCFH = 1;
	}
	else
	{
		// ����� //
		Error=(CurValue-TarValue)*1000/TarValue;            //�������ֵ��������1000
	}
    Result = (INT32U)3011*Error/2000;
	if(JCFH==1)
	{
		Result|=BIT7;
	}
    return Result; 
}

/*********************************************************************************************************
** ��������: SoftAdjust_IB_Process
** ��������: У׼����
** ��ڲ���: jzval�����۹���ֵ�����峣��/3600*��̨�������/1000*ICONT*8388608 �磺1200/3600/220*10/1000*96*8388608=576716
**           channel: ����ͨ�� 0-ͨ��1 1-ͨ��2       
** ���ڲ���: ��	
********************************************************************************************************/
void SoftAdjust_IB_Process(uint32 jzval,uint8 channel)
{
   uint32 val;
   uint32 adjust_wcval;

    CLRWDT();
    if(channel==EMU_CH_L)
    {
        val=0;
        SetMeterCfgACK(val,SCQ);  //У����������
        SetMeterCfgACK(val,PARAQC);   
    }
    else
    {
        val=0;
        WriteRaccoon(val,RegWAPT, BPhy);  //У����������
        //SetMeterCfgACK(val,PARAQC);   
       WriteRaccoon(val,RegWWAPT, BPhy);  // �ǲ�  
    }
   adjust_wcval=Get_Original_Power(2,channel); 
   val = CalculateSC(adjust_wcval,jzval);
   
    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.w2gain=val;      
    }
    else
    {
        gs_adj_emu_param.w1gain=val;      
    }
}	

/*********************************************************************************************************
** ��������: SoftAdjust_IB5_Process
** ��������: У׼С����
** ��ڲ���: jzval�����۹���ֵ ���峣��/3600*��̨�������/1000*ICONT*8388608 �磺1200/3600/220*0.5/1000*96*8388608=28835
**           channle:����ͨ���� 0-ͨ��1  1-ͨ��2
** ���ڲ���: ��	
********************************************************************************************************/
void SoftAdjust_IB5_Process(uint32 jzval,uint8 channel)
{
   bit Flag_fu=0;   //���ű�־	

   uint32 val;		 
   uint32 adjust_wcval;
              

    CLRWDT();
    val=0;
    if(channel==EMU_CH_L)
    {
        SetMeterCfgACK(val,PARAQC);   
    }
    else
    {
        //SetMeterCfgACK(val,PARAQC);   
       WriteRaccoon(val,RegWWAPT, BPhy);  //���β���
    }
   adjust_wcval=Get_Original_Power(3,channel); 
   val = CalculateAC(adjust_wcval,jzval);

    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.watt2os=val;      
    }
    else
    {
        gs_adj_emu_param.watt1os=val;      
    }

}
			
/*********************************************************************************************************
** ��������: SoftAdjust_Phase_Process
** ��������: ����У׼��λ
** ��ڲ���: jzval�����۹���ֵ ���峣��/3600*��̨�������/1000*ICONT*8388608 �磺1200/3600/220*5/1000*96*8388608=288358
**           channel��ͨ����
** ���ڲ���: ��	
********************************************************************************************************/
void SoftAdjust_Phase_Process(uint32 jzval,uint8 channel)
{   
   uint32 val;		 
   uint32 adjust_wcval;
  
           

    CLRWDT();
    val=0;
    if(channel==EMU_CH_L)
    {
        SetMeterCfgACK(val,PHCCtrl2);   
    }
    else
    {
         WriteRaccoon(0x000B00A9 ,RegMTPARA1, BPhy);  // �ǲ�  
    }
    CLRWDT();

    gs_emu_adj_var.sec_flg=FALSE;
    while(gs_emu_adj_var.sec_flg==FALSE);              //��ʱ1�� �ȴ������ȶ�
    gs_emu_adj_var.sec_flg=FALSE; 

   adjust_wcval=Get_Original_Power(2,channel); 
   val = CalculateAC(adjust_wcval,jzval);
   
    CLRWDT(); 
    if(channel==EMU_CH_L)
    {
        gs_adj_emu_param.p2cal=val;      
    }
    else  //   
    {
	 if(val&BIT7)  //��ֵ
	 {
	  val&=~0x00000080;
	  val = (val*1.1f);
	  val =(val<<8);
	  val|=(0x00040000);  //bit18λ д��1 ��ʱ��ѹ
	 }
	 else
	 {
	  val = (val*1.1f);
	  val =(val<<8);
	  val&=(~0x00040000);//  ȡ������λ
	 }
	 gs_adj_emu_param.p2cal = 0x000B00A9;
	 gs_adj_emu_param.p2cal |=val;
    }

}
      
/*********************************************************************************************************
** ��������: SoftAdjust_dlxProcess	
** ��������: У׼������У׼
** ��ڲ���: jzval�����۹���ֵ ���峣��/3600*��̨�������/1000*ICONT*8388608 �磺1200/3600/220*5/1000*96*8388608=288358
**           channel��ͨ����
** ���ڲ���: ��	
********************************************************************************************************/
//void SoftAdjust_dlxProcess(uint32 jzval,uint8 channel)
//{
//    uint32 xdata adjust_wcval;

//    CLRWDT();
//    Init_EMU(DLX_MODE);
//    gs_emu_adj_var.sec_flg=FALSE;
//    while(gs_emu_adj_var.sec_flg==FALSE);              //��ʱ1�� �ȴ������ȶ�
//    gs_emu_adj_var.sec_flg=FALSE; 
//    CLRWDT();

//    gs_emu_adj_var.sec_flg=FALSE;
//    while(gs_emu_adj_var.sec_flg==FALSE);              //��ʱ1�� �ȴ������ȶ�
//    gs_emu_adj_var.sec_flg=FALSE;    
//    CLRWDT();

//    if(channel==EMU_CH_L)
//    {
//        //Dis_Adjust(7);		
//        adjust_wcval=Get_Original_Irms(3,EMU_CH_L);		//��ȡAͨ��ʵ�� ������Чֵ���� //
//       gs_adj_emu_param.vconst_val_ch1 =((float) jzval)/((float) adjust_wcval);   //��ȡAͨ���ĳ�������ϵ�� //
//    }
//    else
//    {
//        //Dis_Adjust(8);
//        adjust_wcval=Get_Original_Irms(3,EMU_CH_N);   //��ȡBͨ��ʵ�� ������Чֵ���� //
//        gs_adj_emu_param.vconst_val_ch2 =((float) jzval)/((float) adjust_wcval);   //��ȡBͨ���ĳ�������ϵ�� //
//    }

//    CLRWDT();
//    Init_EMU(NORMAL_MODE);
//    Save_EMU_AdjParam();
//    Check_EMU_AdjParam();
//    NOP();
//    NOP();
//}


//�޹�����
uint32 CalculateSChz(int16 error,int32 LastSC)
{
    //���㹫ʽ����,���ı�2011��7��14��
    int16 Error;                    
    uint16 Stemp0remd,Stemp2remd;  
    int32 Stemp0,Stemp1,Stemp2,Stemp3;//
    uint32 Result;
    //��ʽ˵�� ������ʽ S=2^31(1/(1+e)-1)+S1(1/(1+e)),���e����1000����
    //���⹫ʽ��:  S=  2^31(-e/(1000+e))+S1(1000/(1000+e)=S1(1000/(1000+e)-2^31(e/(1000+e))
    //�������  2^31(e/(1000+e))
    Error=error;                                                               //�������ֵ��������1000
    Stemp0=0x80000000/(1000+Error);                     //�ȱ����������� 2^31/(1000+e)=0x80000000/(1000+e)
    Stemp0remd=0x80000000%(1000+Error);                 //��������
    Stemp0remd=Stemp0remd*1000/(1000+Error);            //����С�����֣�С����������1000
    Stemp1=Stemp0*Error+(Stemp0remd*Error)/1000;        //�Ѽ����������С�����ֶ�����ERROR����2^31(e/(1000+e))
    //�������S1*(1000/(1000+e)
    Stemp2=LastSC/(1000+Error);                         //������������
    Stemp2remd=LastSC%(1000+Error);                     //������������
    Stemp2remd=Stemp2remd*1000/(1000+Error);            //С������
    Stemp3=Stemp2*1000+Stemp2remd;                      //�������ּ�С������  

    Result=Stemp3-Stemp1;                               //S=S1(1000/(1000+e)-2^31(e/(1000+e))
    return Result;
 
}
void TimeEventProc(void)
{
    static uint32 temp=0;
    uint16 HZ;
	
	HZ = 8192000/ReadMeterParaACK(0x10fd);
	if(temp != HZ) 
	{
	    temp = HZ;
	    if(HZ > 500)
	    {
	        gs_adj_emu_param.w2gain = CalculateSChz((HZ -500)*2,gs_adj_emu_param.w1gain);  //ÿ��0.1hz��0.2%
	        SetMeterCfgACK(gs_adj_emu_param.w2gain,SCQ);     
	    }
	    else if(HZ < 500)
	    {
	        gs_adj_emu_param.w2gain = CalculateSChz(-(500 -HZ)*2,gs_adj_emu_param.w1gain);
	        SetMeterCfgACK(gs_adj_emu_param.w2gain,SCQ); 
	    }
	    else
	    {
	        SetMeterCfgACK(gs_adj_emu_param.w1gain,SCQ); 
	        gs_adj_emu_param.w2gain = gs_adj_emu_param.w1gain;
	    }
	}

}
/*********************************************************************************************************
** ��������: Hardware_AdjustDiv_Sub
** ��������: Ӳ���̽� У׼�����ж�
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
void Hardware_AdjustDiv_Sub(void)
{
   uint8 i;
    uint32 val;
   uint32 tmpval;
   uint32 tmpval1=0;	 
   uint32 jzwcval;
   uint8 ajust1_type; // A·У����
    uint8 ajust2_type;// B·У����
    uint32 cmp_val[4];//  У��㹦����ֵ
   uint32 adjust1_wcval;  // A ·У����
//   uint32 adjust2_wcval;  // B·У����
   ST_U32_U08 TempValue;

    if(EA==0)  return;

    //  ׼���׶�  ����ȡ����ֵ���жϽ�����һ����У��//
    gs_emu_adj_var.adj_flg =0x55;   // =0X55 ��ʶĿǰ����У��״̬ //

    jzwcval=cst_adj_const.C_PCONST;     // ����ʵ�Ĺ���У׼��������//
    cmp_val[0]=jzwcval*25/10;         //250% IB ����У����������Ĭ��ֵ��ʼ�� //
    cmp_val[1]=jzwcval*70/100;       // ������У׼ //
    cmp_val[2]=jzwcval*35/100;       // �ǲ�У׼ //
    cmp_val[3]=jzwcval*3/100;         // С�ź�У׼ //

    CLRWDT(); 	

// A·׼�� 	 
    adjust1_wcval=Get_Original_Power(4,EMU_CH_L);	 //��ȡʵ�ʹ���
    if(adjust1_wcval>cmp_val[0])
    {
        ajust1_type=HARD_EADJ_STEP0_L_INITLIZE;//IB 1.0 ch0;
    }
    else if(adjust1_wcval>cmp_val[1])
    {
        ajust1_type=HARD_EADJ_STEP1_L_100IB_100L;//IB 1.0 ch0;
    }
    else if(adjust1_wcval>cmp_val[2])
    {
        ajust1_type=HARD_EADJ_STEP2_L_100IB_50L;//IB 0.5 ch0;   
    }   
    else if(adjust1_wcval>cmp_val[3])
    {
        ajust1_type=HARD_EADJ_STEP3_L_5IB_100L;//5%IB 1.0 ch0;   
    }
    else 
    {
        ajust1_type=HARD_EADJ_STEP8_METER_CLR;//5%IB 1.0 ch0;   
	}

	
 // B·״̬//
   /*    adjust2_wcval = Get_Original_Power(4,EMU_CH_N);

        if(adjust2_wcval>cmp_val[0])
        {
            ajust2_type=HARD_EADJ_STEP4_N_INITLIZE;//IB 1.0 ch0;
        }
        else if(adjust2_wcval>cmp_val[1])
        {
            ajust2_type=HARD_EADJ_STEP5_N_100IB_100L;//IB 1.0 ch1;
        }
        else if(adjust2_wcval>cmp_val[2])
        {
            ajust2_type=HARD_EADJ_STEP6_N_100IB_50L;//IB 0.5 ch1;     
        }   
        else if(adjust2_wcval>cmp_val[3])
        {
            ajust2_type=HARD_EADJ_STEP7_N_5IB_100L;//5%IB 1.0 ch1;   
        }
        else
        {
            ajust2_type=HARD_EADJ_STEP8_METER_CLR;// �������  //   
        }

*/
    //   �ֲ���У׼����   //
  // A·//
    //  HARD_EADJ_STEP0_L_INITLIZE   L��·�Ȳ�Ĵ�����ʼ��//
    if(ajust1_type==HARD_EADJ_STEP0_L_INITLIZE)
    {                      
        gs_adj_emu_param.w2gain = 0;   //��ʼ��L1ͨ���Ȳ�Ĵ���  //
        gs_adj_emu_param.p2cal = 0;   //��ʼ��L1ͨ���Ȳ�Ĵ���  //
		api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_0);   // Һ����ʾ //
    }

    //  HARD_EADJ_STEP1_L_100IB_100L   L��·100%Ib, 1.0L У׼//
    if(ajust1_type==HARD_EADJ_STEP1_L_100IB_100L)
    {                      
        // L��·�й�����У׼ // 
        SoftAdjust_IB_Process(jzwcval,EMU_CH_L); 

        // L��·������Чֵ����У׼ //  	
        tmpval=0;
        for(i=0;i<8;i++)
        {
            Lib_Delay_ms(30);
            val = ReadMeterParaACK(RMSII2); // 2017-1-12 ZWK
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();          
        }
        tmpval=tmpval/8;
        //������Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.I_ref�ͻ������������ı���//
        gs_adj_emu_param.i2rms_xs=(float)cst_adj_const.I_ref/(float)tmpval;  
        //��ѹ��Чֵ����У׼ //             		
        tmpval=0;
        for(i=0;i<8;i++)
        {
            Lib_Delay_ms(30);
            val = ReadMeterParaACK(RMSIU); // �޸�Ϊ����ƽ��ֵ
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();        
        }
          tmpval=tmpval/8;      
        //��ѹ��Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.U_ref�ͻ�����ѹ�����ı���//
        gs_adj_emu_param.vrms_xs=(float)cst_adj_const.U_ref/(float)tmpval;  
	    api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_1);   // Һ����ʾ //

	CLRWDT();
    }

    //  HARD_EADJ_STEP2_L_100IB_50L   L��·100%Ib, 0.5L У׼//
    if(ajust1_type==HARD_EADJ_STEP2_L_100IB_50L)
    {                            
        jzwcval=jzwcval/2;
        SoftAdjust_Phase_Process(jzwcval,EMU_CH_L);  
	api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_2);   // Һ����ʾ //

    }
    //  HARD_EADJ_STEP3_L_5IB_100L   L��·5%Ib, 1.0L У׼//
    if(ajust1_type==HARD_EADJ_STEP3_L_5IB_100L)
    {                            
        jzwcval=jzwcval/20;
        SoftAdjust_IB5_Process(jzwcval,EMU_CH_L);   
	api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_3);   // Һ����ʾ //

    }


// 9260FУ�����//

    //  HARD_EADJ_STEP4_N_INITLIZE   N��·�Ȳ�Ĵ�����ʼ��//
    if(ajust2_type==HARD_EADJ_STEP4_N_INITLIZE)
    {                      
        gs_adj_emu_param.w2gain = 0;   //��ʼ��L1ͨ���Ȳ�Ĵ���  //
        gs_adj_emu_param.p2cal= 0x000B00A9;   //��ʼ��L1ͨ���Ȳ�Ĵ���  //
	    api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_0);   // Һ����ʾ //
    }

    //  HARD_EADJ_STEP4_N_100IB_100L   N��·100%Ib, 1.0L У׼//
    if(ajust2_type==HARD_EADJ_STEP5_N_100IB_100L)
    {              
        // L��·�й�����У׼ // 
        SoftAdjust_IB_Process(REF_RMSPn_9260,EMU_CH_N);
        tmpval=0;
        for(i=0;i<8;i++)
        {
	   if(ReadRaccoon(RegARTI,1,BPhy)==TRUE)    // �޸�Ϊ����ƽ��ֵ  // ��� 200ms��ȡ�ȴ�    //  ����ʱ��76msRegWARTI
	   {
		memcpy((uint8*)TempValue.B08,gs_RacCtrl.ucBuf+3,4); //�й���ƽ������
		Lib_Rev_Copy_Arry(&TempValue.B08[0],4);// ���ֽ���ǰ  ����//
		val = TempValue.u32;
	   }
	   else // ��ȡʧ�ܣ� ���¶�ȡһ��// 
	   {
		gs_sys_run.font_fg |= BIT4_FONT_FG_EnyBottom;
	   }
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();          
        }
        tmpval=tmpval/8;
        //������Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.I_ref�ͻ������������ı���//
        gs_adj_emu_param.i2rms_xs=(float)cst_adj_const.I_ref/(float)tmpval;  

        /// 2·��ѹ��Чֵ����У׼ //             		
        tmpval=0;
        for(i=0;i<8;i++)
        {
	   if(ReadRaccoon(RegARTU,1,BPhy)==TRUE)    // �޸�Ϊ����ƽ��ֵ  // ��� 200ms��ȡ�ȴ�    //  ����ʱ��76ms   RegWARTU
	   {
		memcpy((uint8*)TempValue.B08,gs_RacCtrl.ucBuf+3,4); //�й���ƽ������
		Lib_Rev_Copy_Arry(&TempValue.B08[0],4);// ���ֽ���ǰ  ����//
		val = TempValue.u32;
	   }
	   else // ��ȡʧ�ܣ� ���¶�ȡһ��// 
	   {
		gs_sys_run.font_fg |= BIT4_FONT_FG_EnyBottom;
	   }
            if(val>=0x80000000)
            {
                val=~val+1;  
            } 		  		
            tmpval=tmpval+val;
            CLRWDT();        
        }
        tmpval=tmpval/8;      
        //��ѹ��Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.U_ref�ͻ�����ѹ�����ı���//
        gs_adj_emu_param.vrms_xs=(float)cst_adj_const.U_ref/(float)tmpval;  
	    api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_1);   // Һ����ʾ //
    }

    if(ajust2_type==HARD_EADJ_STEP6_N_100IB_50L)
    {                      
        jzwcval=jzwcval/2;
        SoftAdjust_Phase_Process(jzwcval,EMU_CH_N);  
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_2);   // Һ����ʾ //		
    }    
    //  HARD_EADJ_STEP7_N_5IB_100L   N��·5%Ib, 1.0L У׼//
    if(ajust2_type==HARD_EADJ_STEP7_N_5IB_100L)
    {                         
        jzwcval=jzwcval/20;
        SoftAdjust_IB5_Process(jzwcval,EMU_CH_N);   
        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_3);   // Һ����ʾ //   
    }

    if((ajust2_type==HARD_EADJ_STEP8_METER_CLR)&&(ajust1_type==HARD_EADJ_STEP8_METER_CLR))
    {        
        api_clr_current_energy_data(); // ��������//
        CLRWDT();
	 //   api_clr_current_MD_data(); //��ǰ��������
        CLRWDT();

#if (BILL_MAX_NUM>0)
	    api_clr_bill_data();
#endif
	    gs_uart_iec_app_var[g_ch_comm].delay_10ms = 0; // 
        CLRWDT();
	    //api_deal_even_class_recode(ID_CLASS_I_resetMD,START);
	    api_chg_LCDDisplay_adj_item(DIS_DATA_CLR);   // Һ����ʾ //
    }

    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    CLRWDT();
    gs_emu_adj_var.adj_flg =0;   // =0X0 ��ʶĿǰ�˳�У��״̬ //	

}
//////////////����Ϊ�������У׼���� yang 2017-12-26/////////////////
//-------------------------------------------------------------------------------//
//  Function:      Measure_Electric_Parameter_Per_Sec(void)      
//  Description: �ϱ��������Gain//
//  Parameters:   ��  
//  Returns:        ��                          
//  Others:   xxx.xxV   xx.xxx A  xxxx.x W     
//-------------------------------------------------------------------------------//
void Measure_Electric_Err_Gain(INT8U *sptr)
{   
	union Union_DWordDef u32_tmp_U,u32_tmp_A,u32_tmp_P,u32_tmp;

	 char errbuf[7];
	 float Err_Data;	
	///Voltage///
	u32_tmp.BYTE[0]=0;	
	u32_tmp.BYTE[1]=Lib_AtoB(*(sptr+13));
	u32_tmp.BYTE[2]=((Lib_AtoB(*(sptr+14)))<<4) + Lib_AtoB(*(sptr+15));
	u32_tmp.BYTE[3]=((Lib_AtoB(*(sptr+17)))<<4) + Lib_AtoB(*(sptr+18));
	u32_tmp_U.UDWORD = Lib_bcd4_long(&u32_tmp.BYTE[0]);
	///Current///
	u32_tmp.BYTE[0]=0;	
	u32_tmp.BYTE[1]=Lib_AtoB(*(sptr+19));
	u32_tmp.BYTE[2]=((Lib_AtoB(*(sptr+20)))<<4) + Lib_AtoB(*(sptr+22));
	u32_tmp.BYTE[3]=((Lib_AtoB(*(sptr+23)))<<4) + Lib_AtoB(*(sptr+24));
	u32_tmp_A.UDWORD = Lib_bcd4_long(&u32_tmp.BYTE[0]);
	///Active Power///
	u32_tmp.BYTE[0]=0;	
	u32_tmp.BYTE[1]=Lib_AtoB(*(sptr+25));
	u32_tmp.BYTE[2]=((Lib_AtoB(*(sptr+26)))<<4) + Lib_AtoB(*(sptr+27));
	u32_tmp.BYTE[3]=((Lib_AtoB(*(sptr+28)))<<4) + Lib_AtoB(*(sptr+30));
	u32_tmp_P.UDWORD = Lib_bcd4_long(&u32_tmp.BYTE[0]);

	//���ת��//
	Lib_Copy_Str_TwoArry( &errbuf[0], sptr+13+6+6+6,6);
	errbuf[6] = '\0';
	Err_Data = atof(&errbuf[0]);   // asc ת float  //

	switch(comm_data.di1_di0.u32)//(comm_data.di1_di0.UDWORD)
	{
		case  0x0000FEB0:
		case  0x0000FEB3:
			Calibration_Power(Err_Data);	
			CLRWDT();
			Calibration_Current(u32_tmp_A.UDWORD,u32_tmp_U.UDWORD);
			break;
		case  0x0000FEB1:
		case  0x0000FEB4:
			Calibration_Angular(Err_Data);
			break;
		case  0x0000FEB2:
		case  0x0000FEB5:
			Calibration_small_signal(Err_Data);
			break;
		default :
			return;
	}
    Save_EMU_AdjParam();
    Check_EMU_AdjParam();
    CLRWDT();
}
//***************************************************************************
// ����:   ͨѶ�е��õ�У׼���������Ȳ�ĺ�����1·��2·�Զ��жϣ�
// ���룺 POWER����ʽ0.1W,16����
// �м�����u32PMdatal��Ϊ�Ȳ�У׼�Ĳ������
//***************************************************************************
void Calibration_Power(float f_err_data)
{
//	 INT8U  offset;
	 INT32U u32_tmp;
	 INT32U u32_PMdataltemp;

//	 static uint32 temp=0;
//	 uint16 HZ;
   	CLRWDT();

    if(f_err_data>0)
    {
        u32_tmp = 100000*(100+f_err_data) ;   
    }
    else
    {
        u32_tmp = 100000*(100+f_err_data) ;  //-
    }
#if meter_type == D_1P3W

	if(comm_data.di1_di0.u32 == 0x0000FEB3)    // DI03B  IA��ΪN��·
	{

		u32_PMdataltemp=ReadMeterParaACK(SCP);  
		u32_PMdataltemp=CalculateSC(u32_tmp,10000000);  
		SetMeterCfgACK(u32_PMdataltemp,SCP);
        gs_adj_emu_param.w1gain=u32_PMdataltemp;      
	}
	else if(comm_data.di1_di0.u32 == 0x0000FEB0)  // DI03B  IB��Ϊ����·  //
	{
		u32_PMdataltemp=ReadMeterParaACK(SCQ);
		u32_PMdataltemp=CalculateSC(u32_tmp,10000000);  
		SetMeterCfgACK(u32_PMdataltemp,SCQ);
        gs_adj_emu_param.w2gain=u32_PMdataltemp;      
	}
#endif

#if meter_type == D_1P2W
	if(comm_data.di1_di0.u32 == 0x0000FEB0)    // DI03B  IA��ΪN��·
	{

		u32_PMdataltemp=ReadMeterParaACK(SCP);  
		u32_PMdataltemp=CalculateSC(u32_tmp,10000000);  
		SetMeterCfgACK(u32_PMdataltemp,SCP);
        gs_adj_emu_param.w1gain=u32_PMdataltemp;
		     
	}

#endif
}


//***************************************************************************
// ����:   ͨѶ�е��õ�У׼��ѹ�����ĺ�����1·��2·�Զ��жϣ�
// ���룺 Current����ʽ0.001A,16����
//        Voltage, ��ʽ0.01V,16����
// �м�����u32PMdatal��Ϊ�Ȳ�У׼�Ĳ������
//***************************************************************************
void  Calibration_Current(INT32U Current,INT32U Voltage)
{
	 INT32U u32_tmp,u32_PMdataltemp,u32_PMdataltempSII1;
  
	if(comm_data.di1_di0.u32 == 0x0000FEB0)    // DI03B  IA��ΪN��·  //0x0000FEB3 <-> 0x0000FEB0
	{
		// ����У׼ //
	    u32_tmp = ReadMeterParaACK(RMSI1);
	   	u32_tmp *= gs_adj_emu_param.i1rms_xs;//��ȡ������ʾֵ yang 2017-12-28
		u32_PMdataltemp = ReadMeterParaACK(SCI1);
		if(u32_PMdataltemp == 0)
		{
			//δУ׼����Ҫ����У׼ //
		  	u32_PMdataltemp =CalculateSC(u32_tmp,Current);	
			gs_adj_emu_param.irms1os=u32_PMdataltemp;
		}

		// ��ѹУ׼ //
		u32_tmp = ReadMeterParaACK(RMSU);
	   	u32_tmp *= (gs_adj_emu_param.vrms_xs*10);//��ȡ��ѹ��ʾֵ yang 2017-12-28
		u32_PMdataltemp =ReadMeterParaACK(SCU);
		if(u32_PMdataltemp == 0) 
		{
			//δУ׼����Ҫ����У׼ //
			u32_PMdataltemp=CalculateSC(u32_tmp,Voltage);
			gs_adj_emu_param.urmsos=u32_PMdataltemp;
			SetMeterCfgACK(u32_PMdataltemp,SCU);
		}
	}
	else if(comm_data.di1_di0.u32 == 0x0000FEB3)  // DI03B  IB��Ϊ����·  //
	{
		// ����У׼ //
		u32_tmp = ReadMeterParaACK(RMSI2);
		u32_tmp*= gs_adj_emu_param.i2rms_xs;//��ȡ��������ʾֵ yang 2017-12-28
		u32_PMdataltemp = ReadMeterParaACK(SCI2);
		if(u32_PMdataltemp == 0)
		{
			//δУ׼����Ҫ����У׼ //
			u32_PMdataltemp =CalculateSC(u32_tmp,Current);	
			gs_adj_emu_param.irms2os=u32_PMdataltemp;
		}

		// ��ѹУ׼ //
		u32_tmp = ReadMeterParaACK(RMSU);
		u32_tmp *= (gs_adj_emu_param.vrms_xs*10);//��ȡ��ѹ��ʾֵ yang 2017-12-28
		u32_PMdataltemp =ReadMeterParaACK(SCU);
		if(u32_PMdataltemp == 0) 
		{
			//δУ׼����Ҫ����У׼ //
			u32_PMdataltemp=CalculateSC(u32_tmp,Voltage);
			gs_adj_emu_param.urmsos=u32_PMdataltemp;
			SetMeterCfgACK(u32_PMdataltemp,SCU);
		}
	}


	
}

//***************************************************************************
// ����:   ���������ǲ�У׼��1·��2·�Զ��жϣ�
// ���룺 POWER����ʽ0.1W,16����
// �м�����u32PMdatal��Ϊ�ǲ�У׼�Ĳ������
//***************************************************************************
void Calibration_Angular(float f_err_data)
{
	INT32U u32_tmp,u32_PMdataltemp;
//	INT8U  offset;
	union Union_DWordDef    PHCCTRL1_adj_val;	// I1 �ǲ���ڼĴ��� ʵ��Ϊ8λ  //
	union Union_DWordDef	PHCCTRL2_adj_val;	// I2 �ǲ���ڼĴ��� ʵ��Ϊ8λ  //
    if(f_err_data>0)
    {
        u32_tmp = 100000*(100+f_err_data) ;   
    }
    else
    {
        u32_tmp = 100000*(100+f_err_data) ;  //-
    }

    u32_PMdataltemp=(INT32U)CalculateAC(u32_tmp,10000000);	
#if meter_type == D_1P3W
	if(comm_data.di1_di0.u32 == 0x0000FEB4)    // DI03B  IA��ΪN��·  
	{
		/*u32_PMdataltemp =ReadMeterParaACK(DATAP);
		if (u32_PMdataltemp&0x80000000)
		{    
		u32_PMdataltemp = ~u32_PMdataltemp+1;
		} 
		u32_tmp= u32_PMdataltemp*10;
		u32_tmp /=K_RMSP;
		//offset=113;	// 2��·���˹���Ԥ����ֵ  //  0.6
		offset=0;
		*/
		gs_adj_emu_param.p1cal=u32_PMdataltemp;
		Lib_long_bcd4(&PHCCTRL1_adj_val.BYTE[0],u32_PMdataltemp);
		SetMeterCfgACK(PHCCTRL1_adj_val.BYTE[3],PHCCtrl1);  //����I1�ǲ�ֵ
	}
	else if(comm_data.di1_di0.u32 == 0x0000FEB1)   // DI03B  IB��Ϊ����·  //	
	{
		/*
		u32_PMdataltemp =ReadMeterParaACK(DATAQ);
		if (u32_PMdataltemp&0x80000000)
		{    
			u32_PMdataltemp = ~u32_PMdataltemp+1;
		} 
		u32_tmp= u32_PMdataltemp*10;
		u32_tmp /=K_RMSQ;
		u32_PMdataltemp=(INT32U)CalculateAC(u32_tmp,POWER);	
		*/
		gs_adj_emu_param.p2cal=u32_PMdataltemp;
		Lib_long_bcd4(&PHCCTRL2_adj_val.BYTE[0],u32_PMdataltemp);
		SetMeterCfgACK(PHCCTRL2_adj_val.BYTE[3],PHCCtrl2);  //����I2�ǲ�ֵ

	}
#endif
#if meter_type == D_1P2W
	if(comm_data.di1_di0.u32 == 0x0000FEB1)    // DI03B  IA��ΪN��·  
	{
		gs_adj_emu_param.p1cal=u32_PMdataltemp;
		Lib_long_bcd4(&PHCCTRL1_adj_val.BYTE[0],u32_PMdataltemp);
		SetMeterCfgACK(PHCCTRL1_adj_val.BYTE[3],PHCCtrl1);  //����I1�ǲ�ֵ
	}
	else if(comm_data.di1_di0.u32 == 0x0000FEB4)   // DI03B  IB��Ϊ����·  //	
	{
		gs_adj_emu_param.p2cal=u32_PMdataltemp;
		Lib_long_bcd4(&PHCCTRL2_adj_val.BYTE[0],u32_PMdataltemp);
		SetMeterCfgACK(PHCCTRL2_adj_val.BYTE[3],PHCCtrl2);  //����I2�ǲ�ֵ

	}
#endif

}

//***************************************************************************
// ����:   С�źŲ�������
// ���룺 POWER����ʽ0.1W,16����
// �м�����
//***************************************************************************
void Calibration_small_signal(float f_err_data)
{
	 INT32U u32_PMdataltemp;
	 INT8U  offset;
	 INT32S s32_tmp,s32_PMdataltemp;

#if meter_type == D_1P3W
	if(comm_data.di1_di0.u32 == 0x0000FEB5)          // DI03B  IA��ΪN��·  
	{
		s32_PMdataltemp=ReadMeterParaACK(DATAP);
	
		s32_tmp = (INT32S)((float)f_err_data *s32_PMdataltemp/100.0);

		offset=0;    //2��·���˹���Ԥ����ֵ  //
		if(s32_tmp>0) u32_PMdataltemp = s32_tmp;
		else	u32_PMdataltemp = 	0xFFFFFFFF +s32_tmp;
		

		SetMeterCfgACK(u32_PMdataltemp,PARAPC);
        gs_adj_emu_param.watt1os=u32_PMdataltemp;      
	}

	else if(comm_data.di1_di0.u32 == 0x0000FEB2) 	// DI03B  IB��Ϊ����·  //
	{
		s32_PMdataltemp=ReadMeterParaACK(DATAQ);
	
		s32_tmp = (INT32S)((float)f_err_data *s32_PMdataltemp/100.0);

		offset=0;    //2��·���˹���Ԥ����ֵ  //
		if(s32_tmp>0) u32_PMdataltemp = s32_tmp;
		else	u32_PMdataltemp = 	0xFFFFFFFF +s32_tmp;
		

		SetMeterCfgACK(u32_PMdataltemp,PARAQC);
        gs_adj_emu_param.watt2os=u32_PMdataltemp;      
	}
#endif
#if meter_type == D_1P2W
	if(comm_data.di1_di0.u32 == 0x0000FEB2)          // DI03B  IA��ΪN��·  
	{
		s32_PMdataltemp=ReadMeterParaACK(DATAP);
	
		s32_tmp = (INT32S)((float)f_err_data *s32_PMdataltemp/100.0);

		offset=0;    //2��·���˹���Ԥ����ֵ  //
		if(s32_tmp>0) u32_PMdataltemp = s32_tmp;
		else	u32_PMdataltemp = 	0xFFFFFFFF +s32_tmp;
		

		SetMeterCfgACK(u32_PMdataltemp,PARAPC);
        gs_adj_emu_param.watt1os=u32_PMdataltemp;      
	}

	else if(comm_data.di1_di0.u32 == 0x0000FEB5) 	// DI03B  IB��Ϊ����·  //
	{
		s32_PMdataltemp=ReadMeterParaACK(DATAQ);
	
		s32_tmp = (INT32S)((float)f_err_data *s32_PMdataltemp/100.0);

		offset=0;    //2��·���˹���Ԥ����ֵ  //
		if(s32_tmp>0) u32_PMdataltemp = s32_tmp;
		else	u32_PMdataltemp = 	0xFFFFFFFF +s32_tmp;
		

		SetMeterCfgACK(u32_PMdataltemp,PARAQC);
        gs_adj_emu_param.watt2os=u32_PMdataltemp;      
	}
#endif

}




/////////////////////////////////////////////////////////////////////////

/*******************************************************************************************
**    END
*******************************************************************************************/


