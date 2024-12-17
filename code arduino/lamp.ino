#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Pin lampu
#define lampu1 D1
#define lampu2 D2
#define lampu3 D3
#define lampu4 D4
#define lampu5 D5
#define lampu6 D6
#define lampu7 D7
#define lampu8 D8

// Informasi WiFi dan MQTT
const char* ssid = "gilang";
const char* password = "akbar153";
const char* mqtt_server = "test.mosquitto.org";
const char* topik = "iot/kendali/G.231.22.0035";

// Inisialisasi objek WiFi dan MQTT
WiFiClient espClient;
PubSubClient client(espClient);
String messages;

// Fungsi callback untuk menangani pesan MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Pesan dari MQTT [");
  Serial.print(topic);
  Serial.print("] ");

  messages = "";
  for (int i = 0; i < length; i++) {
    messages += (char)payload[i]; // Menyusun pesan dari payload
  }
  Serial.println(messages);

  // Kendali lampu berdasarkan pesan yang diterima
  if (messages == "D1=1") digitalWrite(lampu1, HIGH);
  if (messages == "D1=0") digitalWrite(lampu1, LOW);
  if (messages == "D2=1") digitalWrite(lampu2, HIGH);
  if (messages == "D2=0") digitalWrite(lampu2, LOW);
  if (messages == "D3=1") digitalWrite(lampu3, HIGH);
  if (messages == "D3=0") digitalWrite(lampu3, LOW);
  if (messages == "D4=1") digitalWrite(lampu4, HIGH);
  if (messages == "D4=0") digitalWrite(lampu4, LOW);
  if (messages == "D5=1") digitalWrite(lampu5, HIGH);
  if (messages == "D5=0") digitalWrite(lampu5, LOW);
  if (messages == "D6=1") digitalWrite(lampu6, HIGH);
  if (messages == "D6=0") digitalWrite(lampu6, LOW);
  if (messages == "D7=1") digitalWrite(lampu7, HIGH);
  if (messages == "D7=0") digitalWrite(lampu7, LOW);
  if (messages == "D8=1") digitalWrite(lampu8, HIGH);
  if (messages == "D8=0") digitalWrite(lampu8, LOW);
}

// Fungsi untuk menghubungkan ke WiFi
void konek_wifi() {
  Serial.print("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Fungsi untuk menghubungkan ke MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan diri ke MQTT Server: ");
    Serial.print(mqtt_server);
    Serial.print("connected");

    // Client ID unik untuk menghindari konflik
    String clientId = "ESP8266Client-" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("\nTerhubung ke MQTT!");
      client.subscribe(topik);
    } else {
      Serial.print("\nGagal, rc=");
      Serial.print(client.state());
      Serial.println(". Coba lagi dalam 5 detik.");
      delay(5000);
    }
  }
}

// Fungsi setup
void setup() {
  Serial.begin(115200); // Ganti baud rate menjadi 115200
  konek_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Atur pin lampu sebagai output
  pinMode(lampu1, OUTPUT);
  pinMode(lampu2, OUTPUT);
  pinMode(lampu3, OUTPUT);
  pinMode(lampu4, OUTPUT);
  pinMode(lampu5, OUTPUT);
  pinMode(lampu6, OUTPUT);
  pinMode(lampu7, OUTPUT);
  pinMode(lampu8, OUTPUT);

  // Pastikan semua lampu mati saat awal
  digitalWrite(lampu1, LOW);
  digitalWrite(lampu2, LOW);
  digitalWrite(lampu3, LOW);
  digitalWrite(lampu4, LOW);
  digitalWrite(lampu5, LOW);
  digitalWrite(lampu6, LOW);
  digitalWrite(lampu7, LOW);
  digitalWrite(lampu8, LOW);
}

// Fungsi loop
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    konek_wifi(); // Reconnect jika WiFi terputus
  }

  if (!client.connected()) {
    reconnect(); // Reconnect jika MQTT terputus
  }

  client.loop(); // Menjalankan loop MQTT
}
