#include <mcp_can.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

#define CAN0_INT 2

MCP_CAN CAN0(10);     // Set CS to pin 10
LiquidCrystal_I2C lcd(0x3F, 16, 2);  

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];

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
  lcd.setCursor(0, 0);
}

byte data[8] = {0x02, 0x01, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00}; // bytes to send

void loop()
{
  int speed;
  requestSpeed();

  while (digitalRead(CAN0_INT)) { delay(1); }

  speed= responseSpeed();

  if ((rxId & 0x1FFFFFFF) == 0x18DAF110 
  || (rxId & 0x1FFFFFFF) == 0x18DAF118
  || (rxId & 0x1FFFFFFF) == 0x18DAF128) {  //0x18DAF110/0x18DAF118/0x18DAF128 0x7E8
    static int count = 0;

    if (count % 10 == 0) {
      lcd.clear();
      lcd.print(speed);
      lcd.print("km/h");
    }
    count++;
    Serial.print(speed);
  }
      
  
 
  delay(10);
}

void requestSpeed(void) {
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x18DB33F1, 1, 8, data); //0x18DB33F1 //0x7DF
  Serial.println(sndStat, BIN);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
    delay(1000);
    exit(1);
  }
}

int responseSpeed(void) {
  CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
  
  if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
    sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
  else
    sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

  Serial.print(msgString);

  if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
    sprintf(msgString, " REMOTE REQUEST FRAME");
    Serial.print(msgString);
  } else {
    for(byte i = 0; i<len; i++){
      sprintf(msgString, " 0x%.2X", rxBuf[i]);
      Serial.print(msgString);
    }
  }
  Serial.println();

  return int(rxBuf[3]);
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
