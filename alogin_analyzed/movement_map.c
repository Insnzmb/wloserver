/**
 * movement_map.c - WLO Yürüme, Koordinat Kontrolleri ve MapData Harita Yükleme Algoritmaları.
 * Extracted from aLogin.exe decompiled C code.
 */

/*******************************************************************************
 * @fonksiyon      FUN_0032d924
 * @başlık         Harita Limit Hesaplayıcı (Map Dimension Loader)
 * @açıklama       Harita verisindeki grid boyutlarına göre haritanın piksel limitlerini ayarlar.
 * @ofsetler       +0x14 ofsetinde grid genişliği, +0x18 ofsetinde grid yüksekliği saklanır. +0x38 block_size değeridir.
 * @paketler       Harita sınır kontrol paketleri.
 * 
 * @detaylı_analiz 
 * * 1. Harita grid genişliği (width) ve yüksekliği (height) okunur.
 *  * 2. Piksel boyutuna dönüştürmek için block_size ile çarpılır.
 *  * 3. Harita sınırları tampon belleğe (+0x1c, +0x20) kaydedilir.
 *******************************************************************************/
void FUN_0032d924(int param_1,int param_2,int param_3)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  *(int *)(param_1 + 0x14) = param_2 / (int)(uint)*(byte *)(param_1 + 0x38);
  *(int *)(param_1 + 0x18) = param_3 / (int)(uint)*(byte *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x18);
  iVar3 = *(int *)(*(int *)(param_1 + 0x3c) + 0x158);
  if (*(int *)(param_1 + 0x14) < iVar3) {
    uVar2 = iVar3 - *(int *)(param_1 + 0x14);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    *(int *)(param_1 + 0x50) = iVar3;
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(*(int *)(param_1 + 0x3c) + 0x158);
    *(undefined1 *)(param_1 + 0x24) = 1;
  }
  iVar3 = *(int *)(*(int *)(param_1 + 0x3c) + 0x15c);
  if (*(int *)(param_1 + 0x18) < iVar3) {
    uVar2 = iVar3 - *(int *)(param_1 + 0x18);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    *(int *)(param_1 + 0x54) = iVar3;
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(*(int *)(param_1 + 0x3c) + 0x15c);
    *(undefined1 *)(param_1 + 0x24) = 1;
  }
  lVar1 = (longlong)*(int *)(param_1 + 0x14) * (longlong)*(int *)(param_1 + 0x18);
  uVar4 = FUN_00012794((int)lVar1 * 2,(int)((ulonglong)lVar1 >> 0x20));
  *(undefined4 *)(param_1 + 8) = uVar4;
  FUN_00018010(uVar4,*(int *)(param_1 + 0x14) * *(int *)(param_1 + 0x18) * 2,0);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0032cd88
 * @başlık         MapData Yükleyici 1 (MapData Loader 1)
 * @açıklama       İistemci tarafında XOR 0x190c ile maskelenmiş MapData dosyasını çözer.
 * @ofsetler       param_1 harita referansıdır. Harita ID'si 0x190c sabiti ile XOR'lanarak dosya adı oluşturulur.
 * @paketler       Vahşi Karşılaşma ve Bölge Verileri.
 * 
 * @detaylı_analiz 
 * * 1. Harita ID'si 0x190c sabiti ile XOR'lanır.
 *  * 2. user\Map\<XOR_ID>.MapData dosyası açılır ve şifresi çözülür.
 *  * 3. 36 byte'lık (0x24) kayıtlar halinde canavar spawn bölgeleri ve koordinat kutuları okunur.
 *******************************************************************************/
void FUN_0032cd88(int param_1)

