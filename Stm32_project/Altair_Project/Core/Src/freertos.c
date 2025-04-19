/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "dht.h"
#include "adc.h"
#include "sd_card.h"
#include "date_time.h"
#include "config.h"
#include "system_state.h"
#include "message_data.h"
#include "event_logger.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

osMessageQueueId_t messageQueueHandle;
osMessageQueueId_t eventQueueHandle;
osEventFlagsId_t commEventFlags;
MessageData message = {0};
DateTime* g_dt;
uint32_t buffer[2];
uint32_t length = 2;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_LOG_DAYS 8
#define COMM_EVENT_RX_COMPLETE  0x01
#define COMM_EVENT_KEEP_ALIVE   0x02

static char currentLogFile[20] = "";
static char logFiles[MAX_LOG_DAYS][20];
static int logFileCount = 0;

void DHT_Task(void *argument);
void SampleData();
void ControllerTask(void* argument);
void LoggerTask(void *argument);
void EventTask(void *argument);
void CommTask(void *argument);
void KeepAliveTask(void *argument);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern DHT11_Data data;
extern RTC_HandleTypeDef hrtc;
extern TIM_HandleTypeDef htim6;

osTimerId_t timID;
uint32_t delay = 5000;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

osMutexId_t sdMutexHandle;
const osMutexAttr_t sdMutex_attributes = {
  .name = "sdMutex"
};

