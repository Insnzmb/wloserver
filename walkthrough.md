# Walkthrough - Client Code Analysis and Categorization

We have successfully scanned the decompiled client code `aLogin.exe.1.c` and categorized/extracted the major game-related functions into the [alogin_analyzed](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed) directory.

## Changes Made

We created/updated the following classified files inside the `alogin_analyzed/` workspace folder with extensive Turkish inline headers detailing purpose, offsets, packets, and line-by-line analyses:

1. **[network_packet.c](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed/network_packet.c)**:
   - Contains all 14 key packet sending, receiving, queueing, status monitoring, and dispatcher routines from WLO Client:
     - `FUN_000799c8` (Socket Connect): Asenkron soket bağlantısı.
     - `FUN_0007a284` (Socket Recv Wrapper): Direct recv wrapper.
     - `FUN_0012479c` (Socket Send Wrapper 1): Direct send helper.
     - `FUN_00296660` (Socket Send Wrapper 2): Giden paket kuyruğu.
     - `FUN_00436178` (Port Validator): Port range check.
     - `FUN_00124a1c` (Recv Buffer Framer): TCP akışından paket sınırlarını ayrıştırıp çerçeveler.
     - `FUN_00124ff0` (Socket Recv Worker Thread): Soket dinleme işçisi.
     - `FUN_00125204` (Socket Recv Length Reader): Blok okuma garantileyicisi.
     - `FUN_00125f30` (Socket MSG_PEEK Checker): Sokette veri denetimi.
     - `FUN_00079f88` (Socket Queue Buffer Flusher): Transmit kuyruğu flusher.
     - `FUN_0007a0fc` (Socket Immediate Send Wrapper): Doğrudan anlık gönderici.
     - `FUN_00124df4` (Socket Send Worker Thread): Asenkron kuyruk gönderim işçisi.
     - **NEW**: `FUN_00115a38` (Main Packet Dispatcher 1): Ana paket dağıtıcısı. Sunucudan gelen tüm OPCODE'ları (Chat, Movement, Combat, Warp, Friend, Pet, Action, Interaction, Item, Trade, Quest, Battle, Login) çözümler.
     - **NEW**: `FUN_0010e218` (Main Packet Dispatcher 2): İkincil arayüz paket dağıtıcısı. Arayüz eylemleriyle ilişkili OPCODE'ları kontrol eder.

2. **[login_server.c](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed/login_server.c)**:
   - Contains login response parsing, `SERVER.INI` parsing, and server channel listing routines (`FUN_0033c310`, `FUN_0032f674`, `FUN_0014c114`).
3. **[movement_map.c](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed/movement_map.c)**:
   - Contains grid calculation and MapData loader/decrypter logic (`FUN_0032d924`, `FUN_0032cd88`, `FUN_0032d5b8`).
   - Added NPC click distance absolute checker (`FUN_0031d874`), player/mount coordinate syncer (`FUN_0015013c`), and companion/pet walk direction copier (`FUN_0013d3f4`).
4. **[combat_battle.c](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed/combat_battle.c)**:
   - Contains PK challenge verification, target distance constraints, and battle starters (`FUN_003a6f18`, `FUN_003a7154`).
5. **[quest_journal.c](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed/quest_journal.c)**:
   - Contains Quest Journal UI initialization (`FUN_0030859c`) and abandon/guild listing sub-opcode packets (`FUN_0041892c`, `FUN_0041894c`, `FUN_0041896c`, `FUN_0041898c`, `FUN_0041a110`).
   - Added Dialogue form manager (`FUN_004896f4` managing Form_Talk_1, Form_Talk_2, Form_Talk_3) and Quest dialogue loader (`FUN_0040d550` loading TalkForm1).
6. **[pet_companion.c](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed/pet_companion.c)**:
   - Contains active pet summoning toggles (`FUN_003de310`) and state capability mappings (`FUN_003e9898`).
7. **[trade_shop.c](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed/trade_shop.c)**:
   - Contains secure trade item slot renderer (`FUN_002a1f14`).
   - Added Alchemy item compounding compounder (`FUN_0033ace0`) sending Opcode 23 Sub-opcode 33.

Each C function block is preceded by descriptive comments detailing its functional purpose, used offset values, and utilized/dispatched network opcodes.

## Categorized Findings Summary (50 Items Documented)

We have compiled and structured **50 distinct client-side system checks, packet parameters, and UI routines** in [bulgular.md](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/bulgular.md), ranging from combat/movement/inventory restrictions to complex social systems:
- **1-10**: Socket IO functions, connecting states, ports, buffers, framing, and queue flush routines.
- **11-20**: Map data decrypting, click range check, coordinate synchronization, player/companion directional movement alignment, Dialog manager, Talk forms, and Combat starters.
- **21-30**: Pet summoning, pet attribute capability mappings, Quest abandon forms, Alchemy compound recipes, hotkey layout maps, vehicle garage limits, ship fuel checks, bathing state, trade lock safety, and marriage age/level restrictions.
- **31-40**: Item Mall mini-games double rewards, chat prefixes, element skill learn limitations, water gathering distance checks, fishing blocks, mailbox 90% warnings, tent furniture tags, team restrictions, mini-map expansions, ghost state sprites, remote control bot blocks, and Castle Siege defense logs.
- **41-50**: Teleport scroll blocks, blacksmith repair fee warnings, in-battle repair locks, friend log targets, friend delete panels, Forgotten Scroll stat reset lists, level up logs, durability depletion notifications, and daily PvP challenge limits.

## Taşıt Binme & Tamir Güncellemeleri (Vehicle Ride & Repair System)

İstemci üzerinde gerçekleştirilen derinlemesine C kod analizlerine dayanarak binek/taşıt sistemi protokolleri sunucuya entegre edildi:
- İstemciden gelen `[23, 51, vehicle_type]` (taşıta binme) ve `[23, 52]` (taşıttan inme) paketleri işlendi, sunucu onay mesajları ile görünüm eşlemeleri yapıldı.
- `[23, 134]` (yakıt yükleme) komutuyla envanterden yakıt yüklenmesi sağlandı, yanlış yakıt tipinde `"No suitable fuel type"` uyarısı eklendi.
- İstemci tarafında `0x27` (taşıt) dışındaki eşyalara tamir kiti uygulanması engellendi (`Only for Vehicles`). Sunucu tamir durumlarında `[15, 23, status]` paketiyle başarı (`Vehicle repaired`) veya başarısızlık durumlarını istemciye iletmektedir.

## Validation Results

- Successfully extracted and structured all findings in Turkish within [bulgular.md](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/bulgular.md).
- Updated the files inside [alogin_analyzed](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/alogin_analyzed) to ensure accurate code documentation.
- Automatically updated the workspace [README.md](file:///C:/Users/muham/OneDrive/Documents/GitHub/Wonderland%20Online/README.md) at each step to maintain synchronization.

