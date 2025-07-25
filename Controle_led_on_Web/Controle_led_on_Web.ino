#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char* ssid = ""; // Aqui você vai escrever o nome da sua Rede
const char* password = ""; // Senha da rede

AsyncWebServer server(80);

// Configuração do pino do ESP32
const int ledPin = 2;

void handleRequest(AsyncWebServerRequest *request) {
    if (request->hasParam("cmd")) {
        String cmd = request->getParam("cmd")->value();
        if (cmd == "ON") {
            digitalWrite(ledPin, HIGH);
        } else if (cmd == "OFF") {
            digitalWrite(ledPin, LOW);
        }
        request->send(200, "text/plain", "OK");
    } else {
        request->send(400, "text/plain", "Comando inválido");
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }
    Serial.println("WiFi conectado!");

    pinMode(ledPin, OUTPUT);

    // Define rota para controle do ESP32
    server.on("/control", HTTP_GET, handleRequest);
    server.begin();

    // Aqui estou pegando o endereço Ip do meu ESP32 conectado na rede
    Serial.print("Conectado! IP do ESP32: ");
    Serial.println(WiFi.localIP()); 
}

void loop() {}
