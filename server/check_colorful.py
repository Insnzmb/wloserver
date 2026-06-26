import sqlite3, json

conn = sqlite3.connect('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/ServerDataBase.db')
d = json.load(open('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/data/drop_table.json', encoding='utf-8'))

rows = conn.execute("SELECT id, name FROM npc_data WHERE name LIKE 'Colorful%'").fetchall()
for r in rows:
    name = r[1].replace('\x00', '').strip()
    print(r[0], name, d.get(str(r[0])))
