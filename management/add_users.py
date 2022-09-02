import cookiedb


def add_users():
    db = cookiedb.CookieDB()
    db.create_database('poinsys', if_not_exists=True)
    db.open('poinsys')

    print('-=' * 15)
    print('Adding new users')
    print('-=' * 15)

    while True:
        tag_id = input('User tag ID: ').strip()
        username = input('Username: ').strip()

        db.add(f'users/{tag_id}', {'name': username, 'entries': []})


add_users()
