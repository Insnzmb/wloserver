# aLogin.exe Oyun, Paket, Mekanik, Görev ve NPC Bulguları

Decompile edilmiş `aLogin.exe.1.c` istemci kodlarında yapılan derinlemesine analiz sonucunda; ağ iletişimi, login yönetimi, oyun mekanikleri (savaş, ticaret, pet, yetenek ağaçları, etkinlikler), görev (quest) paketleri, NPC tıklama/eşleştirme ve istemci tarafında otomatik savaş/karşılaşma tetikleyen canavarların listesinin çıkarılma mekanizmaları aşağıda detaylandırılmıştır.

---

## 1. Ağ Bağlantısı ve Alt Seviye Paket İletişimi

Aşağıdaki fonksiyonlar, Winsock API'lerini sarmalayarak sunucuyla ham TCP/IP verisi alışverişini sağlar.

- **`FUN_000799c8` (Socket Connect):** Hedef sunucu IP ve portuna bağlantıyı (`connect()`) başlatır. Asenkron soket modunu ayarlar.
- **`FUN_0007a284` (Socket Recv Wrapper):** Bağlı soket üzerinden veri tamponunu okumak için `recv()` fonksiyonunu tetikler.
- **`FUN_0012479c` ve `FUN_00296660` (Socket Send):** Sunucuya ham paket veya komut tamponu yollayan sarmalayıcılardır.
- **`FUN_00436178` (Port Doğrulayıcı):** Bağlanılmak istenen portun Wonderland Online varsayılan portları olan **25221** (`0x6285`) veya **25620** (`0x6414`) olup olmadığını kontrol eder.
- **`FUN_002d6994` (Paket Gönderim Yardımcısı):** Soket referansı, Opcode, Alt-Opcode ve veri parametrelerini alarak sunucuya paket yollayan ana istemci fonksiyonudur.

---

## 2. Giriş ve Sunucu/Kanal Listesi Paketleri

Giriş ekranında sunucuların çekilmesi ve doğrulama cevaplarının işlenmesiyle ilgili paket handler yapılarıdır.

- **`FUN_0033c310` (Login Response Packet Handler) [Satır: ~303177]:**
  - Sunucudan gelen giriş sonucunu (`param_2 + 1` ofsetindeki byte) kontrol eder.
  - `0x01` gelirse başarılı giriştir: Oyuncunun GUID/Player ID'sini (`DAT_0071ef58 + 0x268`) okur ve kaydeder.
  - `0x02` gelirse "Login/Pwd error" (Kullanıcı adı/şifre hatası) hatası fırlatır.
  - `0x03` / `0x04` durumlarında diğer güvenlik hatalarını gösterir.
- **`FUN_0032f674` (SERVER.INI Parser) [Satır: ~299311]:**
  - Yerel `SERVER.INI` dosyasındaki sunucu ve kanal listesini parse eder. Karakter Seçim / Kanal Seçim ekranına veri hazırlar.
- **`FUN_0014c114` (Channel List Packet Parser) [Satır: ~146882]:**
  - Sunucudan gelen kanal listesini işler (Maksimum 21 kanal).
  - Kanal durum bayrağına göre kanal tiplerini belirler: Normal (`0x01`), PVP (`0x02`), Etkinlik/Özel (`0x03`). IP/Port bilgilerini diziye atar.

---

## 3. Oyun Mekanikleri Paketleri ve Fonksiyonları

### A. Etkinlik ve Sistem Duyuruları Paketi (Satır: ~378494 ve ~379475)
Bu switch-case yapısı, sunucudan gelen etkinlik durum paketlerini dinler ve arayüzde duyuruları tetikler:
- **EXP Etkinliği:** `Double EXP event has begun! Don't miss it!`
- **Mini-Game Etkinliği:** `Double rewards in Item Mall mini-games has begun/ended!`
- **Team PVP Etkinliği (Satır ~379475):** `Team PVP begins in 5 minutes...` ve `Team PVP has begun! Players LV10+...` duyurularını ve LV10 sınırını kontrol eder.
- **Battle Royale Etkinliği (Satır ~178541):** `Battle Royale has begun. Players LV10+ can go to Capitol Building 4F...` duyurusunu ve katılım şartlarını işler.
- **Trojan War Etkinliği (Satır ~180353):** Lonca kısıtlamasını (`Only same guild can join`) ve Branch 1 yönlendirmesini doğrular.

### B. Evcil Hayvan (Pet) Yönetimi, Kısıtlamaları ve Mod Değişimi
Pet durumlarını ve pet takas (trade) paket kurallarını kontrol eden mantıksal bloklar:
- **Savaş Durumu Kısıtlaması (Satır ~141943):** Evcil hayvan savaştaysa (`Pet in battle!`) veya binek olarak kullanılıyorsa (`Pet is mounted!`) işlem yapılmasını engeller.
- **Takas Kısıtlaması (Satır ~306216):**
  - Petin takas edilebilmesi için Pet Kafesi (`Use Pet Cage to trade`) gerekip gerekmediğini denetler. Mamalanmış veya satılamayan pet kısıtlamalarını yönetir.
- **Aktif Pet Çağırma/Gizleme (Satır ~376386 - `FUN_003de310`):**
  - Oyuncunun en fazla 4 pet yuvasını (`iVar1` 1'den 5'e) tarar.
  - Pet yapısındaki `0x1efc` offset bayrağını temizler/setler. Bu bayrak, petin haritada **görünür/aktif** (summoned) olup olmadığını belirler.
- **Pet Yapay Zeka/Yetenek Doğrulaması (Satır ~382158 - `FUN_003e9898`):**
  - Petin ID'si ve yetenek durumlarına göre (örneğin `0x1088`, `0xca0`, `0xafe`, `0x91b`) petin durum kodunu (AI yetenek modu) geri döndürür.
  - `active_pet + 0x121` adresindeki pet mod değerlerini (Savaş, Dinlenme, Tezgah, Dolaşma vb.) durum değişikliklerine göre `0` ile `7` ve geçiş modları olan `0x2f`, `0x31`, `0x33`, `0x35` değerleriyle eşleştirip günceller.

### C. Güvenli Takas ve Stall Mekanizması (Satır: ~200621, ~243850, ~263852)
Oyuncular arası ticaret ve pazar sisteminin paket alt parametreleri:
- **Durum Kontrolleri (Satır ~200621):** Hedef oyuncunun kilitli olup olmadığını (`Target uses Secure Lock`) veya pazar açıp açmadığını (`Target uses Stall`) kontrol eden paket durumlarını işler.
- **Güvenli Takas Arayüzü (Satır ~263852):** Sol ve sağ tarafa yerleştirilen takas eşyalarını paketlemek için `TradeLeftItem`, `OtherSafeTradeItem`, `MySafeTradeItem` gibi metotları çağırır.

### D. Yetenek (Skill) Ağacı ve Savaş Arayüzü (Satır: ~237908, ~266146, ~272183)
Yeteneklerin öğrenilmesi ve savaş esnasında kullanılmasına dair arayüz fonksiyonları:
- **NPC Yetenek Ağacı (Satır ~237908):** `form_npcSkillTree` formunu ve yetenek seviyesi artırma arayüzünü (`icon_levelUp`) oluşturur.
- **Savaş Yetenekleri Kontrolü (Satır ~266146):** Kullanılmaya çalışılan yeteneğin sadece savaşta geçerli olup olmadığını (`Skill only for battle` veya `Can't use skill`) paket içeriğinden doğrular.
- **Savaş Yeteneği Arayüzü (Satır ~272183):** `Form_BattleSkill_1` ve yön tuşu butonlarını (`Btn_ArrowUp_1`) yükler.

### E. Karakter Sınıfları ve Özellikleri (Satır: ~178108)
Karakterlerin savaş alanındaki rollerini ve sınıfsal önceliklerini belirten paket/metin açıklamaları bu fonksiyonda işlenir (Killer, Warrior, Knight).

---

## 4. Görev (Quest / Journal) Mekanikleri ve Paketleri

Oyundaki görevlerin (Quest Journal), lonca davetlerinin ve görev iptal etme işlemlerinin istemci tarafındaki akışını yöneten paket yapısı **Opcode 39 (`0x27`)** üzerinden yürütülür.

`FUN_002d6994` fonksiyonu aracılığıyla sunucuya gönderilen **Opcode 39** alt paket kodları:

- **Alt-Opcode `1` (Görev Listesi/Günlük Talebi):**
  - İstemcideki Görev günlüğü arayüzü (`form_taskview_1`) açıldığında sunucuya aktif görevlerin listesini istemek amacıyla gönderilir (Satır: ~286856).
- **Alt-Opcode `2` (Görev Yardım / Ortak Görev Talebi):**
  - Bir görevde yardım talep edildiğinde veya takım içi görev paylaşımı yapıldığında tetiklenir (Satır: ~408280).
