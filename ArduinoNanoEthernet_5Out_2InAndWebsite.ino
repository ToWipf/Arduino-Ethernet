#include <UIPEthernet.h>
//VERSION VOM Jan18
int erstausgang = 4;
int letztausgang = 8;

int ersteingang = A0;
int letzteingang = A1;


byte mac[] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0x12 };
IPAddress ip(192, 168, 2, 42);
EthernetServer server(80);

String readString = String(20);

void setup() {
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);

  Ethernet.begin(mac, ip);
  server.begin();

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
        if (readString.length() < 20) {
          readString = readString + c;
        }
        if (c == '\n')
          {
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

          client.println("<!DOCTYPE html><html><head><meta name=viewport content='width=150' /></head><body>");
          //<meta http-equiv=refresh content=5; URL=192.168.2.42/>

          for (int i = erstausgang; i <= letztausgang; i++) {
            // ERSTELLT DIE TASTER
            
            client.print("<br>Zimmer ");
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
              client.print("red");
            }
            else
            {
              client.print("green");
            }
            client.print("'> ");

            //client.print(y);
            if (y > 980) {
              client.print("Aus");
            }
            else
            {
              client.print("An");
            }
            
            client.println("<br></font>");
          }
          client.println("<br><INPUT TYPE=button onClick=history.go(0) VALUE=Neuladen><p>by Tobias Fritsch</p></body></html>");
//          client.println("<br>by Tobias Fritsch</body></html>");
          //clearing string for next read
          readString = "";
          
          //stopping client
          client.stop();
        }
      }
    }
  }
}
