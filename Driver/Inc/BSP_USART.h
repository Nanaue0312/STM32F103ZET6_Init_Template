//
// Created by nanaue on 2024/8/7.
//

#ifndef INC_01_FREERTOS_BSP_USART_H
#define INC_01_FREERTOS_BSP_USART_H

#define USART1_Port GPIOA
#define USART1_TX GPIO_Pin_9
#define USART1_RX GPIO_Pin_10

void BSP_USART1_Init();

void USART1_SendData(uint8_t data);

void USART1_SendArray(uint8_t array[], uint16_t length);

void USART1_SendString(char *String);

#endif //INC_01_FREERTOS_BSP_USART_H
