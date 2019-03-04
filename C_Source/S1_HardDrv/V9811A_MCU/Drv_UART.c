/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_UART.c
**Author		: maji
**date			: 2016-04-20 
**description	: UARTģ���Ӳ������C����
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>



UART_DRV_VAR gs_uart_drv_var[UART_CH_NUM];


/*******************************************************************************************
** ��������: Set_Uart2_badu
** ��������: UART2����������
** ��ڲ���: u16 badu�����ڲ����ʣ�˫�ֽ�16��������
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Set_Uart2_badu(uint16 rate)
{
    TMOD2 = 0x20;                               // 8-bit counter with auto-reload
    switch(rate)
    {
        case BPS600:
#if(FSYSCLK==FSYSCLK_3M2)
        TCON2 = 0x82;
#if(C_Fq == 60)
        TL21=TH21=0xDE;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xE4;	 
#endif
#endif
#if(FSYSCLK==FSYSCLK_6M5)
        TCON2 = 0x82;		
#if(C_Fq == 60)
        TL21=TH21=0xBC;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xC7;	 
#endif
#endif
        break;

        case BPS1200:
#if(FSYSCLK==FSYSCLK_3M2)
        TCON2 = 0x82;
#if(C_Fq == 60)
        TL21=TH21=0xEF;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xF2;	 
#endif
#endif
#if(FSYSCLK==FSYSCLK_6M5)
        TCON2 = 0x82;		
#if(C_Fq == 60)
        TL21=TH21=0xDE;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xE4;	 
#endif
#endif
        break;

        case BPS2400:
#if(FSYSCLK==FSYSCLK_3M2)
        TCON2 = 0xA2;		//�����ʼӱ� //�����ʷ�����ʱ��Դclk ��Ϊʱ��Դ//�����ʷ�����������
#if(C_Fq == 60)
        TL21=TH21=0x9A;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xAB;	 
#endif
#endif
#if(FSYSCLK==FSYSCLK_6M5)
        TCON2 = 0xA2;		
#if(C_Fq == 60)
        TL21=TH21=0x34;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0x56;	 
#endif
#endif
        break;

        case BPS4800:

#if(FSYSCLK==FSYSCLK_3M2)
        TCON2 = 0xA2;
#if(C_Fq == 60)
        TL21=TH21=0xCD;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xD5;	 
#endif
#endif
#if(FSYSCLK==FSYSCLK_6M5)
        TCON2 = 0xA2;		
#if (C_Fq == 60)
        TL21=TH21=0x9A;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xAB;	 
#endif
#endif
        break;

        case BPS9600:
#if(FSYSCLK==FSYSCLK_3M2)
       TCON2 = 0xA2;
#if(C_Fq == 60)
        TL21=TH21=0xe7;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xEB;	 
#endif
#endif
#if(FSYSCLK==FSYSCLK_6M5)
        TCON2 = 0xA2;		
#if(C_Fq == 60)
        TL21=TH21=0xCD;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xD5;	 
#endif
#endif
        break;
        case BPS300:
        default:	// 300
#if(FSYSCLK==FSYSCLK_3M2)
        TCON2 = 0x82;				//�����ʼӱ� //�����ʷ�����ʱ��Դclk/12 ��Ϊʱ��Դ/
#if(C_Fq == 60)
        TL21=TH21=0xBE;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0xC7;	 
#endif
#endif
#if(FSYSCLK==FSYSCLK_6M5)
        TCON2 = 0x82;		
#if(C_Fq == 60)
        TL21=TH21=0x78;	 
#endif
#if(C_Fq == 50)
        TL21=TH21=0X8E;	 
#endif
#endif
        break;

    }

}


/*******************************************************************************************
** ��������: Set_Uart4_badu
** ��������: UART4����������
** ��ڲ���: u16 badu�����ڲ����ʣ�˫�ֽ�16��������
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Set_Uart4_badu(uint16 rate)
{
    TMOD4 = 0x20;                               // 8-bit counter with auto-reload
    switch(rate)
    {
        case BPS600:
		#if(FSYSCLK==FSYSCLK_3M2)
			TCON4 = 0x22;				//�����ʲ��ӱ� //�����ʷ�����ʱ��Դclk ��Ϊʱ��Դ/
			#if (C_Fq == 60)
				TL41=TH41=0x33;  
			#else
				TL41=TH41=0x55;  
			#endif
		#endif
		#if(FSYSCLK==FSYSCLK_6M5)
			TCON4 = 0x82;				//�����ʼӱ� //�����ʷ�����ʱ��Դclk/12 ��Ϊʱ��Դ/
			#if (C_Fq == 60)
				TL41=TH41=0xBC;  
			#else
				TL41=TH41=0xC7;  
			#endif
		#endif
        break;

        case BPS1200:
		#if(FSYSCLK==FSYSCLK_3M2)
        	TCON4 = 0x82;//�����ʼӱ� //�����ʷ�����ʱ��Դclk/12 ��Ϊʱ��Դ/
			#if (C_Fq == 60)
				TL41=TH41=0xEF;  
			#else
				TL41=TH41=0xF2;  
			#endif
		#endif
		#if(FSYSCLK==FSYSCLK_6M5)
			TCON4 = 0x82;//�����ʼӱ� //�����ʷ�����ʱ��Դclk/12 ��Ϊʱ��Դ/
			#if (C_Fq == 60)
				TL41=TH41=0xDE;  
			#else
				TL41=TH41=0xE4;  
			#endif
		#endif
        break;

        case BPS2400:
		#if(FSYSCLK==FSYSCLK_3M2)
        	TCON4 = 0xA2;		//�����ʼӱ� //�����ʷ�����ʱ��Դclk ��Ϊʱ��Դ//�����ʷ�����������
			#if (C_Fq == 60)
				TL41=TH41=0x9A;  
			#else
				TL41=TH41=0xAB;  
			#endif
		#endif
		#if(FSYSCLK==FSYSCLK_6M5)
	        TCON4 = 0xA2;		//�����ʼӱ� //�����ʷ�����ʱ��Դclk ��Ϊʱ��Դ//�����ʷ�����������
			#if (C_Fq == 60)
		        TL41=TH41=0x33;	 
			#else
		        TL41=TH41=0x55;	 
			#endif
		#endif
        break;

        case BPS4800:
		#if(FSYSCLK==FSYSCLK_3M2)
			TCON4 = 0xA2;		//�����ʼӱ� //�����ʷ�����ʱ��Դclk ��Ϊʱ��Դ//�����ʷ�����������
			#if (C_Fq == 60)
				TL41=TH41=0xCD;  
			#else
				TL41=TH41=0xD5;  
			#endif
		#endif
		#if(FSYSCLK==FSYSCLK_6M5)
			TCON4 = 0xA2;		//�����ʼӱ� //�����ʷ�����ʱ��Դclk ��Ϊʱ��Դ//�����ʷ�����������
			#if (C_Fq == 60)
				TL41=TH41=0x9A;  
			#else
				TL41=TH41=0xAB;  
			#endif
		#endif			
        break;

        case BPS9600:
		#if(FSYSCLK==FSYSCLK_3M2)
			TCON4 = 0xA2;		//�����ʼӱ� //�����ʷ�����ʱ��Դclk ��Ϊʱ��Դ//�����ʷ�����������
			#if (C_Fq == 60)
				TL41=TH41=0xE6;  
			#else
				TL41=TH41=0xEB;  
			#endif
		#endif	
		#if(FSYSCLK==FSYSCLK_6M5)
			TCON4 = 0xA2;		//�����ʼӱ� //�����ʷ�����ʱ��Դclk ��Ϊʱ��Դ//�����ʷ�����������
			#if (C_Fq == 60)
				TL41=TH41=0xCD;  
			#else
				TL41=TH41=0xD5;  
			#endif
		#endif			
        break;
        case BPS300:
        default:	// 300
		#if(FSYSCLK==FSYSCLK_3M2)
			TCON4 = 0x82;				//�����ʼӱ� //�����ʷ�����ʱ��Դclk/12 ��Ϊʱ��Դ/
			#if (C_Fq == 60)
				TL41=TH41=0xBC;  
			#else
				TL41=TH41=0xC7;  
			#endif
		#endif
		#if(FSYSCLK==FSYSCLK_6M5)
			TCON4 = 0x82;				//�����ʼӱ� //�����ʷ�����ʱ��Դclk/12 ��Ϊʱ��Դ/
			#if (C_Fq == 60)
				TL41=TH41=0x77;  
			#else
				TL41=TH41=0x8E;  
			#endif
		#endif
        break;

    }

}



/*******************************************************************************************
** ��������: Dis_UART0_rx
** ��������: UART2���ڽ��ս�ֹ
** ��ڲ���: NO
** ���ڲ���: NO
** ˵��    : 
*******************************************************************************************/
void En_UART2_rx(void)
{
    UART2_INITLIZE_ON(); 
    SCON2 = 0x50;        //8 λ UART���������ɲ����ʷ�����������  ����ʹ��//
    ExInt2IFG &= ~(BIT0+BIT1);			
    ExInt2IE&=~BIT0;		//ȡ�������ж� //
    ExInt2IE|=BIT1;		//�����ж� en
    EIE|=BIT0;
}

