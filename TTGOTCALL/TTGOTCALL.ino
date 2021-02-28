/**************************************************************

   For this example, you need to install Blynk library:
     https://github.com/blynkkk/blynk-library/releases/latest

   TinyGSM Getting Started guide:
     https://tiny.cc/tinygsm-readme

 **************************************************************

   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   You can easily build graphic interfaces for all your
   projects by simply dragging and dropping widgets.

   Blynk supports many development boards with WiFi, Ethernet,
   GSM, Bluetooth, BLE, USB/Serial connection methods.
   See more in Blynk library examples and community forum.

                  http://www.blynk.io/

   Change GPRS apm, user, pass, and Blynk auth token to run :)
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
// #define BLYNK_HEARTBEAT 30

// Please select the corresponding model

#define SIM800L_IP5306_VERSION_20190610
// #define SIM800L_AXP192_VERSION_20200327
// #define SIM800C_AXP192_VERSION_20200609
// #define SIM800L_IP5306_VERSION_20200811

#include "utilities.h"

#define S1 21
#define relay1 25

#define S2 19
#define relay2 14

#define S3 18
#define relay3 33

#define S4 22
#define relay4 13

// Select your modem:
#define TINY_GSM_MODEM_SIM800

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

// See all AT commands, if wanted
//#define DUMP_AT_COMMANDS

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

// set GSM PIN, if any
#define GSM_PIN ""

// Your GPRS credentials, if any
const char apn[] = "ENTER_YOUR_APN";  // search for apn of your network provider on Google
const char gprsUser[] = "";
const char gprsPass[] = "";

#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
TinyGsmClient client(modem);

int switch_ON_Flag1_previous_I = 0;
int switch_ON_Flag1_previous_II = 0;
int switch_ON_Flag1_previous_III = 0;
int switch_ON_Flag1_previous_IV = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
const char auth[] = "AUTH_TOKE";


BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay1, !pinValue);
  delay(1000);
  // process received value
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay2, !pinValue);
  // process received value
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay3, !pinValue);
  // process received value
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay4, !pinValue);
  // process received value
}
void setup()
{
  // Set console baud rate
  SerialMon.begin(115200);

  pinMode(S1, INPUT_PULLUP);
  pinMode(relay1, OUTPUT);

  pinMode(S2, INPUT_PULLUP);
  pinMode(relay2, OUTPUT);

  pinMode(S3, INPUT_PULLUP);
  pinMode(relay3, OUTPUT);

  pinMode(S4, INPUT_PULLUP);
  pinMode(relay4, OUTPUT);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);

  delay(10);

  setupModem();

  SerialMon.println("Wait...");

  // Set GSM module baud rate and UART pins
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);

  delay(6000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();
  // modem.init();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  Blynk.begin(auth, modem, apn, gprsUser, gprsPass);

}

void loop()
{
  Blynk.run();
  Switch();
}

void Switch()
{
  if (digitalRead(S1) == LOW)
  {
    if (switch_ON_Flag1_previous_I == 0 )
    {
      digitalWrite(relay1, LOW);
      Serial.println("Relay1 ON");
      Blynk.virtualWrite(V1, 1);
      switch_ON_Flag1_previous_I = 1;
    }
    Serial.println("Switch1 ON");

  }
  if (digitalRead(S1) == HIGH )
  {
    if (switch_ON_Flag1_previous_I == 1)
    {
      digitalWrite(relay1, HIGH);
      Serial.println("Relay1 OFF");
      Blynk.virtualWrite(V1, 0);
      switch_ON_Flag1_previous_I = 0;
    }
    Serial.println("Switch1 OFF");
  }


  if (digitalRead(S2) == LOW)
  {
    if (switch_ON_Flag1_previous_II == 0 )
    {
      digitalWrite(relay2, LOW);
      Serial.println("Relay2 ON");
      Blynk.virtualWrite(V2, 1);
      switch_ON_Flag1_previous_II = 1;
    }
    Serial.println("Switch2 ON");

  }
  if (digitalRead(S2) == HIGH )
  {
    if (switch_ON_Flag1_previous_II == 1)
    {
      digitalWrite(relay2, HIGH);
      Serial.println("Relay2 OFF");
      Blynk.virtualWrite(V2, 0);
      switch_ON_Flag1_previous_II = 0;
    }
    Serial.println("Switch2 OFF");
  }


  if (digitalRead(S3) == LOW)
  {
    if (switch_ON_Flag1_previous_III == 0 )
    {
      digitalWrite(relay3, LOW);
      Serial.println("Relay3 ON");
      Blynk.virtualWrite(V3, 1);
      switch_ON_Flag1_previous_III = 1;
    }
    Serial.println("Switch3 ON");

  }
  if (digitalRead(S3) == HIGH )
  {
    if (switch_ON_Flag1_previous_III == 1)
    {
      digitalWrite(relay3, HIGH);
      Serial.println("Relay3 OFF");
      Blynk.virtualWrite(V3, 0);
      switch_ON_Flag1_previous_III = 0;
    }
    Serial.println("Switch3 OFF");
  }


  if (digitalRead(S4) == LOW)
  {
    if (switch_ON_Flag1_previous_IV == 0 )
    {
      digitalWrite(relay4, LOW);
      Serial.println("Relay4 ON");
      Blynk.virtualWrite(V4, 1);
      switch_ON_Flag1_previous_IV = 1;
    }
    Serial.println("Switch4 ON");

  }
  if (digitalRead(S4) == HIGH )
  {
    if (switch_ON_Flag1_previous_IV == 1)
    {
      digitalWrite(relay4, HIGH);
      Serial.println("Relay4 OFF");
      Blynk.virtualWrite(V4, 0);
      switch_ON_Flag1_previous_IV = 0;
    }
    Serial.println("Switch4 OFF");
  }


}
