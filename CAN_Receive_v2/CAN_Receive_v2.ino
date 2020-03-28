/**************************
 *         Author         *
 *      Raimonds              *
 *           Recieve Can             *
 *        26/2/2020        *
 *                        *
 * **************************/

#include <SPI.h>          //SPI is used to talk to the CAN Controller
#include <mcp_can.h>

MCP_CAN CAN(10);          //set SPI Chip Select to pin 10

unsigned char len = 0;
unsigned char buf[8];
unsigned int canID;

void setup()
{
  Serial.begin(9600);   //to communicate with Serial monitor
  
//tries to initialize, if failed --> it will loop here for ever
START_INIT:

    if(CAN_OK == CAN.begin(CAN_100KBPS))      //setting CAN baud rate to 500Kbps
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}
short s;
void loop()
{
    if(CAN_MSGAVAIL == CAN.checkReceive())    //check if data is coming
    {
        CAN.readMsgBuf(&len, buf);    //read data,  len: data length, buf: data buffer
        canID = CAN.getCanId();       //getting the ID of the incoming message

        Serial.print("ID is: ");
        Serial.print(canID, HEX);     //printing the ID in its standard form, HEX

        Serial.print("    Length is: ");
        Serial.println(len);
        
        s = buf[1];
        s = s << 8;
        s = s + buf[0];
        Serial.println(s);     //Serial.write prints the character itself
    }
}
