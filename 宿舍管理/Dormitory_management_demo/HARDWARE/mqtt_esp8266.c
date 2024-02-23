#include "config.h"
#include "mqtt_esp8266.h"
//电闸Id
const char switch_elecId[10] = "Elec-001";
//水闸Id
const char sluice_waterId[15]= " Sluice-002";

void MQTT_Topic(void)
{
    usart_send_string(USART2,(u8*)"AT+MQTTSUB=0,\"control_sluice\",1\r\n");
    delay_Ms(2000);
    usart_send_string(USART2,(u8*)"AT+MQTTSUB=0,\"control_switch\",1\r\n");
    delay_Ms(2000);
    usart_send_string(USART2,(u8*)"AT+MQTTSUB=0,\"monitor\",1\r\n");
    delay_Ms(2000);
}
void Esp8266_MQTT_Init(void)
{
    init_usart2(115200);
    usart_send_string(USART2,(u8*)"\r\nAT+CWMODE=1\r\n");
    delay_Ms(2000);
    usart_send_string(USART2,(u8*)"AT+MQTTUSERCFG=0,1,\"0\",\"cyfs\",\"123456\",0,0,\"\"\r\n");
    delay_Ms(2000);
    usart_send_string(USART2,(u8*)"AT+MQTTCONN=0,\"120.26.241.86\",1883,1\r\n");
    delay_Ms(2000);
    MQTT_Topic();

}

char topic[20];
char Data[256];
int Data_lenght;
int switch_state = 0;
int sluice_state = 0;
void Esp_Read(char *data)
{
    printf("%s\r\n",data);

    if(!strstr(data,(char*)"MQTTSUBRECV"))return;
    sscanf(data,"+MQTTSUBRECV:0,\"%[^\"]\",%d,%[^}]",topic,&Data_lenght,Data);
    Data[Data_lenght - 1]='}';
    Data[Data_lenght]='\0';

    cJSON *root = cJSON_Parse((const char*)Data);
    if(root == NULL)
    {
        printf("JSON Error\r\n");
        return;
    }
    printf("%s\r\n",topic);
    if(strcmp(topic,(char*)"control_switch") == 0)
    {
        //控制电闸
        cJSON * elecId = cJSON_GetObjectItem(root,"elecId");
        cJSON * state = cJSON_GetObjectItem(root,"state");
        if(strcmp(elecId->valuestring,switch_elecId) == 0)
        {
            printf("接收成功\r\n");
            switch_state = state->valueint;
        }

    }
    else if(strcmp(topic,(char*)"control_sluice") == 0)
    {
        //控制水闸
        printf("处理 control_sluice\r\n");
        cJSON * waterId = cJSON_GetObjectItem(root,"waterId");
        cJSON * state = cJSON_GetObjectItem(root,"state");
        printf("%s\r\n",waterId->valuestring);
        if(strcmp(waterId->valuestring,sluice_waterId) == 0)
        {
            printf("接收成功\r\n");
            sluice_state = state->valueint;
        }
    }
    else if(strcmp(topic,(char*)"monitor") == 0)
    {
        //发送数据
        printf("处理 monitor\r\n");
        cJSON * request = cJSON_GetObjectItem(root,"request");
        if(request == NULL) return;
        printf("%s\r\n",request->valuestring);
        if(strcmp(request->valuestring,"get_data") == 0)
        {
            printf("接收成功\r\n");   
            MQTT_Send_Monitor();
        }
    }
    // printf("%d\r\n",sluice_state);
    cJSON_Delete(root);
}
const char *name = "吴艺彬";
void MQTT_Send_Door_Open(void)
{

    // 创建一个 cJSON 对象，表示 JSON 对象
    cJSON *root = cJSON_CreateObject();

    // 添加字符串字段
    cJSON_AddStringToObject(root, "name",name);
    cJSON_AddStringToObject(root, "machine","CK-001");
    cJSON_AddStringToObject(root, "accessld","card-01");
    // 将 cJSON 对象转换为 JSON 字符串
    char *jsonString = cJSON_Print(root);

    char send[50];;
    sprintf(send,"\r\nAT+MQTTPUBRAW=0,\"access_control\",%d,0,0\r\n",strlen(jsonString));
    usart_send_string(USART2,(u8*)send);
    delay_Ms(500);
    usart_send_string(USART2,(u8*)jsonString);
    // 释放 cJSON 对象和 JSON 字符串的内存
    //printf("%s",jsonString);
    cJSON_Delete(root);
    free(jsonString);
}

void MQTT_Send_Monitor(void)
{

    // 创建一个 cJSON 对象，表示 JSON 对象
    cJSON *root = cJSON_CreateObject();

    // 添加字符串字段
    cJSON_AddStringToObject(root, "dormitoryId","荷苑1号楼");
    cJSON_AddStringToObject(root, "roomId","荷苑1号楼1层101房间");
    cJSON_AddStringToObject(root, "mntid","MNT-001");
    cJSON_AddNumberToObject(root,"temp",rec_data[2]);
    cJSON_AddNumberToObject(root,"hum",rec_data[0]);
    
    
    // 将 cJSON 对象转换为 JSON 字符串
    char *jsonString = cJSON_Print(root);

    char send[50];;
    sprintf(send,"\r\nAT+MQTTPUBRAW=0,\"monitor\",%d,0,0\r\n",strlen(jsonString));
    usart_send_string(USART2,(u8*)send);
    delay_Ms(500);
    usart_send_string(USART2,(u8*)jsonString);
    // 释放 cJSON 对象和 JSON 字符串的内存
    //printf("%s",jsonString);
    cJSON_Delete(root);
    free(jsonString);
}
