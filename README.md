# Wonderland Online Server

This repository contains the custom server implementation for Wonderland Online. 

## Structure
- `main.py` - Entry point for the server
- `gameserver.py` - Core game server logic
- `database.py` - Database interactions
- `battle.py` - Battle mechanics and logic
- `network.py` - Network handling and packet processing
- `quest_manager.py` / `quests.py` - Quest system implementation

## Setup
1. Make sure you have Python 3.x installed.
2. Install any required dependencies.
3. Run `main.py` to start the server.

## Database
The server uses an SQLite database (`wlo_server.db` / `ServerDataBase.db`) to store player data, accounts, and game state.