- **Alt-Opcode `7` (Görevi Bırakma / Abandon Quest):**
  - Oyuncu günlükten bir görevi iptal ettiğinde çalışır (Satır: ~409054).
- **Alt-Opcode `10` (0x0a) ve `11` (0x0b):**
  - Görev durumu güncellemeleri veya arayüz tetiklemeleri (Satır: ~409087 ve ~409076).
- **Alt-Opcode `12` (0x0c) (Lonca Üye Listesi Talebi):**
  - Klan arayüzü tetiklendiğinde veya görev günlüğünde lonca üyeleri listelenirken gönderilir (Satır: ~409068).
- **Alt-Opcode `16` (0x10), `17` (0x11), `19` (0x13):**
  - Diğer görev günlük etkileşimleri ve görev durum kayıtları (Satır: ~409961, ~410538, ~411556).
- **Alt-Opcode `50` (0x32) ve `51` (0x33):**
  - Görev bildirim ayarları veya görev izleme (tracking) durum değişim paketleri (Satır: ~390660 ve ~390766).

---

## 5. NPC Tıklama ve Eşleştirme (NPC Click & Matching)

Oyuncunun haritadaki bir NPC'ye tıklaması ve bu tıklamanın sunucu tarafında doğrulanıp doğru NPC ID'siyle eşleştirilmesi mekanizması **Opcode 20 (`0x14`)** üzerinden yürütülür.

### A. İstemci Tarafı Tıklama ve Mesafe Kontrolü (Satır: ~290800)
- Oyuncu haritada bir NPC veya nesneye tıkladığında, istemci öncelikle oyuncunun koordinatları ile tıklanan nesnenin koordinatları arasındaki mesafeyi ölçer:
  ```c
  uVar4 = player_x - npc_x;
  uVar5 = player_y - npc_y;
  ```
- Mesafe her iki eksende de **`0xa9` (169 piksel)** değerinden büyükse tıklama eylemi iptal edilir:
  ```c
  if (0xa9 < abs(uVar4)) return;
  if (0xa9 < abs(uVar5)) return;
  ```
- Karakter yeterince yakınsa, tıklanan nesnenin harita üzerindeki benzersiz dizin index'i (`target_idx` / `click_id`) kaydedilir ve sunucuya etkileşim paketi gönderilir:
  ```c
  FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4, 0x14, 1, 0); // Opcode 20, Sub-opcode 1
  ```

### B. Sunucu Tarafı Eşleştirme ve Çözümleme:
- Bulunan NPC'nin şablon ID'si (`npc_id`), istemci tarafından gönderilen şifreli/kodlanmış haldedir. Sunucu, bu ID'yi veritabanı ID'sine (`db_id`) dönüştürmek için aşağıdaki **NPC Eşleştirme Algoritmasını** kullanır:
  ```python
  dec_no_offset = (npc_id & 0xFFFF) ^ 0x5209
  dec_with_offset = dec_no_offset - 9
  ```
  Burada **`0x5209` (21001)** değeri, istemcinin harita dosyalarında veya veri yapılarında NPC şablon ID'lerini maskelemek için kullandığı XOR anahtarıdır.

### C. İstemci Tarafı Özel Şablon ID Eşleştirmeleri (Satır: ~350823 - `FUN_003ab628`):
İstemci bazı özel NPC template ID'lerini paketlemeden veya işlemeden önce kendi içinde statik olarak dönüştürür:
- **`0x908e` (36999)** -> **`0x5209` (21001)** değerine dönüştürülür.
- **`0x9092` (37010)** -> **`0x9090` (37008)** değerine dönüştürülür.
- **`0x9093` (37011)** -> **`0x9091` (37009)** değerine dönüştürülür.
- **`0x9094` (37012)** -> **`0x9095` (37013)** değerine dönüştürülür.
- **`0x9096` (37014)** -> **`0x9097` (37015)** değerine dönüştürülür.

---

## 6. İstemci Tarafı Canavar Veritabanı ve Savaş Tetikleme (Client Side Encounters)

`aLogin.exe` istemcisi, vahşi doğadaki rastgele savaşları (random encounters) ve canavar listelerini tamamen kendi yerel veritabanı dosyalarından okuyarak yönetir.

### A. Canavar Özellikleri ve Şablon Veritabanı (`Data\odd.dat`):
- İstemci, oyundaki tüm canavarların adlarını, seviyelerini, elementlerini, grafik dosyalarını ve savaş istatistiklerini `"Data\odd.dat"` dosyasından yükler (Eğer bu dosya yoksa `"Data\odd_d01.dat"` dosyasına fallback yapar).
- Bu dosya istemci açılışında stream decryptor (şifre çözücü) fonksiyonlar (`FUN_00024290` ve `FUN_00023ea8` vb.) ile okunarak hafızada `PTR_DAT_004c8cf4` ve `PTR_DAT_004c8898` işaretçi adreslerinde saklanır.
- Bir canavarın veya NPC'nin şablon özelliklerini sorgulamak için `FUN_0010eaa8` fonksiyonu kullanılır.

### B. Harita Karşılaşma ve Bölge Listesi (`user\Map\<MapID_XOR_0x190c>.MapData`):
- İstemci, oyuncunun o an bulunduğu haritadaki vahşi canavar karşılaşma havuzunu ve bölgelerini `"user\Map\"` altındaki `.MapData` dosyalarından okur.
- Hedef harita dosya adının bulunması için Map ID değeri **`0x190c` (6412)** sabiti ile XOR işlemine tabi tutulur:
  ```c
  // Harita Dosya Yolu Çözümleme (Satır: ~297951 ve ~297969)
  map_file_id = current_map_id ^ 0x190c;
  format("user\\Map\\%d.MapData", map_file_id);
  ```
- `.MapData` dosyaları `FUN_000243ec` ve `FUN_00013144` fonksiyonları ile çözülerek belleğe aktarılır. Dosyanın içerisinde **`0x24` (36 byte)** uzunluğunda kayıt blokları halinde canavar karşılaşma bölgeleri (koordinat kutuları), karşılaşma olasılıkları ve canavar spawn havuzları saklanır.

### C. Yürüyüş Esnasında Savaşın Tetiklenmesi (Step Counter & Encounter Trigger):
- Oyuncu harita üzerinde hareket ettikçe (veya `0x5549` bayrağının aktif olduğu **Auto Walk** durumunda), istemci oyuncunun koordinatlarını kontrol eder ve adım sayacını günceller.
- Oyuncu eğer `.MapData` içerisinde tanımlanmış bir karşılaşma bölgesindeyse ve adım limitine ulaşıldıysa, o bölgenin spawn havuzundan olasılıklara göre rastgele bir canavar seçilir.
- Seçilen canavarın ID bilgisi `odd.dat` veritabanından doğrulanır ve sunucuya **Opcode 11 (`0x0b`), Sub-opcode 2** (Combat request) paketi gönderilerek savaş başlatılır:
  ```c
  // Savaş Talep Paketinin Gönderilmesi (Satır: ~348158)
  FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4, 0xb, 2, 0); 
  ```

---

## 7. İstemci Ağ Paket Dağıtıcıları (Packet Dispatchers)

İstemci tarafında sunucudan gelen paketlerin işlenmesi ve dağıtılması iki ana fonksiyon tarafından yürütülür:

- **`FUN_00115a38` (Main Packet Dispatcher 1):**
  - Sunucudan gelen paketlerin ilk baytı olan **OPCODE** değerini okur.
  - Bir `switch-case` tablosu üzerinden Chat (`0x02`), Movement (`0x06`), Action (`0x13`), Interaction (`0x14`), Item (`0x17`), Trade (`0x19`), Quest (`0x27`), Battle (`0x32`) ve Login (`0x3f`) alt paket yönlendiricilerini çalıştırır.
- **`FUN_0010e218` (Main Packet Dispatcher 2):**
  - Arayüz ve form tetikleyicilerine ait paketleri (Action 19, Interaction 20, Item 23, Trade 25, Battle 50) süzerek ilgili form nesnelerine yansıtır.

---

## 8. Sunucu Tarafı Güvenlik ve PVP Savaş Entegrasyon Metotları

İstemci analizlerinden elde edilen verilere göre sunucu tarafında (`gameserver.py`, `handle_11_combat.py`, `handle_20_interaction.py` ve `handle_50_battle.py`) uygulanan ve istemciyle birebir eşleşen yeni metotlar:

### A. NPC Etkileşim ve Mesafe Güvenlik Kontrolleri
- **NPC Tıklama Mesafesi:** `handle_20_interaction.py` üzerinde oyuncu NPC'ye tıkladığında, istemcinin `FUN_0031d874` mesafesiyle (`0xa9` = 169 piksel) aynı kontrol sunucuda yapılır. Aşılırsa paket reddedilir.
- **Canavar Savaş Mesafesi:** `gameserver.py` içerisindeki `_start_pve_battle` fonksiyonunda, oyuncunun tıkladığı canavarla mesafesi 169 pikseli aşıyorsa savaş başlatılması engellenir.

