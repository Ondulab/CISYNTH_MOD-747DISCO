/**
 ******************************************************************************
 * @file           : udp_serveur.c
 * @brief          : sss udp server
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "config.h"

#include "arm_math.h"

#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/
#include "udp_server.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define UDP_BUFFER_SIZE			((CIS_PIXELS_NB + UDP_HEADER_SIZE) * 2)

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
int32_t udp_imageData[UDP_BUFFER_SIZE] = {0};
int32_t multiplier[CIS_PIXELS_NB] = {2};
struct udp_pcb *upcb;

/* Private function prototypes -----------------------------------------------*/
void udp_serverReceiveCallback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  Initialize the server application.
 * @param  None
 * @retval None
 */
void udp_serverInit(void)
{
	printf("-------- UDP SERVER INIT ------\n");
	printf("-------------------------------\n");

	struct udp_pcb *upcb;
	err_t err;

	/* Create a new UDP control block  */
	upcb = udp_new();

	if (upcb)
	{
		/* Bind the upcb to the UDP_PORT port */
		/* Using IP_ADDR_ANY allow the upcb to be used by any local interface */
		err = udp_bind(upcb, IP_ADDR_ANY, UDP_SERVER_PORT);

		if(err == ERR_OK)
		{
			/* Set a receive callback for the upcb */
			udp_recv(upcb, udp_serverReceiveCallback, NULL);
		}
		else
		{
			udp_remove(upcb);
		}
	}
}

/**
 * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
 * @param arg user supplied argument (udp_pcb.recv_arg)
 * @param pcb the udp_pcb which received data
 * @param p the packet buffer that was received
 * @param addr the remote IP address from which the packet was received
 * @param port the remote port from which the packet was received
 * @retval None
 */
void udp_serverReceiveCallback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	struct pbuf *p_tx;
	static int32_t ptr_position = 0;

	/* allocate pbuf from RAM*/
	p_tx = pbuf_alloc(PBUF_TRANSPORT,p->len, PBUF_RAM);

	if(p_tx != NULL)
	{
		pbuf_take(p_tx, (char*)p->payload, p->len);

		if ((ptr_position + (p->len / 4)) > UDP_BUFFER_SIZE - 1)
		{
			ptr_position = 0;
		}

		arm_copy_q31((int32_t*)p->payload, &udp_imageData[ptr_position], p->len / 4);

		ptr_position += (p->len / 4);

		/* Free the p_tx buffer */
		pbuf_free(p_tx);

		/* Free the p buffer */
		pbuf_free(p);
	}
}

uint32_t greyScale(uint32_t rbg888) {
	static uint32_t grey = 0;

    uint32_t r = rbg888 		& 0xFF; // XXXXX___________
    uint32_t g = (rbg888 >> 8) 	& 0xFF; // ___________XXXXX
    uint32_t b = (rbg888 >> 12) & 0xFF; // _____XXXXXX_____

    grey = (r * 299 + g * 587 + b * 114);
    return grey >>= 2;
}


void udp_serverReceiveImage(volatile int32_t *image_buff)
{
	int32_t maxPix = 0;
	uint32_t maxPixPosition = 0;

	SCB_CleanDCache_by_Addr((uint32_t *)udp_imageData, UDP_BUFFER_SIZE * 4);
	arm_max_q31(udp_imageData, UDP_BUFFER_SIZE / 2, &maxPix, &maxPixPosition);
	if(maxPix == IMAGE_HEADER)
	{
		arm_copy_q31(&udp_imageData[maxPixPosition + UDP_HEADER_SIZE], (int32_t *)image_buff, CIS_PIXELS_NB);
		for (int i = 0; i < CIS_PIXELS_NB; i++)
		{
			image_buff[i] = greyScale(image_buff[i]) / 2;
		}
	}
}

/**
 * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
 * @param arg user supplied argument (udp_pcb.recv_arg)
 * @param pcb the udp_pcb which received data
 * @param p the packet buffer that was received
 * @param addr the remote IP address from which the packet was received
 * @param port the remote port from which the packet was received
 * @retval None
 */
void udp_clientSendImage(int32_t *image_buff)
{
	struct pbuf *p;

	/* allocate pbuf from pool*/
	p = pbuf_alloc(PBUF_TRANSPORT, (CIS_PIXELS_NB + UDP_HEADER_SIZE) * sizeof(uint32_t), PBUF_RAM);

	if (p != NULL)
	{
		/* copy data to pbuf */
		pbuf_take(p, (char*)image_buff, (CIS_PIXELS_NB + UDP_HEADER_SIZE) * sizeof(uint32_t));

		/* send udp data */
		udp_send(upcb, p);

		/* free pbuf */
		pbuf_free(p);
	}
}
