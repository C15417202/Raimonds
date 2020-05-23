#
# This Python Code, Recieves CAN Bus Messages and
# Accelerometer Data and Displays them on the Drivers Screen.
# By: Raimonds Kaminskis
# Last Updated, 08/05/2020
#

# Importing required libraries
import board
import busio
import adafruit_mma8451
import sys
import can
import socket
import struct
import MySQLdb as mdb

from PySide2.QtWidgets import QApplication
from PySide2.QtUiTools import QUiLoader
from PySide2 import QtCore
from PySide2.QtCore import QTimer

MainWindow = None
can_socket = None
can_fmt = "=IB3xHIH"

class hello:
    def __init__(self):
        pass  # call __init__(self) of the custom base class here

def refreshScreenFunction():
    # Open the accelerometer file and read the contents
    f = open("accel.txt","r")
    contents = f.read()
    
    # Unpack the Can bus messages
    cf,addr = can_socket.recvfrom(16)
    can_id,can_dlc,data,seconds,milliseconds = struct.unpack(can_fmt,cf)
    can_id = can_id & 0x7fffffff
    CANString = "ID: "+str(can_id) + " len: "+str(can_dlc)+ " data: "+ str(data) + " timestamp: " + str(seconds) + "." + str(milliseconds)

    # Connect and insert the data in to the database
    con = mdb.connect('localhost', 'root', '12345678', 'pyqt5')
    cur = con.cursor()
    cur.execute("INSERT INTO data(CAN_ID, CAN_LEN, CAN_DATA, SECONDS, MILLISECONDS) VALUES(%d, %d, %d, %d, %d) " %(can_id, can_dlc, data, seconds, milliseconds))
    con.commit()
    
    # Display Can bus messages on the GUI
    if(str(can_id) == "1"):
        if(str(data) == "1"):
            MainWindow.eStop.setText("Pressed")
        if(str(data) == "0"):
            MainWindow.eStop.setText("Not Pressed")
    if(str(can_id) == "2"):
        MainWindow.bmsTemp_1.setText(str(data))
        MainWindow.bmsTemp_2.setText(str(data))
    if(str(can_id) == "3"):
        MainWindow.carSpeed.display(str(data))
    if(str(can_id) == "4"):
        MainWindow.bmsVoltage_1.setValue(data)
        MainWindow.bmsVoltage_2.setText(str(data))
    if(str(can_id) == "5"):
        MainWindow.bmsCurrent.setText(str(data))
    if(str(can_id) == "6"):
        MainWindow.tsPower.setText(str(data))
    if(str(can_id) == "7"):
        MainWindow.motorVoltageFL.setText(str(data))
    if(str(can_id) == "8"):
        MainWindow.motorVoltageFR.setText(str(data))
    if(str(can_id) == "9"):
        MainWindow.motorCurrentFL.setText(str(data))
    if(str(can_id) == "10"):
        MainWindow.motorCurrentFR.setText(str(data))
    if(str(can_id) == "11"):
        MainWindow.steering.setText(str(data))
    if(str(can_id) == "12"):
        MainWindow.throttle.setText(str(data))
    MainWindow.Rmessages.append(CANString)
    MainWindow.Rmessages_2.append(contents)
    QApplication.processEvents()

def loadUiWidget(uifilename, parent=None):
    loader = QUiLoader()
    uifile = QtCore.QFile(uifilename)
    uifile.open(QtCore.QFile.ReadOnly)
    ui = loader.load(uifile, parent)
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
