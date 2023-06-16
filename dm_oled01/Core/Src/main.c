/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "bmp.h"
#include "stdio.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// #define p3 -2.754473214725226e-10
// #define p2 3.880617499823303e-06
// #define p1 0.004462373429928
// #define p0 -2.699917658824761
#define p3 -2.430422433894448e-10
#define p2 4.009034911700140e-06
#define p1 0.005319481128602
#define p0 -3.902463651665676
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t startFlag = 0;
uint8_t endMeasureFlag = 0;
uint8_t caliFlag = 1;
uint8_t base; // ��У׼
uint8_t paper;
float f_paper;
float Clk_Internal;
float frequency;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ch, 1 , 0xffff);
    return ch;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
  
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_LPUART1_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  printf("ready to go!\n");
  OLED_Init();

  // PA4 �������
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // OLED_ShowPicture(0,0,128,8,BMP1);
    // HAL_Delay(500);
		// OLED_Clear();
		// OLED_ShowChinese(0,0,0,16);//��
		// OLED_ShowChinese(18,0,1,16);//��
		// OLED_ShowChinese(36,0,2,16);//԰
		// OLED_ShowChinese(54,0,3,16);//��
		// OLED_ShowChinese(72,0,4,16);//��
		// OLED_ShowChinese(90,0,5,16);//��
		// OLED_ShowChinese(108,0,6,16);//��
		// OLED_ShowString(8,16,"ZHONGJINGYUAN",16);
		// OLED_ShowString(20,32,"2014/05/01",16);
		// OLED_ShowString(0,48,"ASCII:",16);  
		// OLED_ShowString(63,48,"CODE:",16);
		// OLED_ShowChar(48,48,t,16);//��ʾASCII�ַ�	   
		// t++;
		// if (t > 50) t= 0;
		// OLED_ShowNum(103,48,t,3,16);
		// OLED_Refresh();
		// HAL_Delay(500);
		// OLED_Clear();
		// OLED_ShowChinese(0,0,0,16);  //16*16 ��
	  // OLED_ShowChinese(16,0,0,24); //24*24 ��
		// OLED_ShowChinese(24,20,0,32);//32*32 ��
	  // OLED_ShowChinese(64,0,0,64); //64*64 ��
		// OLED_Refresh();
	  // HAL_Delay(500);
  	// OLED_Clear();
		// OLED_ShowString(0,0,"ABC",12);//6*12 ��ABC��
	  // OLED_ShowString(0,12,"ABC",16);//8*16 ��ABC��
		// OLED_ShowString(0,28,"ABC",24);//12*24 ��ABC��
	  // OLED_Refresh();
		// HAL_Delay(500);
		// OLED_ScrollDisplay(11,4);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET){ //*pc13 push button 
          startFlag = 1;
          HAL_Delay(500);
          OLED_Clear();
          OLED_ShowChinese(0,0,0,16);//ֽ
		      OLED_ShowChinese(18,0,1,16);//��
		      OLED_ShowChinese(36,0,2,16);//��
		      OLED_ShowChinese(54,0,3,16);//��
		      OLED_ShowChinese(72,0,4,16);//��
          OLED_Refresh();
          HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // ����PWM ��������
          HAL_Delay(1000);
          HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    }
    // if (startFlag || caliFlag){
    if (startFlag) {
        //todo Open TIM4 (IT)
        // caliFlag = 0;
        Clk_Internal = HAL_RCC_GetHCLKFreq() / (float)((TIM4->PSC + 1)*(TIM4->ARR + 1));
        
        HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET); // �̵�
        HAL_TIM_Base_Start(&htim2);
        HAL_TIM_Base_Start_IT(&htim4);
        TIM4->CNT = 0;
        TIM2->CNT = 0;
        startFlag = 0;
        endMeasureFlag = 1;
    }
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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 25;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // ����ص�
{
  if (htim->Instance == TIM4){
      if (endMeasureFlag) {
        endMeasureFlag = 0;
        HAL_TIM_Base_Stop_IT(&htim4); // �������ܸĳ���������
        // HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
        HAL_TIM_Base_Stop(&htim2);
        HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
        // if (caliFlag) {
        //     caliFlag = 0;
        //     base = 
        // else {
          frequency = TIM2->CNT * Clk_Internal;
          f_paper = (p3*pow(frequency,3) + p2*pow(frequency, 2) + p1 * frequency + p0) + 0.5;
          printf("freq: %.2f @%.2f\n", frequency, f_paper);
          // printf("f_paper: %.3f\n", f_paper);
          paper = (uint8_t) f_paper;

          // if (f_paper < 0) paper = 0;
          // printf("$%d\n", paper);
          // OLED_ShowNum(54,32,paper,2,24); // oled
          // OLED_Refresh();
          // startFlag = 1;
          // todo oled��ʾ����
          if (f_paper <= 0) {
            printf("SHORT CIRCUIT\n");
            OLED_ShowString(32,32,"SHORT CIRCUIT",16);
            OLED_Refresh();
            
            HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
            HAL_Delay(1000);
            HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
          }
          else {
            printf("$%d\n", paper); // my app
            OLED_ShowNum(54,32,paper,2,24); // oled
            OLED_Refresh();
          }
          
          startFlag = 1;
        // }

    }
  }
  
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
