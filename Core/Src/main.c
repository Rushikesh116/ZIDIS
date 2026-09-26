/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include <stdio.h> // Added for printf

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <tk/tkernel.h>
#include "zidis_core/config.h"
#include "zidis_core/dsp.h"
#include "zidis_core/mlp.h"
#include "zidis_core/protocol.h"
#include <stdlib.h>
#include <math.h>
#include <tm/tmonitor.h>
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

COM_InitTypeDef BspCOMInit;
__IO uint32_t BspButtonState = BUTTON_RELEASED;
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
// Variables to store your sensor readings
uint32_t soil_moisture = 0;
uint32_t water_level = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ICACHE_Init(void);
static void MX_TIM3_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */
void UART_Print(const char* str);
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

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_ICACHE_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();

  /* USER CODE BEGIN 2 */

  // 1. Start the PWM Siren on TIM3 Channel 1
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

  // 2. Set the Siren volume/duty cycle to 50% (500 out of 1000 period)
  // Note: Set this to 0 if you don't want the siren making noise while testing!
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 500);

  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN BSP */

  /* -- Sample board code to send message over COM1 port ---- */
  UART_Print("\r\n=======================================\r\n");
  UART_Print(" ZIDIS Earthquake Node - System Booting \r\n");
  UART_Print("=======================================\r\n");

  /* -- Sample board code to switch on leds ---- */
  BSP_LED_Off(LED_GREEN);

  // --- BOOT uT-KERNEL ---
  extern void knl_start_mtkernel(void);
  knl_start_mtkernel(); // Jump into the RTOS (Never returns!)

  /* USER CODE END BSP */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_CSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.CSIState = RCC_CSI_ON;
  RCC_OscInitStruct.CSICalibrationValue = RCC_CSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_CSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 129;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the programming delay
  */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_0);
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.SamplingMode = ADC_SAMPLING_MODE_NORMAL;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_247CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 0x7;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi2.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi2.Init.ReadyPolarity = SPI_RDY_POLARITY_HIGH;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 249;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SD_CS_Pin|GPIO_PIN_5|LORA_NSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : SD_CS_Pin PB5 LORA_NSS_Pin */
  GPIO_InitStruct.Pin = SD_CS_Pin|GPIO_PIN_5|LORA_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};
  MPU_Attributes_InitTypeDef MPU_AttributesInit = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region 0 and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x08FFF000;
  MPU_InitStruct.LimitAddress = 0x08FFFFFF;
  MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER0;
  MPU_InitStruct.AccessPermission = MPU_REGION_ALL_RO;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Attribute 0 and the memory to be protected
  */
  MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER0;
  MPU_AttributesInit.Attributes = INNER_OUTER(MPU_NOT_CACHEABLE);

  HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  BSP Push Button callback
  * @param  Button Specifies the pressed button
  * @retval None
  */
