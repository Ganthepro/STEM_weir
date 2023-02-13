#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64);        //สูง 128 กว้าง 64 pixcell
String pset = "          <>           ";  //กำหนดตัวแปรสำหรับการแสดงผล

String host_ip = "ganthedev.koreacentral.cloudapp.azure.com";

#define LED 2   //LED
#define PB1 34  //DN ปุ่มสีน้ำเงินซ้าย
#define PB2 35  //UP ปุ่มสีน้ำเงินขวา
#define PB3 32  //Set ปุ่มสีส้มตรงกลาง
#define TX 5    //Ultrasonic
#define RX 18   //Ultrasonic
#define RANGE 400

const char *ssid = "IHearToo";
const char *password = "ganza112";

volatile float flow = 0;
int height = 0;
int volume = 0;
volatile unsigned int ct = 0;
volatile long distances;
int set_mode = 0;
int counter = 40;
bool setting = false;
bool http_status;
bool fir_time;
bool fir_time_mode2;
bool release;
bool wifi_status = true;
int op = 0;
String p_content;
WiFiServer server(80);

void setup() {
  pinMode(2, OUTPUT);
  pinMode(PB1, INPUT);
  pinMode(PB2, INPUT);
  pinMode(PB3, INPUT);
  Serial2.begin(9600, SERIAL_8N1, TX, RX);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Weir Flow Meter");
  display.display();
  delay(500);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  // Serial.println(myIP);
  server.begin();
  if (WiFi.status() != WL_CONNECTED) {
    display.print("Connecting...");
    display.display();
  }
  float timing = 0.0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(2, !digitalRead(2));
    timing += 0.5;
    if (timing == 10.0) {
      break;
    }
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(2, HIGH);
    display.println("Weir Flow Meter");
    display.println("WiFi Connected");
    display.println("IP address: ");
    display.print(WiFi.localIP());
    display.display();
  } else {
    digitalWrite(2, LOW);
    display.println("Weir Flow Meter");
    display.println("WiFi");
    display.println("Failed to connect.");
    display.display();
  }
  delay(1500);
  xTaskCreate(but, "but", 6144, NULL, 0, NULL);
  xTaskCreate(sonic, "sonic", 4096, NULL, 1, NULL);
  xTaskCreate(show, "show", 4096, NULL, 0, NULL);
  xTaskCreate(wiFi, "wiFi", 4096, NULL, 1, NULL);
}

void wiFi(void *p) {
  while (true) {
    if (wifi_status == true) {
      wifi_status = false;
    } else {
      wifi_status = true;
    }
    // delay(1000);
    delay(500);
  }
}

void but(void *p) {
  while (true) {
    if (set_mode == 0) {
      fir_time_mode2 = true;
      fir_time = true;
      if (digitalRead(PB1) == LOW) {
        setting = true;
        counter--;
        delay(100);
        if (counter == 10) {
          set_mode = 1;
          counter = 40;
        }
      } else if (digitalRead(PB2) == LOW) {  // แก้เป็นปิด-เปิด Wifi + เคลียลค่า
        setting = true;
        counter--;
        delay(100);
        if (counter == 10) {
          set_mode = 2;
          counter = 40;
        }
      } else if (digitalRead(PB3) == LOW) {
        set_mode = 3;
      } else if (digitalRead(PB2) == HIGH && digitalRead(PB1) == HIGH && digitalRead(PB3) == HIGH) {
        counter = 40;
        setting = false;
        set_mode = 0;
      }
    } else {
      if ((digitalRead(PB3) == HIGH && set_mode == 3) || (digitalRead(PB3) == LOW && set_mode == 1)) {
        set_mode = 0;
        if (digitalRead(PB3) == LOW && set_mode == 0) {
          setting = false;
          while (digitalRead(PB3) != HIGH) {
            delay(10);
          }
        }
      }
      if (digitalRead(PB3) == LOW && set_mode != 3) {
        if (set_mode == 2 && digitalRead(PB3) == LOW) {
          while (digitalRead(PB3) != HIGH) {
            setting = true;
            counter--;
            delay(100);
            if (counter == 10) {
              fir_time = true;
              while (digitalRead(PB3) != HIGH) {
                release = true;
                delay(10);
              }
              release = false;
              set_mode = 0;
            }
          }
          if (counter >= 35) {
            if (op == 0) {
              if (WiFi.status() == WL_CONNECTED) {
                WiFi.disconnect();
              } else {
                WiFi.reconnect();
              }
            } else if (op == 1) {
              flow = 0;
              height = height - distances;
              volume = 0;
              // ทำ Distance เป็น 0
            }
            counter = 40;
          }
        }
      } else if (digitalRead(PB2) == HIGH && digitalRead(PB1) == HIGH && digitalRead(PB3) == HIGH) {
        counter = 40;
        setting = false;
      } else if (digitalRead(PB1) == LOW) {
        if (fir_time == true && set_mode != 2) {
          while (digitalRead(PB1) != HIGH) {
            release = true;
            delay(10);
          }
          fir_time = false;
          release = false;
        } else {
          delay(200);
          if (set_mode == 1) {
            height++;
            if (height > 300) { height = 0; }
          } else if (set_mode == 2) {
            if (op == 1) {
              op = 0;
            } else {
              op++;
            }
          }
        }
      } else if (digitalRead(PB2) == LOW) {
        if (fir_time_mode2 == true && set_mode != 1) {
          while (digitalRead(PB2) != HIGH) {
            release = true;
            delay(10);
          }
          fir_time_mode2 = false;
          release = false;
        } else {
          delay(200);
          if (set_mode == 1) {
            height--;
            if (height < 0) { height = 300; }
          } else if (set_mode == 2) {
            if (op == 0) {
              op = 1;
            } else {
              op--;
            }
          }
        }
      }
    }
  }
}

