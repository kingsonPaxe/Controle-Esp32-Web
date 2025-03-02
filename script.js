const ESP32_IP = "http://192.168.100.123"; // Substitua pelo IP do ESP32 na rede

function sendCommand(command) {
    fetch(`${ESP32_IP}/control?cmd=${command}`)
        .then(response => response.text())
        .then(data => console.log("Resposta do ESP32:", data))
        .catch(error => console.error("Erro:", error));
}