### B. PVP Düello (PK) Savaş Motoru Entegrasyonu
- **PK Davet ve Mesafe Doğrulaması:** `handle_11_combat.py` üzerinde `pk_type == 3` (PK Daveti) geldiğinde, istemcinin `FUN_003a7154` mesafesiyle (`0x10f` = 271 piksel) eşleşen mesafe kontrolü sunucu tarafında doğrulanır. Davet eden ve edilen oyuncunun aynı haritada olması şart koşulur.
- **`_start_pvp_battle(challenger, target)`:** İki oyuncuyu ve aktif petlerini düello alanına alır. Oyuncuları `role=1/2` ve petleri `role=5/6` olarak setler.
- **`_send_pvp_battle_start_to_client`:** Her iki oyuncunun istemcisine, kendilerini merkezde rakiplerini karşıda gösterecek şekilde `AC 11:250` (oyuncu verisi) ve `AC 11:5` (rakip verisi) paketlerini yollar.
- **`_resolve_pvp_turn`:** Oyuncu ve petlerin hız değerlerini (`spd`) karşılaştırarak saldırı sırasını (Turn Order) belirler. Hasar ve yetenek etkilerini hesaplayıp ortak animasyon (`AC 50:1`) ve durum güncelleme (`AC 51:1`) paketlerini her iki istemciye yayınlar.
- **`_end_pvp_battle`:** Savaş bittiğinde kazananı belirler, `AC 11:0` ve `AC 11:1` ile düelloyu sonlandırıp oyuncuların `in_battle` durumlarını temizler.
- **`handle_50_battle.py` (PVP Sıra Çözümleme):** Hem challenger hem de target oyuncunun (ve petlerinin) o tura ait hamlelerini (`expected_coords`) yapmasını bekler ve tüm hamleler tamamlandığında turu çözer.

---

## 9. İstemci-Sunucu Ağ Protokolü OPCODE Eşleşme Tablosu

Wonderland Online istemci (`aLogin.exe`) ve sunucu (`server/handlers/`) arasındaki paket OPCODE'larının ve alt sistemlerinin tam listesi:

| Opcode (Dec) | Opcode (Hex) | Özellik / Sistem Adı | Sunucu Handler Dosyası | İstemci Dağıtıcı / Açıklama |
|---|---|---|---|---|
| **0** | `0x00` | El Sıkışma (Handshake) | `handle_0_handshake.py` | Soket doğrulama ve ilk bağlantı kurulumu |
| **2** | `0x02` | Sohbet (Chat System) | `handle_2_chat.py` | Genel, Takım, Lonca, Fısıldama kanalları (`FUN_00115a38` case 2) |
| **6** | `0x06` | Hareket (Movement) | `handle_6_movement.py` | Grid tabanlı yürüme ve yön paketleri (`FUN_00115a38` case 6) |
| **8** | `0x08` | Karakter Statları | `handle_8_stats.py` | Seviye puanı dağıtımı ve stat eşleme (`FUN_00115a38` case 8) |
| **9** | `0x09` | Karakter Oluşturma | `handle_9_char_creation.py` | Yeni karakter görünüm ve isim kaydı (`FUN_00115a38` case 9) |
| **11** | `0x0b` | Savaş / PK Başlatma | `handle_11_combat.py` | Savaş isteği ve PK düello daveti (`FUN_00115a38` case 0xb) |
| **12** | `0x0c` | Işınlanma (Warp) | `handle_12_warp.py` | Harita geçişleri ve portal warp tetikleyicisi (`FUN_00115a38` case 0xc) |
| **14** | `0x0e` | Arkadaşlar & Posta | `handle_14_friends.py` | Arkadaş listesi, posta ve fısıltı engeli (`FUN_00115a38` case 0xe) |
| **15** | `0x0f` | Yoldaş (Pet) | `handle_15_companion.py` | Evcil hayvan çağırma/mod değiştirme (`FUN_00115a38` case 0xf) |
| **19** | `0x13` | Karakter Eylemleri | `handle_19_action.py` | Emotelar, oturma ve özel hareketler (`FUN_00115a38` case 0x13) |
| **20** | `0x14` | NPC Diyalog / Seçim | `handle_20_interaction.py` | NPC konuşmaları ve diyalog seçenekleri (`FUN_00115a38` case 0x14) |
| **23** | `0x17` | Eşyalar (Item) | `handle_23_items.py` | Eşya kullanımı, çöpe atma, simya birleştirme (`FUN_00115a38` case 0x17) |
| **25** | `0x19` | Ticaret / Stall | `handle_25_trade.py` | Oyuncular arası takas ve pazar tezgahı (`FUN_00115a38` case 0x19) |
| **30** | `0x1e` | Ek Eylemler 1 | `handle_30_action.py` | Karakter oturma/kalkma senkronizasyonu (`FUN_00115a38` case 0x1e) |
| **31** | `0x1f` | Ek Eylemler 2 | `handle_31_action.py` | Diğer hareket animasyon paketleri (`FUN_00115a38` case 0x1f) |
| **33** | `0x21` | Ayarlar (Settings) | `handle_33_settings.py` | Grafik, ses ve arayüz seçenekleri (`FUN_00115a38` case 0x21) |
| **35** | `0x23` | Karakter Silme | `handle_35_char_deletion.py` | Karakter silme istek doğrulaması (`FUN_00115a38` case 0x23) |
| **37** | `0x25` | Arayüz Eylemleri | `handle_37_action.py` | Arayüz kapatma ve menü durumları (`FUN_00115a38` case 0x25) |
| **39** | `0x27` | Görev Günlüğü (Quest) | `handle_39_quest.py` | Görev listesi, yardım ve iptal paketleri (`FUN_00115a38` case 0x27) |
| **43** | `0x2b` | Takım / Grup (Team) | `handle_43_team.py` | Takım kurma, davet etme ve ayrılma (`FUN_00115a38` case 0x43) |
| **50** | `0x32` | Savaş Tur Girişleri | `handle_50_battle.py` | Savaş turu eylemleri (saldır/defans/kaç) (`FUN_00115a38` case 0x50) |
| **54** | `0x36` | Özel Duyurular | `handle_54_action.py` | Etkinlik duyuruları ve sistem mesajları (`FUN_00115a38` case 0x54) |
| **63** | `0x3f` | Giriş / Login | `handle_63_login.py` | Sunucu doğrulama ve giriş işlemleri (`FUN_00115a38` case 0x3f) |

---

## 10. İstemcide Tespit Edilen Ek Gizli Oyun Mekanikleri

aLogin decompile kodlarında taranan anahtar kelimelere göre oyunda yer alan diğer gizli/ileri seviye mekanikler ve bunları yöneten istemci fonksiyonları şunlardır:

### A. Evlilik (Marriage) Sistemi (`FUN_0021e388` ve `FUN_0021d414`):
- Oyuncuların evlenebilmesi için en az **Level 30** olması şarttır (`Requires LV30 to marry`).
- Aynı cinsiyetteki karakterlerin evlenmesi engellenmiştir (`Can't marry same gender`).
- Evlilik töreni başlatıldığında istemci genel duyuru geçer ve töreni başlatır (`Marriage ceremony has begun`, `Marriage matched in heaven for the lifetime.`).

### B. Çadır ve Mobilya (Tent & Furniture) Sistemi (`FUN_0025caa0` ve `FUN_0022c738`):
- Oyuncunun kişisel çadırı içerisine yerleştirebileceği mobilyalar ve alan sınırları kontrol edilir. Yeterli yer olmadığında `"No space for furniture"` uyarısı verilir.
- Savaş esnasında çadır içindeki mobilyaların sabitlenmesi veya düzenlenmesi engellenmiştir (`Can't fix in battle`).

### C. Kaplıca / Hamam (Hot Spring) Sistemi (`FUN_0040a774`):
- Karakterlerin kaplıcada kalarak HP/SP yenileme sürelerini denetler (`Hot Spring Pack time: `, `Hot Spring ended`).
- Maksimum kaplıca süresi dolduğunda karakteri kaplıcadan çıkarır (`Hot Spring time at max!`).

### D. Evcil Hayvan Evrimleşme (Pet Reborn) Sistemi (`FUN_0022b454` ve `FUN_0022b668`):
- Petlerin evrimleşebilmesi (reborn) için üzerlerindeki tüm pet ekipmanlarının çıkarılmış olması gerekir (`Remove all pet equips to reborn`).

### E. Kısayol Tuş Atamaları (Hotkey System) (`FUN_002a8fe0`):
- Yeteneklerin ve eşyaların hızlı kullanım çubuğuna (`Form_HotKey_V`) atanmasını ve senkronizasyonunu yönetir.

---

## 11. İstemcide Tespit Edilen Diğer İleri Seviye Özellikler

