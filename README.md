## Fogwing-mqtt-client-c-lang (windows & linux)

**Note:-** These SDKs are currently in preview and are subject to change.

### Pre-requisites:
- [MQTTClient.h](https://github.com/eclipse/paho.mqtt.c)
- [json.h](https://github.com/json-c/json-c)

### Step: 1
- [Setup C/C++ IDE](https://visualstudio.microsoft.com/).

### Step: 2
- [Install vcpkg manager](https://vcpkg.io/en/getting-started.html) and above mentioned libraries.

### Step: 3
- Download the [fw_mqtt_conn.c](https://github.com/factana/fogwing-mqtt-connector-c-lang/blob/main/fw_mqtt_conn.c).

### Step: 4
- Enter the [Fogwing](https://portal.fogwing.net/) IoTHub credentials.

### Step: 5
- Create build and run the client.

**Note:-** Provided everything goes in line with the above mentioned
           instructions,you will be able to see a message that reads 
           **successfully published** in command line.

### Step: 6
 
- Now you are ready to analyze your data at [Fogwing Platform](https://portal.fogwing.net/) portal,
you can check all the data within the data storage in the portal.
