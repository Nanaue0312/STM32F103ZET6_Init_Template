#include "stm32f10x.h"
#include <stdio.h>
#include "main.h"
#include "BSP_USART.h"

int main() {
    BSP_USART1_Init();
    USART1_SendString("Hello World\n");
}