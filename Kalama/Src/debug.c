#include "global.h"

#define UART_BUFFER_SIZE 256
extern UART_HandleTypeDef huart1;

static char uartTxBuffer[UART_BUFFER_SIZE];

/**
 * @brief ��ӡ�ı���USART1
 * @param �ı����ݣ���ʽ���׼���printf����һ��
 * @return �޷���ֵ
 */
void uart_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsnprintf(uartTxBuffer, UART_BUFFER_SIZE, fmt, args);
    va_end(args);
    // ʹ��������ʽ��������
	HAL_UART_Transmit(&huart1, (uint8_t *)uartTxBuffer, strlen(uartTxBuffer), HAL_MAX_DELAY);
}














