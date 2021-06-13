/**
 ******************************************************************************
 * @file           : udp_server.h
 * @brief          : 5 key keybord driver
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UDP_SERVER_H__
#define __UDP_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void udp_serverInit(void);
void udp_serverReceiveImage(int32_t *image_buff);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__UDP_SERVER_H__*/
