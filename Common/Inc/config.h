/* config.h */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "stm32h7xx_hal.h"

/**************************************************************************************/
/********************            QSPI FLASH definitions            ********************/
/**************************************************************************************/
#define BUFFER_SIZE         ((uint32_t)0x0200)
#define WRITE_READ_ADDR     ((uint32_t)0x4000000) //64M offset

/**************************************************************************************/
/********************              debug definitions               ********************/
/**************************************************************************************/
//#define PRINT_IFFT_FREQUENCY
//#define PRINT_IFFT_FREQUENCY_FULL
//#define PRINT_CIS_CALIBRATION

/**************************************************************************************/
/********************             Display definitions              ********************/
/**************************************************************************************/
#define DISPLAY_REFRESH_FPS						(5)

/**************************************************************************************/
/********************              Synth definitions               ********************/
/**************************************************************************************/
#define SAMPLING_FREQUENCY				      	(48000)

#define IFFT_1
#define SIN										//SIN-SAW-SQR

#define GAP_LIMITER
#define IFFT_GAP_PER_LOOP_INCREASE				(100000)
#define IFFT_GAP_PER_LOOP_DECREASE				(1000)

#define NOISE_REDUCER							(200)
//#define STEREO_1
#define RELATIVE_MODE

/**************************************************************************************/
/******************              Ethernet definitions               *******************/
/**************************************************************************************/
#define SEND_CIS_LINE_FREQUENCY				    (3000)
#define IMAGE_HEADER							(1397969715) //01010011 01010011 01010011 00110011 SSS3
#define IMAGE_HEADER_SIZE						(1)//uint32

/* UDP local connection port */
#define UDP_SERVER_PORT    						((uint16_t)60U)
/* UDP remote connection port */
#define UDP_CLIENT_PORT    						((uint16_t)60U)

/*Static DEST IP ADDRESS: DEST_IP_ADDR0.DEST_IP_ADDR1.DEST_IP_ADDR2.DEST_IP_ADDR3 */
#define DEST_IP_ADDR0   						((uint8_t)192U)
#define DEST_IP_ADDR1   						((uint8_t)168U)
#define DEST_IP_ADDR2   						((uint8_t)0U)
#define DEST_IP_ADDR3   						((uint8_t)10U)

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0   								((uint8_t) 192U)
#define IP_ADDR1   								((uint8_t) 168U)
#define IP_ADDR2   								((uint8_t) 0U)
#define IP_ADDR3   								((uint8_t//) 1U)

/*NETMASK*/
#define NETMASK_ADDR0   						((uint8_t) 255U)
#define NETMASK_ADDR1   						((uint8_t) 255U)
#define NETMASK_ADDR2   						((uint8_t) 255U)
#define NETMASK_ADDR3   						((uint8_t) 0U)

/*Gateway Address*/
#define GW_ADDR0   								((uint8_t) 192U)
#define GW_ADDR1   								((uint8_t) 168U)
#define GW_ADDR2   								((uint8_t) 0U)
#define GW_ADDR3   								((uint8_t) 1U)

/**************************************************************************************/
/********************                  CV MODE                     ********************/
/**************************************************************************************/
#define IMAGE_WEIGHT							(25)

/**************************************************************************************/
/********************              DAC definitions                 ********************/
/**************************************************************************************/
#define AUDIO_BUFFER_SIZE             			(512)
#define VOLUME									(30)

/**************************************************************************************/
/********************         Wave generation definitions          ********************/
/**************************************************************************************/
#define CIS_ACTIVE_PIXELS_PER_LINE				(1152)
#define CIS_ADC_OUT_LINES						(3)
#define CIS_IFFT_OVERSAMPLING_RATIO				(16)

#define WAVE_AMP_RESOLUTION 					(65535)   	//in decimal
#define START_FREQUENCY     					(40)
#define MAX_OCTAVE_NUMBER   					(20)
#define SEMITONE_PER_OCTAVE 					(12)
#define COMMA_PER_SEMITONE  					(4)

#define NUMBER_OF_NOTES     					(((CIS_ACTIVE_PIXELS_PER_LINE) * (CIS_ADC_OUT_LINES)) / CIS_IFFT_OVERSAMPLING_RATIO)

#endif // __CONFIG_H__

