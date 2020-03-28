#
# This Python Code, Recieves CAN Bus Data and Accelerometer Data and Displays them on the Drivers Screen.
# By: Raimonds Kaminskis
# Last Updated, 25/03/2020
#

# Importing required libraries
import board
import busio
import adafruit_mma8451
import sys
import can
import socket
import struct

from PySide2.QtWidgets import QApplication
from PySide2.QtUiTools import QUiLoader
from PySide2 import QtCore
from PySide2.QtCore import QTimer

MainWindow = None
can_socket = None
can_fmt = "=IB3xH"

class hello:
    def __init__(self):
        pass  # call __init__(self) of the custom base class here

def ButtonHandler():
    print("Got a button press")
    bus = can.interface.Bus(channel='can0', bustype='socketcan_native')
    msg = can.Message(arbitration_id = 0x10, is_fd = 0, data=[0x34,0x12])
    print(msg)
    bus.send(msg)

def refreshScreenFunction():
    # Initialize I2C bus.
    i2c = busio.I2C(board.SCL, board.SDA)
    # Initialize MMA8451 module.
    sensor = adafruit_mma8451.MMA8451(i2c)
    x, y, z = sensor.acceleration
    accelerationString = "Acceleration(m/s^2): x= " +str('{0:.3f}'.format(x)) + " y= " +str('{0:.3f}'.format(y))+ " z= " +str('{0:.3f}'.format(z))

    cf,addr = can_socket.recvfrom(10)
    can_id,can_dlc,data = struct.unpack(can_fmt,cf)
    can_id = can_id & 0x7fffffff
    CANString = "ID: "+str(can_id) + " len: "+str(can_dlc)+ " data: "+ str(data)
    if(str(can_id) == "1"):
        if(str(data) == "1"):
            MainWindow.eStop.setText("Pressed")
        if(str(data) == "0"):
            MainWindow.eStop.setText("Not Pressed")
    if(str(can_id) == "2"):
        MainWindow.bmsTemp_1.setText(str(data))
        MainWindow.bmsTemp_2.setText(str(data))
    if(str(can_id) == "3"):
        MainWindow.speed_1.display(str(data))
        MainWindow.speed_2.setText(str(data))
    if(str(can_id) == "4"):
        MainWindow.bmsVoltage_1.setValue(data)
        MainWindow.bmsVoltage_2.setText(str(data))
    if(str(can_id) == "5"):
        MainWindow.bmsCurrent.setText(str(data))
    if(str(can_id) == "6"):
        MainWindow.motorVoltage.setText(str(data))
    if(str(can_id) == "7"):
        MainWindow.motorCurrent.setText(str(data))
    if(str(can_id) == "8"):
        MainWindow.tsPower.setText(str(data))
    MainWindow.Rmessages.append(CANString)
    MainWindow.Rmessages_2.append(accelerationString)
    QApplication.processEvents()

def loadUiWidget(uifilename, parent=None):
    loader = QUiLoader()
    uifile = QtCore.QFile(uifilename)
    uifile.open(QtCore.QFile.ReadOnly)
    ui = loader.load(uifile, parent)
    ui.sendCan.clicked.connect(ButtonHandler)
    uifile.close()
    return ui

if __name__ == "__main__":
    app = QApplication([])
    can_socket=socket.socket(socket.AF_CAN,socket.SOCK_RAW,socket.CAN_RAW)
    can_socket.bind(("can0",))
    MainWindow = loadUiWidget("mainwindow.ui")
    refreshScreenTimer = QTimer()
    refreshScreenTimer.start(200)
    refreshScreenTimer.timeout.connect(refreshScreenFunction)
    MainWindow.show()
    window = hello()
    sys.exit(app.exec_())
