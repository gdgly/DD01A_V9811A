/*******************************************************************
* Copyright (c) 2010
* All rights reserved.
* 
* �ļ����ƣ�data.c
* ժ    Ҫ��           
*
* Ӧ��ϵͳ��
*
* �汾�ţ�     v01.00            
* ���ߣ�          sosomj  
* ������ڣ�2010.08.12
****************************************************************/
#include <MyIncludes_H.h>

//**********************************************************************
//*ϵͳȫ�ֱ�������
//**********************************************************************
//struct AUTO_ERR_ADJ_VAR  gs_auto_err_adj_var;

// ST_EMU_ADJ_VAR      gs_emu_adj_var;

//����
// ST_EMU_ADJ_PARAM  gs_adj_emu_param;


//const  ST_Adjust_CONST  code   cst_adj_const = 
//{
//    C_Un*10,        //uint32 U_ref;       //�αȵ�ѹֵ������0.1V  // 
//    C_Ib*1000,     //uint32 I_ref;       //�αȵ���ֵ������0.001A  //     
//    INITGATEP,     //uint32 GATEP;    // ��������ֵ //
//    INITGATECP,   //uint32 C_GATECP;   // Ǳ������ֵ //
//    REF_RMSPn,    // uint32 C_PCONST;   // ����ʵ�У׼���׼ֵ//
//    K_RMSP,         //float   Kim_Prms;          //�й�������Чֵϵ��//   
//};

//-------------------------------------------------------------------------------//
//  Function:      void get_default_mem_data(INT8U index)     
//  Description:  �������������ȡĬ������
//  Parameters:   ��  
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
//void  Proc_Auto_Err_Adj_Pre_sec(void)
//{
    INT8U  u8_channel_fg;

//    if(Judge_ERR_ADJ_key() == FALSE)
//    {
//        Initlize_Auto_Err_Adj_Var();
//        return;
//    }

//    if(gs_auto_err_adj_var.u8_flg == FLG_HAD_ERR_ADJ)   return;

//    switch(gs_auto_err_adj_var.u8_sec_cnt)
//    {
//        case 0:
//        case 1:
//        case 2:
//	 case 3:         
//            gs_auto_err_adj_var.u8_sec_cnt++;
//        break;
//        case 4:            // ��ӹ��ʶ�ȡ�ж�У���㣬 1.0IB ������Ȳ�//
//		ADJ_Err_prepare();
//	       gs_auto_err_adj_var.u8_sec_cnt++;
//	break;
//        case SEC_INIT_ADJ_ERR:   //�̽��ȶ�ʱ�䵽λ�����ͨ��У����� ��ʼ��//
//		ADJ_Err_Adj();
//		gs_dis_ctl_var.mode = DIS_MODE_ADJ;
//		gs_dis_ctl_var.keep_sec[4] = 5;
//		gs_auto_err_adj_var.u8_flg = FLG_HAD_ERR_ADJ;
//        break;
//        default:
//            Initlize_Auto_Err_Adj_Var();
//        break;

//    }

//}

//-------------------------------------------------------------------------------//
//  Function:      void get_default_mem_data(INT8U index)     
//  Description:  �������������ȡĬ������
//  Parameters:   ��  
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
//INT8U  Judge_Auto_Err_Adj_Input_Data(INT8U u8_channel)
//{
//	if(u8_channel>2)  return(0) ;

//	if(gs_auto_err_adj_var.u32_urms_tmp[u8_channel] >URMS_MAX)   return(0);
//    	if(gs_auto_err_adj_var.u32_urms_tmp[u8_channel] <URMS_MIN)   return(0);

//    
//	if(gs_auto_err_adj_var.u32_irms_tmp[u8_channel] >IRMS_MAX)   return(0);
//    	if(gs_auto_err_adj_var.u32_irms_tmp[u8_channel] <IRMS_MIN)   return(0);