void BSP_PB_Callback(Button_TypeDef Button)
{
  if (Button == BUTTON_USER)
  {
    BspButtonState = BUTTON_PRESSED;
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param None
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
#ifdef USE_FULL_ASSERT
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

/* USER CODE BEGIN 4 */

/* ========================================================================= */
/*                          RTOS OBJECT DEFINITIONS                          */
/* ========================================================================= */
ID flg_detect;     // Event flag to wake up T_DETECT
ID mbf_claim;      // Message buffer for internal claims
ID tsk_sense;
ID tsk_detect;
ID tsk_consensus;
ID tsk_net;
ID tsk_diag;

// Cyclic handler ID
ID cyc_sense;

// Global State
DspState_t g_dsp_state;
ProtocolState_t g_proto_state;

// Helper to get time in ms
static uint32_t get_system_time_ms(void) {
    SYSTIM sys_time;
    tk_get_otm(&sys_time);
    return sys_time.lo;
}

// Mock Sensor Data Generation - Realistic P-Wave Simulation
// P-Waves (Primary waves) are compressional, high-frequency (5-15Hz),
// moderate-amplitude waves that arrive first before the damaging S-wave.
static uint32_t pwave_start_time = 0;

static float get_mock_sensor_data(void) {
    // Background micro-seismic noise floor (~0.01-0.05g RMS)
    float noise = ((float)(rand() % 200) - 100.0f) / 1000.0f; // ±0.1g noise
    
    if (BspButtonState == BUTTON_PRESSED) {
        uint32_t now = get_system_time_ms();
        
        // Record when the P-wave event started
        if (pwave_start_time == 0) {
            pwave_start_time = now;
        }
        
        uint32_t elapsed = now - pwave_start_time;
        float t = (float)elapsed / 1000.0f; // Time in seconds
        
        // ---- P-Wave Model ----
        // Real P-waves have:
        //   - Sudden onset (exponential ramp-up over ~0.1s)
        //   - Dominant frequency 5-15 Hz
        //   - Moderate amplitude (~0.5-2.0g for a significant quake)
        //   - Multiple frequency components
        //   - Gradual decay envelope
        
        // Exponential onset envelope (ramps up over ~100ms)
        float onset = 1.0f - expf(-t * 15.0f);
        
        // Decay envelope (P-wave energy decays over ~2s)
        float decay = expf(-t * 0.5f);
        
        // Combined envelope
        float envelope = onset * decay;
        
        // P-wave is a superposition of multiple frequency components:
        //   - Primary:   8 Hz  (strongest P-wave component)
        //   - Secondary: 12 Hz (higher harmonic)
        //   - Tertiary:  5 Hz  (low-frequency body wave)
        float f1 = sinf(2.0f * 3.14159f * 8.0f * t);   // 8 Hz primary
        float f2 = sinf(2.0f * 3.14159f * 12.0f * t);   // 12 Hz harmonic
        float f3 = sinf(2.0f * 3.14159f * 5.0f * t);    // 5 Hz body wave
        
        // Weighted sum: primary strongest, harmonic weaker, body wave weakest
        float pwave = (0.6f * f1) + (0.25f * f2) + (0.15f * f3);
        
        // Scale by envelope and peak amplitude (~1.5g)
        float amplitude = 1.5f;
        noise += amplitude * envelope * pwave;
    } else {
        // Reset P-wave start time when button is released
        pwave_start_time = 0;
    }
    
    return noise;
}

/* ========================================================================= */
/*                            uT-KERNEL TASKS                                */
/* ========================================================================= */

extern UART_HandleTypeDef hcom_uart[];
void knl_hardfault_handler(void) {
    char* msg = "\r\n*** HARD FAULT ***\r\n";
    int len = 0; while(msg[len]) len++;
    HAL_UART_Transmit(&hcom_uart[0], (uint8_t*)msg, len, 1000);
    while(1);
}

// Custom UART Print to bypass Newlib printf completely
extern UART_HandleTypeDef hcom_uart[];
void UART_Print(const char* str) {
    int len = 0;
    while(str[len]) len++;
    HAL_UART_Transmit(&hcom_uart[0], (uint8_t*)str, len, 1000);
}

// Send a sample value over UART for live plotting
// Format: "D:<integer>\r\n" where integer = sample * 1000
// This avoids printf/snprintf entirely.
static void UART_PrintSample(float sample) {
    char buf[16];
    int idx = 0;
    buf[idx++] = 'D';
    buf[idx++] = ':';
    
    // Convert float to integer (scale by 1000 for 3 decimal places)
    int val = (int)(sample * 1000.0f);
    
    // Handle negative
    if (val < 0) {
        buf[idx++] = '-';
        val = -val;
    }
    
    // Convert integer to string (reverse then flip)
    if (val == 0) {
        buf[idx++] = '0';
    } else {
        char digits[8];
        int d = 0;
        while (val > 0 && d < 7) {
            digits[d++] = '0' + (val % 10);
            val /= 10;
        }
        // Reverse
        for (int i = d - 1; i >= 0; i--) {
            buf[idx++] = digits[i];
        }
    }
    buf[idx++] = '\r';
    buf[idx++] = '\n';
    
    HAL_UART_Transmit(&hcom_uart[0], (uint8_t*)buf, idx, 100);
}

// --- 10ms Cyclic Handler ---
void SenseCyclicHandler(void *exinf) {
    // Wake up T_SENSE
    tk_set_flg(flg_detect, 0x02);
}

// --- T_SENSE Task (Priority 10 - Medium) ---
void Task_Sense(INT stacd, void *exinf) {
    UART_Print("[T_SENSE] Task Started.\r\n");
    UINT flgptn;

    while(1) {
        // Wait for 10ms cyclic handler signal
        tk_wai_flg(flg_detect, 0x02, TWF_ANDW | TWF_CLR, &flgptn, TMO_FEVR);

        float sample = get_mock_sensor_data();
        
        // Stream sample over UART for live plotting (format: "D:<value>\r\n")
        UART_PrintSample(sample);
        
        // Process sample through STA/LTA detection
        if (Dsp_ProcessSample(&g_dsp_state, sample)) {
            // Window is full! Wake up T_DETECT
            UART_Print("[T_SENSE] Window full -> waking T_DETECT\r\n");
            tk_set_flg(flg_detect, 0x01);
        }
    }
}

// --- T_DETECT Task (Priority 5) ---
void Task_Detect(INT stacd, void *exinf) {
    UART_Print("[T_DETECT] Task Started.\r\n");
    UINT flgptn;
    ZidisFeatures_t features;

    while(1) {
        // Wait for T_SENSE to signal window is full
        tk_wai_flg(flg_detect, 0x01, TWF_ANDW | TWF_CLR, &flgptn, TMO_FEVR);
        
        UART_Print("[T_DETECT] Triggered! Extracting features...\r\n");
        
        Dsp_ExtractFeatures(&g_dsp_state, &features);
        
        float confidence;
        EventClass_t evt = Mlp_Classify(&features, &confidence);
        
        if (evt == EVENT_EARTHQUAKE) {
            UART_Print("[T_DETECT] Earthquake Event Detected!\r\n");
            ClaimPacket_t claim;
            claim.source_node = ZIDIS_NODE_ID_SELF;
            claim.sequence_num = get_system_time_ms();
            claim.timestamp_ms = get_system_time_ms();
            claim.event_class = evt;
            claim.confidence = confidence;
            
            // Send to consensus task (and to T_NET to broadcast)
            tk_snd_mbf(mbf_claim, &claim, sizeof(ClaimPacket_t), TMO_FEVR);
        }
        
        // Reset window state in DSP
        g_dsp_state.window_full = false;
        g_dsp_state.window_idx = 0;
    }
}

// --- T_CONSENSUS Task (Priority 7) ---
void Task_Consensus(INT stacd, void *exinf) {
    UART_Print("[T_CONSENSUS] Task Started.\r\n");
    ClaimPacket_t claim;
    AlertLevel_t last_alert = ALERT_NONE;
    
    while(1) {
        // We can wait with timeout to run periodic ticks
        if (tk_rcv_mbf(mbf_claim, &claim, 100) >= 0) {
            // Received a claim (from local T_DETECT or remote T_NET)
            Protocol_OnClaimRx(&g_proto_state, &claim);
        }
        
        // Tick protocol
        Protocol_Tick(&g_proto_state, get_system_time_ms());
        
        // Evaluate Quorum
        AlertLevel_t new_alert = Protocol_EvaluateQuorum(&g_proto_state);
        
        if (new_alert != last_alert) {
             if (new_alert >= ALERT_L1_LOCAL) {
                 if (new_alert >= ALERT_L2_CORROBORATED) {
                     UART_Print("[T_CONSENSUS] *** ALERT: CORROBORATED ***\r\n");
                     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 500); // Siren ON
                     BSP_LED_On(LED_GREEN);
                 } else {
                     UART_Print("[T_CONSENSUS] *** ALERT: LOCAL ***\r\n");
                     BSP_LED_Toggle(LED_GREEN);
                 }
             } else {
                 UART_Print("[T_CONSENSUS] *** ALERT: NONE / CLEAR ***\r\n");
                 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0); // Siren OFF
                 BSP_LED_Off(LED_GREEN);
             }
             last_alert = new_alert;
        }
        
        // Clear user button state if it was pressed for a sufficient time
        if (BspButtonState == BUTTON_PRESSED) {
            static uint32_t press_start = 0;
            if (press_start == 0) press_start = get_system_time_ms();
            if (get_system_time_ms() - press_start > 1500) {
                BspButtonState = BUTTON_RELEASED;
                press_start = 0;
            }
        }
    }
}

