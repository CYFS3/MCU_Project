#ifndef __MQTT_ESP8266_H__
#define __MQTT_ESP8266_H__
void Esp8266_MQTT_Init(void);
void Esp_Read(char *data);
void MQTT_Send_Door_Open(void);
void MQTT_Send_Monitor(void);
void MQTT_Send_Water(char State);
void MQTT_Send_LED(char State);
void MQTT_Send_monitor(int temp,int hum);
extern char switch_state;
extern char sluice_state;
#endif