//	//if(gs_auto_err_adj_var.u32_prms_tmp[u8_channel] >PRMS_MAX)   return(0);
//    	//if(gs_auto_err_adj_var.u32_prms_tmp[u8_channel] <PRMS_MIN)   return(0);  
//    	
//        return (1);
//}


//-------------------------------------------------------------------------------//
//  Function:      void get_default_mem_data(INT8U index)     
//  Description:  �������������ȡĬ������
//  Parameters:   ��  
//  Returns:        ��                          
//  Others:         
//-------------------------------------------------------------------------------//
//void  Initlize_Auto_Err_Adj_Var(void)
//{
//	gs_auto_err_adj_var.u8_flg = 0;
//	gs_auto_err_adj_var.u8_sec_cnt = 0;


//	gs_auto_err_adj_var.u32_urms_tmp[0] = 0;
//	gs_auto_err_adj_var.u32_irms_tmp[0]  =  0;

//}






/*********************************************************************************************************
** ��������: Hardware_AdjustDiv_Sub
** ��������: Ӳ���̽� У׼�����ж�
** ��ڲ���: ��
** ���ڲ���: ��
********************************************************************************************************/
//void Hardware_AdjustDiv_Sub(void)
//{
//    uint8 i;
//    uint32 val;
//   uint32 tmpval;
//   uint32 tmpval1=0;	 
//   uint32 jzwcval;
//   uint8 ajust_type;
//   uint32 cmp_val[4];
//   uint32 adjust_wcval;

//    if(EA==0)  return;

//    //  ׼���׶�  ����ȡ����ֵ���жϽ�����һ����У��//
//   gs_emu_adj_var.adj_flg = 0x55;     // =0X55 ��ʶĿǰ����У��״̬ //

//    jzwcval=cst_adj_const.C_PCONST;     // ����ʵ�Ĺ���У׼��������//
//    cmp_val[0]=jzwcval*25/10;         //250% IB ����У����������Ĭ��ֵ��ʼ�� //
//    cmp_val[1]=jzwcval*70/100;       // ������У׼ //
//    cmp_val[2]=jzwcval*35/100;       // �ǲ�У׼ //
//    cmp_val[3]=jzwcval*3/100;         // С�ź�У׼ //

//    CLRWDT(); 	 	 
// // ��·���ʶ�ȡ//
//    adjust_wcval=Get_Original_Power(4,EMU_CH_L);	 //��ȡʵ�ʹ���
//   // A ·У��״̬��ȡ// 
//    if(adjust_wcval>cmp_val[0])
//    {
//        ajust_type=HARD_EADJ_STEP0_L_INITLIZE;//��ʼ�� ch0;
//    }
//    else if(adjust_wcval>cmp_val[1])
//    {
//        ajust_type=HARD_EADJ_STEP1_L_100IB_100L;//IB 1.0 ch0;
//    }
//    else if(adjust_wcval>cmp_val[2])
//    {
//        ajust_type=HARD_EADJ_STEP2_L_100IB_50L;//IB 0.5 ch0;   
//    }   
//    else if(adjust_wcval>cmp_val[3])
//    {
//        ajust_type=HARD_EADJ_STEP3_L_5IB_100L;//5%IB 1.0 ch0;   
//    }