// --- T_NET Task (Priority 3) ---
void Task_Net(INT stacd, void *exinf) {
    UART_Print("[T_NET] Task Started.\r\n");
    uint32_t last_beacon = 0;
    
    while(1) {
        uint32_t now = get_system_time_ms();
        
        // Send Beacon every 1000ms
        if (now - last_beacon >= 1000) {
            BeaconPacket_t bcn;
            bcn.source_node = ZIDIS_NODE_ID_SELF;
            bcn.sequence_num = now;
            bcn.timestamp_ms = now;
            
            // Mock network: just feed it back to protocol as if it's alive
            Protocol_OnBeaconRx(&g_proto_state, &bcn);
            
            // Also pretend node 2 sent a beacon
            BeaconPacket_t bcn2;
            bcn2.source_node = 2;
            bcn2.sequence_num = now;
            bcn2.timestamp_ms = now;
            Protocol_OnBeaconRx(&g_proto_state, &bcn2);

            last_beacon = now;
        }
        
        // If we want to test Quorum, we could mock a claim from node 2 when user button is pressed
        if (BspButtonState == BUTTON_PRESSED) {
             ClaimPacket_t claim2;
             claim2.source_node = 2;
             claim2.sequence_num = now;
             claim2.timestamp_ms = now;
             claim2.event_class = EVENT_EARTHQUAKE;
             claim2.confidence = 0.9f;
             tk_snd_mbf(mbf_claim, &claim2, sizeof(ClaimPacket_t), TMO_FEVR);
             tk_dly_tsk(100);
        }
        
        tk_dly_tsk(100);
    }
}

