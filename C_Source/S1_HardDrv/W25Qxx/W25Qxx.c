/************************************************************************
* ��Ȩ���� (C)2016, �����������ܿƼ��ɷ����޹�˾��
*
* �ļ����ƣ� // W25QXX.c
* �ļ���ʶ�� // 
* ����ժҪ�� //����Flash��������
* ����˵���� // 
* ��ǰ�汾�� // V01.00
* �� �ߣ�    // yangxing
* ������ڣ� // 2010��7��06��
*
* �޸ļ�¼1��//
* �޸����ڣ� //
* �� �� �ţ� // V01
* �� �� �ˣ� //
* �޸����ݣ� //
************************************************************************/
#include <MyIncludes_H.h>

/************************************************************************
* ������ ��//Delay_W25Xxx
* ���� ��//��ʱ�ӳ���
* ������� ��//n����ʱʱ��
* ������� ��//��
* ����ֵ˵�� ��//��
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
void Delay_W25Xxx( unsigned char i )
{  
    for(i=0;i<3;i++)	
        nop();
}

/************************************************************************
* ������ ��//W25Xxx_Init
* ���� ��//W25Xxx�ܽų�ʼ��
* ������� ��//��
* ������� ��//��
* ����ֵ˵�� ��//��
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
void W25Xxx_Init(void)
{
	/*
    P_FLASH_CS_H;
	P_FLASH_WP_H;
    //P_FLASH_HOLD_H;
    P_FLASH_SCL_H;
    P_FLASH_SDO_H;
    P_FLASH_CS_DIROUT();
    P_FLASH_WP_DIROUT();
    //P_FLASH_HOLD_DIROUT();
    P_FLASH_SCL_DIROUT();
    P_FLASH_SDO_DIROUT();
    P_FLASH_SDI_DIRIN();
	*/
	
	P_FLASH_SCL_DIROUT();
    P_FLASH_SDO_DIROUT();
    P_FLASH_SDI_DIRIN();
	P_FLASH_CS_DIROUT();
	
	P_FLASH_CS_H;
    P_FLASH_SCL_H;
    P_FLASH_SDO_H;
}

