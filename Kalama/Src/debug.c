#include "global.h"

#define UART_BUFFER_SIZE 256
extern UART_HandleTypeDef huart1;

static char uartTxBuffer[UART_BUFFER_SIZE];

/**
 * @brief 打印文本到USART1
 * @param 文本内容，格式与标准库的printf函数一致
 * @return 无返回值
 */
void uart_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsnprintf(uartTxBuffer, UART_BUFFER_SIZE, fmt, args);
    va_end(args);
    // 使用阻塞方式发送数据
	HAL_UART_Transmit(&huart1, (uint8_t *)uartTxBuffer, strlen(uartTxBuffer), HAL_MAX_DELAY);
}














