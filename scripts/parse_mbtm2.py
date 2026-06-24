"""
Analyze SkillData.MBTM region around offset 1217026 where Fire skills cluster.
Try to determine record structure from sequential Fire skill IDs.
"""
import struct, json

MBTM_PATH = 'data/SkillData.MBTM'
SKILLS_JSON = 'server/skills.json'

data = open(MBTM_PATH, 'rb').read()
skills_db = json.load(open(SKILLS_JSON, encoding='utf-8'))
skill_map = {s['id']: s for s in skills_db}

# Known starter skill offsets from _SKILL_TABLE_ORDER:
# 11076 -> 93498 (offset 934980 bytes)
# Let's check if skill_id=11076 appears near byte 934980
known = {
    11076: 93498 * 10,
    11075: 93497 * 10,
    11077: 93499 * 10,
}
print("Verifying known skill positions:")
for sid, expected_offset in known.items():
    target = struct.pack('<H', sid)
    found = data.find(target, expected_offset - 20)
    print(f"  skill_id={sid}: expected near {expected_offset}, actual first find near there: {found}")
    if found != -1:
        print(f"    Context: {data[found-4:found+16].hex()}")
    
print()

# If _SKILL_TABLE_ORDER gives "offset // 10" → actual offset = value * 10
# Let's check if there's a record at offset 93498*10 = 934980
# Check 20 bytes before/after
offset = 93498 * 10
print(f"At offset {offset} (=93498*10):")
print(f"  Hex: {data[offset-10:offset+30].hex()}")
print(f"  skill_id=11076 as LE uint16: {struct.pack('<H', 11076).hex()}")

print()
# Search for the pattern: is 11076 at exactly offset 934980?
pos = 0
count = 0
while count < 5:
    pos = data.find(struct.pack('<H', 11076), pos)
    if pos == -1: break
    print(f"  11076 found at offset {pos} (={pos//10} in /10 units)")
    count += 1
    pos += 1

print()
# Find Fire skills cluster around 1,200,000+
print("Fire skills near offset 1,200,000:")
fire_ids = [s['id'] for s in skills_db if s['element'] == 3]
cluster_results = []
for sid in fire_ids:
    target = struct.pack('<H', sid)
    pos = data.find(target, 1200000)
    if pos != -1 and pos < 1240000:
        cluster_results.append((pos, sid))

cluster_results.sort()
for i, (pos, sid) in enumerate(cluster_results[:30]):
    name = skill_map[sid]['name']
    print(f"  offset={pos} (/{10}={pos//10}): skill_id={sid} ({name})")
    if i > 0:
        diff = pos - cluster_results[i-1][0]
        print(f"    diff from prev: {diff}")