### A. Uzaktan Kumanda / Otomatik Savaş Botu (Remote Control) (`FUN_001fe658` ve `FUN_001fec48`):
- WLO'nun meşhur yerleşik bot sistemidir. Bot profili kaydetme (`Remote profile saved`) ve profil yükleme işlemlerini yönetir. Yapılandırma bulunamazsa `"No Remote config"` uyarısı döner.
- Sunucular arası haritalarda bot kullanımını engeller (`Can\'t auto-use at Interserv`).
- Otomatik EXP iksiri kullanım durumunu doğrular (`Auto-use EXP Potion is on` -> `FUN_001c5274`).

### B. Eşya Dövme ve Güçlendirme (Forge & Refine) (`FUN_001e0988` ve `FUN_001e3214`):
- Eşyalara artı basma ve istatistik ekleme arayüzleridir. Dövülebilir olmayan eşyalarda veya ekipman olmayan nesnelerde `"Can\'t forge this"` veya `"Can\'t forge this Eq"` uyarısı döndürülür. Sadece dövülmüş nesneler için `"Forged items only"` doğrulamasını yapar.

### C. Pet Eğitim Oteli (Pet Training INN) (`FUN_0023d1c4` ve `FUN_003de45c`):
- Evcil hayvanları tecrübe puanı kazanmaları için eğitime bırakma (`panel_restrainINN_2`) ve eğitimdeki petlerin takas/çıkarılma engellerini (`Can\'t replace, pet in training`) denetler. Eğitilecek pet yoksa `"No pet to train"` uyarısı verilir.

### D. Posta Kutusu ve Mektup (Mailbox System) (`FUN_001adc88` ve `FUN_001ee918`):
- Mektup alım ve gönderim loglama dosyalarını yönetir (`\MailBoxMsgLog` ve `\MsgMailBoxLog`).
- Posta kutusu %90 doluluğa ulaştığında oyuncuya bildirim geçer: `"Mailbox volume at 90%. When full, old letters get deleted"`. Postadan mektup silindiğinde `"Letter removed"` uyarısı tetiklenir.

### E. PVP Arena Sistemi (`FUN_003e6c10`):
- PVP arenasının başlangıç ve bitiş duyurularını yönetir (`PVP arena has begun! Come and join at venue!`, `PVP arena has ended! Come again next time!`).

### F. Lonca Feshetme (Guild Disband) (`FUN_0030f634` ve `FUN_00418280`):
- Oyuncunun kurduğu loncayı/birliği silme/feshetme onay arayüzünü yönetir (`Disband your Guild?`). Fesih gerçekleştiğinde oyunculara `"Disbanded"` durum güncellemesi yollanır.

### G. Karnaval ve Takım Kısıtlamaları (`FUN_001d9f08` ve `FUN_0021e388`):
- Oyuncu takım/grup (party) halindeyken Karnaval alanına erişimi engeller (`Can\'t access Carnie with party`).
- Evlilik töreni veya benzeri grup aktivitelerinde gruptaki yanlış üye durumunu denetler (`Wrong party member`).

### H. Tezgah / Pazar Kurma (Stall) Kısıtlamaları (`FUN_0013e694` ve `FUN_0017ad30`):
- Hedef oyuncu pazar tezgahı açmışsa tıklanıldığında `"Stall is being used"` uyarısı döner.
- Oyuncu pazar kurup satış yaparken bazı yetenek veya eşyaların kullanımını engeller (`Can\'t use when selling`).

---

## 12. İstemcide Tespit Edilen Diğer Yardımcı Alt Sistemler

### A. DirectSound Ses ve BGM Motoru (`FUN_0007bdc0`, `FUN_001399f4` ve `FUN_00140c50`):
- Ses kartıyla iletişim kurmak için `DSound.dll` ve `DirectSoundCreate` API'lerini dinamik yükler.
- Oyun içi arka plan müziklerini (BGM) (`sound\BGM0019.wav` vb.) ve ses efektlerini (WAV) yönetir.

### B. Lonca Kalesi Kuşatmaları (Castle Siege) (`FUN_001a6498` ve `FUN_001a6768`):
- Lonca savaşlarında kaleyi ele geçiren veya savunan loncaları anons eder (`defended castle`).
- Kaleyi sahiplenmiş aktif lonca bulunmuyorsa `"No guild own Castle"` durumunu doğrular.

### C. Mini Oyun (Mini-games) Limit ve Engelleri (`FUN_001c5400` ve `FUN_0036d26c`):
- Oyuncu şans çarkı veya mini oyun ekranındayken diğer yetenek veya eşya kullanım paketlerini engeller (`Can\'t use in mini-game`).
- Başka bir oyuncu mini oyundaki hedefe eylem yaptığında `"Target in mini-game"` uyarısı fırlatır.

---

## 13. Yetenek (Skill) Öğrenme ve Genişleme Paketi Mekanikleri

### A. Element Tabanlı Yetenek Sınırlamaları (`FUN_00256ed4`):
- Karakterlerin kendi elementleri dışındaki yetenekleri öğrenmesi engellenmiştir. Örneğin, toprak elementi karakterler için `"Can\'t learn Earth skill"` (veya diğer elementlerin yetersizlik) doğrulamaları tetiklenir.

### B. Hızlı Kısayol Yetenek Sınırı (`FUN_001d71cc`):
- Hızlı kısayol tuş çubuğuna sadece saldırı/aktif yeteneklerin yerleştirilmesini denetler. Pasif veya destek dışı yeteneklerde `"Can\'t set non-Atk skill"` uyarısı döndürülür.

### C. Dark Spell Genişleme Paketi Denetimi (`FUN_003cf7ac` ve `FUN_0045ab80`):
- İstemci açılışında ve harita geçişlerinde `"Dark Spell"` genişleme paketine ait dosyaları denetler. Eksik veya bulunamayan dosya durumunda oyuncuya `"Dark Spell expansion not found"` uyarısı gösterilir.

---

## 14. Nesne Market (Item Mall / NPC Shop) ve Puan Sistemleri

### A. Eşya Dükkan Arayüzü (Form_EightTwelve) (`FUN_001aec08`):
- İstemci, oyun içi Item Mall veya NPC Dükkan arayüzü olarak `"Form_EightTwelve"` form nesnesini belleğe yükler.
- Satın alım işlemini tetiklemek için `"Btn_Buy_1"` butonu tanımlanır ve tıklama tetikleyicisi olarak `FUN_001af620` geri çağırım fonksiyonuna bağlanır. Seçilen nesneleri `"NpcStoreSelectedItem"` slotlarında depolar.

### B. Bakiye / Puan Yetersizliği Denetimi (`FUN_001af620`):
- Satın alma işlemi tetiklendiğinde oyuncunun güncel cüzdan bakiyesini (Item Mall Points) kontrol eder:
  ```c
  if (points < item_cost) {
      // Puan yetersiz uyarısı gösterilir
      ShowAlert("Not enough Points");
  }
  ```
- Eğer bakiye yeterliyse, satın alım onayı (`FUN_00366ebc`) metin kutusunda gösterilerek onaylanması istenir.

---

## 15. Depolama, Çadır İçi Dolaplar ve Geri Dönüşüm (Recycling) Mekanizmaları

### A. Eşya Dolabı (Cabinet) Doluluk Denetimi (`FUN_0044651c`):
- Oyuncunun çadırındaki eşya dolabına eşya yerleştirirken doluluk durumunu kontrol eder. Dolap limiti aşıldığında `"Cabinet is full, can\'t store"` uyarısı döndürülür.

### B. Çadır Depolama Yöneticisi (`FUN_0044e008`):
- Çadır deposuna yeni nesneler eklendiğinde arayüze başarıyla yüklendiğini bildiren `"Added to tent storage"` durum metnini tetikler.

### C. Geri Dönüşüm Kutusu (Recycling Machine) Sınırları (`FUN_00376178`):
- Çadırdaki geri dönüşüm cihazı çalıştırıldığında, çıktı eşyasının yerleştirileceği depolama alanının doluluk durumunu doğrular. Depo doluysa `"Can\'t recycle, storage full"` uyarısı verilir ve işlem durdurulur.

### D. EXP Boost Katlayıcı Durumu (`FUN_001a8c54`):
- Karakterlerin EXP potu veya iksirleri kullanarak tecrübe katlayıcı buff durumlarını yükler. Aktif olduğunda `"EXP Boost"` görsel uyarısını sohbette veya arayüzde görüntüler.

---

## 16. Taşıt Depolama (Garaj) ve Montaj (Crafting) Mekanizmaları

### A. Kişisel Garaj (Garage) Doluluk Kontrolü (`FUN_0044651c`):
- Oyuncunun sahip olduğu araç ve binek taşıtlarını (sal, kano, araba vb.) depoladığı garajın sınırlarını denetler. Garaj doluysa `"Garage is full, can\'t store"` uyarısı döndürülür.
- Taşıtların çadır içinde sergilenmesi için de garaj kaydının varlığını şart koşar: `"Display requires garage"`.

