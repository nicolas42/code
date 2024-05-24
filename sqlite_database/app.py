import sqlite3
from werkzeug.security import generate_password_hash, check_password_hash

DATABASE = 'accounts.db'

def get_db():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

def create_account(username, password, email, full_name):
    conn = get_db()
    password_hash = generate_password_hash(password)
    try:
        with conn:
            conn.execute('''
                INSERT INTO users (username, password, email, full_name)
                VALUES (?, ?, ?, ?)
            ''', (username, password_hash, email, full_name))
        print(f"Account for {username} created successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} already exists.")

def edit_account(user_id, username, email, full_name):
    conn = get_db()
    with conn:
        conn.execute('''
            UPDATE users
            SET username = ?, email = ?, full_name = ?
            WHERE id = ?
        ''', (username, email, full_name, user_id))
    print(f"Account {user_id} updated successfully.")

def delete_account(user_id):
    conn = get_db()
    with conn:
        conn.execute('DELETE FROM users WHERE id = ?', (user_id,))
    print(f"Account {user_id} deleted successfully.")

def view_accounts():
    conn = get_db()
    cur = conn.cursor()
    cur.execute('SELECT * FROM users')
    rows = cur.fetchall()
    for row in rows:
        print(dict(row))

def find_account(username):
    conn = get_db()
    cur = conn.cursor()
    cur.execute('SELECT * FROM users WHERE username = ?', (username,))
    row = cur.fetchone()
    if row:
        print(dict(row))
    else:
        print(f"No account found for username: {username}")

if __name__ == '__main__':
    while True:
        print("\nAccount Management System")
        print("1. Create Account")
        print("2. Edit Account")
        print("3. Delete Account")
        print("4. View All Accounts")
        print("5. Find Account by Username")
        print("6. Exit")

        choice = input("Enter your choice: ")

        if choice == '1':
            username = input("Enter username: ")
            password = input("Enter password: ")
            email = input("Enter email: ")
            full_name = input("Enter full name: ")
            create_account(username, password, email, full_name)
        
        elif choice == '2':
            user_id = input("Enter user ID: ")
            username = input("Enter new username: ")
            email = input("Enter new email: ")
            full_name = input("Enter new full name: ")
            edit_account(user_id, username, email, full_name)
        
        elif choice == '3':
            user_id = input("Enter user ID to delete: ")
            delete_account(user_id)
        
        elif choice == '4':
            view_accounts()
        
        elif choice == '5':
            username = input("Enter username to search: ")
            find_account(username)
        
        elif choice == '6':
            break
        
        else:
            print("Invalid choice. Please try again.")
