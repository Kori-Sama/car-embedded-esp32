#include <WiFi.h>
#include "control.h"

const char *ssid = "ESP32";
const char *password = "12345678";

WiFiServer server(80);

enum State
{
  WAITING = 0,
  CONNECTED
};

State state = WAITING;

void setup()
{
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  Serial.println("SoftAP started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
  Serial.println("Server started");
}

void loop()
{
  Serial.println("Waiting for client connection...");

  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("Client connected");
    state = CONNECTED;
  }

  while (state == CONNECTED)
  {
    if (client.available())
    {
      String cmd = client.readStringUntil('\n');
      if (cmd.startsWith("CTRL"))
      {

        ctrl::control(cmd.substring(5).c_str());
      }
      if (cmd.startsWith("OFF"))
      {
        client.stop();
        state = WAITING;
      }
    }
  }
}