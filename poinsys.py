import serial
import cookiedb


class Poinsys:
    def __init__(self, serial_port: str) -> None:
        self.ser = serial.Serial(serial_port)
        self.cookiedb = cookiedb.CookieDB()
