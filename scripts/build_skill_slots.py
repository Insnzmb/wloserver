"""
Build complete skill_id -> slot_position mapping from SkillData.MBTM
and update skills.json with 'slot' field for each skill.
"""
import struct, json

MBTM_PATH = 'data/SkillData.MBTM'
SKILLS_JSON = 'server/skills.json'

data = open(MBTM_PATH, 'rb').read()
skills_db = json.load(open(SKILLS_JSON, encoding='utf-8'))

print(f"Total skills in skills.json: {len(skills_db)}")

# Find each skill_id as uint16 LE in MBTM file
# The slot value = first_occurrence_offset // 10
skill_slots = {}
not_found = []

for sk in skills_db:
    sid = sk['id']
    target = struct.pack('<H', sid)
    
    # Find all occurrences
    offsets = []
    pos = 0
    while True:
        p = data.find(target, pos)
        if p == -1:
            break
        offsets.append(p)
        pos = p + 1
    
    if offsets:
        # Use the first occurrence in the main skill block (around 1,200,000+)
        # Prefer occurrences in the 1,200,000+ range
        main_offsets = [o for o in offsets if o >= 1200000]
        if main_offsets:
            slot = min(main_offsets) // 10
        else:
            slot = min(offsets) // 10
        skill_slots[sid] = slot
        sk['slot'] = slot
    else:
        not_found.append(sid)
        sk['slot'] = 0  # unknown

print(f"Found slots for {len(skill_slots)} skills")
print(f"Not found: {len(not_found)} skills: {not_found[:10]}")

# Show Fire skill slots
fire_skills = [(s['id'], s['name'], s.get('slot', 0)) for s in skills_db if s['element'] == 3]
print(f"\nFire skill slots (first 15):")
for sid, name, slot in sorted(fire_skills, key=lambda x: x[2])[:15]:
    print(f"  {sid} ({name}): slot={slot}")

# Save updated skills.json
with open(SKILLS_JSON, 'w', encoding='utf-8') as f:
    json.dump(skills_db, f, ensure_ascii=False, indent=2)
print(f"\nUpdated skills.json with slot values.")
