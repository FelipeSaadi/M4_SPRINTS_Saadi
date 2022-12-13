#include <WiFi.h>
#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "ESP32";      // Enter SSID here
const char* password = "saadi1234";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

int led1 = 1;
bool LED1status = LOW;

int led2 = 2;
bool LED2status = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", gameInit);
  server.on("/player1", player1Win);
  server.on("/player2", player2Win);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  if (LED1status) {
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
  }

  if (LED2status) {
    digitalWrite(led2, HIGH);
  } else {
    digitalWrite(led2, LOW);
  }
}

void gameInit() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("O jogo começou!");
  server.send(200, "text/html");
}

void player1Win() {
  LED1status = HIGH;
  Serial.println("Player 1 Venceu!");
  server.send(200, "text/html");
}

void player2Win() {
  LED2status = HIGH;
  Serial.println("Player 2 Venceu!");
  server.send(200, "text/html");
}
