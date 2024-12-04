/*
 * i2c.c
 *
 *  Created on: Nov 30, 2024
 *      Author: 20854
 */

#include "global.h"
// ͨ�õ� I2C д�뺯�����Զ����㳤��
HAL_StatusTypeDef I2C_Write(I2C_Config_TypeDef *i2c_config, uint8_t reg_address, uint8_t* data)
{
    // ��� hi2c �Ƿ�Ϊ NULL
    if (i2c_config == NULL || i2c_config->hi2c == NULL)
    {
        // ���Ϊ NULL�����ش���
        return HAL_ERROR;
    }

    HAL_StatusTypeDef status;
    uint8_t *buffer = data;
    uint16_t length = 0;

    // ��������ĳ���
    while (buffer[length] != '\0' && length < 256)  // ������󳤶ȱ���Խ��
    {
        length++;
    }

    // ���Ĵ�����ַ��Ϊ���ֽ�
    uint8_t buffer_with_address[length + 1];
    buffer_with_address[0] = reg_address;
    for (uint16_t i = 0; i < length; i++)
    {
        buffer_with_address[i + 1] = buffer[i];
    }

    // ��������
    status = HAL_I2C_Master_Transmit(i2c_config->hi2c, (i2c_config->address << 1), buffer_with_address, length + 1, HAL_MAX_DELAY);

    return status;
}

HAL_StatusTypeDef I2C_Read(I2C_Config_TypeDef *i2c_config, uint8_t reg_address, uint8_t* data, uint16_t length)
{
    // ��� i2c_config �Ƿ�Ϊ NULL
    if (i2c_config == NULL || i2c_config->hi2c == NULL)
    {
        return HAL_ERROR;
    }

    HAL_StatusTypeDef status;

    // ���ͼĴ�����ַ
    status = HAL_I2C_Master_Transmit(i2c_config->hi2c, (i2c_config->address << 1), &reg_address, 1, HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        return status;  // ������ͼĴ�����ַʧ�ܣ����ش���
    }

    // ��ȡָ�����ȵ�����
    status = HAL_I2C_Master_Receive(i2c_config->hi2c, (i2c_config->address << 1), data, length, HAL_MAX_DELAY);

    return status;
}