//    //B ·У��״̬��ȡ//
//    ReadRaccoonInt(DATAP,5,BPhy);     // ��� 200ms��ȡ�ȴ�    //  ����ʱ��76ms
//    if( gs_sys_run.font_fg & BIT3_FONT_FG_readpower)
//    	{
//    	    gs_sys_run.font_fg &= (~BIT3_FONT_FG_readpower) ;
//	    ReadbackABCPhy();   //���ʡ���ѹ���������������ء�Ƶ�ʻ�ȡ//
//    	}
//	else // ��ȡʧ�ܣ� ���¶�ȡһ��// 
//	{
//           ReadRaccoonInt(DATAP,5,BPhy);     
//           gs_sys_run.font_fg &= (~BIT3_FONT_FG_readpower) ;
//           ReadbackABCPhy();   //���ʡ���ѹ���������������ء�Ƶ�ʻ�ȡ//
//	}
//		
//        adjust_wcval = gs_measure_var_data.gs_really[1].dw_p_val.u32;	 //��ȡʵ�ʹ���
//        // ״̬��ȡ//
//        if(adjust_wcval>cmp_val[0])
//        {
//            ajust_type=HARD_EADJ_STEP4_N_INITLIZE;//��ʼ�� 1.0 ch0;
//        }
//        else if(adjust_wcval>cmp_val[1])
//        {
//            ajust_type=HARD_EADJ_STEP5_N_100IB_100L;//IB 1.0 ch1;
//        }
//        else if(adjust_wcval>cmp_val[2])
//        {
//            ajust_type=HARD_EADJ_STEP6_N_100IB_50L;//IB 0.5 ch1;     
//        }   
//        else if(adjust_wcval>cmp_val[3])
//        {
//            ajust_type=HARD_EADJ_STEP7_N_5IB_100L;//5%IB 1.0 ch1;   
//        }
//        else
//        {
//            ajust_type=HARD_EADJ_STEP8_METER_CLR;// �������  //   
//        }




//    //   �ֲ���У׼����   //
//    //  HARD_EADJ_STEP0_L_INITLIZE   L��·�Ȳ�Ĵ�����ʼ��//
//    if(ajust_type==HARD_EADJ_STEP0_L_INITLIZE)
//    {                      
//        gs_adj_emu_param.w1gain = 0;   //��ʼ��L1ͨ���Ȳ�Ĵ���  //
//        Save_EMU_AdjParam();
//        Check_EMU_AdjParam();
//        CLRWDT();
//        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_0);   // Һ����ʾ //
//    }

//    //  HARD_EADJ_STEP1_L_100IB_100L   L��·100%Ib, 1.0L У׼//
//    if(ajust_type==HARD_EADJ_STEP1_L_100IB_100L)
//    {                      
//        //Dis_Adjust(1);  
//        // L��·�й�����У׼ // 
//        SoftAdjust_IB_Process(jzwcval,EMU_CH_L); 

//        // L��·������Чֵ����У׼ //  	
//        tmpval=0;
//        for(i=0;i<8;i++)
//        {
//            Lib_Delay_ms(30);
//            val = ReadMeterParaACK(RMSII1);
//            if(val>=0x80000000)
//            {
//                val=~val+1;  
//            } 		  		
//            tmpval=tmpval+val;
//            CLRWDT();          
//        }
//        tmpval=tmpval/8;
//        //������Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.I_ref�ͻ������������ı���//
//        gs_adj_emu_param.i1rms_xs=(float)cst_adj_const.I_ref/(float)tmpval;  
//        //��ѹ��Чֵ����У׼ //             		
//        tmpval=0;
//        for(i=0;i<8;i++)
//        {
//            Lib_Delay_ms(30);
//            val = ReadMeterParaACK(RMSIU);
//            if(val>=0x80000000)
//            {
//                val=~val+1;  
//            } 		  		
//            tmpval=tmpval+val;
//            CLRWDT();        
//        }
//        tmpval=tmpval/8;      
//        //��ѹ��Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.U_ref�ͻ�����ѹ�����ı���//
//        gs_adj_emu_param.vrms_xs=(float)cst_adj_const.U_ref/(float)tmpval;  

//        // L��·�����ߵ�ѹ����У׼//  
//        CLRWDT();            
//        //Dis_Adjust(99);   //׼���׶�    
//        SoftAdjust_dlxProcess(jzwcval,EMU_CH_L);
//        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_1);   // Һ����ʾ //
//    }

