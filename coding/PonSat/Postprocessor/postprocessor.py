import pandas as pd 
from math import pi, atan

data = pd.read_csv('test.csv', sep=';')
accel = data.iloc[:, 3:6]
gyro = data.iloc[:, 6:9]
mag = data.iloc[:, 9:12]
print(accel)
print(gyro)
print(mag)
G = 9.807
accelScale = G * 4/32767.5

aX = accelScale * accel.iloc[:, 1]
aY = accelScale * accel.iloc[:, 0]
aZ = accelScale * -accel.iloc[:, 2]

rad_coeff = pi/180.0
gyroScale = rad_coeff * 500/32767.5

gX = gyroScale * gyro.iloc[:, 1]
gY = gyroScale * gyro.iloc[:, 0]
gZ = gyroScale * -gyro.iloc[:, 2]

magScaleX = 0.18
magScaleY = 0.18
magScaleZ = 0.17

data = {
    'TeamID': data.iloc[:, 0],
    'Time': data.iloc[:, 1],
    'Altitude': data.iloc[:, 2],
    'aX_mss': aX,
    'aY_mss': aY,
    'aZ_mss': aZ,
    'gX_rads': gX,
    'gY_rads': gY,
    'gZ_rads': gZ,
}

data = pd.DataFrame(data, columns=['TeamID', 'Time', 'Altitude', 'aX_mss', 'aY_mss', 'aZ_mss', 'gX_rads', 'gY_rads', 'gZ_rads',])


print(data)