/************************************************************************
* ������ ��//W25Xxx_SendByte
* ���� ��//����һ���ֽ����ݻ��ַ
* ������� ��//TxData:�����͵���Ϣ
* ������� ��//��
* ����ֵ˵�� ��//��
* ����˵�� ��//��CLK������ʱ������SD0�ź�
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
void W25Xxx_SendByte(unsigned char TxData)
{
    unsigned char i;

    for( i = 0; i < 8; i++ )
    {
        //Delay_W25Xxx(3);
        P_FLASH_SCL_L;// CLK=0
        if( TxData & 0x80 )
            P_FLASH_SDO_H;// SD0=1
        else
            P_FLASH_SDO_L;// SD0 = 0
        //Delay_W25Xxx(3);
        P_FLASH_SCL_H;// CLK = 1
        TxData <<= 1;
    }
}

/************************************************************************
* ������ ��//W25Xxx_ReceiveByte
* ���� ��//����һ���ֽ�����
* ������� ��//��
* ������� ��//MX25LXX ��ȡ����
* ����ֵ˵�� ��//��
* ����˵�� ��//��CLK�½���ʱ����ȡSDI�ź�
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
unsigned char W25Xxx_ReceiveByte(void)
{
    unsigned char i,RxData=0;

    //P_FLASH_SCL_H;//SCL=1
    for( i = 0; i < 8; i++ )
    {
        P_FLASH_SCL_L;//SCL=0
        Delay_W25Xxx(3);
        P_FLASH_SCL_H;//SCL=1
        //Delay_W25Xxx(3);
        RxData <<= 1;
		P_FLASH_SDI_DIRIN();
        if( P_FLASH_SDI_Read )
            RxData |= 0x01;
    }
    return(RxData);
}

/************************************************************************
* ������ ��//W25X_WriteEnable
* ���� ��//����д
* ������� ��//��
* ������� ��//
* ����ֵ˵�� ��//��
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
void W25X_WriteEnable(void)
{
    if( W25X_WaitForWriteEnd() == 0 )
    {
        P_FLASH_CS_L;
        W25Xxx_SendByte(W25X_WriteEn);
        P_FLASH_CS_H;
    }
}

/************************************************************************
* ������ ��//W25X_WriteDisable
* ���� ��//��ֹд
* ������� ��//��
* ������� ��//
* ����ֵ˵�� ��//��
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
void W25X_WriteDisable(void)
{
    P_FLASH_CS_L;

    W25Xxx_SendByte(W25X_WriteDis);

    P_FLASH_CS_H;
}

/************************************************************************
* ������ ��//W25X_WaitForWriteEnd
* ���� ��//flash ���м��
* ������� ��//��
* ������� ��//
* ����ֵ˵�� ��//0--���� 1---����
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
unsigned char W25X_WaitForWriteEnd(void)
{
    unsigned char FlashSta =0x01;
    unsigned long i=0;
    
    P_FLASH_CS_L;
    W25Xxx_SendByte(W25X_ReadStatus);//��״̬�Ĵ���
    while(FlashSta & 0x01)
    {
        CLRWDT();;//�忴�Ź�
        FlashSta = W25Xxx_ReceiveByte();
        i++;
        if( i > 120000 )//��ȴ�700ms������FLASH����
           break;
        if(( i%5000 )==0)
            W25Xxx_SendByte(W25X_ReadStatus);//��״̬�Ĵ���
    }
    P_FLASH_CS_H;
    if( i<120000 ) 
    {
        return 0;			
    }	
    else
    {
       // Flag.Error |= F_FLASH_Err;
        return 1;
    }	
}

/************************************************************************
* ������ ��//W25X_ChkWriteEn
* ���� ��//дʹ�ܿ��ؼ��
* ������� ��//��
* ������� ��//
* ����ֵ˵�� ��//0--���� 1---����
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
unsigned char W25X_ChkWriteEn(void)
{    
    unsigned char FlashSta = 0x06;	
    unsigned long i=0;
    P_FLASH_CS_L;

    W25Xxx_SendByte(W25X_ReadStatus);//��״̬�Ĵ���
    while( (FlashSta & 0x0f)!=0x02 )
    {
        CLRWDT();//�忴�Ź�
//		W25Xxx_SendByte(W25X_ReadStatus);//��״̬�Ĵ���
        FlashSta = W25Xxx_ReceiveByte();
        i++;
        if( i > 120000 )//��ȴ�700ms������FLASH����
           break;
        if(( i%5000 )==0)
            W25Xxx_SendByte(W25X_ReadStatus);//��״̬�Ĵ���
    }
    P_FLASH_CS_H;
    
    if( i<120000 ) 
    {
        return 0;			
    }	
    else
    {
        //Flag.Error |= F_FLASH_Err;
        return 1;
    }	
}
/**********************************************************************
* ������ ��//W25X_StatusRead
* ���� ��//��״̬�Ĵ���		CMD=0x05
* ������� ��//��
* ������� ��//
* ����ֵ˵�� ��//����״̬��
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**********************************************************************/
unsigned char W25X_StatusRead(void)
{
    unsigned char i;
    unsigned char Temp=0,Temp1=0;

    P_FLASH_CS_L;
    W25Xxx_SendByte( W25X_ReadStatus );	
    for( i=0;i<10;i++ )
    {
        Temp = W25Xxx_ReceiveByte();										
        Temp1 = W25Xxx_ReceiveByte();
        if( Temp == Temp1 ) 
            break;										
    }	
    P_FLASH_CS_H;
    return Temp;
}
/**********************************************************************
* ������ ��//W25X_StatusWrite
* ���� ��//д״̬�Ĵ���		CMD=0x01
* ������� ��//��
* ������� ��//
* ����ֵ˵�� ��//
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**********************************************************************/
void W25X_StatusWrite(void)
{
    W25X_WriteEnable();
    if( W25X_WaitForWriteEnd() == 0 ) 
    {
        P_FLASH_CS_L;
        W25Xxx_SendByte( W25X_WriteStatus );	
        W25Xxx_SendByte( 0x00 );	
        P_FLASH_CS_H;
    } 
}
/************************************************************************
* ������ ��//W25X_SectorErase_4KByte
* ���� ��//����4K������
* ������� ��//��
* ������� ��//Addr:������ʼ��ַ
* ����ֵ˵�� ��//��
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
void W25X_SectorErase_4KByte(unsigned long Addr)
{
    unsigned char FlashCheck = 0x00;
    CLRWDT();//�忴�Ź�

    W25Xxx_Init();  

    FlashCheck = W25X_StatusRead();
    if(( FlashCheck & 0xFC ) != 0 ) 
        W25X_StatusWrite();
    
    W25X_WriteEnable();//����д
    
    if( W25X_ChkWriteEn() == 0 )
    {
        P_FLASH_CS_L;
        W25Xxx_SendByte(W25X_S_Erase);
        W25Xxx_SendByte( (Addr & 0xFF0000) >> 16 );
        W25Xxx_SendByte( (Addr & 0xF000) >> 8 );//0XFF00 ��Ϊ������ʼ��ַ��16λ����000������������0xF000
        W25Xxx_SendByte( Addr & 0x00 );//0XFF ��Ϊ������ʼ��ַ��16λ����000������������0x00
        P_FLASH_CS_H;
        W25X_WaitForWriteEnd();//Ŀ���Ǳ�֤д����
    }
}

/************************************************************************
* ������ ��//W25Xxx_HighSpeedRead
* ���� ��//���ٶ�
* ������� ��//��
* ������� ��//Dest:Ŀ�ĵ�ַ Addr��Դ��ַ Lenth�����ݳ���
* ����ֵ˵�� ��//��
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
void W25Xxx_HighSpeedRead( unsigned char* Dest, unsigned long Addr, unsigned short Lenth )
{
    unsigned short i;

    CLRWDT();//�忴�Ź�

    W25Xxx_Init();

    if(W25X_WaitForWriteEnd()==0)
    {
        P_FLASH_CS_L;
        W25Xxx_SendByte( W25X_ReadDATA8 );//��ͨ��
        //W25Xxx_SendByte( W25X_FastRead );//���ٶ�
        W25Xxx_SendByte( (Addr & 0xFF0000) >> 16 );
        W25Xxx_SendByte( (Addr& 0xFF00) >> 8 );
        W25Xxx_SendByte( Addr & 0xFF );
        //W25Xxx_SendByte( Dummy_Byte );
        for( i = 0; i < Lenth; i++)
        {
            *Dest = W25Xxx_ReceiveByte();
            Dest++;
        }
        P_FLASH_CS_H;
    }
}

/************************************************************************
* ������ ��//W25Xxx_Write
* ���� ��//����д
* ������� ��//Addr��Flash��ַ Src:���ݵ�ַ Len�����ݳ���
* ������� ��//��
* ����ֵ˵�� ��//��
* ����˵�� ��//��
* �޸����� :
* ------------------------------------------------------------------------
* 2010/07/06 V1.0 yangxing XXXX
**************************************************************************/
void W25Xxx_Write( unsigned long Addr, unsigned char* Src, unsigned short Lenth )
{
    unsigned short i;
    unsigned Len = 0;
    unsigned char FlashCheck = 0x00;
    CLRWDT();//�忴�Ź�

    W25Xxx_Init();

    FlashCheck = W25X_StatusRead();
    if(( FlashCheck & 0xFC ) != 0 ) 
        W25X_StatusWrite();
    
    while( Lenth > 0 )
    {
        if( Addr & 0x000000FF )
        {
            Len = 256 - (Addr & 0x000000FF);
            if( Len > Lenth )
                Len = Lenth;
        }
        else
        {
            if( Lenth > 256)
                Len = 256;
            else
                Len = Lenth;
        }
        W25X_WriteEnable();//����д
        if( W25X_ChkWriteEn() == 0 )
        {
            P_FLASH_CS_L;
            W25Xxx_SendByte( W25X_Write );
            W25Xxx_SendByte( (Addr & 0xFF0000) >> 16 );
            W25Xxx_SendByte( (Addr & 0xFF00) >> 8 );
            W25Xxx_SendByte( Addr & 0xFF );
            for( i = 0; i < Len; i++ )
            {
                W25Xxx_SendByte( *(Src+i) );
            }
            P_FLASH_CS_H;
        } 
        Addr += Len;
        Src += Len;
        Lenth -= Len;
        W25X_WaitForWriteEnd();
    }
}


