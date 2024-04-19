#include <WiFi.h>
#include <WebServer.h>

constexpr int L1 = 6;  // Yellow
constexpr int L2 = 10; // Orange
constexpr int R1 = 0;  // Green
constexpr int R2 = 1;  // Gray

constexpr int DELAY = 500;

const char *ssid = "ESP32";
const char *password = "12345678";

WebServer server(80);

void control(const char *cmd)
{
  if (strcmp(cmd, "CTRL U") == 0)
  {
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, HIGH);
    digitalWrite(R2, LOW);
    delay(DELAY);
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
  }
  else if (strcmp(cmd, "CTRL D") == 0)
  {
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
    delay(DELAY);
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
  }
  else if (strcmp(cmd, "CTRL L") == 0)
  {
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
    delay(DELAY);
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
  }
  else if (strcmp(cmd, "CTRL R") == 0)
  {
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(R2, LOW);
    delay(DELAY);
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
  }
  else if (strcmp(cmd, "CTRL S") == 0)
  {
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
  }
}

void setup()
{
  pinMode(12, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  server.on("/heart", HTTP_GET, []()
            {
      digitalWrite(12, HIGH);
      server.send(200, "text/plain", "heart");
      digitalWrite(12, LOW); });

  server.on("/move", HTTP_POST, []()
            {
    String data = server.arg("plain");
    if(data.startsWith("CTRL"))
    {
      control(data.c_str());
    }
    server.send(200, "text/plain","ok"); });

  server.begin();
}

void loop()
{
  server.handleClient();
}