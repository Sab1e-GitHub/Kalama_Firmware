/*
 * amg8833.c
 *
 *  Created on: Nov 30, 2024
 *      Author: 20854
 */

#include "global.h"

I2C_Config_TypeDef i2c_amg8833 = { .hi2c = NULL, .address = 0x00, };

AMGD_StatusTypeDef AMG8833_Init(I2C_HandleTypeDef *hi2c, uint8_t i2cAddress) {
	if (hi2c == NULL) {
		// ��� I2C ���Ϊ�գ��򷵻�
		return AMGD_ERROR;
	}
	i2c_amg8833.hi2c = hi2c;
	i2c_amg8833.address = i2cAddress;

	uint8_t data;
	data=CMD_PWR_CTL_NORMAL_MODE;
	if (I2C_Write(&i2c_amg8833, ADDR_POWER_CONTROL_REG, &data)
					!= HAL_OK)
		return AMGD_ERROR;
	data = CMD_RST_INITIAL_RESET;
	if (I2C_Write(&i2c_amg8833, ADDR_RESET_REG, &data)
					!= HAL_OK)
		return AMGD_ERROR;

	if (AMG8833_SetFrameRate(AMGD_FPS_10) != AMGD_OK)
		return AMGD_ERROR;

	I2C_Read(&i2c_amg8833, ADDR_FRAME_RATE_REG, &data, 1);
//	uart_printf("FPS:%d\r\n",data);
	return AMGD_OK;
}

AMGD_StatusTypeDef AMG8833_SetFrameRate(AMGD_FPSTypeDef fps) {
	uint8_t data;
	switch (fps) {
	case AMGD_FPS_10:
		data = CMD_FRAME_RATE_10FPS;
		if (I2C_Write(&i2c_amg8833, ADDR_FRAME_RATE_REG, &data)
						== HAL_OK)
			return AMGD_OK;
		break;
	case AMGD_FPS_1:
		data = CMD_FRAME_RATE_1FPS;
		if (I2C_Write(&i2c_amg8833, ADDR_FRAME_RATE_REG, &data)
						== HAL_OK)
			return AMGD_OK;
		break;
	}
	return AMGD_ERROR;
}
float ParseThermistorTemperature(uint8_t *high_byte, uint8_t *low_byte) {
	// ���ָ���Ƿ�Ϊ NULL
	if (high_byte == NULL || low_byte == NULL) {
		return 0.0f;  // ���߷��ش����־
	}

	// ��ȡ����λ
	int sign = ((*high_byte >> 3) & 0x01) ? -1 : 1;

	// ������������ (High Byte��0~2λ��Low Byte��4~7λ)
	int integer_part = ((*high_byte & 0x07) << 4) | ((*low_byte >> 4) & 0x0F);

	// ����С������ (Low Byte��0~3λ)
	int fractional_part = *low_byte & 0x0F;

	return sign * (integer_part + (fractional_part << 2)) * 0.0625f;
}

float AMG8833_ReadThermistor() {
	uint8_t lowLevelData = 0;
	uint8_t highLevelData = 0;

	// ��ȡ���ֽ�
	if (I2C_Read(&i2c_amg8833, ADDR_THERMISTOR_MSB_REG, &highLevelData,1)
					!= HAL_OK) {
//        uart_printf("I2C read error for high byte\r\n");
		return -1.0f;  // ������
	}

	// ��ȡ���ֽ�
	if (I2C_Read(&i2c_amg8833, ADDR_THERMISTOR_LSB_REG, &lowLevelData,1)
					!= HAL_OK) {
//        uart_printf("I2C read error for low byte\r\n");
		return -1.0f;  // ������
	}

	// ���ؽ�������¶�
	return ParseThermistorTemperature(&highLevelData, &lowLevelData);
}

float ParseThermography(uint8_t *high_byte, uint8_t *low_byte) {
	// ���ָ���Ƿ�Ϊ NULL
	if (high_byte == NULL || low_byte == NULL) {
		return 0.0f;  // ���߷��ش����־
	}

//	uart_printf("\r\nHigh Byte: %02X, Low Byte: %02X  ", *high_byte, *low_byte);

	// ��ȡ����λ������λ�ڸ��ֽڵĵ� 3 λ
	int sign = ((*high_byte >> 3) & 0x01) ? -1 : 1;

	// �����������֣����ֽڵĵ�3λ�͵��ֽڵĸ�6λ��
	int integer_part = ((*high_byte & 0x07) << 6) | ((*low_byte >> 2) & 0x3F);

	// ����С�����֣����ֽڵĵ�2λ��
	int fractional_part = *low_byte & 0x03;

	// �����¶�ֵ������
	return sign * (integer_part + (fractional_part * 0.25f));
}

void AMG8833_ReadThermography(uint8_t buffer[8][16]) {
    uint8_t data[128];  // ���ڴ洢64�����ص�ԭʼ���ݣ�ÿ������2���ֽڣ�
    HAL_StatusTypeDef status = I2C_Read(&i2c_amg8833, 0x80, data, 128);  // ��ȡ128�ֽ�
    if (status == HAL_OK) {
        // ����ȡ�����ݴ洢��buffer�У�ÿ�����ֽ�Ϊһ�����أ�ԭʼ���ݣ�
        for (uint8_t row = 0; row < 8; row++) {
            for (uint8_t col = 0; col < 8; col++) {
                buffer[row][col * 2] = data[row * 16 + col * 2];      // �洢���ֽ�
                buffer[row][col * 2 + 1] = data[row * 16 + col * 2 + 1];  // �洢���ֽ�
            }
        }
    }
}

