//
// Created by nanaue on 2024/8/7.
//
#include <stdio.h>
#include "stm32f10x.h"
#include "BSP_USART.h"

uint8_t DataBuffer[30];
uint8_t BufferIndex;

/**
 * @brief USART1初始化
 * @note TX:PA9 RX:PA10
 */
void BSP_USART1_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = USART1_TX | USART1_RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(USART1_Port, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

/**
 * @brief 发送一个字节数据
 * @param data 要发送的数据
 */
void USART1_SendData(uint8_t data) {
    USART_SendData(USART1, data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/**
 * @brief 发送一个字节数组
 * @param array 要发送的数据
 * @param length 数组长度
 */
void USART1_SendArray(uint8_t array[], uint16_t length) {
    for (int i = 0; i < length; ++i) {
        USART1_SendData(array[i]);
    }
}

/**
 * @brief 发送一个字符串
 * @param String 要发送的字符串
 */
void USART1_SendString(char *String) {
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
    {
        USART1_SendData(String[i]);        //依次调用Serial_SendByte发送每个字节数据
    }
}

void USART1_IRQHandler() {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        DataBuffer[BufferIndex++] = USART_ReceiveData(USART1);
        if (BufferIndex >= 10) {
            for (int i = 0; i < BufferIndex; ++i) {
                printf("data\n");
                BufferIndex = 0;
            }
        }
    }
}