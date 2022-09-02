import os

import serial

from management.poinsys import PoinSys


def main():    
    if not os.path.isfile('poinsys.cookiedb'):
        print('\033[31mPlease make database setup first\033[m')
        return None

    serial_port = input('Serial port: ').strip()

    try:
        PoinSys(serial_port)
    except serial.SerialException:
        print('\033[31mInvalid serial port. Try again.\033[m')


main()
