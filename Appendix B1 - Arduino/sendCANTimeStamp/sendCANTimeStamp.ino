//
// This Arduino Code, Sends Dummy Values amd Timestamps over a CAN Bus
// By: Raimonds Kaminskis
// Last Updated: 07/05/2020
//

//####################################################
//Include libraries

#include <SPI.h>          //SPI library is used to talk to the CAN controller
#include <mcp_can.h>      //CAN bus shield library

//####################################################
//Set up CAN, SPI & Serial communication

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

//####################################################
//Declare variables

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

//####################################################
//Main loop

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
  
  //To send dummy values and timestamps call the function
  sendCAN_Message_with_timestamp(eStop, 0x1, 0, 0);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(bmsTemp, 0x2, 0, 200);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(carSpeed, 0x3, 0, 400);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(bmsVoltage, 0x4, 0, 600);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(bmsCurrent, 0x5, 0, 800);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(tsPower, 0x6, 1, 0);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(motorVoltageFL, 0x7, 1, 200);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(motorVoltageFR, 0x8, 1, 400);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(motorCurrentFL, 0x9, 1, 600);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(motorCurrentFR, 0xA, 1, 800);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(steering, 0xB, 2, 0);
  delay(200); //200ms delay
  sendCAN_Message_with_timestamp(throttle, 0xC, 2, 200);
  delay(200); //200ms delay
}

//####################################################
//Function to send a value and timestamp as 8 bytes.

void sendCAN_Message_with_timestamp(float signalValue, int CAN_ID, long seconds, int milliseconds) { //This function takes signed 2 byte value (-3276.8 up to 3276.7), adds a dummy timestamp and sends it onto the bus!

  //Initialise 8 byte message array
  unsigned char message[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  //Split signal into two bytes and add to message
  short oneDecimalPlaceValue = signalValue; //Send with one decimal place. Currently only sending whole integers anyway.
  byte small = (byte) (oneDecimalPlaceValue & 0xFF);
  byte big = (byte) ((oneDecimalPlaceValue >> 8) & 0xFF);
  message[0] = small;
  message[1] = big;

  //Split timestamp seconds into 4 bytes and add it to the message
  for (int i = 0; i < 4; i++) {
    message[i+2] = ((seconds >> (i*8)) & 0xFF); //Extract the right-most byte of the shifted variable
  }

  //Split the timestamp milliseconds into two bytes and add it to the message
  oneDecimalPlaceValue = milliseconds;
  small = (byte) (oneDecimalPlaceValue & 0xFF);
  big = (byte) ((oneDecimalPlaceValue >> 8) & 0xFF);
  message[6] = small;
  message[7] = big;

  //Send message!
  CAN.sendMsgBuf(CAN_ID, 0, 8, message);
  Serial.println(CAN_ID);
  Serial.println(message);
}