### B. Taşıt Montaj ve Yarı-Mamul Sınırı (`FUN_0013d794`):
- Tersane veya montaj masasında kano, sal, uçak gibi araçlar inşa edilirken limit kontrolü yapar. Üretilemeyen bir nesne için `"Can\'t craft"` hatası verilir.
- Aynı anda maksimum yarıda kalmış/inşa halinde olan taşıt sayısını 5 ile sınırlar, aşılırsa `"Already 5 semi-finished crafts"` uyarısı verir.

---

## 17. Sosyal İlişkiler, Güvenlik Kilidi ve Savaş Gözlemcisi Mekanizmaları

### A. Güvenli Kilit (Secure Lock) ve Engelleme (`FUN_001d9f08`):
- Oyuncular arası takas, arkadaş ekleme veya etkileşim isteklerinde hedef oyuncunun Secure Lock (güvenli şifre kilidi) ile korunup korunmadığını kontrol eder. Korumalı durumdaysa `"Target uses Secure Lock"` hatasını döndürür.
- Ayrıca karşı tarafın sizi engelleyip engellemediğini (` ignore`) kontrol eder.

### B. Kara Liste / Engelleme Sistemi (Blacklist) (`FUN_001b8ee8` ve `FUN_00269700`):
- Sosyal etkileşimde engellenen kişilerin işlemlerini denetler. Kara listedeki bir oyuncu işlem yapmak istediğinde `"Blacklisted by target"` veya `"You\'ve been blacklisted"` uyarısını tetikler.

### C. Savaş İzleyici (Spectate System) Engelleri (`FUN_001a4d00` ve `FUN_002a6ef0`):
- Devam eden PvE veya PvP savaşlarına izleyici olarak katılma durumunu doğrular. Savaş izlenemez moddaysa `"Can\'t spectate"` uyarısı verir.

### D. Etkinlik Kupon Sınırı (Coupon System) (`FUN_002c1408`):
- Belirli mini oyunlara veya özel etkinliklere katılırken oyuncunun kupon cüzdanını sorgular. Yetersiz kupon durumunda `"Not enough coupons, can\'t join"` veya `"Player %s lacks coupons"` uyarısı verilir.

---

## 18. Banyo (Bathing), Yakıt Tüketim ve Kostüm Sistemleri

### A. Hamam/Banyo (Bathing State) Kısıtlamaları (`FUN_0013d794`, `FUN_001b5784` ve `FUN_003a6f18`):
- Oyuncunun banyoda yıkanması (Bathing) durumundaki kısıtlamaları yönetir.
- Yıkanma esnasında taşıt/araç üretimi engellenir (`Bathing, unable to make`).
- Yıkanırken çanta eşyalarının ve yeteneklerin kullanımı yasaklanır (`Can\'t use in bath`).
- Yıkanma süresince savaş veya diğer eylemler engellenir (`Bathing, can\'t act`).

### B. Ev Aletleri Yakıt Uygunluk Denetimi (`FUN_001f225c`):
- Çadır içi üretim fırını veya ocaklarda kullanılan yakıt türünü doğrular. Uygun olmayan yakıt konulduğunda `"No suitable fuel type"` uyarısı verilir.

### C. Tavşan Kostümü (Rabbit Suit) ve Kozmetikler (`FUN_0026db14`):
- Oyundaki özel Rabbit Suit (Tavşan Elbisesi) veya benzeri kozmetik kostümlerin oyuncu entity'si üzerindeki görsel ve yapısal çizimlerini yönetir.

---

## 19. Ağ İstekleri Zaman Aşımı (Response Timeout) Mekanizmaları

### A. Etkileşim İstekleri Zaman Aşımı Kontrolü (`FUN_0021e388` ve `FUN_002259a8`):
- İstemci ile sunucu arasındaki etkileşimlerde (örneğin evlilik davetleri, secure trade onayları veya takım katılım istekleri) sunucudan cevap alınması için belirli bir süre tanınır.
- Tanınan süre aşılırsa işlem iptal edilir ve oyuncuya `"Response timeout, aborted"` veya `"Response timeout, canceled"` durum uyarıları gösterilir.

---

## 20. Karakter Sınıfları (Reborn Jobs) ve Pasif Yetenek Bonusları

İstemcideki sınıf tanıtımları ve pasif istatistik hesaplama rutinlerine (`FUN_001a3f68` ve `FUN_001a4424`) göre karakter sınıflarının kazandığı özel bonuslar:

### A. Killer (Katil):
- Saldırı gücünde çok büyük oranda pasif ATK artışı kazanır (`greatly increased ATK`). Savaşta kritik vuruş olasılığını ve hasar çarpanını yükseltir.

### B. Warrior (Savaşçı):
- Hız ve çevikliğinden feragat ederek çok yüksek oranda savunma (DEF) gücü kazanır (`increased DEF`).

### C. Knight (Şövalye):
- Binek hızı avantajına sahiptir. Bineğe eyer (saddle) takılmamış olsa dahi, bineğin hızının (SPD) 5'te 1'ini (`1/5 SPD of their mount without a saddle`) doğrudan kendi SPD değerine ekler.

### D. Mage (Büyücü):
- Saldırı büyüleri hasarını artırır. Ekipmanlar hariç ham büyüsel saldırı gücünü %10 oranında artırır (`Increases MATK by 10% (without equips)`).

### E. Priest (Rahip):
- Mistik enerjilere ve büyülere karşı dirençlidir. Karakterin ham büyüsel savunma (MDEF) değerini ve savaşta hayatta kalma süresini artırır.

---

## 21. Giriş Sunucu Hataları ve Şifre Doğrulama

### A. Giriş Sunucusu Bağlantı Hatası (`FUN_00161c64`):
- İstemcinin giriş (login) sunucusu ile bağlantı kuramadığı durumları denetler. Sunucu çevrimdışıysa `"Can\'t reach login server"` uyarısı döndürülerek oyuncu giriş ekranına (`Icon_LoginLogo_1`) yönlendirilir.

### B. Karakter İşlem Şifre Doğrulaması (`FUN_002345c8` ve `FUN_0026fee4`):
- Karakter seçimi, silinmesi veya şifreli diğer güvenlik işlemlerinde girilen şifrenin doğruluğunu kontrol eder. Eşleşme başarısız olursa arayüzde `"Wrong Passwords"` hatasını fırlatır.

---

## 22. Evcil Hayvan / Yoldaş (Companion) Tıklama ve Diyalog Mekanizmaları

### A. Yoldaş Etkileşim Menüsü (`FUN_0026db14`):
- Oyuncunun aktif olan insansı yoldaşına (Niss, Fred, Xaolan vb.) haritada tıkladığında tetiklenen özel diyalog sistemidir.
- Yoldaş, oyuncuya `"Master, what can I do for you?"` (Sahibim, sizin için ne yapabilirim?) sorusuyla etkileşim seçenekleri (yardım, durma vb.) sunar.
- Oyuncu, yoldaşına ne giyeceğini sorma seçeneğiyle (`"Master, what should I wear?"`) onun ekipman ve kozmetik giysi penceresini açar.

---

## 23. Lonca (Guild / Birlik) Yönetim Arayüzü ve Kuralları

İstemcideki lonca işlemlerini, listeleri, duyuruları ve müttefik denetimlerini gerçekleştiren C fonksiyonları şunlardır:

### A. Lonca Kurma ve İsim Limitleri (`FUN_00417d04`):
- Yeni birlik kurarken girilen lonca isminin geçerliliğini denetler. İsim kurallara uymuyorsa `"Wrong Guild name"` uyarısı verilir.
- Sunucu genelindeki maksimum aktif lonca sayısına ulaşıldıysa `"Too many Guilds"` hatası fırlatılır.

### B. Loncaya Katılım ve Başvuru (`FUN_00418854` ve `FUN_004190d8`):
- Haritadaki bir oyuncuyu loncaya davet ederken veya başvuru listesini incelerken `"Want to join guild"` penceresini açar.
- Eğer loncanın üye limiti doluysa `"Guild is full"` uyarısı döndürülür. Loncada olmayan oyuncuların klan menüsü işlemlerinde `"Join Guild first"` hatası verilir.

### C. Loncadan Ayrılma (Leave Guild) (`FUN_00417fb4`):
- Oyuncu klandan çıktığında arayüze ve sohbete `"You left Guild"` veya `"Leaves Guild"` sistem durum bildirimlerini yansıtır.

### D. Lider Duyuru ve Kuralları (Guild Rules) (`FUN_00419894`):
- Lonca liderinin arayüzden klan duyurularını ve kurallarını güncellemesini yönetir: `"Leaders, setup rules as follows.\nIt's very simple:\n1. 200 chars\n2. Click Modify Rules\n3. Guild Message to Announce to all"`.

### E. Lonca Müttefikleri (Guild Allies) (`FUN_0031764c`):
- Loncaya ait müttefik klanların ve ortaklık ilişkilerinin varlığını doğrular. Müttefiklik yoksa `"No guild allies"` durumunu işler.

