import serial
import cookiedb

import datetime
import time


class PoinSys:
    def __init__(self) -> None:
        self.cookiedb = cookiedb.CookieDB()
        self.cookiedb.open('poinsys')

    def start(self, serial_port: str) -> None:
        self.ser = serial.Serial(serial_port)

        signal = self.ser.readline().decode()
        signal = signal.replace('\r\n', '')

        if signal != 'started':
            raise ValueError('Unexpected value received from serial')

        while True:
            date = datetime.datetime.now()
            self.ser.write((date.strftime('%d/%m/%Y') + '\r\n').encode())

            uid = self.ser.readline().decode()
            uid = uid.replace('\r\n', '')

            user = self.cookiedb.get(f'users/{uid}')
            time_now = datetime.datetime.now()
            time_str = time_now.strftime('%H:%M:%S')

            print('-=' * 15)
            print(f'Card ID: {uid}')

            if user:
                print(f'User name: {user["name"]}')
                print(f'Time: {time_str}')
                self.ser.write(f'{user["name"]},{time_str}\r\n'.encode())

                entries_list = self.cookiedb.get(f'users/{uid}/entries')
                entries_list.append(('OK', time_now.strftime('%d.%m.%Y %H:%M:%S')))

                self.cookiedb.update(f'users/{uid}/entries', entries_list)
            else:
                print('Not found')
                self.ser.write(b'false\r\n')

            time.sleep(1.5)