/*******************************************************************************************
** ��������: Dis_UART0_rx
** ��������: UART0���ڽ��ս�ֹ
** ��ڲ���: NO
** ���ڲ���: NO
** ˵��    : 
*******************************************************************************************/
/*void En_UART4_rx(void)
{
    UART4_INITLIZE_ON();      
//   SCON4 = 0x50;        //8 λ UART���������ɲ����ʷ�����������  ����ʹ��  62056//
    SCON4=0xD0;                                 //����λ9λ,8λ����λ+1У��λ// 9260+07
    ExInt2IFG &= ~(BIT2+BIT3);			
    ExInt2IE&=~BIT2;		//�����ж�dis
    ExInt2IE|=BIT3;		//�����ж� en
    EIE|=BIT0;
}
*/
void En_UART4_rx(void)
{
 /*   SCON4=0xD0;                                 //����λ9λ,8λ����λ+1У��λ// 9260+07
//    P2OE &= ~BIT1;                      //Uart4���Ϳ��������
//    P2IE &= ~BIT1;                      //Uart4���Ϳ������ֹ
//    P2OE |= BIT0;                       //Uart4���տ������ֹ
//    P2IE |= BIT0;                       //Uart4���տ���������
    P20FS=2;                            //P2.0���ó�RXD
    P21FS=2;                            //P2.1���ó�TXD
    EIP|=BIT0;
	
    ExInt2IE|=BIT2;
    ExInt2IE|=BIT3;
    EIE|=BIT0;
    ExInt2IFG&=(~BIT2);       //���жϱ�־
    ExInt2IFG&=(~BIT3);
    */
    
	 UART4_INITLIZE_ON(); 
	 SCON4 = 0x50;		  //8 λ UART���������ɲ����ʷ�����������  ����ʹ��//
	 ExInt2IFG &= ~(BIT2+BIT3); 		 
	 ExInt2IE&=~BIT2;		 //ȡ�������ж� //
	 ExInt2IE|=BIT3;	 //�����ж� en
	 EIE|=BIT0;
}

