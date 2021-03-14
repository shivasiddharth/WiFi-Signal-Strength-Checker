/**************************************************************************************
                     Code for Wi-Fi Signal Strength Monitor
                      Written by Sid for Sid's E Classroom
                    https://www.youtube.com/c/SidsEClassroom
             All text above must be included in any redistribution.
  If you find this useful and want to make a donation -> https://paypal.me/sidsclass
 **************************************************************************************/


#include <ESP8266WiFi.h>
#include <Wire.h>
#include "SSD1306.h"

// Enter the WiFi credentials
char wifissid[] = "ENTER YOUR WiFi SSID HERE";
char wifipass[] = "ENTER YOUR WiFi PASSWORD HERE";

// The following values are from https://www.intuitibits.com/2016/03/23/dbm-to-percent-conversion/
int signal_dBM[] = { -100, -99, -98, -97, -96, -95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81, -80, -79, -78, -77, -76, -75, -74, -73, -72, -71, -70, -69, -68, -67, -66, -65, -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1};
int signal_percent[] = {0, 0, 0, 0, 0, 0, 4, 6, 8, 11, 13, 15, 17, 19, 21, 23, 26, 28, 30, 32, 34, 35, 37, 39, 41, 43, 45, 46, 48, 50, 52, 53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 69, 71, 72, 73, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 90, 91, 92, 93, 93, 94, 95, 95, 96, 96, 97, 97, 98, 98, 99, 99, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
int strength = 0;
int percentage = 0;

// Syntax -> display(Address of Display, SDA_PIN, SCL_PIN)
SSD1306  display(0x3c, D2, D1);

void setup() {
  // Initialize display
  display.init();
  // Choose to flip the screen depending upon the display orientation
  display.flipScreenVertically();
  // Font for the text
  display.setFont(ArialMT_Plain_10);
  // Setting the text allignment to Center
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.clear();
  Serial.begin(115200);
  Serial.println("ESP8266 WiFi Signal Strength Checker");

  // Set WiFi to Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);

  // Connect to WiFi
  WiFi.begin(wifissid, wifipass);
  Serial.print("Connecting to WiFi...");
  display.drawString(64, 15, "Connecting to WiFi...");
  display.display();

  // Check if connected to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print connection information
  display.clear();
  display.drawString(64, 15, "Connected to " + String(wifissid));
  display.display();
  Serial.print("\nConnected to: ");
  Serial.println(wifissid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}

void loop ()
// While checking for signal strength, check if ESP got disconnected
{
  if (WiFi.status() != WL_CONNECTED) {
    display.clear();
    display.drawString(64, 15, "Connection lost");
    display.display();
    delay(1000);
  }
// Get signal strength if ESP is connected to WiFi
  else if (WiFi.status() == WL_CONNECTED) {
    display.clear();
    Serial.println(" ");
    Serial.print("WiFi Signal Strength - ");
    // Print the received signal strength in dBm
    Serial.print("RSSI: ");
    strength = WiFi.RSSI();
    Serial.print(strength);
    Serial.print("dBm");
    Serial.print(" ");
    // Get the signal percentage value
    for (int x = 0; x < 100; x = x + 1) {
      if (signal_dBM[x] == strength) {
        // Print the received signal strength in percentage
        Serial.print("Percentage: ");
        percentage = signal_percent[x];
        Serial.print(percentage);
        Serial.println("%");
        break;
      }
    }
    drawProgressBar();
    display.display();
    delay(1000);
  }
}

// Using a progress bar for visual strength indication
void drawProgressBar() {
  display.drawProgressBar(10, 32, 100, 10, percentage);
  display.drawString(64, 0, "WiFi Signal Strength");
  display.drawString(64, 15, String(strength) + "dBm" + " | " + String(percentage) + "%");
  if (percentage == 0) {
    display.drawString(64, 45, "No Signal");
  }
  else if (percentage == 100) {
    display.drawString(64, 45, "Maximum Signal");
  }
}
