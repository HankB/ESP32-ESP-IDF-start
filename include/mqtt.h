#ifndef MQTT_H
#define MQTT_H
//Stuff shared between mqtt.c and other C files

void mqtt_app_start(void);
void mqtt_publish(const char* topic, const char* payload);

#endif // MQTT_H