/*******************************************************************************************
** ��������: Dis_UART0_rx
** ��������: UART0���ڽ��ս�ֹ
** ��ڲ���: NO
** ���ڲ���: NO
** ˵��    : 
*******************************************************************************************/
void Dis_UART2_rx(void)
{
    ExInt2IE &= ~BIT1;	 //�رմ��ڽ����ж�//
}

/*******************************************************************************************
** ��������: Dis_UART0_rx
** ��������: UART0���ڽ��ս�ֹ
** ��ڲ���: NO
** ���ڲ���: NO
** ˵��    : 
*******************************************************************************************/
void Dis_UART4_rx(void)
{
    ExInt2IE&=~BIT3;		//�����ж�dis 
}

/*******************************************************************************************
** ��������: Dis_UART0_rx
** ��������: UART0���ڽ��ս�ֹ
** ��ڲ���: NO
** ���ڲ���: NO
** ˵��    : 
*******************************************************************************************/
void En_UART2_Tx(void)
{
    ExInt2IFG &= ~(BIT0+BIT1);			
    ExInt2IE |=BIT0;		//���ŷ����ж� //
    ExInt2IE &= ~BIT1;	 //�رմ��ڽ����ж�//
    EIE|=BIT0;          //�����ж�����8  //
  //  UART2_PWM38K_EN();
}


/*******************************************************************************************
** ��������: Dis_UART0_rx
** ��������: UART0���ڽ��ս�ֹ
** ��ڲ���: NO
** ���ڲ���: NO
** ˵��    : 
*******************************************************************************************/
void En_UART4_Tx(void)
{
    ExInt2IFG &= ~(BIT2+BIT3);			
    ExInt2IE |=BIT2;		//���ŷ����ж� //
    ExInt2IE &= ~BIT3;	 //�رմ��ڽ����ж�//
    EIE|=BIT0;          //�����ж�����8  //
}



