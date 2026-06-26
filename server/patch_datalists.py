import json
import re

items = json.load(open('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/data/items.json', encoding='utf-8'))
npcs = json.load(open('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/data/npc.json', encoding='utf-8'))

items_html = '<datalist id="items-datalist">\n'
for k, v in items.items():
    if int(k) > 0:
        items_html += f'    <option value="{k} - {v}"></option>\n'
items_html += '</datalist>'

pets_html = '<datalist id="pets-datalist">\n'
for k, v in npcs.items():
    if isinstance(v, dict) and int(k) > 0:
        pets_html += f'    <option value="{k} - {v.get("name", "Unknown")}"></option>\n'
pets_html += '</datalist>'

with open('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/web_admin.py', 'r', encoding='utf-8') as f:
    content = f.read()

content = content.replace('</body>', f'{items_html}\n{pets_html}\n</body>')

with open('C:/Users/muham/OneDrive/Documents/GitHub/Wonderland Online/server/web_admin.py', 'w', encoding='utf-8') as f:
    f.write(content)
print('Datalists injected!')
