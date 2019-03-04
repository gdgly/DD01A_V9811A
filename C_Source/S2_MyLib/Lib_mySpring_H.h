/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Lib_mySpring_H.H
**Author: maji
**date: 
**description:  define for general library function
**note: memer type  SD03A
**--------------------Version History -------------------------------------
** NO.	Date        		Ver    		By     			Description 
**==============================================================
** 1		2014-05-22  		0.1  			sosomj   			1. frist version                             
**
**==============================================================
*/


#ifndef  _Lib_mySpring_H
#define	    _Lib_mySpring_H

//******************************************************************
//              1     ������Ԥ����                                            
//                      
//******************************************************************



//******************************************************************
//               2     ���ݽṹ����                                                 //
//******************************************************************


//******************************************************************
//              3    ��������                                                             //
//******************************************************************



//******************************************************************
//             4     ��������                                                              //
//******************************************************************
extern INT8U Lib_Cmp_TwoArry(INT8U* s1, INT8U* s2, INT8U len) ;
extern void  Lib_Rev_Copy_Arry(INT8U* s1, INT8U len) ;
extern void  Lib_Copy_Str_TwoArry(INT8U *s1, INT8U *s2, INT16U len) ;
extern void  Lib_Set_String(INT8U *s1, INT8U tmp, INT16U len) ;
extern void  Lib_Clr_String_U16(INT16U *s1,  INT16U len) ;
extern void  Lib_Clr_String(INT8U *s1,  INT16U len) ;
extern INT16U Lib_get_data_0xFF_asclen(INT8U *Addr,INT16U numbyte);
extern void Lib_MVHalfByte_R(INT8U *addr,INT8U numbyte);
extern void Lib_MVHalfByte_L(INT8U *addr,INT8U numbyte);
extern void Lib_FCpyTMem(uxdata8 *des,const INT8U code *src,INT8U len);

//******************************************************************
//             5     �������ݣ�����αָ���              //
//******************************************************************




#endif
/***************************************************************
*    END
****************************************************************/
