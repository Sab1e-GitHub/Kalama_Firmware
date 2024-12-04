/*
 * amg8833.h
 *
 *  Created on: Nov 30, 2024
 *      Author: 20854
 */

#ifndef KALAMA_INC_AMG8833_H_
#define KALAMA_INC_AMG8833_H_

#define AMG8833_I2C_ADDRESS 0x69

/*================== Power Control Register ==================*/
#define ADDR_POWER_CONTROL_REG 0x00		// RW

#define CMD_PWR_CTL_NORMAL_MODE 0x00
#define CMD_PWR_CTL_SLEEP_MODE 0x10
#define CMD_PWR_CTL_STAND_BY_60S_MODE 0x20	// Stand-by mode (60sec intermittence)
#define CMD_PWR_CTL_STAND_BY_10S_MODE 0x21	// Stand-by mode (10sec intermittence)

/*================== Reset Register ==================*/
#define ADDR_RESET_REG 0x01		// W

#define CMD_RST_FLAG_RESET 0x30	// Only clear the Status Register（0x04）,Interrupt Flag, and Interrupt Table（0x10～0x17）.
#define CMD_RST_INITIAL_RESET 0x3F	// Clear All

/*================== Frame Rate Register ==================*/
#define ADDR_FRAME_RATE_REG 0x02		// RW

#define CMD_FRAME_RATE_10FPS 0x00
#define CMD_FRAME_RATE_1FPS 0x01

/*================== Status Register ==================*/
#define ADDR_STATUS_REG 0x04		// R

#define STATUS_INTF_BIT 0x01			// Bit 1	Interrupt Outbreak（Value of Interrupt Table Register（0x10～0x17）: Except for 0x00）
#define STATUS_OVF_IRS_BIT 0x02	// Bit 2	Temperature Output Overflow（Value of Temperature Register（0x80～0xFF）: 0xFFF）
#define STATUS_OVF_THS_BIT 0x03	// Bit 3	Thermistor Temperature Output Overflow（Value of Thermistor (0x0E、0x0F) : 0xFFF）

/*================== Status Clear Register ==================*/
#define ADDR_STATUS_CLEAR_REG 0x05	// W

#define STATUS_CLEAR_INT_CLR_BIT 0x01		// Bit 1 Interrupt Flag Clear
#define STATUS_CLEAR_OVF_CLR_BIT 0x02	// Bit 2 Temperature Output Overflow Flag Clear
#define STATUS_CLEAR_OVT_CLR_BIT 0x03	// Bit 3 Thermistor Temperature Output Overflow Flag Clear

/*================== Average Register ==================*/
#define ADDR_AVERAGE_REG 0x07		// RW

#define AVERAGE_MAMOD_BIT 0x05	// Bit 5 Twice moving average Output Mode

/*==================  Thermistor Register ==================*/
/*
 * Thermistor Temperature Register is a read only register which indicate
 * Thermistor Temperature Data.
 * Temperature Data is 12 bit data and 2 byte data.
 * 1 LSB has 12 bit resolution which is equivalent to 0.0625℃ and
 * it is indicated as code + absolute value.
 * Main temperature data are shown below.
 */
/*
 * 地址：0x0E  BBBB_CCCC
 * 地址：0x0F  0000_ABBB
 * A_BBBBBBB_CCCC
 * A是正负号 0为+ 1为-
 * B为整数位，共计7位，0~127
 * C位小数位，共计4位，分辨率0.0625
 */
#define ADDR_THERMISTOR_LSB_REG 0x0E		//R
#define ADDR_THERMISTOR_MSB_REG 0x0F	//R

/*================== Temperature Register ==================*/
/*
 * Register for reading only to indicate temperature data per 1 pixel.
 * Temperature Data of each pixel is 12 bit data and 2 byte data.
 * 1 LSB has 12 bit resolution (11 bit + sign) which is equivalent to 0.25℃
 * and it is indicated as two's complement form.
 * Main temperature data are shown below.
 */
/*
 * 例 地址：0x80  BBBB_BBCC	Lower Level
 * 例 地址：0x81  0000_ABBB	Upper Level
 * A_BBBBBBBBB_CC
 * A是正负号 0为+ 1为-
 * B为整数位，共计9位
 * C位小数位，共计4位，分辨率0.25
 */
/*
 * 行地址：0x80~0xF0
 * 列地址：0x01~0x0F	奇数为Upper Level 偶数为Lower Level
 * 例如：0x8E 是第一行的第8个像素（1 Base Index）的Lower Level
 */


typedef enum{
	AMGD_ERROR=0,
	AMGD_OK,
} AMGD_StatusTypeDef;

typedef enum{
	AMGD_FPS_10,
	AMGD_FPS_1
}AMGD_FPSTypeDef;

AMGD_StatusTypeDef AMG8833_Init(I2C_HandleTypeDef *hi2c,uint8_t i2cAddress);
AMGD_StatusTypeDef AMG8833_SetFrameRate(AMGD_FPSTypeDef fps);
float AMG8833_ReadThermistor();
void AMG8833_ReadThermography(uint8_t buffer[8][16]);
void PrintTemperatureMatrix(uint8_t *buffer) ;
#endif /* KALAMA_INC_AMG8833_H_ */