INT8U SPI_FLASH_BUF[1024];
void SPI_Flash_Write(INT8U *pbuf,INT32U addr, INT16U len)
{
		INT32U secpos;
		INT16U secoff;
		INT16U secremain;
		INT16U i,j;
		INT16U seclen;
//		INT16U isErase = 0;

		secpos = addr/4096;			//�ڵڼ�������
		secoff = addr%4096;			//�ڵ�ǰ������ƫ��
		secremain = 4096-secoff;	//��ǰ������ʣ��ռ�
		
		if(len <= secremain) //д�볤��С�ڵ�ǰ������ʣ��ռ䣬����д����һ����
			secremain = len;
		while(1)
		{

			for(i=0;i<4;i++)
			{
				W25Xxx_HighSpeedRead(SPI_FLASH_BUF,(secpos*4096+1024*i),1024);
				mem_write( ADR_BLOCK180_LOAD_START_E2P+1024*i,SPI_FLASH_BUF,1024,MEM_E2P1);
			}
			W25X_SectorErase_4KByte(secpos*4096);

			if(len > secremain)
			{
				seclen = secremain;	
			}
			else
			{
				seclen = len;
			}
			for(i = 0; i < 4;i++)
			{
				mem_read( SPI_FLASH_BUF,ADR_BLOCK180_LOAD_START_E2P+1024*i,1024,MEM_E2P1);
				if(i < secoff/1024)
				{
					W25Xxx_Write(4096*secpos+1024*i,SPI_FLASH_BUF,1024);
				}
				if(i == secoff/1024)
				{
					for(j=0;j<(1024-secoff%1024);j++)
					{
						if(seclen > 0)
						{
							SPI_FLASH_BUF[secoff%1024+j] = pbuf[j];
							seclen--;
						}
					}
					W25Xxx_Write(4096*secpos+1024*i,SPI_FLASH_BUF,1024);
				}
				if(i > secoff/1024)
				{
					for(j=0;j<1024;j++)
					{
						if(seclen > 0)
						{
							SPI_FLASH_BUF[j] = pbuf[j+1024*(i-secoff/1024)];
							seclen--;
						}
						
					}
					W25Xxx_Write(4096*secpos+1024*i,SPI_FLASH_BUF,1024);
				}
				
			}
			if(len <= secremain)//�ֽڲ�����4096��ʾ
				break;
			else
			{
				secpos++;
				if(secpos == 16)
				{
					secpos = 0;
				}
				secoff=0;
				pbuf+=secremain;
				addr += secremain;
				len -= secremain;

				if(len > 4096)
					secremain = 4096;
				else
					secremain = len;
			}
		}
}
