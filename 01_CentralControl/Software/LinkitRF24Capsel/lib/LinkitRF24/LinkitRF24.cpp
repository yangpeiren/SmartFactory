#include <LinkitRF24.h>

RF24 radio(7,8);
RF24Network network(radio);
RF24Mesh mesh(radio,network);
RF24EthernetClass RF24Ethernet(radio,network,mesh);

EthernetClient ethClient;
PubSubClient client(ethClient);

IPAddress ip(10,10,2,8);//mesh.getIPAdress()
IPAddress gateway(10,10,2,2); //Specify the gateway in case different from the server
IPAddress server(10,10,2,2);

const uint16_t MAX_CONNECTION_TRIES = 3;
const uint16_t DELAY_TIME_CONNECTION_TRY = 350; //[ms]
bool SYS_SUBSCRIBED = false;

void LinkitRF24::setup(MQTT_CALLBACK_SIGNATURE,char *clID){
  SYS_SUBSCRIBED = false;
  clientID = clID;
  client.setServer(server, 1883);
  client.setCallback(callback);
  Ethernet.begin(ip);
  Ethernet.set_gateway(gateway);
  clientID[13] = ip[3] + 48; //Convert last octet of IP to ascii & use in clientID
  // //check for timeout!

  while(!buildConnection()){
    delay(250);
    // while(!meshBegins());
    // //check for timeout
    // while(!connectMqtt());


//
// Serial.print("LinkitRF24 ready");
//
// Serial.print("Subscribed to SYS");
//
// clientLoop();
// Serial.print("Client Loop");
}
//publish("smartfactory/fts","hello world");

}

bool LinkitRF24::buildConnection(){
  uint16_t cnt =0;
  while (cnt < MAX_CONNECTION_TRIES) {

    if(!meshBegins() || !connectMqtt())SYS_SUBSCRIBED = false;
    //check for timeout
client.connect(clientID);
    delay(DELAY_TIME_CONNECTION_TRY);
    if(mqttConnected()){
      if(!SYS_SUBSCRIBED){
        client.subscribe("$SYS/#",1);//not nice
        Serial.println("subscribed to SYS");
        SYS_SUBSCRIBED = true;
      }
      client.subscribe("smartfactory/#",1);
      Serial.println("subscribed");
      client.loop();
      return true;
    }

    cnt++;
}
return false;
}

bool LinkitRF24::meshBegins(){
  return mesh.begin(97);
}

bool LinkitRF24::mqttConnected(){
  return client.connected();
}

bool LinkitRF24::connectMqtt(){
  return client.connect(clientID);
}

void LinkitRF24::publish(const char* topic , const char* payload){
  if(mqttConnected()){
    client.publish(topic,payload);
  }else{
    //try again
    if(buildConnection()){
    client.publish(topic,payload);
  }else{
    //Pech gehabt
  }

  }
}

void LinkitRF24::subscribe(const char* topic){
  client.subscribe(topic);
}
int LinkitRF24::clientState(){
  return client.state();
}

bool LinkitRF24::clientLoop(){
  return client.loop();
}