// --- T_DIAG Task (Priority 15) ---
void Task_Diag(INT stacd, void *exinf) {
    UART_Print("[T_DIAG] Task Started.\r\n");
    int count = 0;
    while(1) {
        tk_dly_tsk(3000); // 3 seconds
        count++;
        if (count == 1) UART_Print("[T_DIAG] tick 1\r\n");
        if (count == 2) UART_Print("[T_DIAG] tick 2\r\n");
        if (count == 3) UART_Print("[T_DIAG] tick 3\r\n");
        if (count > 3)  UART_Print("[T_DIAG] tick N\r\n");
    }
}

// --- USERMAIN (Initial Thread Entry Point) ---
EXPORT INT usermain(void) {
    // Debug: If we reach here, turn on the LED and spin forever.
    // If the LED turns on but nothing prints, we know printf is crashing it.
    BSP_LED_On(LED_GREEN);
    
    // Direct HAL output test
    extern UART_HandleTypeDef hcom_uart[];
    char test_msg[] = "\r\n[DIRECT HAL] usermain is alive!\r\n";
    HAL_UART_Transmit(&hcom_uart[0], (uint8_t*)test_msg, sizeof(test_msg)-1, 1000);

    UART_Print("\r\n--- ZIDIS Earthquake Early Warning System Booting ---\r\n");

    // Initialize Subsystems
    Dsp_Init(&g_dsp_state);
    // Pre-seed the LTA so the STA/LTA ratio starts at ~1.0 instead of 0/0
    g_dsp_state.lta = 0.25f;  // Expected average noise level
    g_dsp_state.sta = 0.25f;
    Mlp_Init();
    Protocol_Init(&g_proto_state);

    // Create Event Flags
    T_CFLG cflg = {0};
    cflg.flgatr = TA_TFIFO | TA_WMUL;
    flg_detect = tk_cre_flg(&cflg);

    // Create Message Buffers
    T_CMBF cmbf = {0};
    cmbf.mbfatr = TA_TFIFO;
    cmbf.bufsz = sizeof(ClaimPacket_t) * 10;
    cmbf.maxmsz = sizeof(ClaimPacket_t);
    mbf_claim = tk_cre_mbf(&cmbf);

    // Create Tasks
    T_CTSK ctsk = {0};
    ctsk.tskatr = TA_HLNG;
    ctsk.stksz = 2048;
    
    ctsk.task = Task_Sense;
    ctsk.itskpri = 10;
    tsk_sense = tk_cre_tsk(&ctsk);

    ctsk.task = Task_Detect;
    ctsk.itskpri = 5;
    tsk_detect = tk_cre_tsk(&ctsk);
    
    ctsk.task = Task_Consensus;
    ctsk.itskpri = 7;
    tsk_consensus = tk_cre_tsk(&ctsk);
    
    ctsk.task = Task_Net;
    ctsk.itskpri = 3;
    tsk_net = tk_cre_tsk(&ctsk);

    ctsk.task = Task_Diag;
    ctsk.itskpri = 15;
    tsk_diag = tk_cre_tsk(&ctsk);

    // Create Cyclic Handler
    T_CCYC ccyc = {0};
    ccyc.cycatr = TA_HLNG;

    ccyc.cychdr = SenseCyclicHandler;
    ccyc.cyctim = 10; // 10ms = 100Hz
    ccyc.cycphs = 10;
    cyc_sense = tk_cre_cyc(&ccyc);

    // Start everything
    tk_sta_tsk(tsk_sense, 0);
    tk_sta_tsk(tsk_detect, 0);
    tk_sta_tsk(tsk_consensus, 0);
    tk_sta_tsk(tsk_net, 0);
    tk_sta_tsk(tsk_diag, 0);
    
    tk_sta_cyc(cyc_sense);

    // Sleep forever so the RTOS scheduler can run the other tasks!
    // If usermain returns, T-Kernel triggers a full system shutdown.
    tk_slp_tsk(TMO_FEVR);

    return 0;
}

/* ========================================================================= */
/*              BOARD-SPECIFIC HARDWARE INIT/SHUTDOWN STUBS                  */
/* ========================================================================= */

EXPORT ER knl_init_device( void ) { return E_OK; }
EXPORT ER knl_start_device( void ) { return E_OK; }
EXPORT ER knl_finish_device( void ) { return E_OK; }
EXPORT void knl_shutdown_hw( void ) { while(1); }
EXPORT void knl_restart_hw( void ) { while(1); }
EXPORT void low_pow( void ) {
    __asm("nop");
}

/* Provide missing symbols required by uT-Kernel's sys_start.c */
EXPORT void knl_startup_hw(void) {
    // STM32 HAL already initialized hardware in main()
}

/* USER CODE END 4 */
