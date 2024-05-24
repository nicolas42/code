import sqlite3

def init_db():
    conn = sqlite3.connect('accounts.db')
    with conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL UNIQUE,
                password TEXT NOT NULL,
                email TEXT,
                full_name TEXT
            )
        ''')
    print("Database initialized.")

if __name__ == '__main__':
    init_db()
