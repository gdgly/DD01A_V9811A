/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name			: Drv_EMU_hard.c
**Author		: maji
**date			: 2016-04-20 
**description	: V9811A��EMU����ģ��Ӳ���ײ�����C����
**note			: V9811A ��MERTER FOR DL03C
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-26   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>



/*******************************************************************************************
** ��������: Open_EmuPwr
** ��������: ��EMU��׼��Դ
** �������: ��
** �������: ��
** ˵��    : 
*******************************************************************************************/
/*void Open_EmuPwr(uint8 mode)
{
    INT8U temp;

    temp=0;
    while(!temp)
        temp=SetPLL(SETPLL_3DOT2M);

   if(mode ==EMU_NORMALL_MODE)
   {
        //ADC SET  //
        CtrlADC5=0; //m channel measure temperature new sensor
	CtrlADC6=0;
	ADCOPEN(ADCAPDN+ADCUPDN);//OPEN ADC U A 
       CtrlADC0=(ADCA16X+ADCU2X); //ADC A 16X GAIN  ADC B 4x GAIN ADC U 2X GAIN	      
   }

        //     SP ��ʼ��  // 
    PMG=0;
    SetMeterCfgACK(0x00,PMCtrl4);
    SetMeterCfgACK(0x00,PMCtrl1);
    SetMeterCfgACK(INITGATEP,GATEP);//���ü�����ʼֵ
    SetMeterCfgACK(INITGATEQ,GATEQ);
    SetMeterCfgACK(0,0x10f0);
    SetMeterCfgACK(0,0x10f1);
    SetMeterCfgACK(0,0x10f2);
    SetMeterCfgACK(0,0x10f3);
    SetMeterCfgACK(0,0x10f6);
    SetMeterCfgACK(0,0x10f7);
    SetMeterCfgACK(0,0x10f8);
    SetMeterCfgACK(0,0x10f9);
    SetMeterCfgACK(0xC8,PMCtrl4);		// ����
    SetMeterCfgACK(0x08,PMCtrl4);
    SetMeterCfgACK(0x00,PMCtrl4);
    SetMeterCfgACK(0,0x10f0);
    SetMeterCfgACK(0,0x10f1);
    SetMeterCfgACK(0,0x10f2);
    SetMeterCfgACK(0,0x10f3);
    SetMeterCfgACK(0,0x10f6);
    SetMeterCfgACK(0,0x10f7);
    SetMeterCfgACK(0,0x10f8);
    SetMeterCfgACK(0,0x10f9);
    SetMeterCfgACK(0x01,GATECP);//Ǳ��1  //
    SetMeterCfgACK(0x01,GATECQ);//Ǳ��2   //
    SetMeterCfgACK(0x00,DATACP);//�������ʼĴ��� //

    SetMeterCfgACK(0x57,PMCtrl1);//��������ͨ��
    SetMeterCfgACK(0x00,PMCtrl2);//
    SetMeterCfgACK(0x30,PMCtrl3);//������·�й�����г������
    SetMeterCfgACK(0xc0,PMCtrl4);//�ȴ��˲����ȶ�����
    SetMeterCfgACK(0,PHCCtrl1);//��0
       SetMeterCfgACK(0,PHCCtrl2);//��0   

} */

/*******************************************************************************************
** ��������: Close_EmuPwr
** ��������: �ر�EMU��׼��Դ
** �������: ��
** �������: ��
** ˵��    : 
*******************************************************************************************/
void Close_EmuPwr(void)
{

}

/*******************************************************************************************
** ��������: OpenCF
** ��������:  ��CF��������
** �������: ��
** �������: 
** ˵��    : 
*******************************************************************************************/
void OpenCF(void)
{
    if((EIE&BIT1)!=BIT1)       EIE|=BIT1;
    if((ExInt3IE&BIT7)!=BIT7)  ExInt3IE|=BIT7;     // ����CF2�ж� //

}


/*******************************************************************************************
** ��������: Close_Cf
** ��������:  �ر�CF��������
** �������: ��
** �������: 
** ˵��    : 
*******************************************************************************************/
void Close_Cf(void)
{   
	INT32U PmPara;

	PmPara = ReadMeterParaACK(PMCtrl4);
	PmPara &= ~(BIT4+BIT3+BIT5);     
	SetMeterCfgACK(PmPara,PMCtrl4);  //��ֹE1 ��E2  ���ۼӺ���������ͼ��� //

	ExInt2IE &= ~BIT7;           // �ر�CF�ж� //
   // ���GPIO ��ֹ//
	P1OD|= BIT3;
}