### F. Lonca Listesi Arayüzü (Guild List) (`FUN_001fa870`):
- Arayüzdeki `"Guild List"` tablosunu ve butonlarını yükler, listeyi çekmek için `FUN_001fc72c` callback metodunu dinler.

---

## 24. Evcil Hayvan Dostluk (Pet Amity) ve Sadakat Sınırları

### A. Dostluk Puanı (Amity) Savaşı Yetenek Kısıtlaması (`FUN_001a72e8`):
- Evcil hayvanların (pet) sadakat durumunu belirleyen Amity (Dostluk) puanını denetler.
- Eğer yoldaşın/evcil hayvanın Amity değeri 40'ın altına düşerse savaşta yetenek veya eşya kullanması engellenir: `"Can\'t use, Amity below 40"`.

### B. Karakter/Pet Kartı Bilgi Güncelleme (`FUN_001c5cb0`):
- Petin arayüz detay kartında Amity durumunun anlık olarak güncellenmesini ve arayüze basılmasını yönetir.

---

## 25. Simya ve Eşya Birleştirme (Alchemy / Compound) Mekanizmaları

### A. Simya Arayüzü ve Yetenek Simgesi (`FUN_002351fc`):
- Oyuncunun envanterindeki eşyaları birleştirerek yeni nesneler üretmesini sağlayan simya arayüzünü (`Form_Compound_1`) yükler.
- Simya işlemi esnasında yetenek barında gösterilecek simya ikonunu (`Icon_UseCompoundSkill`) çizer.

### B. Simya Yetenek Seviye Kontrolleri (`FUN_00237d00`):
- Oyuncunun simya yeteneğinin (Alchemy skill) seviye ve yetki kontrolünü yapar. Seviyeye göre arayüzdeki başlığı `"Use Junior Alchemy"` (Düşük Seviye Simya Kullan) veya daha üst sürümlerle günceller.

---

## 26. Sohbet Kanalları ve Filtreleme Mekanizmaları

### A. Sohbet Kanalı Açık/Kapalı Kontrolleri (`FUN_0027e180`):
- Oyuncunun girmek istediği sohbet kanalının (Fısıltı, Takım, Lonca, GM vb.) durumunu doğrular. Kanal kapalı veya engelliyse ilgili uyarıları fırlatır:
  - Fısıltı kapalıysa: `"Whisper is closed"`
  - Takım sohbeti kapalıysa: `"Team chat is off"`
  - Lonca sohbeti kapalıysa: `"Guild chat is off"`
  - GM sohbeti kapalı/engelliyse: `"GM Chat disabled"`

### B. Sohbet Kanal Etiketleme (`FUN_003f3b10`):
- Gelen mesajların hangi kanala ait olduğunu belirten etiketleri ekler (örneğin fısıltı mesajları için `"Direct: "` veya GM mesajları için `"GM Chat"` öneki).

---

## 27. Güvenli Takas (Secure Trade) ve Eşya Sınırları

### A. Güvenli Takas (Secure Trade) Durum Engeli (`FUN_001d9f08`):
- Oyuncunun takas aşamasındayken başka etkileşimlere girmesini engeller. Takas aktifken `"In a Secure Trade"` durumunu denetler.

### B. Takas Edilemez Eşya Etiketleme (`FUN_001c5cb0`):
- Oyuncunun envanterindeki eşyaların detay pencerelerinde veya takas listelerinde eşya kısıtlamasını kontrol eder. Takas edilemeyen eşyalar için `<Non-tradeable>` (Takas Edilemez) ibaresini ekler.

### C. Takas İptal Bildirimi (`FUN_003221b4`):
- Karşılıklı takas ekranında oyunculardan biri takası iptal ettiğinde sohbette veya sistem günlüğünde `"Cancel deal"` uyarısını tetikler.

---

## 28. Eşya Hammadde Sınıfları (Material Type) Eşleştirme Tablosu

İstemci tarafında eşyaların simya (alchemy) birleştirmelerinde ve envanter niteliklerinde hangi hammadde grubuna ait olduğunu belirten ID çözme fonksiyonu **`FUN_0049f5e8`**'dir. Bu fonksiyon, sayısal malzeme sınıflarını şu şekilde eşleştirir:

| **Hammadde ID** | **İstemci String Adı** | **Türkçe Karşılığı** |
| :--- | :--- | :--- |
| **1** | `Flower` | Çiçek |
| **2** | `Grass` | Çimen / Ot |
| **7** | `Veggie` | Sebze |
| **8** | `Fruit` | Meyve |
| **13 (`0xd`)** | `Seafood` | Deniz Ürünü |
| **30 (`0x1e`)** | `Diamond` | Elmas |
| **31 (`0x1f`)** | `Crystal` | Kristal |
| **32 (`0x20`)** | `Mercury` | Cıva |
| **33 (`0x21`)** | `Silver` | Gümüş |
| **34 (`0x22`)** | `Stone` | Taş |
| **35 (`0x23`)** | `Magnet` | Mıknatıs |
| **43 (`0x2b`)** | `Red Clay` | Kırmızı Kil |
| **45 (`0x2d`)** | `Black Clay` | Siyah Kil |
| **46 (`0x2e`)** | `White Clay` | Beyaz Kil |
| **47 (`0x2f`)** | `Grey Clay` | Gri Kil |
| **48 (`0x30`)** | `Dry Clay` | Kuru Kil |
| **50 (`0x32`)** | `Feather` | Tüy |
| **55 (`0x37`)** | `Feces` | Gübre / Dışkı |
| **56 (`0x38`)** | `Secrets` | Gizli / Özel Hammaddeler |
| **57 (`0x39`)** | `Alcohol` | Alkol |
| **58 (`0x3a`)** | `Nylon` | Naylon |
| **59 (`0x3b`)** | `Crude` | Ham Petrol |
| **60 (`0x3c`)** | `Ref Oil` | Rafine Yağ / Petrol |

---

## 29. Hava Durumu ve Kar (Snow Particle) Efekt Sistemleri

### A. Harita Kar Efekti Yöneticisi (`FUN_0034f4c8`):
- Karlı bölgelerdeki harita temalarında (Snow Village, karlı dağ yolları vb.) ekran üzerine yağan kar efekti parçacıklarını (Snow particles) oluşturur ve render eder.
- Kar animasyonunu gerçekleştirmek için `icon_Snow1`, `icon_Snow2`, `icon_Snow3` gibi kar tanesi grafik nesnelerini yükler ve konumlarını günceller.

---

## 30. Binek Atama (Ride System) ve Gelinlik Zorunluluğu Mekanizmaları

### A. Binek Hayvan Atama Buton Kontrolleri (`FUN_0028f4f4`):
- Oyuncunun pet arayüz penceresindeki binek atama durumunu denetler. Bir hayvanı binek olarak atamak veya binekten indirmek için `"Btn_AssignRide_1"` butonu ile durum güncellemelerini yönetir.

### B. Evlilik Töreni Gelinlik Kontrolü (`FUN_0021e388`):
- Evlilik töreni başlatılırken gelin karakterin evlilik kostümü (wedding dress) giymiş olup olmadığını denetler. Kostüm giyilmemişse `"Bride needs to dress up"` uyarısı verilir ve tören başlatılmaz.

---

## 31. Item Mall Çift Ödül Etkinliği ve Sistem Sohbet Önekleri

### A. Item Mall Şans Oyunları Çift Ödül Bildirimleri (`FUN_003e175c`):
- Sunucudan gelen klan/etkinlik log paketlerini dinler. Item Mall şans/mini oyunlarında (Slot makinesi, çarkıfelek vb.) iki kat ödül etkinliğinin başlangıç ve bitiş loglarını sohbete bastırır:
  - Başlangıçta: `"Double rewards in Item Mall mini-games has begun!"`
  - Bitişte: `"Double rewards in Item Mall mini-games has ended!"`

### B. Sistem Sohbet Promp Öneki (`FUN_004a44cc`):
- Sohbet pencerelerinde yazdırılan sistem mesajlarına prefix (öneki) ekler: `"(SystemPromp):"`.

---

## 32. Element Kısıtlamaları (Earth/Water/Fire/Wind) ve Kaynak Toplama Sınırları

### A. Element Becerisi Öğrenme Kısıtlamaları (`FUN_00256ed4`):
- Karakterlerin kendi element nitelikleri (Toprak, Su, Ateş, Rüzgar) dışındaki büyü veya becerileri öğrenmelerini engeller. Eşleşme hatasında şu uyarıları fırlatır:
  - `"Can\'t learn Earth skill"`
  - `"Can\'t learn Water skill"`
  - `"Can\'t learn Fire skill"`

### B. Su Kaynağı Mesafe Kontrolü (`FUN_0037a808`):
- Haritadaki su kaynaklarından veya nehirlerden su toplarken oyuncunun mesafesini denetler. Mesafe uygun değilse `"Too far from water"` uyarısını verir.

