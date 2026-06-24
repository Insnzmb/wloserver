# Wonderland Online Server

This repository contains a custom python-based server implementation for Wonderland Online. 

## Structure
- `start.bat` / `start.sh` - Launch scripts for the server
- `server/main.py` - Entry point
- `server/gameserver.py` - Core game server logic
- `server/database.py` - Database interactions
- `server/battle.py` - Battle mechanics and logic
- `server/network.py` - Network handling and packet processing
- `server/quest_manager.py` / `quests.py` - Quest system implementation

## Setup & Installation

> **IMPORTANT:** This server relies on the original Wonderland Online game client data files.

1. **Clone this repository directly into your Wonderland Online game client directory.** 
   The server needs access to the `data/` folder (e.g. `data/Skill.dat`, `data/eve.Emg`) to function properly.
   
2. Make sure you have Python 3.8+ installed.
3. Install the required dependencies:
   ```bash
   pip install -r requirements.txt
   ```
4. Run the server:
   - On Windows: Double click `start.bat` or run `python -m server.main`
   - On Linux/Mac: `./start.sh` or run `python3 -m server.main`

## Database
The server uses SQLite databases (`wlo_server.db` / `server/ServerDataBase.db`) to store player data, accounts, and static game state.

## Admin Commands
You can type these commands in the game chat to modify your character:
- `:warp <map_id> <x> <y>` - Teleport to a specific map and coordinates.
- `:item add <item_id> [amount]` - Add an item to your inventory.
- `:level <level>` - Set your character's level.
- `:stat <str> <con> <int> <wis> <agi>` - Set your base attributes.
- `:gold <amount>` - Set your gold.
- `:heal` - Fully restore HP and SP.
- `:element <0-4>` - Change your character's element (0: Earth, 1: Water, 2: Fire, 3: Wind, 4: None).
- `:skill <skill_id> [grade]` - Add or level up a skill.
- `:clear` - Clear all items from your inventory.
- `:propshop` - Open the property shop.
