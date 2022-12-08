#include <WiFi.h>
#include <string>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* SSID = "Inteli-COLLEGE";
const char* PWD = "QazWsx@123";
const String serverName = "https://ur524n-3000.preview.csb.app/teobaldo";

String alphanumeric = "abcdefghijklmnopqrstuvwxyz0123456789";

String Criptografar(String mensagem, int key) {
  String criptografia = "";
  for (int i = 0; i < mensagem.length(); i++) {
    for (int j = 0; j < alphanumeric.length(); j++) {
      if (toLowerCase(mensagem[i]) == alphanumeric[j]) {
        if (j + key > alphanumeric.length()) {
          criptografia += alphanumeric[j - key];
        } else {
          criptografia += alphanumeric[j + key];
        }
      }
      if (String(mensagem[i]) == " ") {
        criptografia += " ";
        break;
      }
    }
  }

  return criptografia;
}

void Post() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    // Envio de dados do acelerometro para o servidor em JSON
    StaticJsonDocument<200> doc;
    doc["Nome"] = String("Felipe Saadi Siegert");
    doc["Turma"] = String("Turma 3");
    doc["Grupo"] = String("Grupo 3 - Sauron");
    doc["Mensagem"] = String("Alemanha 7 x 1 Brasil");
    doc["MensagemCriptografada"] = Criptografar(doc["Mensagem"], 12);
    String requestBody;
    serializeJson(doc, requestBody);
    int httpResponseCode = http.POST(requestBody);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("HTTP Response Body: ");
      Serial.println(response);
    }
    else {
      Serial.println("Erro no POST");
    }
    // Free resources
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PWD);

  String criptografia = Criptografar("alemanha 7 x 1 brasil", 12);

  Serial.println(criptografia);
}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    WiFi.disconnect();
    delay(1000);
    WiFi.reconnect();
    delay(1000);
  }

  Serial.println("Aperte 1 para enviar!");
  while (!Serial.available()) {};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while (Serial.available()) {
    if (Serial.read() == '\n') break;
    Serial.read();
  }
  Post();
}