void sonic(void *p) {
  while (true) {
    Serial2.flush();
    Serial2.write(0X55);
    if (Serial2.available() >= 2) {
      int HighByte = Serial2.read();
      int LowByte = Serial2.read();
      HighByte = HighByte * 256 + LowByte;
      if (HighByte > 1 && HighByte < RANGE) {
        distances = height - HighByte;
        if (distances > 0) {
          flow = float(40351.1842108257 * pow(((distances * 0.00328084) + 0.0036961744), 2.5));
          volume = volume + flow;
        } else flow = 0.0;
      }
    }
    delay(500);
  }
}

void show(void *p) {
  while (true) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    if (set_mode == 0) {
      if (release == true) {
        display.setCursor(0, 32);
        display.print("       <Release>      ");
      } else {
        display.print("Distances: ");
        display.println(distances);
        display.print("Flow: ");
        display.println(flow);
        display.print("Volume: ");
        display.println(volume);
        if (WiFi.status() == WL_CONNECTED) {
          display.println("Wifi: Connected");
          digitalWrite(2, HIGH);
        } else {
          display.println("Wifi: Disconnected");
          digitalWrite(2, LOW);
        }
        if (http_status == true) {
          display.print("Http Status: Online");
        } else {
          display.print("Http Status: Offline");
        }
        if (setting == true) {
          display.setCursor(0, 56);
          if (digitalRead(PB1) == LOW && set_mode == 0) {
            display.print("Set Height...");
            display.println(counter / 10);
          } else if (digitalRead(PB2) == LOW && set_mode == 0) {
            display.print("Option...");
            display.println(counter / 10);
          }
        } else {
          display.setCursor(0, 56);
          display.print("<SH>    <IP>    <OP>");
        }
      }
    } else if (set_mode == 1) {
      if (release == true) {
        display.setCursor(0, 32);
        display.print("       <Release>      ");
      } else {
        display.println("----Set  Height----");
        display.print("Height: ");
        display.println(height);
        display.setCursor(0, 56);
        display.print("<+>      <H>      <->");
      }
    } else if (set_mode == 2) {
      if (release == true) {
        display.setCursor(0, 32);
        display.print("       <Release>      ");
      } else {
        display.println("-------Option-------");
        display.print("WiFi: ");
        if (WiFi.status() == WL_CONNECTED) {
          display.println("On");
        } else {
          display.println("Off");
        }
        display.print("Reset Data");
        if (op == 0) {
          display.setCursor(65, 8);
        } else {
          display.setCursor(65, 17);
        }
        display.print("<--");
        display.setCursor(0, 56);
        if (setting == true) {
          if (digitalRead(PB3) == LOW) {
            display.print("Home(Hold)...");
            display.println(counter / 10);
          }
        } else {
          display.print("<UP>     <H>     <DW>");
        }
      }
    } else if (set_mode == 3) {
      display.setCursor(0, 0);
      display.print("Host IP: ");
      display.println(host_ip);
      display.print("Local IP: ");
      display.println(WiFi.localIP());
    }
    display.display();
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Serial.println(wifi_status);
    digitalWrite(2, HIGH);
    String url = "https://" + host_ip + "/update.php";
    url = url + "?distance=" + String(distances)
          + "&height=" + String(height)
          + "&flow=" + String(flow)
          + "&mode=" + String(set_mode)
          + "&volume=" + String(volume)
          + "&wifi=" + String(wifi_status);
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == 200) {
      String content = http.getString();
      http_status = true;
    } else {
      http_status = false;
      Serial.println("Fail. error code " + String(httpCode));
    }
    String text = "https://" + host_ip + "/send.txt";
    http.begin(text);
    httpCode = http.GET();
    if (httpCode == 200) {
      String content = http.getString();
      Serial.println(content);
      if (content == "+") {
        height++;
        if (height > 300) { height = 0; }
      } else if (content == "-") {
        height--;
        if (height < 0) { height = 300; }
      } else if (content == "r") {
        flow = 0;
        height = height - distances;
        volume = 0;
      }
    }
    text = "https://" + host_ip + "/write.php?wmode=null";
    http.begin(text);
    httpCode = http.GET();
    if (httpCode == 200) {
      String content = http.getString();
    }
  } else {
    digitalWrite(2, LOW);
  }
}
