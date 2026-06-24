import sqlite3, json, os

# The real databases
dbs = [
    'wlo_server.db',
    os.path.join('server', 'ServerDataBase.db'),
]

for db_path in dbs:
    print(f"\n=== {db_path} ===")
    conn = sqlite3.connect(db_path)
    tables = [r[0] for r in conn.execute("SELECT name FROM sqlite_master WHERE type='table'").fetchall()]
    print(f"Tables: {tables}")
    
    if 'characters' in tables:
        cols = [r[1] for r in conn.execute("PRAGMA table_info(characters)").fetchall()]
        print(f"Columns: {cols[:20]}")
        conn.row_factory = sqlite3.Row
        chars = conn.execute("SELECT * FROM characters LIMIT 5").fetchall()
        for c in chars:
            name = c['name'] if 'name' in cols else c[cols[0]]
            element = c['element'] if 'element' in cols else '?'
            skills_raw = c['skills'] if 'skills' in cols else '[]'
            try:
                skills = json.loads(skills_raw) if skills_raw else []
            except:
                skills = []
            print(f"  Char: {name} | element={element} | skills={len(skills)} | ids={[s.get('skill_id') for s in skills[:5]]}")
    conn.close()

print()
skills_db = json.load(open('server/skills.json', encoding='utf-8'))
for elem in [0, 1, 2, 3, 4]:
    count = sum(1 for s in skills_db if s['element'] == elem)
    names = [s['name'] for s in skills_db if s['element'] == elem][:5]
    print(f"  element={elem}: {count} skills in skills.json  e.g. {names}")