/*******************************************************************************************
** ��������: Init_UART0_hard
** ��������: UART0����Ӳ����ʼ��
** ��ڲ���: u16 badu�����ڲ����ʣ�˫�ֽ�16��������
**           u16 bits_len: ͨѶ�ֽ�λ����ʽ��8��7
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Init_UART2_hard(uint16 badu)
{
     
    Set_Uart2_badu(badu);
    En_UART2_rx();

}

/*******************************************************************************************
** ��������: Init_UART0_hard
** ��������: UART0����Ӳ����ʼ��
** ��ڲ���: u16 badu�����ڲ����ʣ�˫�ֽ�16��������
**           u16 bits_len: ͨѶ�ֽ�λ����ʽ��8��7
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Init_UART4_hard(uint16 badu)
{
     
    Set_Uart4_badu(badu);
    En_UART4_rx();

}


/*******************************************************************************************
** ��������: Init_UART_soft
** ��������: UART[X]ͨ�������ʼ��
** ��ڲ���: uint8 ch: ͨ�����X
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Init_UART_soft(uint8 ch)
{
uint8 i;
    //init mem
    if(ch > UART_CH_INDEX_MAX )  return ;

    
    gs_uart_drv_var[ch].tx_len = 0;				//COMM_485_TX_LEN = 0 ;
    gs_uart_drv_var[ch].buff_index = 0;			//COMM_485_BUFF_INDEX = 0 ;
    gs_uart_drv_var[ch].buff_index_back = 0;	//COMM_485_BUFF_INDEX_BAK = 0 ;
    gs_uart_drv_var[ch].rx_over_ticks = 0;		//COMM_485_RX_OVERTIME_TICKS = 0 ;
    gs_uart_drv_var[ch].status = UART_STATUS_IDLE;		//COMM_485_RX_OVERTIME_TICKS = 0 ;
    gs_uart_drv_var[ch].bits_len = 7;		//COMM_485_RX_OVERTIME_TICKS = 0 ;
    for (i=0; i<UART_BUFF_SIZE; i++)
    {
        gs_uart_drv_var[ch].buff[i]=0;    
    }
}

/*******************************************************************************************
** ��������: Hdl_UART_10ms_run
** ��������: UART[X]ͨ��ÿ10ms����
** ��ڲ���: uint8 ch: ͨ�����X
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Hdl_UART_10ms_run(uint8 ch)
{
    uint8 rx_len ;

	if(ch > UART_CH_INDEX_MAX )  return ;

    // ���ڷ���״̬ʱ�������ʱ�Ĵ������ۼ�      //
    if (gs_uart_drv_var[ch].tx_len != 0)
    {
        gs_uart_drv_var[ch].rx_over_ticks = 0 ;
        return ;
    }

    //���ͺͷ��ͽ���״̬��Чʱ���������� //
    if (gs_uart_drv_var[ch].status ==UART_STATUS_BUSY_TX)
    {
        gs_uart_drv_var[ch].rx_over_ticks = 0 ;
        return ;
    }
    
    if (gs_uart_drv_var[ch].status ==UART_STATUS_BUSY_TX_OVER)
    {
        if(ch==UART_CH0_IR)
        {
            En_UART4_rx();
        }
        if(ch==CH_RF)
        {
          //  En_UART4_rx();  ͨ������9260F ��ֹ��������
          nop();
        }
        Init_UART_soft(ch);
        return ;
    }


    // δ���յ�����ʱ�������ʱ�Ĵ������ۼ�     //
    rx_len = gs_uart_drv_var[ch].buff_index	;
    if (rx_len == 0)
    {
        gs_uart_drv_var[ch].rx_over_ticks = 0 ;
        return ;
    }

    gs_uart_drv_var[ch].status = UART_STATUS_BUSY_RX;
    // ���յ�����ʱ����������������     ��ʱ�Ĵ������ۼ�     //
    if (rx_len ==gs_uart_drv_var[ch].buff_index_back)
    {
        gs_uart_drv_var[ch].rx_over_ticks++;
    }
    else
    {
        gs_uart_drv_var[ch].rx_over_ticks = 0 ;     	
    }
    gs_uart_drv_var[ch].buff_index_back = rx_len;


}


/*******************************************************************************************
** ��������: Tx_UART_frist
** ��������: UART[X]ͨ���������ֽڴ�����
** ��ڲ���: uint8 *p_buf: ��������ͨ���Ļ������׵�ַ
**           uint8 len : ���������ֽڳ���   
**           uint16 badu: ���ڷ��Ͳ�����
**           uint8 ch   : ����ͨ����
** ���ڲ���: ��
** ˵��    : 
*******************************************************************************************/
void Tx_UART_frist (uint8 *p_buf, uint8 len,uint16 badu,uint8 ch)
{    
    uint8 i ;
    uint8 bits_len;


    bits_len = 7;  //����7λ����λ //
    //
    if (len > UART_BUFF_SIZE)
    {
    len = UART_BUFF_SIZE ;
    }

    if(ch > UART_CH_INDEX_MAX )  return ;
    
    for (i=0; i<len; i++)
    {
        gs_uart_drv_var[ch].buff[i] = p_buf[i] ;
    }  
    gs_uart_drv_var[ch].tx_len = len-1;
    gs_uart_drv_var[ch].buff_index = 1;
    gs_uart_drv_var[ch].buff_index_back = 0;
    gs_uart_drv_var[ch].status = UART_STATUS_BUSY_TX;

    if(ch==UART_CH0_IR)
    {
		DisableINT(); 
    	if(gs_uart_drv_var[ch].bits_len==7)
    	{
    	// 7λ���ݴ���ʽ //
    	    ACC=(gs_uart_drv_var[ch].buff[0] &0x7F);
    	    if(P)
    	    {
    	        gs_uart_drv_var[ch].buff[0] |= BIT7;
    	    }
    	    else
    	    {
    	        gs_uart_drv_var[ch].buff[0] &= ~BIT7;
    	    }
    	}
    	EnableINT();
        Set_Uart4_badu(badu);// �������л�
        Dis_UART4_rx();
        En_UART4_Tx();
        SBUF4=gs_uart_drv_var[ch].buff[0];   
    }

    if(ch==CH_RF)
    {
       G_LoRaConfig.PayloadLength = len;
   	   SX1276_TxPacket(&gs_uart_drv_var[ch].buff[0]);                    //��������
	   Rx_mode(); 
       gs_uart_drv_var[CH_RF].buff_index = 0;
       gs_uart_drv_var[CH_RF].status = UART_STATUS_BUSY_TX_OVER;   
       gs_uart_drv_var[CH_RF].tx_len =0 ;
    }

       

}