{
  undefined1 *puVar1;
  char *pcVar2;
  char cVar3;
  short sVar4;
  ushort uVar5;
  char **ppcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int *in_FS_OFFSET;
  int local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  int iStack_58;
  int iStack_54;
  int local_50;
  char **local_4c;
  char **local_48;
  int iStack_44;
  char *pcStack_40;
  undefined1 *puStack_3c;
  char *local_38;
  char *local_34;
  char *local_30;
  undefined4 uStack_2c;
  int iStack_28;
  undefined1 *puStack_24;
  undefined4 local_20;
  
  local_20 = &stack0xfffffffc;
  iVar10 = 0xc;
  do {
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  puStack_24 = &LAB_0032d26c;
  iStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_28;
  uStack_2c = *(undefined4 *)PTR_DAT_004c8c60;
  local_30 = "user\\Map\\";
  local_34 = (char *)0x32cdcc;
  FUN_00015470(&local_48,*(uint *)(param_1 + 0x58) ^ 0x190c);
  local_34 = (char *)0x32cdd7;
  FUN_00015890(&local_48,&local_38);
  local_34 = local_38;
  local_38 = ".MapData";
  puStack_3c = (undefined1 *)0x32cdec;
  FUN_000141ec(&local_34,4);
  puStack_3c = (undefined1 *)0x32cdf4;
  cVar3 = FUN_0001972c(local_34);
  if (cVar3 != '\0') {
    ppcVar6 = (char **)(0x40 / (ulonglong)*(byte *)(param_1 + 0x38));
    puStack_3c = (undefined1 *)0x32ce25;
    uVar7 = FUN_00012794((int)ppcVar6 * (int)ppcVar6 * 2,0);
    puStack_3c = (undefined1 *)0x32ce34;
    uVar8 = FUN_00013114(&PTR_LAB_00020594,1);
    puStack_3c = *(undefined1 **)PTR_DAT_004c8c60;
    pcStack_40 = "user\\Map\\";
    iStack_44 = 0x32ce62;
    FUN_00015470(&local_60,*(ushort *)(*(int *)PTR_DAT_004c98f4 + 0x235c) ^ 0x190c);
    iStack_44 = 0x32ce6d;
    FUN_00015890(&local_60,&local_50);
    iStack_44 = local_50;
    local_48 = (char **)0x32d298;
    local_4c = (char **)0x32ce82;
    FUN_000141ec(&local_4c,4);
    puStack_3c = (undefined1 *)0x32ce8d;
    FUN_000244c0(uVar8,local_4c);
    pcStack_40 = &LAB_0032d158;
    iStack_44 = *in_FS_OFFSET;
    *in_FS_OFFSET = (int)&iStack_44;
    local_48 = (char **)0x32cea6;
    puStack_3c = &stack0xfffffffc;
    sVar4 = FUN_000158bc(*(undefined4 *)(param_1 + 0x28));
    uVar11 = 0;
    local_20._2_2_ = sVar4;
    do {
      uVar9 = uVar11 & 0xffff;
      local_48 = (char **)0x32ced4;
      FUN_00023eec(uVar8,*(int *)(param_1 + 0x28) + 0x14 + uVar9 * 0x24,1);
      if (*(char *)(*(int *)(param_1 + 0x28) + 0x14 + uVar9 * 0x24) == '\x01') {
        local_20._0_2_ = *(short *)(*(int *)(param_1 + 0x28) + 0x10 + uVar9 * 0x24);
        uVar5 = 0;
        do {
          sVar4 = *(short *)(*(int *)(param_1 + 0x28) + 0x12 + (uVar11 & 0xffff) * 0x24);
          uVar9 = 0;
          do {
            *(undefined1 *)
             (*(int *)(*(int *)(*(int *)(param_1 + 0x28) + 0x1c + (uVar11 & 0xffff) * 0x24) +
                      (uint)uVar5 * 4) + (uVar9 & 0xffff)) = 1;
            uVar9 = uVar9 + 1;
            sVar4 = sVar4 + -1;
          } while (sVar4 != 0);
          uVar5 = uVar5 + 1;
          local_20._0_2_ = (short)local_20 + -1;
        } while ((short)local_20 != 0);
        local_48 = *(char ***)(*(int *)(param_1 + 0x28) + (uVar11 & 0xffff) * 0x24);
        local_4c = (char **)&DAT_0032d2ac;
        local_50 = 0x32cfdc;
        FUN_0001953c(uVar11 & 0xffff,&local_68);
        local_50 = local_68;
        iStack_54 = 0x32cfec;
        FUN_000141ec(&local_64,3);
        iStack_54 = 0x32cffa;
        (**(code **)(**(int **)(param_1 + 0x60) + 0x34))(*(int **)(param_1 + 0x60),local_64);
      }
      else {
        local_20._0_2_ = *(short *)(*(int *)(param_1 + 0x28) + 0x10 + uVar9 * 0x24);
        uVar5 = 0;
        do {
          sVar4 = *(short *)(*(int *)(param_1 + 0x28) + 0x12 + (uVar11 & 0xffff) * 0x24);
          uVar9 = 0;
          do {
            local_48 = (char **)0x32cf45;
            FUN_00023eec(uVar8,*(int *)(*(int *)(*(int *)(param_1 + 0x28) + 0x1c +
                                                (uVar11 & 0xffff) * 0x24) + (uint)uVar5 * 4) +
                               (uVar9 & 0xffff),1);
            uVar9 = uVar9 + 1;
            sVar4 = sVar4 + -1;
          } while (sVar4 != 0);
          uVar5 = uVar5 + 1;
          local_20._0_2_ = (short)local_20 + -1;
        } while ((short)local_20 != 0);
        local_20._0_2_ = 0;
      }
      uVar11 = uVar11 + 1;
      local_20._2_2_ = local_20._2_2_ + -1;
    } while (local_20._2_2_ != 0);
    local_48 = (char **)0x32d010;
    uVar5 = FUN_000158bc(*(undefined4 *)(param_1 + 0x28));
    local_20 = (undefined1 *)((uint)uVar5 << 0x10);
    uVar11 = 0;
    do {
      local_20 = (undefined1 *)
                 CONCAT22(local_20._2_2_,
                          *(undefined2 *)
                           (*(int *)(param_1 + 0x28) + 0x10 + (uVar11 & 0xffff) * 0x24));
      uVar5 = 0;
      do {
        sVar4 = *(short *)(*(int *)(param_1 + 0x28) + 0x12 + (uVar11 & 0xffff) * 0x24);
        uVar9 = 0;
        do {
          if (*(char *)(*(int *)(*(int *)(*(int *)(param_1 + 0x28) + 0x1c + (uVar11 & 0xffff) * 0x24
                                         ) + (uint)uVar5 * 4) + (uVar9 & 0xffff)) != '\0') {
            local_48 = (char **)0x32d09e;
            FUN_00023eec(uVar8,uVar7,(int)ppcVar6 * (int)ppcVar6 * 2);
            local_4c = &local_30;
            local_50 = 0x32d0b2;
            local_48 = ppcVar6;
            FUN_00020cdc(0,0,ppcVar6);
            local_48 = &local_30;
            local_4c = (char **)(*(int *)(*(int *)(param_1 + 0x28) + 0xc + (uVar11 & 0xffff) * 0x24)
                                 + *(int *)(param_1 + 0x54) + (uVar9 & 0xffff) * (int)ppcVar6);
            local_50 = *(int *)(*(int *)(param_1 + 0x28) + 8 + (uVar11 & 0xffff) * 0x24) +
                       *(int *)(param_1 + 0x50) + (uint)uVar5 * (int)ppcVar6;
            iStack_54 = (int)ppcVar6 * 2;
            iStack_58 = *(int *)(param_1 + 0x14) * 2;
            local_60 = *(undefined4 *)(param_1 + 8);
            local_64 = 0x32d116;
            uStack_5c = uVar7;
            ro_Normal_Blt();
            local_48 = (char **)0x32d128;
            FUN_0001801c(uVar7,(int)ppcVar6 * (int)ppcVar6 * 2);
          }
          puVar1 = puStack_3c;
          uVar9 = uVar9 + 1;
          sVar4 = sVar4 + -1;
        } while (sVar4 != 0);
        uVar5 = uVar5 + 1;
        sVar4 = (short)local_20 + -1;
        local_20 = (undefined1 *)CONCAT22(local_20._2_2_,sVar4);
      } while (sVar4 != 0);
      uVar11 = uVar11 + 1;
      uVar5 = local_20._2_2_ - 1;
      local_20 = (undefined1 *)((uint)uVar5 << 0x10);
    } while (uVar5 != 0);
    *in_FS_OFFSET = iStack_44;
    puStack_3c = (undefined1 *)0x32d21f;
    FUN_00013144(uVar8,iStack_44,puVar1);
    puStack_3c = (undefined1 *)0x32d227;
    FUN_000127ac(uVar7);
  }
  pcVar2 = local_30;
  *in_FS_OFFSET = (int)local_38;
  local_30 = &LAB_0032d273;
  local_34 = (char *)0x32d241;
  FUN_00013ed0(&local_68,2,pcVar2);
  local_34 = (char *)0x32d249;
  FUN_0001583c(&local_60);
  local_34 = (char *)0x32d256;
  FUN_00013ed0(&local_50,2);
  local_34 = (char *)0x32d25e;
  FUN_0001583c(&local_48);
  local_34 = (char *)0x32d26b;
  FUN_00013ed0(&local_38,2);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0032d5b8
 * @başlık         MapData Yükleyici 2 (MapData Loader 2)
 * @açıklama       Harita nesneleri, kapılar (portallar) ve warp tetikleyicilerini MapData'dan yükleyen ana yardımcıdır.
 * @ofsetler       Harita referansı ve yükleme bayrakları.
 * @paketler       Kapı/Portal warp tetikleyicileri.
 * 
 * @detaylı_analiz 
 * * 1. Portal koordinatları ve ışınlanma (warp) hedef harita ID'leri okunur.
 *  * 2. Haritadaki engelli (yürünemeyen) grid alanları işaretlenir.
 *******************************************************************************/
void FUN_0032d5b8(int param_1)

{
  char cVar1;
  uint uVar2;
  short sVar3;
  undefined4 *in_FS_OFFSET;
  char *pcVar4;
  undefined4 uVar5;
  undefined4 uStack_70;
  undefined1 *puStack_6c;
  undefined1 *puStack_68;
  undefined4 uStack_64;
  undefined1 *puStack_60;
  undefined1 *puStack_5c;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c [16];
  short local_1c;
  short local_1a;
  int local_18;
  int local_14;
  undefined4 local_10;
  ushort local_c;
  ushort local_a;
  undefined4 local_8;
  
  puStack_5c = &stack0xfffffffc;
  local_38 = 0;
  local_3c = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_34 = 0;
  local_30 = 0;
  puStack_60 = &LAB_0032d8eb;
  uStack_64 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_64;
  local_18 = (int)(0x40 / (ulonglong)*(byte *)(param_1 + 0x38));
  puStack_68 = (undefined1 *)0x32d612;
  local_14 = local_18;
  local_10 = FUN_00012794(local_18 * local_18 * 2,0);
  puStack_68 = (undefined1 *)0x32d621;
  local_8 = FUN_00013114(&PTR_LAB_00020594,1);
  puStack_68 = (undefined1 *)0x32d62c;
  local_1a = FUN_000158bc(*(undefined4 *)(param_1 + 0x28));
  local_a = 0;
  do {
    uVar2 = (uint)local_a;
    puStack_68 = (undefined1 *)0x32d65c;
    FUN_00023f24(local_8,*(int *)(param_1 + 0x28) + 0x14 + uVar2 * 0x24,1);
    if (*(char *)(*(int *)(param_1 + 0x28) + 0x14 + uVar2 * 0x24) != '\x01') {
      local_1c = *(short *)(*(int *)(param_1 + 0x28) + 0x10 + uVar2 * 0x24);
      local_c = 0;
      do {
        sVar3 = *(short *)(*(int *)(param_1 + 0x28) + 0x12 + (uint)local_a * 0x24);
        uVar2 = 0;
        do {
          puStack_68 = (undefined1 *)0x32d6bf;
          FUN_00023f24(local_8,*(int *)(*(int *)(*(int *)(param_1 + 0x28) + 0x1c +
                                                (uint)local_a * 0x24) + (uint)local_c * 4) +
                               (uVar2 & 0xffff),1);
          uVar2 = uVar2 + 1;
          sVar3 = sVar3 + -1;
        } while (sVar3 != 0);
        local_c = local_c + 1;
        local_1c = local_1c + -1;
      } while (local_1c != 0);
    }
    local_a = local_a + 1;
    local_1a = local_1a + -1;
  } while (local_1a != 0);
  puStack_68 = (undefined1 *)0x32d6e5;
  local_1a = FUN_000158bc(*(undefined4 *)(param_1 + 0x28));
  local_a = 0;
  do {
    local_1c = *(short *)(*(int *)(param_1 + 0x28) + 0x10 + (uint)local_a * 0x24);
    local_c = 0;
    do {
      sVar3 = *(short *)(*(int *)(param_1 + 0x28) + 0x12 + (uint)local_a * 0x24);
      uVar2 = 0;
      do {
        if (*(char *)(*(int *)(*(int *)(*(int *)(param_1 + 0x28) + 0x1c + (uint)local_a * 0x24) +
                              (uint)local_c * 4) + (uVar2 & 0xffff)) != '\0') {
          puStack_68 = (undefined1 *)local_18;
          puStack_6c = local_2c;
          uStack_70 = 0x32d7a1;
          FUN_00020cdc(*(int *)(*(int *)(param_1 + 0x28) + 8 + (uint)local_a * 0x24) +
                       *(int *)(param_1 + 0x50) + (uint)local_c * local_14,
                       *(int *)(*(int *)(param_1 + 0x28) + 0xc + (uint)local_a * 0x24) +
                       *(int *)(param_1 + 0x54) + (uVar2 & 0xffff) * local_18,local_14);
          puStack_68 = local_2c;
          puStack_6c = (undefined1 *)0x0;
          uStack_70 = 0;
          ro_Normal_Blt();
          puStack_68 = (undefined1 *)0x32d7d7;
          FUN_00023f24(local_8,local_10,local_14 * local_18 * 2);
          puStack_68 = (undefined1 *)0x32d7e9;
          FUN_0001801c(local_10,local_14 * local_18 * 2);
        }
        uVar2 = uVar2 + 1;
        sVar3 = sVar3 + -1;
      } while (sVar3 != 0);
      local_c = local_c + 1;
      local_1c = local_1c + -1;
    } while (local_1c != 0);
    local_a = local_a + 1;
    local_1a = local_1a + -1;
  } while (local_1a != 0);
  puStack_68 = (undefined1 *)0x32d824;
  FUN_00014178(&local_30,*(undefined4 *)PTR_DAT_004c8c60,"user\\Map\\");
  puStack_68 = (undefined1 *)0x32d82c;
  cVar1 = FUN_0010ec00(local_30);
  if (cVar1 == '\0') {
    puStack_68 = (undefined1 *)0x32d845;
    FUN_00014178(&local_34,*(undefined4 *)PTR_DAT_004c8c60,"user\\Map\\");
    puStack_68 = (undefined1 *)0x32d84d;
    FUN_00019b8c(local_34);
  }
  puStack_6c = &LAB_0032d8c1;
  uStack_70 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_70;
  uVar5 = *(undefined4 *)PTR_DAT_004c8c60;
  pcVar4 = "user\\Map\\";
  puStack_68 = &stack0xfffffffc;
  FUN_00015470(&local_4c,*(uint *)(param_1 + 0x58) ^ 0x190c);
  FUN_00015890(&local_4c,&local_3c);
  FUN_000141ec(&local_38,4);
  FUN_000243ec(local_8,local_38);
  *in_FS_OFFSET = ".MapData";
  FUN_00013144(local_8,".MapData",pcVar4,&LAB_0032d8c8,uVar5);
  FUN_000127ac(local_10);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0031d874
 * @başlık         NPC Mesafe ve Etkileşim Kontrolü (NPC Click & Distance Checker)
 * @açıklama       Oyuncunun haritadaki bir NPC'ye tıkladığında mesafesini ve mesafenin uygunluğunu doğrular.
 * @ofsetler       Oyuncu koordinatları ile NPC koordinatları arasındaki fark abs() ile hesaplanır. Limit 0xa9 (169 piksel) değeridir.
 * @paketler       NPC Etkileşim Başlatma Paketi (Opcode 20 Sub-opcode 1).
 * 
 * @detaylı_analiz 
 * * 1. abs(player_x - npc_x) ve abs(player_y - npc_y) farkları hesaplanır.
 *  * 2. Mesafe 169 pikselden (0xa9) büyükse tıklama eylemi iptal edilir.
 *  * 3. Karakter NPC'ye yakınsa sunucuya etkileşim paketi (Opcode 20, Sub 1) gönderilir.
 *******************************************************************************/
void FUN_0031d874(int param_1)

{
  int iVar1;
  undefined *puVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  puVar2 = PTR_DAT_004c98f4;
  if (*(char *)(*(int *)PTR_DAT_004c98f4 + 0x20b5) == '\0') {
    if ((*(char *)(*(int *)PTR_DAT_004c98f4 + 0x20f6) == '\0') ||
       (*(uint *)(*(int *)PTR_DAT_004c87e0 + 0x7b) ==
        (uint)*(byte *)(*(int *)PTR_DAT_004c98f4 + 0x20f7))) {
      if ((((*(char *)(*(int *)PTR_DAT_004c8744 + 0x14) != '\x01') &&
           (((*(char *)(*(int *)PTR_DAT_004c98f4 + 0x1eff) != '\x02' &&
             (*(char *)(*(int *)PTR_DAT_004c9884 + 0x145) == '\0')) &&
            (*(char *)(*(int *)PTR_DAT_004c9348 + 0x14) == '\0')))) &&
          (((((*(char *)(*(int *)PTR_DAT_004c97e4 + 0x14) == '\0' &&
              (*(char *)(*(int *)PTR_DAT_004c9884 + 0x14) == '\0')) &&
             (*(char *)(*(int *)PTR_DAT_004c87f0 + 0x14) == '\0')) &&
            ((*(char *)(*(int *)PTR_DAT_004c9468 + 0x14) == '\0' &&
             (*(char *)(*(int *)PTR_DAT_004c8d08 + 0x14) == '\0')))) &&
           ((*(char *)(*(int *)PTR_DAT_004c8e54 + 0x14) == '\0' &&
            (((((*(char *)(*(int *)PTR_DAT_004c97dc + 0x14) == '\0' &&
                (*(char *)(*(int *)PTR_DAT_004c9744 + 0x14) == '\0')) &&
               (*(char *)(*(int *)PTR_DAT_004c861c + 0x14) == '\0')) &&
              ((*(char *)(*(int *)PTR_DAT_004c8f38 + 0x14) == '\0' &&
               (*(char *)(*(int *)PTR_DAT_004c959c + 0x14) == '\0')))) &&
             (*(char *)(*(int *)PTR_DAT_004c88a0 + 0x14) == '\0')))))))) &&
         ((((*(char *)(*(int *)PTR_DAT_004c871c + 0x14) == '\0' &&
            (*(char *)(*(int *)PTR_DAT_004c905c + 0x14) == '\0')) &&
           ((*(char *)(*(int *)PTR_DAT_004c8878 + 4) == '\0' &&
            (((*(char *)(param_1 + 0x732a) == '\0' &&
              (*(char *)(*(int *)PTR_DAT_004c8a08 + 0x14) == '\0')) &&
             (*(char *)(*(int *)PTR_DAT_004c90d4 + 0x14) == '\0')))))) &&
          ((*(char *)(*(int *)PTR_DAT_004c87a4 + 0x14) == '\0' &&
           (*(char *)(*(int *)PTR_DAT_004c9178 + 0x14) == '\0')))))) {
        FUN_00013eac(param_1 + 0x7174);
        FUN_00013eac(param_1 + 0x7178);
        if (*(char *)(param_1 + 0x7108) != '\x01') {
          if (((*(char *)(param_1 + 0x70e8) == '\x01') &&
              (*(char *)(*(int *)puVar2 + 0x1f16) == '\0')) && (*(char *)(param_1 + 0x7109) == '\0')
             ) {
            *(undefined1 *)(param_1 + 0x7108) = 1;
          }
          else if ((((*(char *)(param_1 + 0x7109) != '\x01') &&
                    (*(char *)(*(int *)puVar2 + 0x1f16) == '\0')) &&
                   (*(char *)(*(int *)PTR_DAT_004c87e0 + 0x76) != '\0')) &&
                  ((*(char *)(*(int *)PTR_DAT_004c87e0 + 0x7f) == '\x03' &&
                   (iVar1 = *(int *)(param_1 + 0x10 + *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b) * 4)
                   , *(short *)(iVar1 + 0x14) != 0)))) {
            cVar3 = FUN_00499c40(iVar1);
            if (cVar3 != '\0') {
              cVar3 = FUN_003c9a6c(*(undefined4 *)
                                    (PTR_DAT_004c976c +
                                    *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b) * 4));
              if (cVar3 != '\b') {
                return;
              }
              if (*(char *)(*(int *)puVar2 + 0x2231) != '\0') {
                return;
              }
              if (*(char *)(*(int *)puVar2 + 0x2232) != '\0') {
                return;
              }
              if (*(char *)(*(int *)puVar2 + 0x2233) != '\0') {
                return;
              }
              uVar4 = *(int *)(*(int *)puVar2 + 0x20) -
                      *(int *)(*(int *)(PTR_DAT_004c976c +
                                       *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b) * 4) + 0x20);
              uVar6 = (int)uVar4 >> 0x1f;
              uVar5 = *(int *)(*(int *)puVar2 + 0x24) -
                      *(int *)(*(int *)(PTR_DAT_004c976c +
                                       *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b) * 4) + 0x24);
              uVar7 = (int)uVar5 >> 0x1f;
              if (0xa9 < (int)((uVar4 ^ uVar6) - uVar6)) {
                return;
              }
              if (0xa9 < (int)((uVar5 ^ uVar7) - uVar7)) {
                return;
              }
            }
            if (*(int *)(*(int *)(PTR_DAT_004c976c + *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b) * 4)
                        + 4) == 0x947a) {
              FUN_003da634(*(int *)(PTR_DAT_004c976c + *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b) * 4
                                   ),*(undefined4 *)(*(int *)PTR_DAT_004c87e0 + 0x7b),
                           PTR_DAT_004c976c);
            }
            *(undefined2 *)(param_1 + 0x70fb) = *(undefined2 *)(param_1 + 0x70d8);
            *(undefined2 *)(param_1 + 0x70f9) = *(undefined2 *)(*(int *)PTR_DAT_004c87e0 + 0x7b);
            *(undefined1 *)(param_1 + 0x70fd) = 1;
            *(uint *)(param_1 + 0x714c) = (uint)*(ushort *)(param_1 + 0x70f9);
            *(undefined4 *)(param_1 + 0x70ec) =
                 *(undefined4 *)(param_1 + 0x10 + (uint)*(ushort *)(param_1 + 0x70f9) * 4);
            *(undefined1 *)(param_1 + 0x717d) = 1;
            *(undefined1 *)(param_1 + 0x70e8) = 1;
            FUN_0018d730(*(undefined4 *)PTR_DAT_004c9670);
            FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0x14,1,0);
          }
        }
      }
    }
    else {
      (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                (*(int **)PTR_DAT_004c8d24,"Collecting, can\'t act",2000,0,0);
    }
  }
  else {
    (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
              (*(int **)PTR_DAT_004c8d24,"Fishing, can\'t act",2000,0,0);
  }
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0015013c
 * @başlık         Karakter/Binek Görsel Koordinat Eşitleyici (Visual Coordinates Sync)
 * @açıklama       Karakterin ve bineğinin (mount) harita üzerindeki görsel entity koordinatlarını mantıksal koordinatlarla eşitler.
 * @ofsetler       Parametre 2 binek/pet indeksidir. Oyuncu referansı PTR_DAT_004c98f4 üzerinden X (+0x20) ve Y (+0x24) koordinatları alınarak entity yapısına kopyalanır.
 * @paketler       İstemci içi koordinat senkronizasyonu.
 * 
 * @detaylı_analiz 
 * * 1. param_2 parametresiyle verilen indeks üzerindeki bineğin/petin koordinatları okunur.
 *  * 2. player_ptr + 0x27e8 dizisinden koordinat modeli (+0x20, +0x24) çekilir.
 *  * 3. Görsel entity modelinin koordinatları güncellenerek ekran çizimi yenilenir.
 *******************************************************************************/
void FUN_0015013c(int param_1,uint param_2)

{
  int iVar1;
  undefined *puVar2;
  
  puVar2 = PTR_DAT_004c914c;
  iVar1 = *(int *)(param_1 + 0x13c);
  *(undefined1 *)(iVar1 + 0xd8) = 0x1b;
  param_2 = param_2 & 0xff;
  *(undefined4 *)(iVar1 + 0x4c) =
       *(undefined4 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0x4c);
  *(undefined4 *)(iVar1 + 0x110) =
       *(undefined4 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0x110);
  *(undefined4 *)(iVar1 + 0x114) = 0;
  FUN_00480734(iVar1,*(undefined4 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xac));
  iVar1 = *(int *)(param_1 + 0x13c);
  *(undefined4 *)(iVar1 + 0xdc) =
       *(undefined4 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xdc);
  *(undefined1 *)(iVar1 + 0xe6) =
       *(undefined1 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xe6);
  *(undefined1 *)(iVar1 + 0xe7) =
       *(undefined1 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xe7);
  *(undefined4 *)(iVar1 + 0xe0) =
       *(undefined4 *)(*(int *)(*(int *)PTR_DAT_004c98f4 + 0x27e8 + param_2 * 4) + 0x20);
  *(undefined2 *)(iVar1 + 0xe4) =
       *(undefined2 *)(*(int *)(*(int *)PTR_DAT_004c98f4 + 0x27e8 + param_2 * 4) + 0x24);
  *(undefined1 *)(iVar1 + 0xe8) =
       *(undefined1 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xe8);
  *(undefined4 *)(iVar1 + 0x20) =
       *(undefined4 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0x20);
  *(undefined4 *)(iVar1 + 0x24) =
       *(undefined4 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0x24);
  *(undefined2 *)(iVar1 + 0xea) =
       *(undefined2 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xea);
  *(undefined1 *)(iVar1 + 0xf8) =
       *(undefined1 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xf8);
  *(undefined1 *)(iVar1 + 0xf9) =
       *(undefined1 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xf9);
  *(undefined2 *)(iVar1 + 0xfa) =
       *(undefined2 *)(*(int *)(*(int *)puVar2 + 0xe8 + param_2 * 4) + 0xfa);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0013d3f4
 * @başlık         Yürüme Yönü ve Koordinat Yöneticisi (Walk Direction & Coordinates Copier)
 * @açıklama       Oyuncunun yürürken binek veya petinin takip yönünü ve koordinat dizisini kopyalar.
 * @ofsetler       Oyuncu PTR_DAT_004c98f4 referansından 0x20c1 ila 0x20c6 arasındaki yön ve yol ofsetlerini pet slot yapısına aktarır.
 * @paketler       İstemci içi yürüme ve takip yapısı.
 * 
 * @detaylı_analiz 
 * * 1. Oyuncunun yürüdüğü son yön ve adım geçmişi yön dizisinden okunur.
 *  * 2. Pet/Companion yapısının +0xd8 ofsetine oyuncunun son yön baytları kopyalanır.
 *  * 3. Petin oyuncuyu görsel olarak takip etmesi sağlanır.
 *******************************************************************************/
void FUN_0013d3f4(int param_1)

{
  int iVar1;
  char cVar2;
  int iStack_10;
  int iStack_c;
  
  (**(code **)**(undefined4 **)(param_1 + 0x130))
            (*(undefined4 **)(param_1 + 0x130),*(undefined4 *)PTR_DAT_004c98f4);
  iVar1 = *(int *)(param_1 + 0x130);
  *(undefined1 *)(iVar1 + 0x207d) = 0;
  *(undefined1 *)(iVar1 + 0x20a4) = 0;
  FUN_00480158(*(undefined4 *)(param_1 + 0xec),&iStack_10);
  *(int *)(*(int *)(param_1 + 0x130) + 0x8c) = iStack_10 + 0x11;
  FUN_00480158(*(undefined4 *)(param_1 + 0xec),&iStack_10);
  iVar1 = *(int *)(param_1 + 0x130);
  *(int *)(iVar1 + 0x90) = iStack_c + -0x28;
  *(undefined1 *)(iVar1 + 0x121) = 0;
  *(undefined1 *)(iVar1 + 0x11e) = 0;
  cVar2 = *(char *)(iVar1 + 8);
  if (*(short *)(iVar1 + 0x20b8) != 0) {
    *(undefined1 *)(iVar1 + 0xd8) = *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x20c1);
    *(undefined1 *)(iVar1 + 0xd9) = *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x20c2);
    *(undefined1 *)(iVar1 + 0xda) = *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x20c3);
    *(undefined1 *)(iVar1 + 0xdb) = *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x20c4);
    *(undefined1 *)(iVar1 + 0xdc) = *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x20c5);
    *(undefined1 *)(iVar1 + 0xdd) = *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x20c6);
    cVar2 = *(char *)(*(int *)PTR_DAT_004c98f4 + 0x20bc);
  }
  if (cVar2 == '\x01') {
    if ((byte)*PTR_DAT_004c8a48 < 2) {
      iVar1 = *(int *)(param_1 + 0x130);
      FUN_0031af68(*(undefined4 *)PTR_DAT_004c96dc,*(byte *)(iVar1 + 0xb4) + 0xa51,0,0,0,0,0xff,1,
                   0xff,0,iVar1,iVar1 + 0x11e,iVar1 + 0x120);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x130);
      FUN_0031af68(*(undefined4 *)PTR_DAT_004c87f8,*(byte *)(iVar1 + 0xb4) + 0xa51,0,0,0,0,0xff,1,
                   0xff,0,iVar1,iVar1 + 0x11e,iVar1 + 0x120);
    }
  }
  else if (cVar2 == '\x02') {
    if ((byte)*PTR_DAT_004c8a48 < 2) {
      iVar1 = *(int *)(param_1 + 0x130);
      FUN_0031af68(*(undefined4 *)PTR_DAT_004c9064,*(byte *)(iVar1 + 0xb4) + 0xe39,0,0,0,0,0xff,1,
                   0xff,0,iVar1,iVar1 + 0x11e,iVar1 + 0x120);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x130);
      FUN_0031af68(*(undefined4 *)PTR_DAT_004c94c8,*(byte *)(iVar1 + 0xb4) + 0xe39,0,0,0,0,0xff,1,
                   0xff,0,iVar1,iVar1 + 0x11e,iVar1 + 0x120);
    }
  }
  else if (cVar2 == '\x03') {
    if ((byte)*PTR_DAT_004c8a48 < 2) {
      iVar1 = *(int *)(param_1 + 0x130);
      FUN_0031af68(*(undefined4 *)PTR_DAT_004c8e00,*(byte *)(iVar1 + 0xb4) + 0x1221,0,0,0,0,0xff,1,
                   0xff,0,iVar1,iVar1 + 0x11e,iVar1 + 0x120);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x130);
      FUN_0031af68(*(undefined4 *)PTR_DAT_004c9240,*(byte *)(iVar1 + 0xb4) + 0x1221,0,0,0,0,0xff,1,
                   0xff,0,iVar1,iVar1 + 0x11e,iVar1 + 0x120);
    }
  }
  else if (cVar2 == '\x04') {
    if ((byte)*PTR_DAT_004c8a48 < 2) {
      iVar1 = *(int *)(param_1 + 0x130);
      FUN_0031af68(*(undefined4 *)PTR_DAT_004c9630,*(byte *)(iVar1 + 0xb4) + 0x1609,0,0,0,0,0xff,1,
                   0xff,0,iVar1,iVar1 + 0x11e,iVar1 + 0x120);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x130);
      FUN_0031af68(*(undefined4 *)PTR_DAT_004c8768,*(byte *)(iVar1 + 0xb4) + 0x1609,0,0,0,0,0xff,1,
                   0xff,0,iVar1,iVar1 + 0x11e,iVar1 + 0x120);
    }
  }
  return;
}

