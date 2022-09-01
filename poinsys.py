import serial
import cookiedb

import datetime


class PoinSys:
    def __init__(self, serial_port: str) -> None:
        self.ser = serial.Serial(serial_port)
        self.cookiedb = cookiedb.CookieDB()

        self.cookiedb.open('poinsys')

        signal = self.ser.readline().decode()
        signal = signal.replace('\r\n', '')

        if signal == 'started':
            date = datetime.datetime.now()
            self.ser.write(date.strftime('%d/%m/%Y').encode())

        self._check_id()

    def _check_id(self) -> None:
        while True:
            uid = self.ser.readline().decode()
            uid = uid.replace('\r\n', '')

            user = self.cookiedb.get(f'users/{uid}')
            time_now = datetime.datetime.now()
            time_str = time_now.strftime('%H:%M:%S')

            if user:
                self.ser.write((user['name'] + '\n').encode())
                self.ser.write((time_str + '\n').encode())

                entries_list = self.cookiedb.get(f'users/{uid}/entries')
                entries_list.append(('OK', time_now.strftime('%d.%m.%Y %H:%M:%S')))

                self.cookiedb.add(f'users/{uid}/entries', entries_list)
            else:
                self.ser.write(b'false\n')
