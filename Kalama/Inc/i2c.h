/*
 * i2c.h
 *
 *  Created on: Nov 30, 2024
 *      Author: 20854
 */

#ifndef KALAMA_INC_I2C_H_
#define KALAMA_INC_I2C_H_

typedef struct {
    I2C_HandleTypeDef *hi2c;   // ָ�� I2C ��������ָ��
    uint8_t address;           // I2C ���豸��ַ
} I2C_Config_TypeDef;

HAL_StatusTypeDef I2C_Write(I2C_Config_TypeDef *i2c_config, uint8_t reg_address, uint8_t* data);
HAL_StatusTypeDef I2C_Read(I2C_Config_TypeDef *i2c_config, uint8_t reg_address, uint8_t* data, uint16_t length);

#endif /* KALAMA_INC_I2C_H_ */
