/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : display.c
  * @brief          : display driver
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "display.h"
#include "ssd1306.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
/**
  * @brief  Init display peripherals.
  * @retval none
  */
void display_init(void)
{
  /* Peripheral clock enable */
  __HAL_RCC_I2C1_CLK_ENABLE();
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 2400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    while(1);
  }

  HAL_Delay(10);
  
  /* Check if LCD connected to I2C */
  if (HAL_I2C_IsDeviceReady(&hi2c1, SSD1306_I2C_ADDR, 10, 20000) != HAL_OK) {
    while(1);
  }
  
  // Init lcd using one of the stm32HAL i2c typedefs
  if ( ssd1306_Init(&hi2c1) != 0 )
  {
    while(1);
  }
  HAL_Delay(1000);

  ssd1306_Fill(Black);
  ssd1306_UpdateScreen(&hi2c1);

  HAL_Delay(1000);

  // Write data to local screenbuffer
  ssd1306_SetCursor(0, 0);
  ssd1306_WriteString("ssd1306", Font_11x18, White);

  ssd1306_SetCursor(0, 36);
  ssd1306_WriteString("4ilo", Font_11x18, White);

  // Draw rectangle on screen
  for (uint8_t i=0; i<28; i++) {
      for (uint8_t j=0; j<64; j++) {
          ssd1306_DrawPixel(100+i, 0+j, White);
      }
  }

  // Copy all data from local screenbuffer to the screen
  ssd1306_UpdateScreen(&hi2c1);
}

/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2c->Instance==I2C1)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    //GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    ///* I2C1 DMA Init */
    ///* I2C1_RX Init */
    //hdma_i2c1_rx.Instance = DMA1_Channel7;
    //hdma_i2c1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    //hdma_i2c1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    //hdma_i2c1_rx.Init.MemInc = DMA_MINC_ENABLE;
    //hdma_i2c1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    //hdma_i2c1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    //hdma_i2c1_rx.Init.Mode = DMA_NORMAL;
    //hdma_i2c1_rx.Init.Priority = DMA_PRIORITY_LOW;
    //if (HAL_DMA_Init(&hdma_i2c1_rx) != HAL_OK)
    //{
    //  while(1);
    //}
    //
    //__HAL_LINKDMA(hi2c,hdmarx,hdma_i2c1_rx);
    //
    ///* I2C1_TX Init */
    //hdma_i2c1_tx.Instance = DMA1_Channel6;
    //hdma_i2c1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    //hdma_i2c1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    //hdma_i2c1_tx.Init.MemInc = DMA_MINC_ENABLE;
    //hdma_i2c1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    //hdma_i2c1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    //hdma_i2c1_tx.Init.Mode = DMA_NORMAL;
    //hdma_i2c1_tx.Init.Priority = DMA_PRIORITY_LOW;
    //if (HAL_DMA_Init(&hdma_i2c1_tx) != HAL_OK)
    //{
    //  while(1);
    //}
    //
    //__HAL_LINKDMA(hi2c,hdmatx,hdma_i2c1_tx);
    //
    ///* I2C1 interrupt Init */
    //HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    //HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
  }
}

/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

    /* I2C1 DMA DeInit */
    HAL_DMA_DeInit(hi2c->hdmarx);
    HAL_DMA_DeInit(hi2c->hdmatx);

    /* I2C1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
  }

}