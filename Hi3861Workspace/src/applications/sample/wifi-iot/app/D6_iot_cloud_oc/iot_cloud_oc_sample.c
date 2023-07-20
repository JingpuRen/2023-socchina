
/*
 * Copyright (c) 2020 Nanjing Xiaoxiongpai Intelligent Technology Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"

#include "hi_uart.h"
#include "hi_io.h"

#include "wifi_connect.h"
#include "lwip/sockets.h"

#include "oc_mqtt.h"
#include "E53_IA1.h"

#define MSGQUEUE_OBJECTS 16 // number of Message Queue Objects
#define UART_BUFF_SIZE 1024     //接收缓冲大小
#define UART_TIMEOUT_MS 20      //接收超时时间

typedef struct
{ // object data type
    char *Buf;
    uint8_t Idx;
} MSGQUEUE_OBJ_t;

MSGQUEUE_OBJ_t msg;
osMessageQueueId_t mid_MsgQueue; // message queue id

#define CLIENT_ID "63418ee006cae4010b4c9198_20222023_0_0_2023031213"
#define USERNAME "63418ee006cae4010b4c9198_20222023"
#define PASSWORD "f7b49d0402d81d15bb7de9e91a183cc637f81b29dc4804b5038fd1ec5ee7d597"
#define UART_BUFF_SIZE 1024

typedef enum
{
    en_msg_cmd = 0,
    en_msg_report,
} en_msg_type_t;

typedef struct
{
    char *request_id;
    char *payload;
} cmd_t;

typedef struct
{
    int lum;
    int temp;
    int hum;
    int id;
} report_t;

typedef struct
{
    en_msg_type_t msg_type;
    union
    {
        cmd_t cmd;
        report_t report;
    } msg;
} app_msg_t;

typedef struct
{
    int connected;
    int led;
    int motor;
} app_cb_t;
static app_cb_t g_app_cb;

//向外提供的发送接口
void uart1_send(uint8_t *buf,uint16_t len)
{
    hi_uart_write(HI_UART_IDX_1, (unsigned char *)buf, len);
}
//接收处理函数
void uart1_rxproc(uint8_t *buf,uint16_t len)
{
    uart1_send((unsigned char *)buf, len);
    printf("Uart1 read data len:%d\r\n", len);
}


//串口接收，无数据时阻塞，有数据时收完一帧或者收到最大值返回
uint16_t uart1_recv(uint8_t *buf,uint16_t len)
{
    uint16_t rxlen=0;
    uint16_t ret=0;
    while(len-rxlen>0){
        ret=hi_uart_read_timeout(HI_UART_IDX_1, buf+rxlen, len-rxlen,UART_TIMEOUT_MS);
	if(ret==0&&rxlen!=0){
            return rxlen;
        }
        else{
            rxlen+=ret;
        }
    }
    return rxlen;
}

static void deal_report_msg(report_t *report)
{
    oc_mqtt_profile_service_t service;
    oc_mqtt_profile_kv_t temperature;
    oc_mqtt_profile_kv_t humidity;
    oc_mqtt_profile_kv_t luminance;
    oc_mqtt_profile_kv_t led;
    oc_mqtt_profile_kv_t motor;
    oc_mqtt_profile_kv_t name;

    service.event_time = NULL;
    service.service_id = "Agriculture";
    service.service_property = &temperature;
    service.nxt = NULL;

    temperature.key = "Temperature";
    temperature.value = &report->temp;
    temperature.type = EN_OC_MQTT_PROFILE_VALUE_INT;
    temperature.nxt = &humidity;

    humidity.key = "Humidity";
    humidity.value = &report->hum;
    humidity.type = EN_OC_MQTT_PROFILE_VALUE_INT;
    humidity.nxt = &luminance;

    luminance.key = "Luminance";
    luminance.value = &report->lum;
    luminance.type = EN_OC_MQTT_PROFILE_VALUE_INT;
    luminance.nxt = &led;

    led.key = "LightStatus";
    led.value = g_app_cb.led ? "ON" : "OFF";
    led.type = EN_OC_MQTT_PROFILE_VALUE_STRING;
    led.nxt = &motor;

    motor.key = "MotorStatus";
    motor.value = g_app_cb.motor ? "ON" : "OFF";
    motor.type = EN_OC_MQTT_PROFILE_VALUE_STRING;
    motor.nxt = &name;

    name.key = "Name";
    name.value = &report->id;
    name.type = EN_OC_MQTT_PROFILE_VALUE_INT;
    name.nxt = NULL;
    
    oc_mqtt_profile_propertyreport(USERNAME, &service);
    return;
}

void oc_cmd_rsp_cb(uint8_t *recv_data, size_t recv_size, uint8_t **resp_data, size_t *resp_size)
{
    app_msg_t *app_msg;

    int ret = 0;
    app_msg = malloc(sizeof(app_msg_t));
    app_msg->msg_type = en_msg_cmd;
    app_msg->msg.cmd.payload = (char *)recv_data;

    printf("recv data is %.*s\n", recv_size, recv_data);
    ret = osMessageQueuePut(mid_MsgQueue, &app_msg, 0U, 0U);
    if (ret != 0)
    {
        free(recv_data);
    }
    *resp_data = NULL;
    *resp_size = 0;
}


///< COMMAND DEAL
#include <cJSON.h>
static void deal_cmd_msg(cmd_t *cmd)
{
    cJSON *obj_root;
    cJSON *obj_cmdname;
    cJSON *obj_paras;
    cJSON *obj_para;

    int cmdret = 1;
    oc_mqtt_profile_cmdresp_t cmdresp;
    obj_root = cJSON_Parse(cmd->payload);
    if (NULL == obj_root)
    {
        goto EXIT_JSONPARSE;
    }

    obj_cmdname = cJSON_GetObjectItem(obj_root, "command_name");
    if (NULL == obj_cmdname)
    {
        goto EXIT_CMDOBJ;
    }
    if (0 == strcmp(cJSON_GetStringValue(obj_cmdname), "Agriculture_Control_light"))
    {
        obj_paras = cJSON_GetObjectItem(obj_root, "paras");
        if (NULL == obj_paras)
        {
            goto EXIT_OBJPARAS;
        }
        obj_para = cJSON_GetObjectItem(obj_paras, "Light");
        if (NULL == obj_para)
        {
            goto EXIT_OBJPARA;
        }
        ///< operate the LED here
        if (0 == strcmp(cJSON_GetStringValue(obj_para), "ON"))
        {
            g_app_cb.led = 1;
            Light_StatusSet(ON);
            printf("Light On!");
        }
        else
        {
            g_app_cb.led = 0;
            Light_StatusSet(OFF);
            printf("Light Off!");
        }
        cmdret = 0;
    }
    else if (0 == strcmp(cJSON_GetStringValue(obj_cmdname), "Agriculture_Control_Motor"))
    {
        obj_paras = cJSON_GetObjectItem(obj_root, "Paras");
        if (NULL == obj_paras)
        {
            goto EXIT_OBJPARAS;
        }
        obj_para = cJSON_GetObjectItem(obj_paras, "Motor");
        if (NULL == obj_para)
        {
            goto EXIT_OBJPARA;
        }
        ///< operate the Motor here
        if (0 == strcmp(cJSON_GetStringValue(obj_para), "ON"))
        {
            g_app_cb.motor = 1;
            Motor_StatusSet(ON);
            printf("Motor On!");
        }
        else
        {
            g_app_cb.motor = 0;
            Motor_StatusSet(OFF);
            printf("Motor Off!");
        }
        cmdret = 0;
    }

EXIT_OBJPARA:
EXIT_OBJPARAS:
EXIT_CMDOBJ:
    cJSON_Delete(obj_root);
EXIT_JSONPARSE:
    ///< do the response
    cmdresp.paras = NULL;
    cmdresp.request_id = cmd->request_id;
    cmdresp.ret_code = cmdret;
    cmdresp.ret_name = NULL;
    (void)oc_mqtt_profile_cmdresp(NULL, &cmdresp);
    return;
}

static int task_main_entry(void)
{
    app_msg_t *app_msg;

    uint32_t ret = WifiConnect("Mate 50 Pro", "66666666");

    device_info_init(CLIENT_ID, USERNAME, PASSWORD);
    oc_mqtt_init();
    oc_set_cmd_rsp_cb(oc_cmd_rsp_cb);

    while (1)
    {
        app_msg = NULL;
        (void)osMessageQueueGet(mid_MsgQueue, (void **)&app_msg, NULL, 0U);
        if (NULL != app_msg)
        {
            switch (app_msg->msg_type)
            {
            case en_msg_cmd:
                deal_cmd_msg(&app_msg->msg.cmd);
                break;
            case en_msg_report:
                deal_report_msg(&app_msg->msg.report);
                break;
            

default:
                break;
            }
            free(app_msg);
        }
    }
    return 0;
}

static int task_sensor_entry(void)
{
    app_msg_t *app_msg;
     E53_IA1_Init();
   E53_IA1_Data_TypeDef data;
    unsigned char uart_buff[UART_BUFF_SIZE] = {0}; // max 1024
    uint32_t ret;
    uint16_t len;
    // const char *data = "Hello OpenHarmony !!!\n";
    const char *data = "1\n";
    hi_uart_attribute uart_attr = {
        .baud_rate = 115200,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 0,
    };

    //Initialize uart driver
    ret = hi_uart_init(HI_UART_IDX_1, &uart_attr, NULL);
   
    char ch = 'f';
    char* elem = &ch;
    
    while (1)
    {
      // 通过UART1 发送数据 Send data through UART1
        hi_uart_write(HI_UART_IDX_1, (unsigned char*)data, strlen(data));
         // 通过UART1 接收数据 Receive data through UART1
        len = hi_uart_read(HI_UART_IDX_1,uart_buff,UART_BUFF_SIZE);
        //处理数据
        if (len > 0) {
            // 把接收到的数据打印出来 Print the received data
            printf("Uart Read Data is: %s \r\n", uart_buff);
        }
        (*elem) = uart_buff[0];
        osDelay(2);
        E53_IA1_Read_Data(&data);
        app_msg = malloc(sizeof(app_msg_t));
        printf("SENSOR:lum:%.2f temp:%.2f hum:%.2f name:%.2f \r\n", data.Lux, data.Temperature, data.Humidity,(*elem) - '0');
        if (NULL != app_msg)
        {
            app_msg->msg_type = en_msg_report;
            app_msg->msg.report.hum = (int)data.Humidity;
            app_msg->msg.report.lum = (int)data.Lux;
            app_msg->msg.report.temp = (int)data.Temperature;
	    app_msg->msg.report.id = (*elem)  - '0';
            if (0 != osMessageQueuePut(mid_MsgQueue, &app_msg, 0U, 0U))
            {
                free(app_msg);
            }
        }
        sleep(3);
    }
    return 0;
}

static void OC_Demo(void)
{
    mid_MsgQueue = osMessageQueueNew(MSGQUEUE_OBJECTS, 10, NULL);
    if (mid_MsgQueue == NULL)
    {
        printf("Falied to create Message Queue!\n");
    }

    osThreadAttr_t attr;

    attr.name = "task_main_entry";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = 24;

    if (osThreadNew((osThreadFunc_t)task_main_entry, NULL, &attr) == NULL)
    {
        printf("Falied to create task_main_entry!\n");
    }
    attr.stack_size = 2048;
    attr.priority = 25;
    attr.name = "task_sensor_entry";
    if (osThreadNew((osThreadFunc_t)task_sensor_entry, NULL, &attr) == NULL)
    {
        printf("Falied to create task_sensor_entry!\n");
    }
}

APP_FEATURE_INIT(OC_Demo);