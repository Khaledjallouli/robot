/* JALLOULI
 * JOUANNIC
 *
 * */

#include "main.h"

// Déclaration des objets synchronisants !! Ne pas oublier de les créer
xSemaphoreHandle xSemaphore_superviseur = NULL;
xSemaphoreHandle xSemaphore_motor = NULL;
xSemaphoreHandle xSemaphore_capteur = NULL;
xSemaphoreHandle xSemaphore_asservssement = NULL;
xSemaphoreHandle xMutex_ecranLCD = 1;
xSemaphoreHandle xSemaphore_Camera = NULL;

xQueueHandle qSuperviseur = NULL;
xQueueHandle qMotor = NULL;
xQueueHandle qCapteur = NULL;
xQueueHandle qEcran = NULL;
xQueueHandle qZegbee = NULL;
xQueueHandle qCam = NULL;
xQueueHandle qAsserv = NULL;

#define to 310.0e-3
#define ti (0.1*to)
#define ki (5.0e-3)/ti
#define kp 0.01

//asserv
float ui_left=0;//hors boucle
int cde_left=100;
float ui_right=0;//hors boucle
int cde_right=100;
float cons_right=-300.0;
float cons_left=-300.0;

int varDefautDroite = 1000;
int varDefautGauche=1000;

int currentLeft = 100, currentRight = 100;
struct AMessage
{
	char command;
	int data;
};

extern uint8_t rec_buf[NB_CAR_TO_RECEIVE+1]; // caractere recu


//========================================================

static void task_superviseur( void *pvParameters )
{
	struct AMessage pxMessage;
	//pxMessage.command='a';
	pxMessage.data=10;
	vTaskDelay(1000);

	for (;;)
	{

		switch(rec_buf[0]){ // avec la liaison  serie on recupere cette valeur dans drv/drv_uart L 97
			case '1': // avancer, c'est nous qui ont choisi les valeurs
				cons_left= 1000;
				cons_right = 1000;
				break;
			case '2': // reculer
				cons_left= -1000;
				cons_right = -1000;
				break;
			case '3': //gauche
				cons_left= -500;
				cons_right = 500;
				break;
			case '4': // droite
				cons_left= 500;
				cons_right = -500;
				break;
			case '5': // stop
				cons_left= 0;
				cons_right = 0;
				break;
			case '6': // accelerate
				cons_left+= 500;
				cons_right += 500;
				break;
			case '7': // decelerate
				cons_left -= 500;
				cons_right-=500;
				break;
			default :
				break;
		}

		xQueueSend( qCapteur, ( void * ) &pxMessage,  portMAX_DELAY );
		xSemaphoreTake( xSemaphore_capteur, portMAX_DELAY );

		xQueueSend( qAsserv, ( void * ) &pxMessage,  portMAX_DELAY );
		xSemaphoreTake( xSemaphore_asservssement, portMAX_DELAY );
		
		xQueueSend( qMotor, ( void * ) &pxMessage,  portMAX_DELAY );
		xSemaphoreTake( xSemaphore_motor, portMAX_DELAY );

		xQueueSend( qCam, ( void * ) &pxMessage,  portMAX_DELAY );
		xSemaphoreTake( xSemaphore_Camera, portMAX_DELAY );

		//xQueueSend( qEcran, ( void * ) &pxMessage,  portMAX_DELAY );
			//	xSemaphoreTake( xSemaphore_ecranLCD, portMAX_DELAY );


		vTaskDelay(5);
	}
}

static void task_motor(void *pvParameters){
	struct AMessage pxRxedMessage;
	for (;;)
	{
		xQueueReceive( qMotor,  &( pxRxedMessage ) , portMAX_DELAY );
		cde_left+=1000;
		cde_right+=1000;
		motorLeft_SetDuty(cde_left);
		motorRight_SetDuty(cde_right);
		xSemaphoreGive( xSemaphore_motor );
	}
}