/*******************************************************************************************
** ��������: SetMeterCfgACKPM800K
** ��������: ˫��ram���ã�ʹ��ACK�ź�
** �������: u32PMdatal ����
**                      : addr  ��ַ
** �������: FALSE ����ʧ�ܣ�TRUE ���óɹ�;
** ˵��    : 
*******************************************************************************************/
INT8U SetMeterCfgACKPM800K(unsigned long u32PMdatal ,unsigned int addr)
{
    unsigned char  index;
    index=0;
	
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
     {
       index++;
	   if(index>CFGDELAY)
	   	{
		  return FALSE	;
	   	}
     }
   XBYTE[BUFF0]=(INT8U)(u32PMdatal&0xff);
   XBYTE[BUFF1]=(INT8U)((u32PMdatal>>8)&(0xff));
   XBYTE[BUFF2]=(INT8U)((u32PMdatal>>16)&(0xff));
   XBYTE[BUFF3]=(INT8U)((u32PMdatal>>24)&(0xff));
   XBYTE[addr]=0;//�������ĵ�ַд��0�������������뵽�����ĵ�ַ
   for(index=0;index<CFGDELAY;index++)
  	_nop_();
   index=0;
   while(XBYTE[ACK])
      {
	  index++;
	  if(index>CFGDELAY)
		 return FALSE	;
      }
   return TRUE	;
    
}




/*******************************************************************************************
** ��������: SetMeterCfgI
** ��������: ˫��ram���ã�ʹ��ACK�ź�
** �������: u32PMdatal ����
**                      : addr  ��ַ
** �������: FALSE ����ʧ�ܣ�TRUE ���óɹ�;
** ˵��    : 
*******************************************************************************************/
INT8U SetMeterCfgI(unsigned long u32PMdatal ,unsigned int addr)
{
    unsigned char  index,i;
    index=0;
	
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
     {
       index++;
	   if(index>CFGDELAY)
	   	{
		  return FALSE	;
	   	}
     }
   XBYTE[BUFF0]=(INT8U)(u32PMdatal&0xff);
   XBYTE[BUFF1]=(INT8U)((u32PMdatal>>8)&(0xff));
   XBYTE[BUFF2]=(INT8U)((u32PMdatal>>16)&(0xff));
   XBYTE[BUFF3]=(INT8U)((u32PMdatal>>24)&(0xff));
   
   MEAFRQ=1;
	 while(!(MEAFRQ))
		{
		   i++;
		   if(i>30)
		   {
		      break ; //��һ��ʱ����û������
		   }
		}  
   XBYTE[addr]=0;//�������ĵ�ַд��0�������������뵽�����ĵ�ַ
  for(index=0;index<CFGDELAY;index++)
  	_nop_();
   index=0;
   while(XBYTE[ACK])
      {
	  index++;
	  if(index>CFGDELAY)
		 return FALSE	;
      }
    
   return TRUE	;
    
}


/*******************************************************************************************
** ��������: SetMeterCfgACK
** ��������: ˫��ram���ã�ʹ��ACK�ź�
** �������: u32PMdatal ����
**                      : addr  ��ַ
** �������: FALSE ����ʧ�ܣ�TRUE ���óɹ�;
** ˵��    : 
*******************************************************************************************/
INT8U SetMeterCfgACK(unsigned long u32PMdatal ,unsigned int addr)
{
    unsigned char  index;
    index=0;
	
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
     {
       index++;
	   if(index>CFGDELAY)
	   	{
		  return FALSE	;
	   	}
     }
   XBYTE[BUFF0]=(INT8U)(u32PMdatal&0xff);
   XBYTE[BUFF1]=(INT8U)((u32PMdatal>>8)&(0xff));
   XBYTE[BUFF2]=(INT8U)((u32PMdatal>>16)&(0xff));
   XBYTE[BUFF3]=(INT8U)((u32PMdatal>>24)&(0xff));
   XBYTE[addr]=0;//�������ĵ�ַд��0�������������뵽�����ĵ�ַ
  for(index=0;index<CFGDELAY;index++)
  	_nop_();
   index=0;
   while(XBYTE[ACK])
      {
	  index++;
	  if(index>CFGDELAY)
		 return FALSE	;
      }
    
  return TRUE;  
}


/*******************************************************************************************
** ��������: ReadMeterParaACK
** ��������: ˫��ram���ã�ʹ��ACK�ź�
** �������: u32PMdatal ����
**                      : addr  ��ַ
** �������: FALSE ����ʧ�ܣ�TRUE ���óɹ�;
** ˵��    : 
*******************************************************************************************/
uint32 ReadMeterParaACK(uint16 addr)
{
    uint8 data index;
    uint32  u32PMdatal,temp;

    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
        return FALSE;
        }
    }

    index=XBYTE[addr];//��ȡ��ʵ��ַ���������ݵ�����//
    for(index=0;index<CFGDELAY;index++)
    _nop_();
    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
        return FALSE;
        }
    }
    u32PMdatal=(INT32U)XBYTE[BUFF0];
    temp=(INT32U)XBYTE[BUFF1]<<8;
    u32PMdatal+= temp;
    temp=(INT32U)XBYTE[BUFF2];
    temp=temp<<16;
    u32PMdatal+=temp;
    temp=(INT32U)XBYTE[BUFF3];
    temp=temp<<24;
    u32PMdatal+=temp;
    return u32PMdatal;
	 
}


/*******************************************************************************************
**    END
*******************************************************************************************/
