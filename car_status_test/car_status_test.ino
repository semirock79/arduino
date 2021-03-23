#include <mcp_can.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

#define CAN0_INT 2
#define RPM 0x0C
#define SPEED 0x0D

MCP_CAN CAN0(10);     // Set CS to pin 10
LiquidCrystal_I2C lcd(0x3F, 16, 2);  

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
//char msgString[128];

int speed = 0;
long rpm = 0;

void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");
  pinMode(CAN0_INT, INPUT);
  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted

  //16x2 display initialization
  lcd.init();
  lcd.backlight();
}

void loop()
{
  byte data1[8] = {0x02, 0x01, SPEED, 0x00, 0x00, 0x00, 0x00, 0x00};
  if (!request(data1))
  {
    Serial.println("Error Sending Message...");
    delay(1000);
    exit(1);
  }

  while (digitalRead(CAN0_INT)) { delay(1); }

  CAN0.readMsgBuf(&rxId, &len, rxBuf);

  if ((rxId & 0x1FFFFFFF) == 0x18DAF110 
  || (rxId & 0x1FFFFFFF) == 0x18DAF118
  || (rxId & 0x1FFFFFFF) == 0x18DAF128) {
    if (rxBuf[2] == SPEED) {
      speed = int(rxBuf[3]);
    }
  }
  
  delay(1);
  
  byte data2[8] = {0x02, 0x01, RPM, 0x00, 0x00, 0x00, 0x00, 0x00};
  if (!request(data2))
  {
    Serial.println("Error Sending Message...");
    delay(1000);
    exit(1);
  }

  while (digitalRead(CAN0_INT)) { delay(1); }

  CAN0.readMsgBuf(&rxId, &len, rxBuf);
  if ((rxId & 0x1FFFFFFF) == 0x18DAF110 
  || (rxId & 0x1FFFFFFF) == 0x18DAF118
  || (rxId & 0x1FFFFFFF) == 0x18DAF128) { 
    if (rxBuf[2] == RPM) {
      rpm = (long(rxBuf[3]) << 8 | long(rxBuf[4])) >> 2;
    }
    
  }
  display();
  delay(10);
}

bool request(byte *data) {
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x18DB33F1, 1, 8, data); //0x18DB33F1 //0x7DF
  if(sndStat == CAN_OK) return true;
  else return false;
}

void display(void)
{
  static int count = 0;
  if (count % 3 == 0) {
    char txt[16];
    sprintf(txt, "%03dkm/h %05drpm", speed, rpm);
    Serial.println(txt);
    lcd.setCursor(0, 0);
    lcd.print(txt);
  }
  count++;
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
