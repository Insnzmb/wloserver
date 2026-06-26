import sqlite3

conn = sqlite3.connect('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/ServerDataBase.db')
print('Kiwi:', [r for r in conn.execute("SELECT id, name FROM npc_data WHERE name LIKE '%kiwi%'").fetchall()])
print('Pineapple:', [r for r in conn.execute("SELECT id, name FROM npc_data WHERE name LIKE '%pineapple%'").fetchall()])
print('Banana:', [r for r in conn.execute("SELECT id, name FROM npc_data WHERE name LIKE '%banana%'").fetchall()])
