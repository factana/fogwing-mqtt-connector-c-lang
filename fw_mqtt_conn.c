#include "MQTTClient.h"
#include <time.h>
#include <json.h>
    
#define HOST                "iothub.fogwing.net:1883"
#define CLIENTID            "Enter Fogwing IoTHub client id"
#define TOPIC               "Enter Fogwing IoTHub publish topic"
#define QOS                 1
#define TIMEOUT             10000L
#define USERNAME            "Enter Fogwing IoTHub username"
#define PWD                 "Enter Fogwing IoTHub password"
#define dataIntervlSec      60  //Configure data interval 


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}


int randint(int lower, int upper,
    int count)
{
    int i, num;
    for (i = 0; i < count; i++) {
        num = (rand() % (upper - lower + 1)) + lower;
    }
    return num;

}


int roundNo(double num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}


int main(int argc, char* argv[])

{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, HOST, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password = PWD;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
   
    while(1) {

        /* Sample payload*/
        float temperature = randint(250, 300, 1) / 10.0;
        float humidity = randint(600, 700, 1) / 10.0;
        
        json_object* jobj = json_object_new_object();

        /*Creating a json integer*/
        json_object* jtemp = json_object_new_double(roundNo(temperature));

        /*Creating a json integer*/
        json_object* jhumi = json_object_new_double(roundNo(humidity));

        /*Form the json object*/
        /*Each of these is like a key value pair*/
        json_object_object_add(jobj, "temperature", jtemp);
        json_object_object_add(jobj, "humidity", jhumi);

        char* PAYLOAD = json_object_to_json_string(jobj);
        pubmsg.payload = PAYLOAD;
        pubmsg.payloadlen = strlen(PAYLOAD);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        
        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        printf("Fogwing-IoTHub: Waiting for up to %d seconds for publication of %s\n",
            (int)(TIMEOUT / 1000), PAYLOAD);
        rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
        printf("Fogwing-IoTHub: Successfully published on topic %s with delivery token: %d \n", TOPIC, token);

        delay(dataIntervlSec);
    }
       
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return rc;
}