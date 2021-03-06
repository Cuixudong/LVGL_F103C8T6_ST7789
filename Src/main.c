/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"

#include "display_drv.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOOTLOADER_SIZE		(9*1024)		/*9K bootloader*/
#define CONFIG_PARAM_SIZE	(127*1024)		/*128K用于保存参数*/

#define CONFIG_PARAM_ADDR 	(FLASH_BASE + CONFIG_PARAM_SIZE)/*配置参数保存地址*/
#define FIRMWARE_START_ADDR (FLASH_BASE + BOOTLOADER_SIZE)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{
    /* Check the parameters */
    assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
    assert_param(IS_NVIC_OFFSET(Offset));

    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

void lv_test_btn_1(void)
{
    /* Create a default button manually set to toggled state*/
    lv_obj_t * btn2 = lv_btn_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_align(btn2, NULL, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_state(btn2, LV_BTN_STATE_TGL_REL);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */
    char str[20];
    uint16_t Color[] = {RED,GREEN,BLUE,YELLOW,BLACK,GRAY,LIGHTBLUE,DARKBLUE,LIGHTGREEN};
    uint8_t value=0;
    NVIC_SetVectorTable(FIRMWARE_START_ADDR,0);
    /* USER CODE END 1 */


    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_USART1_UART_Init();
    MX_RTC_Init();
    MX_ADC2_Init();
    MX_SPI2_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */
    RTC_Init();
    LCD_Init();
    HAL_Delay(100);
    POINT_COLOR = BLUE;
    LCD_ShowString(0,0,240,240,24,"HELLO WORLD");
    LCD_ShowString(0,32,240,240,24,"Lovelessing...");
    /* USER CODE END 2 */



    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    lv_init();
    lv_port_disp_init();
    lv_test_btn_1();
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        lv_task_handler();
        if(0)   //显示日历
        {
            POINT_COLOR = Color[(value++)%9];
            RTCGet();
            sprintf(str,"%4d.%d.%d",date.Year,date.Month,date.Date);
            LCD_ShowString(0,64,240,240,24,(char *)str);

            switch(date.WeekDay)
            {
            case 0:
                sprintf(str,"Sun %2d:%02d:%02d",time.Hours,time.Minutes,time.Seconds);
                break;
            case 1:
                sprintf(str,"Mon %2d:%02d:%02d",time.Hours,time.Minutes,time.Seconds);
                break;
            case 2:
                sprintf(str,"Tue %2d:%02d:%02d",time.Hours,time.Minutes,time.Seconds);
                break;
            case 3:
                sprintf(str,"Wed %2d:%02d:%02d",time.Hours,time.Minutes,time.Seconds);
                break;
            case 4:
                sprintf(str,"Thu %2d:%02d:%02d",time.Hours,time.Minutes,time.Seconds);
                break;
            case 5:
                sprintf(str,"Fri %2d:%02d:%02d",time.Hours,time.Minutes,time.Seconds);
                break;
            case 6:
                sprintf(str,"Sat %2d:%02d:%02d",time.Hours,time.Minutes,time.Seconds);
                break;
            default:
                break;
            }//sprintf(str,"%2d:%02d:%02d",time.Hours,time.Minutes,time.Seconds);

            LCD_ShowString(0,96,240,240,24,(char *)str);
        }
        HAL_Delay(5);
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
