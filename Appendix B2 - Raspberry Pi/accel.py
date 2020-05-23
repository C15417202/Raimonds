# Reading the MMA8451 acceleration every second.
# Author: Raimonds Kaminskis
import time
import board
import busio
import adafruit_mma8451

# Initialize I2C bus.
i2c = busio.I2C(board.SCL, board.SDA)

# Initialize MMA8451 module.
sensor = adafruit_mma8451.MMA8451(i2c)
# Optionally change the address if it's not the default:
#sensor = adafruit_mma8451.MMA8451(i2c, address=0x1D)

# Optionally change the range from its default of +/-4G:
#sensor.range = adafruit_mma8451.RANGE_2G  # +/- 2G
#sensor.range = adafruit_mma8451.RANGE_4G  # +/- 4G (default)
#sensor.range = adafruit_mma8451.RANGE_8G  # +/- 8G

# Optionally change the data rate from its default of 800hz:
#sensor.data_rate = adafruit_mma8451.DATARATE_800HZ  #  800Hz (default)
#sensor.data_rate = adafruit_mma8451.DATARATE_400HZ  #  400Hz
#sensor.data_rate = adafruit_mma8451.DATARATE_200HZ  #  200Hz
#sensor.data_rate = adafruit_mma8451.DATARATE_100HZ  #  100Hz
#sensor.data_rate = adafruit_mma8451.DATARATE_50HZ   #   50Hz
#sensor.data_rate = adafruit_mma8451.DATARATE_12_5HZ # 12.5Hz
#sensor.data_rate = adafruit_mma8451.DATARATE_6_25HZ # 6.25Hz
#sensor.data_rate = adafruit_mma8451.DATARATE_1_56HZ # 1.56Hz

# Main loop to print the acceleration and orientation every second.
while True:
    text = open("accel.txt","w")
    x, y, z = sensor.acceleration
    accelerationString = "Acceleration(m/s^2): x= " +str('{0:.3f}'.format(x)) + " y= " +str('{0:.3f}'.format(y))+ " z= " +str('{0:.3f}'.format(z))
    text.write(accelerationString)
    time.sleep(1.0)