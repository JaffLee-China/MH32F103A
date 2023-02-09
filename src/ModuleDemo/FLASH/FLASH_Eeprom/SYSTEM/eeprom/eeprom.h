#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "mh32f10x.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//�û������Լ�����Ҫ����
#define MH_FLASH_SIZE 512 	 		//��ѡMH32��FLASH������С(��λΪK)
#define MH_FLASH_WREN 1              //ʹ��FLASHд��(0��������;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH��ʼ��ַ
#define MH_FLASH_BASE 0x08000000 	//MH32 FLASH����ʼ��ַ
//FLASH������ֵ
 

u16 MHFLASH_ReadHalfWord(u32 faddr);		  //��������  
void MHFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
u32 MHFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//ָ����ַ��ʼ��ȡָ����������
void MHFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void MHFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
void Test_Write(u32 WriteAddr,u16 WriteData);								   
#endif

