static void task_capteur(void *pvParameters){
	struct AMessage pxRxedMessage;
	int table[2];
	for (;;)
	{
		xQueueReceive( qCapteur,  &( pxRxedMessage ) , portMAX_DELAY );
		captDistIR_Get(table);
		int valBackLeft = captDistUS_Get(0xE0);
		int valBackRight = captDistUS_Get(0xE2);
		if((table[0]>= 2000)  ){
				//0 : gauche				
			cons_left= 0;
			cons_right = 0;
		}
		if(table[1]>=2000 ){
						//0 : gauche
					cons_left= 0;
					cons_right = 0;
				}

		if(((valBackLeft<=20) || (valBackRight<=20))){
			cons_left= 0;
			cons_right = 0;
		}

		xSemaphoreGive( xSemaphore_capteur );
	}
}

static void task_ecran(void *pvParameters){
	struct AMessage pxRxedMessage;
		for (;;)
		{
			xSemaphoreTake( xMutex_ecranLCD, portMAX_DELAY );

			//xQueueReceive( qEcran,  &( pxRxedMessage ) , portMAX_DELAY );
			switch(rec_buf[0]){ // avec la liaison  serie on recupere cette valeur dans drv/drv_uart L 97
				case '1': // avancer, c'est nous qui ont choisi les valeurs

					screenLCD_Write("Avance    ",10 ,0,0);
					break;
				case '2': // reculer
					screenLCD_Write("Recule    ",10 ,0,0);
					break;
				case '3': //gauche
					screenLCD_Write("Gauche    ",10 ,0,0);
					break;
				case '4': // droite
					screenLCD_Write("Droite    ",10 ,0,0);
					break;
				case '5': // stop
					screenLCD_Write("Arret     ",10 ,0,0);
					break;
				case '6': // accelerate
					screenLCD_Write("accelerate",10 ,0,0);
				break;
				case '7': // decelerate
					screenLCD_Write("decelerate",10 ,0,0);
				break;
				default :
					break;

			}
			xSemaphoreGive( xMutex_ecranLCD );

		}
}

static void task_asserv(void *pvParameters)
{
	struct AMessage pxRxedMessage;
	for (;;)
		{
			xQueueReceive(qAsserv, (void*)&pxRxedMessage, portMAX_DELAY);
			int speed_L = quadEncoder_GetSpeedL();
			//left
			float err_left=(cons_left-(float)speed_L);
			float up_left=kp*err_left;
			ui_left=ui_left+kp*ki*err_left;
			cde_left=up_left+ui_left+100;
			//right
			int speed_R = quadEncoder_GetSpeedR();
			float err_right=cons_right-(float)speed_R;
			float up_right=kp*err_right;
			ui_right=ui_right+kp*ki*err_right;
			cde_right=up_right+ui_right+100;
			xSemaphoreGive(xSemaphore_asservssement);
		}
}


