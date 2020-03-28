//
// This Arduino Code, Sends Dummy CAN Bus Messages
// By: Raimonds Kaminskis
// Last Updated, 22/03/2020
//

#include <SPI.h>          //SPI library is used to talk to the CAN controller
#include <mcp_can.h>      //CAN bus shield library

MCP_CAN CAN(10);          //Set SPI chip select to pin 10

void setup()
{
  //Tries to initialize, if failed --> it will loop here for ever
  START_INIT:

  if (CAN_OK == CAN.begin(CAN_100KBPS))
  {
    //Setting CAN baud rate to 100kbps
  }
  else
  {
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

//Car dummy variables
short eStop = 0;
short bmsTemp = 0;
short carSpeed = 0;
short bmsVoltage = 0;
short bmsCurrent = 0;
short motorVoltage = 30;
short motorCurrent = 0;
short tsPower = 0;

void loop()
{ 
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

  //Motor voltage dummy
  if (flagF > 0)
  {
    motorVoltage++;
    if (motorVoltage >= 140)
    {
      flagF = -1;
    }
  }
  else
  {
    motorVoltage--;
    if (motorVoltage <= 30)
    {
      flagF = 1;
    }
  }

  //Motor current dummy
  if (flagG > 0)
  {
    motorCurrent++;
    if (motorCurrent >= 300)
    {
      flagG = -1;
    }
  }
  else
  {
    motorCurrent--;
    if (motorCurrent <= 0)
    {
      flagG = 1;
    }
  }

  //TS power dummy
  if (flagH > 0)
  {
    tsPower = (motorVoltage * motorCurrent)/(1000);
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
  CAN.sendMsgBuf(0x6, 0, 2, (const byte *) &motorVoltage);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x7, 0, 2, (const byte *) &motorCurrent);
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x8, 0, 2, (const byte *) &tsPower);
  delay(200); //200ms delay
}
