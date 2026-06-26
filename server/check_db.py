import sqlite3
conn = sqlite3.connect('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/ServerDataBase.db')
print('kiwi:', conn.execute("SELECT id, name FROM npc_data WHERE name LIKE '%kiwi%'").fetchall())
print('grape:', conn.execute("SELECT id, name FROM npc_data WHERE name LIKE '%grape%'").fetchall())
