"""
Direct fix: inject all Fire element skills into 'ossuruk' character in wlo_server.db
Run this WHILE the server is NOT running to avoid conflicts.
"""
import sqlite3, json

CHAR_NAME = 'ossuruk'  # Change if needed
DB_PATH = 'wlo_server.db'
SKILLS_JSON = 'server/skills.json'

# Load skills
all_skills = json.load(open(SKILLS_JSON, encoding='utf-8'))

conn = sqlite3.connect(DB_PATH)
conn.row_factory = sqlite3.Row

char = conn.execute("SELECT * FROM characters WHERE name=?", (CHAR_NAME,)).fetchone()
if not char:
    print(f"ERROR: character '{CHAR_NAME}' not found in {DB_PATH}")
    chars = [r['name'] for r in conn.execute("SELECT name FROM characters").fetchall()]
    print("Available chars:", chars)
    conn.close()
    exit(1)

element = char['element']
print(f"Character: {CHAR_NAME} | element={element}")

existing_skills = json.loads(char['skills']) if char['skills'] else []
existing_ids = {s['skill_id'] for s in existing_skills}
print(f"Current skills: {len(existing_skills)} | ids: {sorted(existing_ids)}")

# Add all matching element skills
added = 0
for sk in all_skills:
    sk_id = sk['id']
    if sk['element'] == element and sk_id not in existing_ids:
        existing_skills.append({'skill_id': sk_id, 'grade': 1, 'exp': 0})
        existing_ids.add(sk_id)
        added += 1

print(f"Added {added} new skills. Total now: {len(existing_skills)}")

# Save back
conn.execute("UPDATE characters SET skills=? WHERE name=?", 
             (json.dumps(existing_skills), CHAR_NAME))
conn.commit()
conn.close()
print("Done! Restart server and log in to see skills.")
