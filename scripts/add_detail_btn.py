import re, sys, os

path = os.path.join(os.path.dirname(__file__), '..', 'server', 'web_admin.py')
content = open(path, encoding='utf-8').read()

# Find the pet modal button in the player row template and insert Details button after it
old = "onclick=\"openPetModal('${p.name}')\">Pet</button>"
new = ("onclick=\"openPetModal('${p.name}')\">Pet</button>\n"
       "                            <button style=\"background:linear-gradient(135deg,#667eea,#764ba2);\" "
       "onclick=\"openDetailModal('${p.name}')\">&#128203; Details</button>")

if old in content:
    content2 = content.replace(old, new, 1)
    open(path, 'w', encoding='utf-8').write(content2)
    print("OK - Details button added to player rows")
else:
    print("NOT FOUND - searching...")
    idx = content.find("openPetModal")
    print(repr(content[idx:idx+200]))
    sys.exit(1)
