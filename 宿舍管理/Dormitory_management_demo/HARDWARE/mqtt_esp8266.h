#ifndef __MQTT_ESP8266_H__
#define __MQTT_ESP8266_H__
void Esp8266_MQTT_Init(void);
void Esp_Read(char *data);
void MQTT_Send_Door_Open(void);
void MQTT_Send_Monitor(void);
extern int switch_state;
extern int sluice_state;
#endif
