#include <UIPEthernet.h>
//VERSION VOM OKTOBER2016
int erstausgang = 4;
int letztausgang = 8;

int ersteingang = A0;
int letzteingang = A3;

//int Taster = A7;


byte mac[] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0x12 };
IPAddress ip(192, 168, 2, 52);//FALLS NÖTIG FEST EINSTELLEN SONST DHCP----AUCH Ethernet.begin anpassen!!!!!!!!!!
EthernetServer server(80);

String readString = String(100);

void setup() {


//  Serial.begin(9600);
//if (digitalRead(12) == HIGH){
//  IPBER = 2;
//  Serial.print("2");
//}
//else
//{
//  IPBER = 7;
//   Serial.print("7");
//}
//  

  Ethernet.begin(mac, ip);
//  Ethernet.begin(mac);
  server.begin();
//
//Serial.print("RUN");
//  Serial.println(Ethernet.localIP());
//
//  Serial.print("end");
//  Serial.end();

  for (int o = erstausgang; o <= letztausgang; o++) {
    pinMode(o, OUTPUT);
  }
}


void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 100) {
          readString = readString + c;
        }
        if (c == '\n') {

          if (readString.indexOf("4=Ein")  > -1)
          {
            digitalWrite(4, HIGH);
          }
          if (readString.indexOf("4=Aus")  > -1)
          {
            digitalWrite(4, LOW);
          }
          if (readString.indexOf("5=Ein")  > -1)
          {
            digitalWrite(5, HIGH);
          }
          if (readString.indexOf("5=Aus")  > -1)
          {
            digitalWrite(5, LOW);
          }
          if (readString.indexOf("6=Ein")  > -1)
          {
            digitalWrite(6, HIGH);
          }
          if (readString.indexOf("6=Aus")  > -1)
          {
            digitalWrite(6, LOW);
          }
          if (readString.indexOf("7=Ein")  > -1)
          {
            digitalWrite(7, HIGH);
          }
          if (readString.indexOf("7=Aus")  > -1)
          {
            digitalWrite(7, LOW);
          }
          if (readString.indexOf("8=Ein")  > -1)
          {
            digitalWrite(8, HIGH);
          }
          if (readString.indexOf("8=Aus")  > -1)
          {
            digitalWrite(8, LOW);
          }

          client.println("<!DOCTYPE html><html>");

          client.println("<head>");
          client.println("<title>Arduino</title>");
          client.println("<meta name='viewport' content='width=device-width' />");
          client.println("</head>");

          client.println("<body>");

          for (int i = erstausgang; i <= letztausgang; i++) {
            // ERSTELLT DIE TASTER

            client.print("<br>");
            client.print("Ausgang ");
            client.print(i - 3);
            client.print("<font color='");

            if (digitalRead(i) == HIGH) {
              client.print("green'> An");
            }
            else {
              client.print("red'> Aus");
            }
            client.println("</font>");

            client.print("<form method=get>");

            for (int x = 1; x <= 2; x++) {
              client.print("<input type=submit name=");
              client.print(i);
              client.print(" value='");
              if (x == 1) {
                client.print("Ein");
              }
              else {
                client.print("Aus");
              }
              client.print("'>");
              
            }
            client.println("</form>");
          }

          for (int i = ersteingang; i <= letzteingang; i++) {
            int y = analogRead(i);
            client.print("<br>");
            client.print("Eingang ");
            client.print(i - 13);
            client.print(" <font color='");


            if (y > 980) {
              client.print("green");
            }
            else if (y < 100) {
              client.print("red");
            }
            else
            {
              client.print("blue");
            }
            client.print("'> ");

            client.print(y);
            client.print("<br>");
            client.println("</font>");
          }


          client.println("</body>");
          client.println("</html>");

         

          //clearing string for next read
          readString = "";
          
          //stopping client
          client.stop();
        }
      }
    }
  }
}
