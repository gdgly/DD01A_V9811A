/*******************************************************************
*
*  FILE             :                                         
*  DATE            :                                    
*  DESCRIPTION :                     
*  CPU GROUP    :                                                 
*                                                                    
*
*******************************************************************/



#ifndef _RF_comm_H
#define _RF_comm_H


//******************************************************************
//              1     ������Ԥ����                                            //                      
//******************************************************************

#define  RF_BUFF_MAX_SIZE  		100

#define RF_TX_WAIT_MAX_TRM		100   // 10ms ʱ�������ȴ�100ms  //      

// DLT645 ��Լ���//
#define 	DLT_HeadPtr  	0
#define 	DLT_AddrPtr  	1
#define 	DLT_Head0Ptr 	7
#define 	DLT_CtlPtr   	8
#define 	DLT_LenPtr   	9
#define 	DLT_Cmd			10
#define 	DLT_CmdDI0Ptr  	10
#define 	DLT_CmdDI1Ptr  	11
#define 	DLT_CmdDI2Ptr  	12
#define 	DLT_CmdDI3Ptr  	13
#define 	DLT_ReadDataPtr   14
#define 	DLT_MIMAPAPtr   14
#define 	DLT_MIMAP0Ptr   15
#define 	DLT_MIMAP1Ptr   16
#define 	DLT_MIMAP2Ptr   17
#define 	DLT_WriterC0Ptr  18
#define 	DLT_WriterC1Ptr  19
#define 	DLT_WriterC2Ptr  20
#define 	DLT_WriterC3Ptr  21
#define 	DLT_WriteDataPtr  22


/////////////////////////
// Control byte define //
/////////////////////////
#define 	DLT_CTL_Read     		0x11    // 645 ������ //
#define 	DLT_CTL_Write    		0x14	// 645 д���� //
#define 	DLT_CTL_ChgPswd  		0x18	// 645 �޸��������� //
#define 	DLT_CTL_Broadcast     	0x08    // 645 �㲥���� //
/////////////////////////
// DLT 645 ��ԼC�����󷵻ؽ�� //
/////////////////////////
#define	RS_State_OK				0x00   	//�����ɹ� //
#define	RS_State_IVData			0x01	//�����쳣��Ƿ� //		
#define	RS_State_IVID			0x02	//ID�쳣��Ƿ� //				
#define	RS_State_PswE			0x04	//���������쳣 //		 
#define	RS_State_NOres			0x08	//�����޷���//		 
#define	RS_State_Broadcast		0x0C	//�㲥�����ֵ//		 
//----------------------------------------------


//******************************************************************
//               2     ���ݽṹ����                                                 //
//******************************************************************
typedef struct 
{	
    uint8  data_len;					// ���ڷ������ݳ���//  
    uint8  buff[RF_BUFF_MAX_SIZE];	//  ���ڻ����� //
    uint8  status;					// ���ڹ�����ʶ//
    uint8  tmr_tx_max_wait;         //RF���͵ȴ�״̬�����ʱʱ�� //
} RF_DRV_VAR;

typedef struct 
{	
	INT8U u8_result;
	INT8U u8_lenOfData;	
	INT8U tx_ready_10ms;                   //������ʱ //
	INT8U tx_delay_flg;                   //���ͱ�־ //
	INT8U start_index;
	INT8U tx_frame_len;
	union Union_DWordDef  u32_DI;        //ͨѶ����ID��  //
} DLT645_07_VAR;

//******************************************************************
//              3    ��������                                                             //
//******************************************************************
extern RF_DRV_VAR gs_rf_drv_var;
extern DLT645_07_VAR gs_dlt645_07_var;

//******************************************************************
//             4     ��������                                                              //
//******************************************************************
extern void api_RF_commRAM_RESET(void);
extern INT8U api_RF_judge_rx(INT8U **p_buf);

extern void api_DLT645_07_protocol_analysis(void);

extern void api_RF_judge_tx_over_delay(void);
extern void api_RF_judge_tx(void);
extern void api_RF_comm_deal(void);


//******************************************************************
//             5     �������ݣ�����αָ���              //
//******************************************************************
//gs_rf_drv_var. status define  //
#define RF_STATUS_RX                    0                                                                    //����״̬ //
#define RF_STATUS_TX                    1                                                                    // ����״̬ //

//DL/T645_07�汾��Լ����������
//#define 	DLT_LEN   	P_DL645_07_BUFF[DLT_LenPtr]
//#define 	DLT_CS    	P_DL645_07_BUFF[DLT_Cmd+DLT_LEN]
//#define 	DLT_End     	P_DL645_07_BUFF[DLT_Cmd+DLT_LEN+1]  //

	


#endif
/*******************************************************************
*
*  end of file                                    
*
*******************************************************************/

