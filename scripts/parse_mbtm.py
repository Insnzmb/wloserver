"""
Parse SkillData.MBTM to find the skill table slot (uint16) for each skill_id.
The MBTM format has 10-byte records. We scan for known skill IDs to find the correct offsets.
"""
import struct, json

MBTM_PATH = 'data/SkillData.MBTM'
SKILLS_JSON = 'server/skills.json'

data = open(MBTM_PATH, 'rb').read()
print(f"File size: {len(data)} bytes")
print(f"First 80 bytes: {data[:80].hex()}")
print()

# Load known skill IDs from skills.json
skills_db = json.load(open(SKILLS_JSON, encoding='utf-8'))
skill_ids = {s['id'] for s in skills_db}

# Search for skill IDs as uint16 (little-endian) anywhere in file
# and record their byte offsets
print("Scanning for Fire skill IDs (element=3) as uint16 LE:")
fire_skills = [s for s in skills_db if s['element'] == 3]

results = {}
for skill in fire_skills[:20]:
    sid = skill['id']
    target = struct.pack('<H', sid)  # uint16 little-endian
    offset = 0
    offsets = []
    while True:
        pos = data.find(target, offset)
        if pos == -1:
            break
        offsets.append(pos)
        offset = pos + 1
    if offsets:
        results[sid] = offsets[0]  # first occurrence
        print(f"  skill_id={sid} ({skill['name']}) found at offsets: {offsets[:5]}")
    else:
        print(f"  skill_id={sid} ({skill['name']}) NOT FOUND")

print()
# Check if record size is 10 bytes by comparing adjacent skill IDs
print("If records are 10 bytes apart, differences between offsets should be multiples of 10:")
sorted_offsets = sorted((off, sid) for sid, off in results.items())
for i in range(1, min(5, len(sorted_offsets))):
    diff = sorted_offsets[i][0] - sorted_offsets[i-1][0]
    print(f"  Between {sorted_offsets[i-1][1]} and {sorted_offsets[i][1]}: offset diff = {diff}")

print()
# Try to parse as 10-byte records starting from offset 0
print("Sample 10-byte records from start of file:")
RECORD_SIZE = 10
for i in range(min(10, len(data) // RECORD_SIZE)):
    rec = data[i*RECORD_SIZE:(i+1)*RECORD_SIZE]
    if len(rec) == RECORD_SIZE:
        vals = struct.unpack('<HHHHH', rec)  # 5 uint16
        print(f"  Record {i} (offset {i*RECORD_SIZE}): {vals} = {list(rec)}")
