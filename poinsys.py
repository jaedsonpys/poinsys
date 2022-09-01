import serial
import cookiedb

import datetime


class PoinSys:
    def __init__(self, serial_port: str) -> None:
        self.ser = serial.Serial(serial_port)
        self.cookiedb = cookiedb.CookieDB()

        signal = self.ser.readline().decode()
        signal = signal.replace('\r\n', '')

        if signal == 'started':
            date = datetime.datetime.now()
            self.ser.write(date.strftime('%d/%m/%Y').encode())
