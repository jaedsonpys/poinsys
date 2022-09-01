import cookiedb
from management.poinsys import PoinSys


def main():
    serial_port = input('Serial port: ').strip()
    
    try:
        PoinSys(serial_port)
    except cookiedb.exceptions.DatabaseNotFoundError:
        print('\033[31mPlease make database setup first\033[m')


main()
