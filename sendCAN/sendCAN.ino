//
// This Arduino Code, Sends Dummy CAN Bus Messages
// By: Raimonds Kaminskis
// Last Updated, 23/04/2020
//

#include <SPI.h>          //SPI library is used to talk to the CAN controller
#include <mcp_can.h>      //CAN bus shield library

MCP_CAN CAN(10);          //Set SPI chip select to pin 10

void setup()
{
  //To communicate with Serial Monitor
  Serial.begin(9600);
  
  //Tries to initialize, if failed --> it will loop here for ever
  START_INIT:

  //Setting CAN baud rate to 100kbps
  if (CAN_OK == CAN.begin(CAN_100KBPS))
  {
    Serial.println("CAN Bus Shield Init Ok!");
  }
  else
  {
    Serial.println("CAN Bus Shield Init Fail");
    Serial.println("Init CAN Bus Shield Again");
    goto START_INIT;
  }
}

//Flag variables
int flagA = 1;
int flagB = 1;
int flagC = 1;
int flagD = 1;
int flagE = 1;
int flagF = 1;
int flagG = 1;
int flagH = 1;
int flagI = 1;
int flagJ = 1;
int flagK = 1;
int flagL = 1;

//Car dummy variables
short eStop = 0;
short bmsTemp = 0;
short carSpeed = 0;
short bmsVoltage = 0;
short bmsCurrent = 0;
short tsPower = 0;
short motorVoltageFL = 30;
short motorVoltageFR = 30;
short motorCurrentFL = 0;
short motorCurrentFR = 0;
short steering = 0;
short throttle = 0;

void loop()
{ 
  Serial.println("Entered Coms Loop");
  
  //Emergency stop dummy
  if (flagA > 0)
  {
    eStop = 1;
    flagA = -1;
  }
  else
  {
    eStop = 0;
    flagA = 1;
  }
  
  //BMS temperature dummy
  if (flagB > 0)
  {
    bmsTemp++;
    if (bmsTemp >= 125)
    {
      flagB = -1;
    }
  }
  else
  {
    bmsTemp--;
    if (bmsTemp <= 0)
    {
      flagB = 1;
    }
  }

  //Car speed dummy
  if (flagC > 0)
  {
    carSpeed++;
    if (carSpeed >= 90)
    {
      flagC = -1;
    }
  }
  else
  {
    carSpeed--;
    if (carSpeed <= 0)
    {
      flagC = 1;
    }
  }
  
  //Battery level dummy
  if (flagD > 0)
  {
    bmsVoltage++;
    if (bmsVoltage >= 100)
    {
      flagD = -1;
    }
  }
  else
  {
    bmsVoltage--;
    if (bmsVoltage <= 0)
    {
      flagD = 1;
    }
  }

  //Battery current dummy
  if (flagE > 0)
  {
    bmsCurrent++;
    if (bmsCurrent >= 650)
    {
      flagE = -1;
    }
  }
  else
  {
    bmsCurrent--;
    if (bmsCurrent <= 0)
    {
      flagE = 1;
    }
  }

  //TS power dummy
  if (flagF > 0)
  {
    tsPower = ((motorVoltageFL * motorCurrentFL)
    +(motorVoltageFR * motorCurrentFR))/(1000);
  }

  //Left motor voltage dummy
  if (flagG > 0)
  {
    motorVoltageFL++;
    if (motorVoltageFL >= 140)
    {
      flagG = -1;
    }
  }
  else
  {
    motorVoltageFL--;
    if (motorVoltageFL <= 30)
    {
      flagG = 1;
    }
  }

  //Right motor voltage dummy
  if (flagH > 0)
  {
    motorVoltageFR++;
    if (motorVoltageFR >= 140)
    {
      flagH = -1;
    }
  }
  else
  {
    motorVoltageFR--;
    if (motorVoltageFR <= 30)
    {
      flagH = 1;
    }
  }

  //Left Motor current dummy
  if (flagI > 0)
  {
    motorCurrentFL++;
    if (motorCurrentFL >= 300)
    {
      flagI = -1;
    }
  }
  else
  {
    motorCurrentFL--;
    if (motorCurrentFL <= 0)
    {
      flagI = 1;
    }
  }

  //Right Motor current dummy
  if (flagJ > 0)
  {
    motorCurrentFR++;
    if (motorCurrentFR >= 300)
    {
      flagJ = -1;
    }
  }
  else
  {
    motorCurrentFR--;
    if (motorCurrentFR <= 0)
    {
      flagJ = 1;
    }
  }

  //Steering input dummy
  if (flagK > 0)
  {
    steering++;
    if (steering >= 100)
    {
      flagK = -1;
    }
  }
  else
  {
    steering--;
    if (steering <= 0)
    {
      flagK = 1;
    }
  }

  //Throttle input dummy
  if (flagL > 0)
  {
    throttle++;
    if (throttle >= 100)
    {
      flagL = -1;
    }
  }
  else
  {
    throttle--;
    if (throttle <= 0)
    {
      flagL = 1;
    }
  }

  //Send dummy CAN bus messages
  CAN.sendMsgBuf(0x1, 0, 2, (const byte *) &eStop);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x2, 0, 2, (const byte *) &bmsTemp);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x3, 0, 2, (const byte *) &carSpeed);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x4, 0, 2, (const byte *) &bmsVoltage);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x5, 0, 2, (const byte *) &bmsCurrent);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x6, 0, 2, (const byte *) &tsPower);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x7, 0, 2, (const byte *) &motorVoltageFL);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x8, 0, 2, (const byte *) &motorVoltageFR);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x9, 0, 2, (const byte *) &motorCurrentFL);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0xA, 0, 2, (const byte *) &motorCurrentFR);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0xB, 0, 2, (const byte *) &steering);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0xC, 0, 2, (const byte *) &throttle);
  delay(200); //200ms delay
}