osThreadId_t dhtTaskHandle;
const osThreadAttr_t dhtTask_attributes = {
  .name = "dhtTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t controllerTaskHandle;
const osThreadAttr_t controllerTask_attributes = {
  .name = "controllerTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t loggerTaskHandle;
const osThreadAttr_t loggerTask_attributes = {
  .name = "loggerTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t eventTaskHandle;
const osThreadAttr_t eventTask_attributes = {
  .name = "eventTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};

osThreadId_t commTaskHandle;
const osThreadAttr_t commTask_attributes = {
  .name = "commTask",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t keepAliveTaskHandle;
const osThreadAttr_t keepAliveTask_attributes = {
  .name = "keepAliveTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern UART_HandleTypeDef huart2;
void ParseCommand(const char* cmd);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	timID = osTimerNew(SampleData, osTimerPeriodic, NULL, NULL);
	osTimerStart(timID, delay);
	HAL_TIM_Base_Start(&htim6);
	DHT_Init(GPIOB, GPIO_PIN_5, &htim6);
	SD_Init();
	g_dt = DateTimeCreate(&hrtc);
	HAL_UART_Receive_IT(&huart2, uartRxBuffer, 1);
	Config_Init();
	messageQueueHandle = osMessageQueueNew(10, sizeof(MessageData), NULL);
	eventQueueHandle = osMessageQueueNew(10, sizeof(SystemEvent), NULL);
	commEventFlags = osEventFlagsNew(NULL);
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
	sdMutexHandle = osMutexNew(&sdMutex_attributes);
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  dhtTaskHandle = osThreadNew(DHT_Task, NULL, &dhtTask_attributes);
  controllerTaskHandle = osThreadNew(ControllerTask, NULL, &controllerTask_attributes);
  loggerTaskHandle = osThreadNew(LoggerTask, NULL, &loggerTask_attributes);
  eventTaskHandle = osThreadNew(EventTask, NULL, &eventTask_attributes);
  commTaskHandle = osThreadNew(CommTask, NULL, &commTask_attributes);
  keepAliveTaskHandle = osThreadNew(KeepAliveTask, NULL, &keepAliveTask_attributes);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */

  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void SampleData()
{

	xTaskNotifyGive(dhtTaskHandle);

	HAL_ADC_Start_DMA(&hadc1, buffer, length);

	printf("Temperature: %d.%d°C, Humidity: %d.%d%%, Potent: %d.%3dV, Light: %lu%%\r\n",
									message.temperature_int,
									message.temperature_dec,
									message.humidity_int,
									message.humidity_dec,
									message.potent_int,
									message.potent_dec,
									message.light
									);

	xTaskNotifyGive(controllerTaskHandle);
}

void DHT_Task(void *argument)
{
	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if (DHT11_ReadData(&dht, &data) == 0)
		{
			message.temperature_int = data.temperature_int;
			message.temperature_dec = data.temperature_dec;
			message.humidity_int = data.humidity_int;
			message.humidity_dec = data.humidity_dec;
		}
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc->Instance == ADC1) {
		HAL_ADC_Stop_DMA(&hadc1);

		uint16_t integral = buffer[0] / 1000;
		uint16_t fractional = buffer[0] % 1000;
		uint32_t light_value = (buffer[1] * 100) / 4096;

		message.potent_int = integral;
		message.potent_dec = fractional;
		message.light = light_value;
	}
}

void ControllerTask(void* argument)
{
	MessageData msgCopy;
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);

	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		msgCopy = message;

		DateTimeGet(g_dt);

		msgCopy.time = g_dt->time;
		msgCopy.date = g_dt->date;

		if (SystemState_Update(&msgCopy, Config_Get())) {

			printf("System mode changed!\r\n");
		}

		osStatus_t status = osMessageQueuePut(messageQueueHandle, &msgCopy, 0, 0);
		if (status == osOK) {

		} else {
		    printf("FAILED to queue message! Code: %d\r\n", status);
		}

		xTaskNotifyGive(loggerTaskHandle);

	}
}

void LoggerTask(void *argument)
{
    MessageData receivedMsg;
    char buffer[128];

    while (1)
    {
    	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (osMessageQueueGet(messageQueueHandle, &receivedMsg, NULL, osWaitForever) == osOK)
        {
        	SystemConfig* cfg = Config_Get();

        	printf("Thresholds: Temp %d–%d, Humidity > %d, Light > %d, Voltage > %.2f\r\n",
        	       cfg->temp_min,
        	       cfg->temp_max,
        	       cfg->humidity_min,
        	       cfg->light_min,
        	       cfg->voltage_min);

            char filename[20];

            if (receivedMsg.date.year == 0 || receivedMsg.date.month == 0 || receivedMsg.date.day == 0)
            {
                strcpy(filename, "fallback.TXT");
            }
            else
            {
                snprintf(filename, sizeof(filename), "%04d%02d%02d.TXT",
                         receivedMsg.date.year + 2000,
                         receivedMsg.date.month,
                         receivedMsg.date.day);
            }

            if (strcmp(currentLogFile, filename) != 0)
            {
                strcpy(currentLogFile, filename);

                if (logFileCount < MAX_LOG_DAYS)
                {
                    strcpy(logFiles[logFileCount++], filename);
                }
                else
                {
                    f_unlink(logFiles[0]);
                    for (int i = 1; i < MAX_LOG_DAYS; ++i)
                    {
                        strcpy(logFiles[i - 1], logFiles[i]);
                    }
                    strcpy(logFiles[MAX_LOG_DAYS - 1], filename);
                }

                printf("New log file: %s\r\n", filename);
            }

            snprintf(buffer, sizeof(buffer),
                     "%02d-%02d-%02d %02d:%02d:%02d, %d.%d°C, %d.%d%%, %d.%03dV, %lu%%\r\n",
                     receivedMsg.date.year + 2000,
                     receivedMsg.date.month,
                     receivedMsg.date.day,
                     receivedMsg.time.hours,
                     receivedMsg.time.minutes,
                     receivedMsg.time.seconds,
                     receivedMsg.temperature_int,
                     receivedMsg.temperature_dec,
                     receivedMsg.humidity_int,
                     receivedMsg.humidity_dec,
                     receivedMsg.potent_int,
                     receivedMsg.potent_dec,
                     receivedMsg.light);

            SD_AppendToFile(filename, buffer);
            printf("LOGGED: %s", buffer);
        }
    }
}

const char* EventTypeToString(EventType type) {
    switch (type) {
        case EVENT_MODE_CHANGED: return "Mode Changed";
        case EVENT_CONFIG_UPDATED: return "Config Updated";
        default: return "Unknown Event";
    }
}

void EventTask(void *argument)
{
    SystemEvent event;
    char buffer[128];

    while (1)
    {
        if (osMessageQueueGet(eventQueueHandle, &event, NULL, osWaitForever) == osOK)
        {
            snprintf(buffer, sizeof(buffer),
                     "%02d-%02d-%02d %02d:%02d:%02d - EVENT: %s (%d → %d)\r\n",
                     event.date.year + 2000,
                     event.date.month,
                     event.date.day,
                     event.time.hours,
                     event.time.minutes,
                     event.time.seconds,
                     EventTypeToString(event.type),
                     event.old_mode,
                     event.new_mode);

            SD_AppendToFile("events.TXT", buffer);
            printf("LOGGED EVENT: %s", buffer);
        }
    }
}

void CommTask(void *argument)
{
    while (1)
    {
        uint32_t flags = osEventFlagsWait(commEventFlags,
                                          COMM_EVENT_RX_COMPLETE | COMM_EVENT_KEEP_ALIVE,
                                          osFlagsWaitAny,
                                          osWaitForever);

        if (flags & COMM_EVENT_RX_COMPLETE)
        {
            printf("Command complete: %s\r\n", commandBuffer);
            ParseCommand_New(commandBuffer);
        }

        if (flags & COMM_EVENT_KEEP_ALIVE)
        {
            DateTimeGet(g_dt);
            SystemMode mode = SystemState_Get();

            printf("KEEP ALIVE - %04d-%02d-%02d %02d:%02d:%02d | Mode: %d\r\n",
                   g_dt->date.year + 2000,
                   g_dt->date.month,
                   g_dt->date.day,
                   g_dt->time.hours,
                   g_dt->time.minutes,
                   g_dt->time.seconds,
                   mode);
        }
    }
}


void KeepAliveTask(void *argument)
{
    while (1)
    {
        osDelay(6000);

        osEventFlagsSet(commEventFlags, COMM_EVENT_KEEP_ALIVE);
    }
}


/* USER CODE END Application */

