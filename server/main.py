import asyncio
import logging
import os
import sys

# Ensure server folder is on PATH
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from server.v6_runtime_patch import install_v6_rebuild_knowledge
install_v6_rebuild_knowledge()

from server.gameserver import GameServer
from server.web_admin import WebAdminServer
from server.web_registration import WebRegistrationServer

logging.basicConfig(level=logging.DEBUG, format="%(asctime)s [%(levelname)s] %(message)s")
logger = logging.getLogger("Main")

async def main():
    logger.info("Initializing Wonderland Online Private Server...")
    
    # Initialize Game Server on port 6414 with absolute paths
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    db_path = os.path.join(base_dir, "wlo_server.db")
    static_db_path = os.path.join(base_dir, "server", "ServerDataBase.db")
    server = GameServer(db_path=db_path, static_db_path=static_db_path)
    
    # Initialize Web Admin Server on port 8080
    web_admin = WebAdminServer(server)
    
    # Initialize Web Registration Server on port 8081
    web_reg = WebRegistrationServer(db_path=db_path)
    
    # Run all servers concurrently
    await asyncio.gather(
        server.run(host="0.0.0.0", port=6414),
        web_admin.start(host="0.0.0.0", port=8080),
        web_reg.start(host="0.0.0.0", port=8081)
    )

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        logger.info("Server shut down by keyboard interrupt.")
    except Exception as e:
        logger.critical(f"Critical server crash: {e}")
