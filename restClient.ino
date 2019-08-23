#include <UIPEthernet.h>

/*
  Rest
  Tobias Fritsch
  20.08.2019

*/

#define OKT1 192
#define OKT2 168
#define OKT3 2
#define MACBYTE 0x11

byte mac[] = { MACBYTE, MACBYTE, MACBYTE, MACBYTE, MACBYTE, MACBYTE };
IPAddress ip(OKT1, OKT2, OKT3, 242);
EthernetServer server(80);

String readString = String(20);

void setup() {
  Ethernet.begin(mac, ip);

  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  sendaMsg(false);

  server.begin();
}

void sendaMsg(boolean bUseBackupAddr) {

  EthernetClient client;
  IPAddress IP;

  if (bUseBackupAddr) {
    IP = IPAddress(OKT1, OKT2, OKT3, 43);
  } else {
    IP = IPAddress(OKT1, OKT2, OKT3, 10);
  }

  if (client.connect(IP, 8080)) {
    
    while ((client.available()) < 0) {
      delay(10);
    }
 
    client.println(("GET /wipf/s HTTP/1.1\r\nHost: 0.0.0.0:8080\r\n\r\n"));
    //delay(1000);
    client.stop();

  }
  else {
    delay(1000);
    sendaMsg(true);
  }
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 55) {
          readString = readString + c;
        }
        if (c == '\n') {

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();

          client.print("{");
          client.println("}");

          // Nur PUT zulassen
          if (readString.indexOf("PUT /") > -1) {
            if (readString.indexOf("doOn")  > -1) {
              digitalWrite(4, HIGH);
              //client.print("ON");
            }
            else if (readString.indexOf("doOff")  > -1) {
              digitalWrite(4, LOW);
              //client.print("OFF");
            }
          }

          readString = "";
          //stopping client
          client.stop();
        }
      }
    }
  }
}
          //stopping client
          client.stop();
        }
      }
    }
  }
}