static void task_cam( void *pvParameters )//camera
{
	uint16_t tabWH[2]={0,0};
	uint16_t tabXY[2]={0,0};
	int N=10;
	uint16_t valmoy_X=0;
	uint16_t valmoy_Y=0;
	int N_TIMES = 0;
	struct AMessage pxRxedMessage;
	for (;;)
	{
		xQueueReceive(qCam, &(pxRxedMessage), portMAX_DELAY);
		//vTaskDelay(2);


		if(N_TIMES==10)
		{
				for (int i=0; i<N ; i++)
				{
					pixyCam_Get( tabXY, tabWH);

					valmoy_X+=tabXY[0];
					valmoy_Y+=tabXY[1];
				}
		valmoy_X=valmoy_X/N;
		valmoy_Y=valmoy_Y/N;
		if(tabWH[0]>10 ){
			if(tabWH[1]>5 ){
				if(valmoy_X<160)
					{
						servoLow_Set(servoLow_Get()+1);
					}
				if(valmoy_X>160)
					{
						servoLow_Set(servoLow_Get()-1);
					}
				if(valmoy_Y>100)
					{
						servoHigh_Set(servoHigh_Get()+1);
					}
				if(valmoy_Y<100)
					{
						servoHigh_Set(servoHigh_Get()-1);
					}
			}
		}
		N_TIMES=0;
				}
				N_TIMES++;

		xSemaphoreGive(xSemaphore_Camera);
	}
}
//=========================================================
//	>>>>>>>>>>>>	MAIN	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//=========================================================

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	uart2_Init();			// CABLE
	uart6_Init();			// ZIGBEE
	i2c1_Init();
	spi1Init();
	pixyCam_Init();			// Caméra Pixy
	captDistIR_Init();		// Capteurs Infrarouge
	quadEncoder_Init();		// Encodeurs Incrémentaux
	motorCommand_Init();	// Commande des Hacheurs
	servoCommand_Init();	// Commande des Servomoteurs
	HAL_Delay(1000);
	motorLeft_SetDuty(1000);
	motorRight_SetDuty(1000);

 	xTaskCreate( task_superviseur, ( signed portCHAR * ) "task superviseur", 512 /* stack size */, NULL, tskIDLE_PRIORITY+6, NULL );
 	xTaskCreate( task_capteur, ( signed portCHAR * ) "task capteur", 512 /* stack size */, NULL, tskIDLE_PRIORITY+5, NULL );
 	xTaskCreate( task_asserv, ( signed portCHAR * ) "task asservissement", 512 /* stack size */, NULL, tskIDLE_PRIORITY+4, NULL );
 	xTaskCreate( task_motor, ( signed portCHAR * ) "task motor", 512 /* stack size */, NULL, tskIDLE_PRIORITY+3, NULL );
 	xTaskCreate( task_cam, ( signed portCHAR * ) "task cam", 512 /* stack size */, NULL, tskIDLE_PRIORITY+2, NULL );
	xTaskCreate( task_ecran, ( signed portCHAR * ) "task ecran", 512 /* stack size */, NULL, tskIDLE_PRIORITY+1, NULL );

	
	vSemaphoreCreateBinary(xSemaphore_superviseur);
	xSemaphoreTake( xSemaphore_superviseur, portMAX_DELAY );
	vSemaphoreCreateBinary(xSemaphore_capteur);
	xSemaphoreTake( xSemaphore_capteur, portMAX_DELAY );
	vSemaphoreCreateBinary(xSemaphore_asservssement);
	xSemaphoreTake( xSemaphore_asservssement, portMAX_DELAY );
	vSemaphoreCreateBinary(xSemaphore_motor);
	xSemaphoreTake( xSemaphore_motor, portMAX_DELAY );
	vSemaphoreCreateBinary(xSemaphore_Camera);
	xSemaphoreTake( xSemaphore_Camera, portMAX_DELAY );
	vSemaphoreCreateBinary(xMutex_ecranLCD);
	xSemaphoreTake( xMutex_ecranLCD, portMAX_DELAY );



	qCapteur = xQueueCreate( 1, sizeof(struct AMessage ) );
	qAsserv= xQueueCreate( 1, sizeof(struct AMessage ) );
	qMotor = xQueueCreate( 1, sizeof(struct AMessage ) );
	qCam = xQueueCreate( 1, sizeof(struct AMessage ) );
	//qEcran = xQueueCreate( 1, sizeof(struct AMessage ) );



	vTaskStartScheduler();
	return 0;
}

//=================================================================
// Called if stack overflow during execution
extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
		signed char *pcTaskName)
{
	//term_printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
	/* If the parameters have been corrupted then inspect pxCurrentTCB to
	 * identify which task has overflowed its stack.
	 */
	for (;;) {
	}
}
//=================================================================
//This function is called by FreeRTOS idle task
extern void vApplicationIdleHook(void)
{
}
//=================================================================
// brief This function is called by FreeRTOS each tick
extern void vApplicationTickHook(void)
{
//	HAL_IncTick();
}





