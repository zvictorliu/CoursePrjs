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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t flag = 0;
uint8_t Measure_State = 0;
uint8_t Num_OvEvent = 0;
uint8_t Capture_1st, Capture_2nd, Capture_3rd;
uint8_t Front_Num_OvEvent, Total_Num_OvEvent;
float Signal_Duty, Signal_Freq, Signal_Cycle;
uint32_t Clk_Internal; 

u8 t=' ';
uint32_t times_cnt;
float refFreq;
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
  MX_SPI1_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  // printf("ready to go!\n");
  // OLED_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // OLED_ShowPicture(0,0,128,8,BMP1);
    // HAL_Delay(500);
		// OLED_Clear();
		// OLED_ShowChinese(0,0,0,16);//中
		// OLED_ShowChinese(18,0,1,16);//景
		// OLED_ShowChinese(36,0,2,16);//园
		// OLED_ShowChinese(54,0,3,16);//电
		// OLED_ShowChinese(72,0,4,16);//子
		// OLED_ShowChinese(90,0,5,16);//科
		// OLED_ShowChinese(108,0,6,16);//技
		// OLED_ShowString(8,16,"ZHONGJINGYUAN",16);
		// OLED_ShowString(20,32,"2014/05/01",16);
		// OLED_ShowString(0,48,"ASCII:",16);  
		// OLED_ShowString(63,48,"CODE:",16);
		// OLED_ShowChar(48,48,t,16);//显示ASCII字符	   
		// t++;
		// if (t > 50) t= 0;
		// OLED_ShowNum(103,48,t,3,16);
		// OLED_Refresh();
		// HAL_Delay(500);
		// OLED_Clear();
		// OLED_ShowChinese(0,0,0,16);  //16*16 中
	  // OLED_ShowChinese(16,0,0,24); //24*24 中
		// OLED_ShowChinese(24,20,0,32);//32*32 中
	  // OLED_ShowChinese(64,0,0,64); //64*64 中
		// OLED_Refresh();
	  // HAL_Delay(500);
  	// OLED_Clear();
		// OLED_ShowString(0,0,"ABC",12);//6*12 “ABC”
	  // OLED_ShowString(0,12,"ABC",16);//8*16 “ABC”
		// OLED_ShowString(0,28,"ABC",24);//12*24 “ABC”
	  // OLED_Refresh();
		// HAL_Delay(500);
		// OLED_ScrollDisplay(11,4);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET){ //*pc13 push button
        // HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);

        	// HAL_Delay(500);
          // OLED_Clear();
          // // OLED_ShowString(10,24,"Ready to go",16); 
		      // // OLED_ShowNum(54,20,666,3,24); // show num 24
          // OLED_ShowChinese(0,0,0,16);//纸
		      // OLED_ShowChinese(18,0,1,16);//张
		      // OLED_ShowChinese(36,0,2,16);//数
		      // OLED_ShowChinese(54,0,3,16);//量
		      // OLED_ShowChinese(72,0,4,16);//：
          // OLED_Refresh();

        TIM4->CNT = 0;
        times_cnt = 0;
        flag = 1;
        //todo Open TIM4 (IT)
        Measure_State = 0;
        Clk_Internal = HAL_RCC_GetHCLKFreq();
        // printf("HCLK: %d\n", Clk_Internal);
        printf("begin to detect\n");
        refFreq = Clk_Internal / (float)((TIM4->PSC + 1)*(TIM4->ARR + 1));
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        __HAL_TIM_ENABLE_IT(&htim4, TIM_IT_UPDATE); // 溢出中断
        HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_4); // 捕获中断
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    }

    if (flag){
      // todo binking the LED
      HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
      HAL_Delay(300);
      HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
      HAL_Delay(300);
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // 溢出回调
{
  if (times_cnt) {

    printf("freq: %.2f\n", times_cnt * refFreq);

    flag = 0;
    HAL_TIM_IC_Stop_IT(&htim4, TIM_CHANNEL_4);
    __HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
  }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
  ++times_cnt; 
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
