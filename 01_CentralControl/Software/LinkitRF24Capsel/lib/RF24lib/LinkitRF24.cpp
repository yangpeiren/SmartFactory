#include <LinkitRF24.h>

RF24 radio(7,8);
RF24Network network(radio);
RF24Mesh mesh(radio,network);
RF24EthernetClass RF24Ethernet(radio,network,mesh);

EthernetClient ethClient;
PubSubClient client(ethClient);

IPAddress ip(10,10,2,8);
IPAddress gateway(10,10,2,2); //Specify the gateway in case different from the server
IPAddress server(10,10,2,2);

void LinkitRF24::setup(MQTT_CALLBACK_SIGNATURE,char *clID){
  clientID = clID;
  client.setServer(server, 1883);
    // client.setCallback(callback);
  Ethernet.begin(ip);
  Ethernet.set_gateway(gateway);
  //clientID[13] = ip[3] + 48; //Convert last octet of IP to ascii & use in clientID
  // //check for timeout!
  // while(!meshBegins());
  // //check for timeout
  // while(!connectMqtt());
  //
  // Serial.print("LinkitRF24 ready");
  //
  // client.subscribe("SYS/#");
  // Serial.print("Subscribed to SYS");
  //
  // clientLoop();
   Serial.print("Client Loop");

}

bool LinkitRF24::meshBegins(){
  bool ret = false;
  ret = mesh.begin(97);
  return ret;
}

bool LinkitRF24::mqttConnected(){
  // Serial.println("Is MQTT connected?");
  return client.connected();
}

bool LinkitRF24::connectMqtt(){
  bool ret = false;
  ret = client.connect({"arduinoClient"});
  return ret;
}

void LinkitRF24::publish(const char* topic , const char* payload){

  client.publish(topic,payload);
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
