/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN Private defines */

extern uint16_t POINT_COLOR;	//������ɫ	Ĭ��Ϊ��ɫ
extern uint16_t BACK_COLOR;	//������ɫ	Ĭ��Ϊ��ɫ

//LCD�Ŀ�͸߶���
#define LCD_Width 	240
#define LCD_Height 	240

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

/*
	LCD_PWR:	PB7
	LCD_RST:	PB6
	LCD_DC:		PB4
	LCD_CS:		PD7
*/

#define	LCD_RST(n)		(n?HAL_GPIO_WritePin(OLED_RESET_GPIO_Port,OLED_RESET_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(OLED_RESET_GPIO_Port,OLED_RESET_Pin,GPIO_PIN_RESET))
#define	LCD_DC(n)		(n?HAL_GPIO_WritePin(LCD_WR_GPIO_Port,LCD_WR_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_WR_GPIO_Port,LCD_WR_Pin,GPIO_PIN_RESET))
#define	LCD_CS(n)		(n?HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET))

/* USER CODE END Private defines */

void MX_SPI2_Init(void);

/* USER CODE BEGIN Prototypes */

void LCD_Init(void);																	//��ʼ��
void LCD_DisplayOn(void);																//����ʾ
void LCD_DisplayOff(void);																//����ʾ
void LCD_Write_HalfWord(const uint16_t da);													//д����ֽ����ݵ�LCD
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);									//����������ʾ����
void LCD_Clear(uint16_t color);																//����
void LCD_Fill(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);				//��䵥ɫ
void LCD_Draw_Point(uint16_t x, uint16_t y);														//����
void LCD_Draw_ColorPoint(uint16_t x, uint16_t y,uint16_t color);										//������ɫ��
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);										//����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);									//������
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r);												//��Բ
void LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint8_t size);										//��ʾһ���ַ�
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);									//��ʾһ������
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);							//��ʾ����
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,char *p);					//��ʾ�ַ���
void LCD_Show_Image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p);					//��ʾͼƬ
void Display_ALIENTEK_LOGO(uint16_t x,uint16_t y);												//��ʾALIENTEK LOGO

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
