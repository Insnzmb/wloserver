import sqlite3
conn = sqlite3.connect('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/ServerDataBase.db')
print([(r[0], r[1].replace('\x00', '')) for r in conn.execute("SELECT id, name FROM npc_data WHERE name LIKE 'Colorful%'").fetchall()])