### C. Element Sırları / Sırlama Eşyası Gereksinimleri (`FUN_003baa18`):
- Görevlerde veya özel yetenek yükseltmelerinde element kristal sırrı (Glaze) gereksinimini doğrular: `"Can\'t require Earth Glaze"`, `"Can\'t require Fire Glaze"`.

---

## 33. Balık Tutma (Fishing) ve Eylem Engelleri

### A. Balık Tutma Esnasında Üretim Engeli (`FUN_0013e694`):
- Oyuncu balık tutmaktayken başka bir üretim veya montaj (crafting) işlemi başlatmasını engeller: `"Currently fishing"`.

### B. Balık Tutarken Diğer Etkileşimlerin Engellenmesi (`FUN_001d26fc`):
- Karakter balık tutma modundayken hareket etmesini, yetenek kullanmasını veya düello başlatmasını engeller: `"Fishing, can\'t act"`.

---

## 34. Posta Kutusu (Mailbox) Kapasite ve Log Mekanizmaları

### A. Posta Kutusu Doluluk Uyarı Limitleri (`FUN_001ee918`):
- Oyuncunun posta kutusundaki mektup sayısını ve kapasitesini denetler. Posta kutusu %90 doluluğa ulaştığında oyuncuya `"Mailbox volume at 90%. When full, old letters get deleted"` uyarısı gösterilir.

### B. Mektup Silme Onayı (`FUN_001eed04`):
- Posta kutusundan eski bir mektup silindiğinde arayüzde `"Letter removed"` bildirimini tetikler.

### C. Mektup Günlük Dosyası (Mail Log Target) (`FUN_001adc88`):
- İstemci tarafında gönderilen veya alınan postaların özet günlüklerini `\MsgMailBoxLog` dosyasına kaydeder.

---

## 35. Çadır Mobilyası (Furniture) ve Mobilya Kapsülü Mekanizmaları

### A. Eşya Detayı Mobilya Etiketlemesi (`FUN_002242d0`):
- Oyuncunun envanterindeki çadır mobilya eşyalarının (yatak, fırın, dekorasyon vb.) detay kartlarında veya envanter listelerinde eşya tipini `<Furniture>` (Mobilya) olarak etiketler.

### B. Mobilya Kapsülü ve Yerleşimleri (`FUN_0022c738`):
- Çadırdaki mobilya kapsüllerini (`FurnitureCapsule`) ve çadır içi yerleşim slotlarını yönetir.
- Karakter banyo/hamamdayken mobilyaları yerleştirme veya tamir etmeyi engeller: `"Can\'t fix in bat"`.

---

## 36. Grup (Team / Party) İçi Eylem Kısıtlamaları

### A. Gruptayken Üretim / Çadır Engelleri (`FUN_0013e694`):
- Oyuncu bir gruptayken/takımdayken yapamayacağı eylemleri denetler. Gruptayken çadır içi eşya üretimi vb. eylemler engellenir: `"Can\'t do in team"`.

### B. Grup Davet / Katılım Engelleri (`FUN_001a4d00`):
- Karakterin grupta olmasına izin verilmeyen durumlarda grup kurmayı veya daveti engeller: `"Can\'t team"`.

---

## 37. Harita Genişletme (Expand Map) Arayüz Yöneticisi

### A. Genişletilmiş Harita Paneli (`FUN_003255f8` ve `FUN_003282dc`):
- Oyun içi ekranın sağ üstünde yer alan mini harita görüntüsünü veya büyük dünya haritasını tam boyutlu genişletmek için kullanılan arayüz formunu (`"Expand Map"`) yükler.

---

## 38. Ölüm ve Hayalet (Ghost / Spirit) Durumu

### A. Hayalet Karakter Görsel Durumu (`FUN_0017be18`):
- Oyuncu veya yoldaşı savaşta yenilip öldüğünde diriltilmediği takdirde hayalet (spirit/ghost) formuna dönüşmesini yönetir.
- Cinsiyete göre kadın hayalet (`icon_LD_GhostF`) veya erkek hayalet animasyon durumlarını yükler, hareket ve eylemleri buna göre sınırlandırır.

---

## 39. Uzaktan Kumanda (Remote Control / Botting) Eylem Sınırları

### A. Kumanda Modu Eylem Blokları (`FUN_0034a11c` ve `FUN_0043af04`):
- Oyuncu otomatik savaş/uzaktan kumanda (Remote Control) modundayken manuel eşya alışverişi, çadır düzenleme veya takas işlemlerini engeller. Yapılmak istendiğinde `"Can\'t perform during remote control"` uyarısı döndürülür.

---

## 40. Lonca Kalesi Savunma ve Kuşatma (Castle Siege) Günlükleri

### A. Kale Savunma Durum Mesajları (`FUN_001a6498`):
- Lonca savaşı (Castle Siege) esnasında kaleyi başarıyla savunan birlikleri genel sohbette duyurur: `" defended castle "`.

### B. Kale Sahipliği Denetimleri (`FUN_001a6768`):
- Kuşatılan kalenin güncel sahibi olan bir lonca bulunup bulunmadığını kontrol eder, kale boşta ise veya sahipsizse `"No guild own Castle"` durumunu tetikler.

---

## 41. Işınlanma ve Geri Çağırma (Teleportation) Limitleri

### A. Işınlanma Durum Engelleri (`FUN_0013e694`):
- Oyuncu savaşta, zindanda veya eylem engelli haritalardayken portal/ışınlanma eşyası kullanmasını sınırlar: `"Can\'t teleport"`, `"Can\'t use now"`.

---

## 42. Ekipman Demirci Tamiri (Repair Shop) ve Koşulları

### A. Eşya Tamir İhtiyacı Kontrolü (`FUN_001b18f0`):
- Dayanıklılığı tam olan bir eşyayı tamir etmeyi engeller: `"Doesn\'t need repair"`.

### B. Tamir Maliyeti Bilgisi (`FUN_001daa90`):
- Demirci NPC'si veya çadır içi tamir tezgahında eşya tamir edilirken çıkacak masrafı loglar: `"Repairs cost: "`.

---

## 43. Savaşta Tamir Engeli (Repair in Battle)

### A. Savaş Durum Engeli (`FUN_0014fe14`):
- Aktif bir savaşın içindeyken karakterlerin ekipmanlarını tamir etmesini yasaklar: `"Can\'t fix in battle"`.

---

## 44. Arkadaş Log Dosyası (Friend Log Target)

### A. Sosyal İşlem Günlükleri (`FUN_001ec724`):
- Arkadaş ekleme, silme, mesajlaşma veya durum güncellemelerini istemci tarafında `\MsgFriendLog` dosyasına loglar.

---

## 45. Arkadaş Arayüzü ve Silme Onayı (Friend List Form)

### A. Liste Yapısı ve Silme Onay Arayüzü (`FUN_001fa870` ve `FUN_00293298`):
- Oyun içi `"Friend List"` form arayüzünü ve butonlarını (`btn_delFriend_1`) yönetir. Arkadaş silme butonuna tıklandığında `"Delete this friend?"` onay kutusunu tetikler.

---

## 46. Yetenek Sıfırlama (Forgotten Scroll / Skill Reset)

### A. Stat ve Beceri Sıfırlama Kararı (`FUN_0037a808`):
- Forgotten Scroll (Unutkanlık Parşömeni) kullanıldığında `"You will forget learned skills. Select skill to forget: "` uyarısını göstererek sıfırlanacak stat puanı (STR, CON, INT, WIS, AGI) seçimini sunar.

---

## 47. Seviye Atlatma Günlükleri (Level Up Logs)

### A. Karakter ve Pet Level Up Bildirimi (`FUN_003aed54`):
- Oyuncu veya pet seviye atladığında sistem günlüklerine ve sohbet kanalına bu logu basar: `" level up "`.

---

## 48. Ekipman Kırılması ve Dayanıklılık Sıfırlanması (Durability Run Out)

### A. Eşya Kullanılamaz Uyarısı (`FUN_0043d4c4`):
- Kullanılan ekipmanların dayanıklılığı 0 olduğunda arayüzde ve sistem logunda `" durability run out"` uyarısını fırlatır.

---

## 49. Takım Meydan Okuma Arayüzü (PvP Challenge System)

### A. Takım Meydan Okuma Duyuruları (`FUN_002c7854`):
- PvP turnuvalarında veya arena alanlarında oyuncuları takım kurmaya ve kapışmaya yönlendiren panelleri yükler: `"Form a team, challenge others!"`.

---

## 50. Günlük Meydan Okuma Sınırları (Challenges Count Limit)

### A. Mücadele Hakkı Sayaç Doğrulamaları (`FUN_002c79f0`):
- Karakterlerin günlük yapabileceği maksimum PvP/zindan mücadele sayısını denetler ve arayüzde kalan hakkı gösterir: `"Challenges:  %d/%d"`.

---

