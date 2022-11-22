#include <WiFi.h>          //biblioteca WiFi da ESP32
#include <PubSubClient.h>  //biblioteca para comunicação MQTT
#include <Ultrasonic.h>    //biblioteca sensor ultrassonico


#define GREEN_LED 19  //pino para LED verde
#define RED_LED 18    //pino para LED vermelho

int dist;  //variável para armazenar a distância
//conexão dos pinos para o sensor ultrasonico
Ultrasonic ultrasonic(4, 5);


const char* ssid = "WILLIANBARCELOS";           //nome da rede Wi-Fi
const char* password = "1733Ta9{";              //senha da rede Wi-Fi
const char* mqtt_server = "broker.hivemq.com";  //BROKER MQTT


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];


void setup_wifi() {  //função para a conexão WiFi

  delay(10);

  Serial.println();
  Serial.print("Conectando à rede: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {  //função de reconexão
  // Loop até se reconectar
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Cria um ID randomico
    String clientId = "WILLIAN_MQTT";
    clientId += String(random(0xffff), HEX);
    // Tenta se reconectar ao broker
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println("Tentando novamente em 5 segundos...");
      // Espera 5 segundos até tentar novamente
      delay(5000);
    }
  }
}


void setup() {

  Serial.begin(115200);  //inicia a comunicação serial

  pinMode(GREEN_LED, OUTPUT);  //define pino do LED Verde como saída
  pinMode(RED_LED, OUTPUT);    //define pino do LED Vermelho como saída

  setup_wifi();                         //chama a função de conexão Wi-Fi
  client.setServer(mqtt_server, 1883);  //conecta ao servideo e porta MQTT
}

void loop() {

  dist = ultrasonic.read();

  /*Imprime a Leitura da Distãncia na Serial*/
  Serial.print("Distância em cm: ");
  Serial.println(dist);
  sprintf(msg, "%d", dist);
  client.publish("willianbarcelos/distancia", msg);


  if (dist < 20) {                                   //se leitura for menor 20cm
    digitalWrite(RED_LED, HIGH);                      //liga LED Vermelho
    digitalWrite(GREEN_LED, LOW);                     //desliga LED Verde
    Serial.println("Lixeira Cheia");                  //Imprime na Serial falando que está cheio
    snprintf(msg, MSG_BUFFER_SIZE, "Lixeira Cheia");  //concatena texto a ser enviado
    client.publish("willianbarcelos/lixeira", msg);   //publica texto no tópico


  } else {                                                     //se leitura não for menor 20cm
    digitalWrite(RED_LED, LOW);                                //desliga LED Vermelho
    digitalWrite(GREEN_LED, HIGH);                             //liga LED Verde
    Serial.println("Lixeira com Capacidade");                  //Imprime na Serial falando que tem capacidade
    snprintf(msg, MSG_BUFFER_SIZE, "Lixeira com Capacidade");  //concatena texto a ser enviado
    client.publish("willianbarcelos/lixeira", msg);            //publica texto no tópico
  }

  delay(1000);

  if (!client.connected()) {  //se não está conectado, tenta reconectar
    reconnect();
  }
  client.loop();
}