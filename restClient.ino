#include <UIPEthernet.h>

/*
  RestClient GET

  Tobias Fritsch
  02.08.2019
*/

byte mac[] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0x12 };
IPAddress ip(192, 168, 2, 242);
EthernetServer server(80);

String readString = String(20);

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
  pinMode(4, OUTPUT);

}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 20) {
          readString = readString + c;
        }
        if (c == '\n')
        {
          client.print("{");
          if (readString.indexOf("doOn")  > -1)
          {
            digitalWrite(4, HIGH);
            client.print("ON");
          }
          if (readString.indexOf("doOff")  > -1)
          {
            digitalWrite(4, LOW);
            client.print("OFF");
          }
          client.print("}");
          readString = "";

          //stopping client
          client.stop();
        }
      }
    }
  }
}