# II. ALINAN VE GÖNDERİLEN PAKETLERİN DETAYLI PROTOKOL YAPISI (PACKET PROTOCOL)

Aşağıda, Wonderland Online istemcisi (`aLogin.exe`) ve oyun sunucusu (`gameserver.py`) arasında gidip gelen paketlerin OPCODE bazlı bayt (byte) yapıları ve protokol kuralları listelenmiştir:

## 1. El Sıkışma & Bağlantı Kurulumu (Opcode: 0)
- **Gelen (Client -> Server)**: Bağlantı kurulduğunda gönderilir (Opcode 0).
- **Giden (Server -> Client)**: El sıkışma onayı.
  - `[0, 1]` (2 bayt): Bağlantı başlatıldı.
  - `[0, 30]` (2 bayt): Karakter oluşturma hatası durumunda istemciye dönen hata.
  - `[0, 32]` (2 bayt): Geçersiz slot seçiminde istemciye dönen hata.

## 2. Sohbet & GM Komutları (Opcode: 2)
- **Gelen (Client -> Server)**:
  - `[2, 2, chat_channel, ...message_bytes]`
    - `chat_channel` (1 bayt): Sohbet kanalı (1: Genel, 2: Fısıltı, 3: Takım, 4: Lonca).
    - `message_bytes` (String): Gönderilen sohbet metni.
- **Giden (Server -> Client)**:
  - `[2, 2, sender_char_id (4 bytes), chat_channel, ...sender_name_str, ...message_str]`
    - Sunucunun tüm alıcılara veya hedef fısıltı oyuncusuna mesajı yansıtma paketi.

## 3. Karakter Yürüme & Pozisyon Eşleme (Opcode: 6)
- **Gelen (Client -> Server)**:
  - `[6, 1, direction, x (2 bytes), y (2 bytes)]`
    - `direction` (1 bayt): Yürüme yönü (0-7 arası yön indeksleri).
    - `x`, `y` (2'şer bayt - uint16): Hedef koordinatlar.
- **Giden (Server -> Client)**:
  - `[6, 1, char_id (4 bytes), direction, x (2 bytes), y (2 bytes)]`
    - Haritadaki diğer oyunculara yürüme eylemini ve yeni konumu senkronize eder.

## 4. Stat Puanı Dağıtımı (Opcode: 8)
- **Gelen (Client -> Server)**:
  - `[8, 1, target_type, target_slot, stat_id, amount (4 bytes)]`
    - `target_type` (1 bayt): Stat verilecek hedef (0: Karakter, 1: Pet).
    - `target_slot` (1 bayt): Pet slot numarası (1-based, karakter için 0).
    - `stat_id` (1 bayt): Dağıtılacak statün kimliği (27: INT, 28: STR, 29: CON, 30: AGI, 33: WIS).
    - `amount` (4 bayt - uint32): Harcanacak potansiyel puan miktarı.

## 5. Karakter Kurulumu & İsim Kontrolü (Opcode: 9)
- **Gelen (Client -> Server)**:
  - **İsim Sorgusu (Sub 2)**:
    - `[9, 2, ...name_str]` (Karakter ismi kullanılabilir mi?).
  - **Karakter Oluşturma (Sub 1)**:
    - `[9, 1, body (2B), head (2B), hair_color (2B), skin_color (2B), clothing_color (2B), eye_color (2B), element, str, agi, wis, int, con, ...cipher_str]`
- **Giden (Server -> Client)**:
  - **İsim Sorgusu Yanıtı (Sub 3)**:
    - `[9, 3, status]` (status: 0 ise kullanılabilir, 1 ise kullanımda/geçersiz).

## 6. Savaş Başlatma & Kaçma (Opcode: 11)
- **Gelen (Client -> Server)**:
  - **Kaçma Talebi (Sub 1)**:
    - `[11, 1, escape_type]` (escape_type: Kaçma yöntemi/maliyeti).
  - **Savaşa Girme (Sub 2)**:
    - `[11, 2, pk_type, raw_target_id (4 bytes), npc_click_id (2 bytes)]`
      - `pk_type`: 3 ise PvP meydan okuması (hedef player_id), 0 ise PvE (hedef npc_id).

## 7. Harita Warp & Yükleme Tamamlandı (Opcode: 12)
- **Gelen (Client -> Server)**:
  - `[12, 1]` (1 bayt sub): İstemci harita yüklemesini tamamladığını bildirir.
- **Giden (Server -> Client)**:
  - `[20, 8]` ve `[5, 4]` (Warp sonrası kilit açma / kontrol iade paketleri).

## 8. Arkadaş Sistemi (Opcode: 14)
- **Gelen (Client -> Server)**:
  - **Arkadaş Ekleme (Sub 1)**: `[14, 1, ...target_name_str]`
  - **Arkadaş Silme (Sub 2)**: `[14, 2, target_char_id (4 bytes)]`
  - **Kara Liste Ekleme (Sub 3)**: `[14, 3, ...target_name_str]`
  - **Kara Liste Silme (Sub 4)**: `[14, 4, target_char_id (4 bytes)]`

## 9. Pet & Binek İşlemleri (Opcode: 15)
- **Gelen (Client -> Server)**:
  - **Savaş Durumu Değiştir (Sub 2)**: `[15, 2, pet_slot, battle_state]` (battle_state: Savaşta aktif etme/kaldırma).
  - **Pet Salıverme (Sub 4)**: `[15, 4, pet_slot]` (Pet'i serbest bırakır/siler).
  - **Pet Takas Kilidi (Sub 6)**: `[15, 6, pet_slot]` (Pet'i güvenli takasa koyar).

## 10. Çadır & Portallar (Opcode: 20)
- **Gelen (Client -> Server)**:
  - **Çadıra Giriş (Sub 1)**: `[20, 1, target_player_id (4 bytes)]`
  - **Çadırdan Çıkış (Sub 2)**: `[20, 2]`
  - **Portal/Kapı Cisim Etkileşimi (Sub 8)**: `[20, 8, portal_id (2 bytes)]`

## 11. Envanter & Eşya Aksiyonları (Opcode: 23)
- **Gelen (Client -> Server)**:
  - **Eşya Kullan (Sub 2)**: `[23, 2, item_slot, target_type, target_slot]`
  - **Eşya Donan (Sub 3)**: `[23, 3, item_slot, equip_slot]`
  - **Eşya Çıkar (Sub 10)**: `[23, 10, equip_slot, item_slot]`
  - **Eşya Sil/At (Sub 12)**: `[23, 12, item_slot, count]`
  - **Eşya Böl/Ayır (Sub 14)**: `[23, 14, src_slot, dest_slot, count]`

## 12. Oyuncu Takas Sistemi (Opcode: 25)
- **Gelen (Client -> Server)**:
  - **Takas İsteği Gönder (Sub 1)**: `[25, 1, target_player_id (4 bytes)]`
  - **Takas Eşyası Ekle (Sub 3)**: `[25, 3, item_slot, count]`
  - **Takası Onayla/Kilitle (Sub 10)**: `[25, 10]`

## 13. Giriş İşlemleri & Karakter Seçimi (Opcode: 63)
- **Gelen (Client -> Server)**:
  - **Kullanıcı Doğrulama (Sub 4)**:
    - `[63, 4, dummy (2 bytes), ...username_str, ...password_str]`
  - **Slot Seçimi (Sub 2)**:
    - `[63, 2, slot_index]` (slot_index: 1 veya 2).
- **Giden (Server -> Client)**:
  - **Karakter Listesi Gönderme (Sub 1)**:
    - `[63, 1, ...slot1_character_data, ...slot2_character_data]`
  - **Slot Seçim Onayı (Sub 2)**:
    - `[63, 2, char_id (4 bytes)]`

## 14. Eşya Kullanımı ve Binek/Taşıt İşlemleri (Opcode: 23)
- **Gelen (Client -> Server)**:
  - **Taşıta Binme (Sub 51 / 0x33)**:
    - `[23, 51, vehicle_type_id]` (1: Canoe, 2: Raft, 3: Hot Air Balloon, vb.).
  - **Taşıttan İnme (Sub 52 / 0x34)**:
    - `[23, 52]`
  - **Taşıta Yakıt Yükleme (Sub 134 / 0x86)**:
    - `[23, 134, inventory_slot_idx]` (Duble tıkla yakıt yükleme tetiklemesi).
- **Giden (Server -> Client)**:
  - **Taşıta Binme Onayı (Sub 51)**:
    - `[23, 51, vehicle_type_id]`
  - **Taşıttan İnme Onayı (Sub 52)**:
    - `[23, 52]`

## 15. Evcil Hayvan & Taşıt Durum Bildirimleri (Opcode: 15)
- **Giden (Server -> Client)**:
  - **Taşıt Tamir Durum Bildirimi (Sub 23 / 0x17)**:
    - `[15, 23, status]` (status 2: Success "Vehicle repaired", 3: Failed "Repairs failed", 4: "Not enough Pts.").
















