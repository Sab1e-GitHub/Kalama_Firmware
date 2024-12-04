/*
 * i2c.c
 *
 *  Created on: Nov 30, 2024
 *      Author: 20854
 */

#include "global.h"
// 通用的 I2C 写入函数，自动计算长度
HAL_StatusTypeDef I2C_Write(I2C_Config_TypeDef *i2c_config, uint8_t reg_address, uint8_t* data)
{
    // 检查 hi2c 是否为 NULL
    if (i2c_config == NULL || i2c_config->hi2c == NULL)
    {
        // 如果为 NULL，返回错误
        return HAL_ERROR;
    }

    HAL_StatusTypeDef status;
    uint8_t *buffer = data;
    uint16_t length = 0;

    // 计算数组的长度
    while (buffer[length] != '\0' && length < 256)  // 设置最大长度避免越界
    {
        length++;
    }

    // 将寄存器地址作为首字节
    uint8_t buffer_with_address[length + 1];
    buffer_with_address[0] = reg_address;
    for (uint16_t i = 0; i < length; i++)
    {
        buffer_with_address[i + 1] = buffer[i];
    }

    // 发送数据
    status = HAL_I2C_Master_Transmit(i2c_config->hi2c, (i2c_config->address << 1), buffer_with_address, length + 1, HAL_MAX_DELAY);

    return status;
}

HAL_StatusTypeDef I2C_Read(I2C_Config_TypeDef *i2c_config, uint8_t reg_address, uint8_t* data, uint16_t length)
{
    // 检查 i2c_config 是否为 NULL
    if (i2c_config == NULL || i2c_config->hi2c == NULL)
    {
        return HAL_ERROR;
    }

    HAL_StatusTypeDef status;

    // 发送寄存器地址
    status = HAL_I2C_Master_Transmit(i2c_config->hi2c, (i2c_config->address << 1), &reg_address, 1, HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        return status;  // 如果发送寄存器地址失败，返回错误
    }

    // 读取指定长度的数据
    status = HAL_I2C_Master_Receive(i2c_config->hi2c, (i2c_config->address << 1), data, length, HAL_MAX_DELAY);

    return status;
}

