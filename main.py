import os

import serial

from management.poinsys import PoinSys


def main():    
    if not os.path.isfile('poinsys.cookiedb'):
        print('\033[31mPlease make database setup first\033[m')
        return None

    poinsys = PoinSys()

    for port in ['/dev/ttyUSB0', '/dev/ttyUSB1']:
        try:
            poinsys.start(port)
        except serial.SerialException:
            pass

    serial_port = input('Serial port: ').strip()

    try:
        poinsys.start(serial_port)
    except serial.SerialException:
        print('\033[31mInvalid serial port. Try again.\033[m')


main()
