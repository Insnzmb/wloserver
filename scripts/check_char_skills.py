import sqlite3, json

conn = sqlite3.connect('wlo_server.db')
conn.row_factory = sqlite3.Row

# Get full column list
cols = [r[1] for r in conn.execute("PRAGMA table_info(characters)").fetchall()]
print("All columns:", cols)
print()

# Get ossuruk character  
char = conn.execute("SELECT * FROM characters WHERE name='ossuruk'").fetchone()
if char:
    for col in cols:
        val = char[col]
        if col == 'skills':
            try:
                val = json.loads(val)
                print(f"  skills ({len(val)} total): {val[:10]}")
            except:
                print(f"  skills (raw): {val}")
        elif col == 'inventory':
            try:
                val = json.loads(val)
                print(f"  inventory ({len(val)} items): {val[:3]}")
            except:
                print(f"  inventory (raw): {val}")
        else:
            print(f"  {col}: {val}")
else:
    print("ossuruk not found, listing all chars:")
    for c in conn.execute("SELECT name, element FROM characters").fetchall():
        print(f"  {c['name']} (elem={c['element']})")

conn.close()