/*******************************************************************************************
** ��������: Get_UART_rx_buff
** ��������: ��ȡUART[X]ͨ�����յ������׵�ַ�ͳ���
** ��ڲ���: uint8 **p_buf: �������ؽ������ݵ��׵�ַ����
**           uint8 ch   : ����ͨ����
** ���ڲ���: uint8 len : �������ݳ���
** ˵��    : 
*******************************************************************************************/
uint8 Get_UART_rx_buff (uint8 **p_buf,uint8 ch)
{
    uint8 len ;
    
	if(ch > UART_CH_INDEX_MAX )  return 0;
    //

	*p_buf = &gs_uart_drv_var[ch].buff[0] ;
    
    //recv...
    if(gs_uart_drv_var[ch].rx_over_ticks <10)  //�˴���ʱ����Ϊ�ж����ݽ��ս�����ʱ�䣬��Ҫ���ʱ���Ե���150ms  //
    {
        return 0;
    }

     // recv ok    
    gs_uart_drv_var[ch].rx_over_ticks = 0;
    gs_uart_drv_var[ch].status = UART_STATUS_BUSY_RX_OVER;

    if(ch==UART_CH0_IR)
    {
        //close recv
        Dis_UART4_rx () ;
    }

    if(ch==CH_RF)
    {
        //close recv
     // Dis_UART4_rx () ;ͨ������9260F ��ֹ��������
     nop();
    }
    //
    len = gs_uart_drv_var[ch].buff_index;
    gs_uart_drv_var[ch].buff_index = 0;
    gs_uart_drv_var[ch].buff_index_back = 0;

    if(len >UART_BUFF_SIZE)
    {
        len = UART_BUFF_SIZE;
    }
    
    return len ;
}



void Uart4_Transmit(void)
{
    uint8 i;
    if(gs_RacCtrl.ucStatus==Rac_Send)
    {
      if(gs_RacCtrl.ucSendPoint<gs_RacCtrl.ucSendLen)   
      {
        i=Lib_check_bitnum(gs_RacCtrl.ucBuf[gs_RacCtrl.ucSendPoint]);            //������У��λ
        if(i==0)
        {    
          SCON4 |=0x08;                        //żУ���ֵ  0x1906��bit3 1
        }
        else
        {    
          SCON4 &=0xf7;                  //��У���ֵ  0x1906��bit3 0
        }
        SBUF4 = gs_RacCtrl.ucBuf[gs_RacCtrl.ucSendPoint++];
      }
      else
      {
        gs_RacCtrl.ucStatus=Rac_Rev;  
      }
    }
}

/*******************************************************************************************
**    END
*******************************************************************************************/
