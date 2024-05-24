import sqlite3

class GenericDatabase:
    def __init__(self, db_name='generic_db.sqlite'):
        self.db_name = db_name

    def connect_db(self):
        return sqlite3.connect(self.db_name)

    def create_table(self, table_name, columns):
        conn = self.connect_db()
        cursor = conn.cursor()
        columns_definition = ', '.join([f'{col_name} {col_type}' for col_name, col_type in columns.items()])
        cursor.execute(f'''
            CREATE TABLE IF NOT EXISTS {table_name} (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                {columns_definition}
            )
        ''')
        conn.commit()
        conn.close()

    def create_element(self, table_name, element):
        conn = self.connect_db()
        cursor = conn.cursor()
        columns = ', '.join(element.keys())
        placeholders = ', '.join(['?' for _ in element])
        cursor.execute(f'''
            INSERT INTO {table_name} ({columns})
            VALUES ({placeholders})
        ''', tuple(element.values()))
        conn.commit()
        conn.close()

    def read_elements(self, table_name):
        conn = self.connect_db()
        cursor = conn.cursor()
        cursor.execute(f'SELECT * FROM {table_name}')
        elements = cursor.fetchall()
        conn.close()
        return elements

    def update_element(self, table_name, element_id, updates):
        conn = self.connect_db()
        cursor = conn.cursor()
        set_clause = ', '.join([f'{col} = ?' for col in updates.keys()])
        cursor.execute(f'''
            UPDATE {table_name}
            SET {set_clause}
            WHERE id = ?
        ''', (*updates.values(), element_id))
        conn.commit()
        conn.close()

    def delete_element(self, table_name, element_id):
        conn = self.connect_db()
        cursor = conn.cursor()
        cursor.execute(f'''
            DELETE FROM {table_name}
            WHERE id = ?
        ''', (element_id,))
        conn.commit()
        conn.close()


if __name__ == "__main__":

    # Initialize the database
    db = GenericDatabase()

    # Define a table with its columns
    columns = {
        'name': 'TEXT NOT NULL',
        'value': 'TEXT NOT NULL'
    }
    db.create_table('elements', columns)

    # Create a new element
    db.create_element('elements', {'name': 'example_name', 'value': 'example_value'})

    # Read all elements
    elements = db.read_elements('elements')
    print(elements)

    # Update an element
    db.update_element('elements', 1, {'name': 'updated_name', 'value': 'updated_value'})

    # Delete an element
    db.delete_element('elements', 1)

    # Check elements again
    elements = db.read_elements('elements')
    print(elements)



    # Define a table with its columns
    columns = {
        'a': 'TEXT NOT NULL',
        'b': 'TEXT NOT NULL',
        'c': 'TEXT NOT NULL'        
        
    }
    table_name = 'elements2'
    
    db.create_table(table_name, columns)

    # Create a new element
    db.create_element(table_name, {'a': 'omg', 'b':'zomg', 'c':'yes omgomg'})
    db.create_element(table_name, {'a': 'omg', 'b':'zomg', 'c':'yes omgomg'})
    db.create_element(table_name, {'a': 'omg', 'b':'zomg', 'c':'yes omgomg'})
    db.create_element(table_name, {'a': 'omg', 'b':'zomg', 'c':'yes omgomg'})    

    elements = db.read_elements(table_name)
    print("Elements2")
    print(elements)

    # Update an element
    db.update_element(table_name, 1, {'a': 'updated_name', 'b': 'updated_value'})

    # Delete an element
    db.delete_element(table_name, 1)

    # Check elements again
    elements = db.read_elements(table_name)
    print(elements)
    
