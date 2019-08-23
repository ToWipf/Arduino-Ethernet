#include <UIPEthernet.h>
#include <LiquidCrystal_I2C.h>

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
LiquidCrystal_I2C lcd(0x3F, 20, 4);

String readString = String(20);

void setup() {
  Ethernet.begin(mac, ip);

  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  lcd.begin();
  lcd.clear();
  lcd.print("W");
  sendaMsg(false);

  server.begin();
  lcd.print("F");
}

void sendaMsg(boolean bUseBackupAddr) {
  lcd.print("I");
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
      lcd.print(".");
    }
    lcd.print("P");
    
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
          client.print(digitalRead(5));
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
            else if (readString.indexOf("cls")  > -1) {
              lcd.clear();
              lcd.setCursor(0, 0);
            }
            else if (readString.indexOf("/!~") == 4) {
              // Jede Position ansteuern mit z.B. /!~103
              int col = (readString.substring(7, 9).toInt());
              int row = readString.substring(9, 10).toInt();

              lcd.setCursor(col, row);

            }

            else {
              String ss = readString;
              ss.replace("%20", " ");

              // GET /xxx HTTP/1.1
              //      xxx
              String s = ss.substring(ss.indexOf("/") + 1, ss.lastIndexOf("HTTP/1.1") - 1);
              s.remove(s.length());
              if (s.length() <= 20) {
                lcd.print(s);
              } else {
                lcd.print("E2");
              }
            }
          }
          else {
            lcd.print("E1");
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