//    //  HARD_EADJ_STEP2_L_100IB_50L   L��·100%Ib, 0.5L У׼//
//    if(ajust_type==HARD_EADJ_STEP2_L_100IB_50L)
//    {                            
//        //Dis_Adjust(2);
//        jzwcval=jzwcval/2;
//        SoftAdjust_Phase_Process(jzwcval,EMU_CH_L);  
//        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_2);   // Һ����ʾ //
//    }
//    //  HARD_EADJ_STEP3_L_5IB_100L   L��·5%Ib, 1.0L У׼//
//    if(ajust_type==HARD_EADJ_STEP3_L_5IB_100L)
//    {                            
//        //Dis_Adjust(3);
//        jzwcval=jzwcval/20;
//        SoftAdjust_IB5_Process(jzwcval,EMU_CH_L);   
//        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH1_3);   // Һ����ʾ //   
//    }

//    //  HARD_EADJ_STEP4_N_INITLIZE   N��·�Ȳ�Ĵ�����ʼ��//
//    if(ajust_type==HARD_EADJ_STEP4_N_INITLIZE)
//    {                      
//        gs_adj_emu_param.w2gain = 0;   //��ʼ��L1ͨ���Ȳ�Ĵ���  //
//        Save_EMU_AdjParam();
//        Check_EMU_AdjParam();
//        CLRWDT();
//        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_0);   // Һ����ʾ //
//    }

//    //  HARD_EADJ_STEP4_N_100IB_100L   N��·100%Ib, 1.0L У׼//
//    if(ajust_type==HARD_EADJ_STEP5_N_100IB_100L)
//    {              
//        //Dis_Adjust(1);  
//        // L��·�й�����У׼ // 
//        SoftAdjust_IB_Process(jzwcval,EMU_CH_N); 

//        // L��·������Чֵ����У׼ //  	
//        tmpval=0;
//        for(i=0;i<8;i++)
//        {
//            Lib_Delay_ms(30);
//            val = ReadMeterParaACK(RMSII2);
//            if(val>=0x80000000)
//            {
//                val=~val+1;  
//            } 		  		
//            tmpval=tmpval+val;
//            CLRWDT();          
//        }
//        tmpval=tmpval/8;
//        //������Чֵ��λ���ڴ˴�������ȡ����cst_adj_const.I_ref�ͻ������������ı���//
//        gs_adj_emu_param.i2rms_xs=(float)cst_adj_const.I_ref/(float)tmpval;  

//        // N��·�����ߵ�ѹ����У׼//  
//        CLRWDT();            
//        //Dis_Adjust(99);   //׼���׶�    
//        SoftAdjust_dlxProcess(jzwcval,EMU_CH_N);
//        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_1);   // Һ����ʾ //
//    }

//    //  HARD_EADJ_STEP6_N_100IB_50L   N��·100%Ib, 0.5L У׼//
//    if(ajust_type==HARD_EADJ_STEP6_N_100IB_50L)
//    {                      
//        //Dis_Adjust(5);
//        jzwcval=jzwcval/2;
//        SoftAdjust_Phase_Process(jzwcval,EMU_CH_N);  
//        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_2);   // Һ����ʾ //
//    }    
//    //  HARD_EADJ_STEP7_N_5IB_100L   N��·5%Ib, 1.0L У׼//
//    if(ajust_type==HARD_EADJ_STEP7_N_5IB_100L)
//    {                         
//        //Dis_Adjust(6);
//        jzwcval=jzwcval/20;
//        SoftAdjust_IB5_Process(jzwcval,EMU_CH_N);   
//        api_chg_LCDDisplay_adj_item(DIS_ADJ_CH2_3);   // Һ����ʾ //   
//    }

//    if(ajust_type==HARD_EADJ_STEP8_METER_CLR)
//    {        
//        Proc_clr_meter();
//        api_chg_LCDDisplay_adj_item(DIS_DATA_CLR);   // Һ����ʾ //
//    }

//    gs_emu_adj_var.adj_flg =0;   // =0X0 ��ʶĿǰ�˳�У��״̬ //	

//}


/*--------------------------------------------------------------*/
//end of file
/*--------------------------------------------------------------*/
