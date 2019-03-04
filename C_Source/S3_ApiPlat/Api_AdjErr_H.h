/*******************************************************************
*
*  FILE             :                                         
*  DATE            :                                    
*  DESCRIPTION :            
*  CPU GROUP    :                                                
*                                                                    
*  
*
*******************************************************************/

#ifndef _Api_AdjErr_H
#define  _Api_AdjErr_H
//------------------------------------------------------------------------//
//                  ������Ԥ����
//------------------------------------------------------------------------//
//#define URMS_MAX         1651          // XXXX.X V  ���ݸ�ʽ��1270 *1.3 = 1651   127.0v *1.3 //
//#define IRMS_MAX         26000          // xxx.xxx A  ���ݸ�ʽ��20000 *1.3 = 26000   20.000A *1.3 //
//#define PRMS_MAX        16510          //XX.XXXX kW  ���ݸ�ʽ��1270*20*0.5*1.3 = 16510    //

//#define URMS_REF         1270          // XXXX.X V  ���ݸ�ʽ�� 127.0v //
//#define IRMS_REF         20000          // xxx.xxx A  ���ݸ�ʽ�� 20.000A //
//#define PRMS_REF        12700          //XX.XXXX kW  ���ݸ�ʽ��1270*20*0.5 = 12700    //

//#define URMS_MIN         800            // XXXX.X V  ���ݸ�ʽ��1270 *0.7 = 889   127.0v *0.7 //
//#define IRMS_MIN         13000          // xxx.xxx A  ���ݸ�ʽ��20000 *0.7 = 14000   20.000A *0.7 //
//#define PRMS_MIN        8890          //XX.XXXX kW  ���ݸ�ʽ��1270*20*0.5*0.7 = 16510    //

//#define PRMS_104PRE        13208          //XX.XXXX kW  ���ݸ�ʽ��1270*20*0.5*1.04 = 13208   //
//#define PRMS_96PRE        12192          //XX.XXXX kW  ���ݸ�ʽ��1270*20*0.5*0.96= 12192  //


//#define SEC_INIT_ADJ_ERR     5          // У�������ʼ������ʱ���//
//#define SEC_UI_ADJ_ERR	 11          // ������ѹ����У��ʱ���//         
//#define  SEC_PH_ADJ_ERR  	 12        //PH ��λУ��ʱ���//  		  		
//     

//#define FLG_HAD_ERR_ADJ            1        // ���ζ̽��Ѿ����У���־//  



// У������//

//#define ADJ_err_100IB_10L    BIT0 
//#define ADJ_err_100IB_05L    BIT1 
//#define ADJ_err_5IB_10L        BIT2 



//------------------------------------------------------------------------//
//                               ���ݽṹ����
//------------------------------------------------------------------------//
//struct AUTO_ERR_ADJ_VAR
//{
//    INT8U u8_flg;          	           //У���־  //
//    INT8U u8_sec_cnt;		 //�붨ʱ�� //
//    INT8U u8_tpye;          	           //У������ //
//    INT32U u32_urms_tmp[PHASE_MAX_UNM];           // ������·������3�εı�Ƶ�ѹ��Чֵ���ݼĴ��� //
//    INT32U  u32_irms_tmp[PHASE_MAX_UNM];             // ������·������3�εı�Ƶ�����Чֵ���ݼĴ��� //
//    INT32U u32_prms_tmp[PHASE_MAX_UNM];            // ������·������3�εı���й�������Чֵ���ݼĴ��� //
//     INT8U u8_vgain[PHASE_MAX_UNM];		//		//
//     INT8U u8_igain[PHASE_MAX_UNM];			//		//
//     INT8U u8_phsi[PHASE_MAX_UNM];
//} ;


//typedef struct 
//{
//    uint8   sec_flg;  //У׼�����е���仯��ʶ//
//    uint8   adj_flg;  //У�����״̬��=0X55����У������� //
//} ST_EMU_ADJ_VAR;



//typedef struct
//{
//    uint32 U_ref;       //�αȵ�ѹֵ������0.1V  // 
//    uint32 I_ref;       //�αȵ���ֵ������0.001A  //     
//    uint32 C_GATEP;    // ��������ֵ //
//    uint32 C_GATECP;   // Ǳ������ֵ //
//    uint32 C_PCONST;   // ����ʵ�У׼���׼ֵ//
//    float   Kim_Prms;          //�й�������Чֵϵ��//   
//}ST_Adjust_CONST;


//---------------------------------------------------------------//
//                  �ⲿ  ��������
//---------------------------------------------------------------//
//extern struct AUTO_ERR_ADJ_VAR  gs_auto_err_adj_var;
//extern ST_EMU_ADJ_VAR      gs_emu_adj_var;

//extern const  ST_Adjust_CONST  code   cst_adj_const;

//---------------------------------------------------------------//
//                  �ⲿ  ��������
//---------------------------------------------------------------//
//extern void  Proc_Auto_Err_Adj_Pre_sec(void);
//extern void  Calcu_Auto_Err_Channel_Para_PH(INT8U u8_channel);
//extern  void  Calcu_Auto_Err_Channel_Para_UI(INT8U u8_channel);
//extern void Initlize_Auto_Err_Channel_Para(INT8U u8_channel);
//extern INT8U  Judge_Auto_Err_Adj_Input_Data(INT8U u8_channel);
//extern void  Initlize_Auto_Err_Adj_Var(void);




#endif
/*******************************************************************
*
*  end of file                                    
*
*******************************************************************/




