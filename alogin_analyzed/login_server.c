/**
 * login_server.c - WLO Giriş Doğrulama, Sunucu ve Kanal Çözümleme Mantığı.
 * Extracted from aLogin.exe decompiled C code.
 */

/*******************************************************************************
 * @fonksiyon      FUN_0033c310
 * @başlık         Giriş Cevap Paket Yöneticisi (Login Response Handler)
 * @açıklama       Sunucudan gelen giriş doğrulama (auth) sonucunu çözümler.
 * @ofsetler       param_2 sunucudan gelen paket içeriğidir. Başarı durumunda oyuncunun GUID'si 0x268 ofsetine yazılır.
 * @paketler       Opcode 63 (0x3f) - Login Response.
 * 
 * @detaylı_analiz 
 * * 1. param_2 + 1 ofsetindeki giriş başarı kodu okunur.
 *  * 2. Kod 0x01 ise giriş başarılıdır, GUID verileri 0x268 ofsetine kaydedilir.
 *  * 3. Kod 0x02 ise şifre/kullanıcı hatası gösterilir.
 *  * 4. Kod 0x03 veya 0x04 ise güvenlik uyarısı verilir.
 *******************************************************************************/
void FUN_0033c310(int *param_1,int param_2)

{
  char cVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined1 *puStack_1c;
  undefined1 *puStack_18;
  undefined4 local_c;
  undefined4 local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = 0;
  local_c = 0;
  puStack_1c = &LAB_0033c4b1;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  cVar1 = *(char *)(param_2 + 1);
  if (cVar1 == '\x01') {
    *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x3c22) = 2;
    FUN_00014334(param_2,3,4,&local_8);
    uVar3 = FUN_00112f58(*(undefined4 *)PTR_DAT_004c87e4,local_8);
    *(undefined4 *)(DAT_0071ef58 + 0x268) = uVar3;
    FUN_00014334(param_2,7,4,&local_c);
    uVar3 = FUN_00112f58(*(undefined4 *)PTR_DAT_004c87e4,local_c);
    *(undefined4 *)(DAT_0071ef58 + 0x26c) = uVar3;
    uVar3 = FUN_000195a0(*(undefined4 *)(param_1[0x50] + 0x1a0));
    *(undefined4 *)(DAT_0071ef58 + 0x264) = uVar3;
    *(undefined1 *)(DAT_0071ef58 + 0x270) = *(undefined1 *)(param_2 + 10);
    FUN_0048268c(param_1[0x50],&DAT_0033c4c8);
    FUN_0033d100(DAT_0071ef58,99);
    (**(code **)(*param_1 + 0x24))();
  }
  else if (cVar1 == '\x02') {
    *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x3c22) = 0;
    puStack_18 = &stack0xfffffffc;
    (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
              (*(int **)PTR_DAT_004c8d24,"Login/Pwd error",0x4b0,0,0);
  }
  else if (cVar1 == '\x03') {
    *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x3c22) = 0;
    puStack_18 = &stack0xfffffffc;
    (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
              (*(int **)PTR_DAT_004c8d24,&DAT_0033c4ec,0x4b0,0,0);
  }
  else {
    puStack_18 = &stack0xfffffffc;
    if (cVar1 == '\x04') {
      *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x3c22) = 0;
      puStack_18 = &stack0xfffffffc;
      (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                (*(int **)PTR_DAT_004c8d24,&DAT_0033c500,0x4b0,0,0);
    }
  }
  puVar2 = puStack_18;
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0033c4b8;
  puStack_1c = (undefined1 *)0x33c4b0;
  FUN_00013ed0(&local_c,2,puVar2);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0032f674
 * @başlık         SERVER.INI Dosya Ayrıştırıcısı (SERVER.INI Parser)
 * @açıklama       Yerel SERVER.INI dosyasını okuyarak sunucu listesini ve IP'lerini ayrıştırır.
 * @ofsetler       SERVER.INI yolu ve dosya işaretçisi.
 * @paketler       Sunucu Seçim Ekranı verileri.
 * 
 * @detaylı_analiz 
 * * 1. SERVER.INI dosyasını salt okunur açar.
 *  * 2. Sunucu adları, IP adresleri ve portları parse edilerek listeye eklenir.
 *******************************************************************************/
void FUN_0032f674(undefined4 param_1,int param_2)

{
  int *piVar1;
  char *pcVar2;
  undefined1 **ppuVar3;
  undefined4 ***pppuVar4;
  char cVar5;
  undefined1 uVar6;
  ushort uVar7;
  undefined4 uVar8;
  int *piVar9;
  int iVar10;
  int unaff_EBX;
  int *in_FS_OFFSET;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined1 *local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined1 *local_58;
  char *local_54;
  undefined1 **local_50;
  undefined *local_4c;
  undefined4 local_48;
  char *local_44;
  undefined *local_40;
  undefined4 local_3c;
  char *local_38;
  undefined *local_34;
  char *local_30;
  undefined4 ***local_2c;
  int local_28;
  undefined1 *local_24;
  undefined1 **local_20;
  int local_10;
  
  local_20 = (undefined1 **)&stack0xfffffffc;
  iVar10 = 0xe;
  do {
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  local_24 = &LAB_0032fa1a;
  local_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&local_28;
  local_2c = &local_2c;
  local_30 = (char *)0x32f6b1;
  FUN_00014334(param_2,2,4);
  pppuVar4 = local_2c;
  local_2c = (undefined4 ***)0x32f6c0;
  uVar8 = FUN_00112f58(*(undefined4 *)PTR_DAT_004c87e4,pppuVar4);
  local_2c = (undefined4 ***)&local_30;
  local_30 = (char *)0x32f6d8;
  FUN_00014334(param_2,6,2);
  local_2c = (undefined4 ***)0x32f6e7;
  uVar7 = FUN_00112da4(*(undefined4 *)PTR_DAT_004c87e4,local_30);
  if (uVar7 == 0) {
    local_2c = (undefined4 ***)&DAT_0032fa30;
    local_30 = (char *)0x32f702;
    FUN_0001953c(uVar8,&local_38);
    local_30 = local_38;
    local_34 = &DAT_0032fa3c;
    local_38 = "Player offline";
    local_3c = 0x32f71c;
    FUN_000141ec(&local_34,4);
    piVar9 = *(int **)(*(int *)(*(int *)PTR_DAT_004c8e08 + 0x380) + 0x208);
    local_3c = 0x32f737;
    (**(code **)(*piVar9 + 0x34))(piVar9,local_34);
    pcVar2 = local_30;
    *in_FS_OFFSET = (int)local_38;
    local_30 = &LAB_0032fa21;
    local_34 = (undefined *)0x32fa0c;
    FUN_00013ed0(&local_78,0x14,pcVar2);
    local_34 = (undefined *)0x32fa19;
    FUN_00013ed0(&local_24,2);
    return;
  }
  local_30 = &LAB_0032f9eb;
  local_34 = (undefined *)*in_FS_OFFSET;
  *in_FS_OFFSET = (int)&local_34;
  local_38 = (char *)0x32f756;
  local_2c = (undefined4 ***)&stack0xfffffffc;
  piVar9 = (int *)FUN_00013114(&PTR_FUN_000202e8,1);
  local_38 = (char *)0x32f76e;
  FUN_00014178(&local_3c,*(undefined4 *)PTR_DAT_004c8c60,"SERVER.INI");
  local_38 = (char *)0x32f779;
  (**(code **)(*piVar9 + 0x58))(piVar9,local_3c);
  local_10 = 0;
  cVar5 = (char)((ulonglong)uVar7 / 100);
  local_38 = (char *)0x32f7a4;
  iVar10 = (**(code **)(*piVar9 + 0x14))();
  if (-1 < iVar10 + -1) {
    param_2 = 0;
    local_28 = iVar10;
    do {
      local_38 = (char *)0x32f7c0;
      (**(code **)(*piVar9 + 0xc))(piVar9,param_2,&local_40);
      local_38 = (char *)0x32f7cd;
      iVar10 = FUN_00014418(&DAT_0032fa74,local_40);
      if (iVar10 != 0) {
        local_38 = (char *)0x32f7e2;
        (**(code **)(*piVar9 + 0xc))(piVar9,param_2,&local_44);
        local_38 = local_44;
        local_3c = 0x32f7f3;
        FUN_0001953c(cVar5,&local_4c);
        local_3c = 0x32f803;
        FUN_00014178(&local_48,&DAT_0032fa80,local_4c);
        pcVar2 = local_38;
        local_38 = (char *)0x32f80c;
        iVar10 = FUN_00014418(local_48,pcVar2);
        if (iVar10 != 0) {
          unaff_EBX = 0;
          goto LAB_0032f812;
        }
      }
      param_2 = param_2 + 1;
      local_28 = local_28 + -1;
    } while (local_28 != 0);
  }
  goto LAB_0032f899;
  while( true ) {
    local_38 = (char *)0x32f830;
    (**(code **)(*piVar9 + 0xc))(piVar9,unaff_EBX + param_2,&local_50);
    local_38 = (char *)0x32f83d;
    iVar10 = FUN_00014418(&DAT_0032fa74,local_50);
    if (iVar10 != 0) goto LAB_0032f899;
    local_38 = (char *)0x32f854;
    (**(code **)(*piVar9 + 0xc))(piVar9,unaff_EBX + param_2,&local_54);
    local_38 = local_54;
    local_3c = 0x32f865;
    FUN_0001953c((char)uVar7 + cVar5 * -100,&local_58);
    local_3c = 0x32f872;
    FUN_00014134(&local_58,&DAT_0032fa8c);
    pcVar2 = local_38;
    local_38 = (char *)0x32f87b;
    iVar10 = FUN_00014418(local_58,pcVar2);
    if (iVar10 != 0) break;
LAB_0032f812:
    unaff_EBX = unaff_EBX + 1;
    local_38 = (char *)0x32f81b;
    iVar10 = (**(code **)(*piVar9 + 0x14))();
    if (iVar10 <= unaff_EBX + param_2) goto LAB_0032f899;
  }
  local_10 = unaff_EBX + param_2;
LAB_0032f899:
  if (local_10 != 0) {
    local_38 = (char *)0x32f8ad;
    (**(code **)(*piVar9 + 0xc))(piVar9,unaff_EBX + param_2,&local_5c);
    local_38 = (char *)0x32f8ba;
    iVar10 = FUN_00014418(&DAT_0032fa98,local_5c);
    if (iVar10 == 0) {
      local_10 = 0;
    }
  }
  local_38 = (char *)0x32f8cb;
  uVar6 = FUN_0049ebbc(uVar8);
  local_38 = (char *)0x32f8d6;
  uVar8 = FUN_0049eb9c(uVar8);
  local_38 = "ID:";
  local_3c = 0x32f8e9;
  FUN_0001953c(uVar8,&local_60);
  local_3c = local_60;
  local_40 = &DAT_0032faa4;
  local_44 = "Role: ";
  local_48 = 0x32f903;
  FUN_0001953c(uVar6,&local_64);
  local_48 = local_64;
  local_4c = &DAT_0032faa4;
  local_50 = (undefined1 **)0x32f918;
  FUN_000141ec(&local_20,6);
  if (local_10 == 0) {
    local_50 = local_20;
    local_54 = "Channel: ";
    local_58 = (undefined1 *)0x32f932;
    FUN_0001953c(uVar7,&local_6c);
    local_58 = local_6c;
    local_5c = 0x32f942;
    FUN_000141ec(&local_68,3);
    piVar1 = *(int **)(*(int *)(*(int *)PTR_DAT_004c8e08 + 0x380) + 0x208);
    local_5c = 0x32f95d;
    (**(code **)(*piVar1 + 0x34))(piVar1,local_68);
  }
  else {
    local_50 = &local_24;
    local_54 = (char *)0x32f971;
    (**(code **)(*piVar9 + 0xc))(piVar9,unaff_EBX + param_2,&local_70);
    local_54 = (char *)0x32f97e;
    iVar10 = FUN_00014418(&DAT_0032fa98,local_70);
    local_54 = (char *)(iVar10 + -1);
    local_58 = (undefined1 *)0x32f98e;
    (**(code **)(*piVar9 + 0xc))(piVar9,local_10,&local_74);
    pcVar2 = local_54;
    local_54 = (char *)0x32f99c;
    FUN_00014334(local_74,1,pcVar2);
    local_50 = local_20;
    local_54 = "Channel: ";
    local_58 = local_24;
    local_5c = 0x32f9b4;
    FUN_000141ec(&local_78,3);
    piVar1 = *(int **)(*(int *)(*(int *)PTR_DAT_004c8e08 + 0x380) + 0x208);
    local_5c = 0x32f9cf;
    (**(code **)(*piVar1 + 0x34))(piVar1,local_78);
  }
  ppuVar3 = local_50;
  *in_FS_OFFSET = (int)local_58;
  local_50 = (undefined1 **)0x32f9f2;
  if (piVar9 != (int *)0x0) {
    local_54 = (char *)0x32f9ea;
    FUN_0001d83c(&stack0xffffffe8,local_58,ppuVar3);
  }
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0014c114
 * @başlık         Kanal Listesi Paket Ayrıştırıcısı (Channel List Parser)
 * @açıklama       Sunucudan gelen kanalların durum ve doluluk oranlarını arayüze aktarır.
 * @ofsetler       Gelen kanal listesi veri tamponu. Maksimum 21 kanal desteklenir.
 * @paketler       Kanal Durum Güncelleme Paketi.
 * 
 * @detaylı_analiz 
 * * 1. Gelen kanalların aktiflik durumunu (PVP, Normal, Etkinlik) doğrular.
 *  * 2. Kanalların doluluk oranına göre renk kodunu (Yeşil, Sarı, Kırmızı) arayüze yansıtır.
 *******************************************************************************/
void FUN_0014c114(int param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined2 extraout_var;
  byte bVar7;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined1 *puVar13;
  undefined4 uStack_58;
  undefined1 *puStack_54;
  undefined1 *puStack_50;
  undefined1 local_40 [8];
  undefined1 local_38 [8];
  undefined1 local_30 [24];
  undefined4 local_18;
  byte local_13;
  byte local_12;
  char local_11;
  uint local_10;
  ushort local_c;
  byte local_9;
  int local_8;
  
  local_18 = 0;
  puStack_50 = (undefined1 *)0x14c12f;
  local_8 = param_2;
  FUN_000142e0(param_2);
  puStack_54 = &LAB_0014c5f6;
  uStack_58 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_58;
  puStack_50 = &stack0xfffffffc;
  iVar3 = FUN_0001412c(local_8);
  if (0x14 < iVar3) {
    FUN_0014bcb0(param_1);
    local_9 = 3;
    local_12 = 2;
    local_13 = 4;
    bVar7 = 1;
    do {
      local_11 = '\0';
      bVar1 = *(byte *)(local_8 + -1 + (uint)local_9);
      if ((bVar1 == 0) || (0x1e < bVar1)) {
        if ((bVar1 < 0x1f) || (0x3c < bVar1)) {
          if ((bVar1 < 0x3d) || (0x5a < bVar1)) {
            local_c = *(ushort *)(PTR_DAT_004c8934 + (uint)(byte)(bVar1 + 0xa6) * 10 + 2);
            uVar2 = PTR_DAT_004c8934[(uint)(byte)(bVar1 + 0xa6) * 10 + 4];
          }
          else {
            local_c = *(ushort *)(PTR_DAT_004c8b70 + (uint)(byte)(bVar1 - 0x3c) * 10 + 2);
            uVar2 = PTR_DAT_004c8b70[(uint)(byte)(bVar1 - 0x3c) * 10 + 4];
            local_11 = '\x03';
          }
        }
        else {
          local_c = *(ushort *)(PTR_DAT_004c8614 + (uint)(byte)(bVar1 - 0x1e) * 10 + 2);
          uVar2 = PTR_DAT_004c8614[(uint)(byte)(bVar1 - 0x1e) * 10 + 4];
          local_11 = '\x02';
        }
      }
      else {
        local_c = *(ushort *)(PTR_DAT_004c9864 + (uint)bVar1 * 10 + 2);
        uVar2 = PTR_DAT_004c9864[(uint)bVar1 * 10 + 4];
        local_11 = '\x01';
      }
      uVar6 = (uint)bVar7;
      *(uint *)(param_1 + 0x16d + uVar6 * 0x16) = (uint)local_c;
      *(undefined1 *)(param_1 + 0x179 + uVar6 * 0x16) = uVar2;
      uVar4 = FUN_00430924(*(undefined4 *)PTR_DAT_004c94d4,local_c);
      *(undefined4 *)(param_1 + 0x175 + uVar6 * 0x16) = uVar4;
      FUN_004309d4(*(undefined4 *)PTR_DAT_004c94d4,local_c,&local_18);
      FUN_00013f00(param_1 + 0x171 + uVar6 * 0x16,local_18);
      if (local_11 != '\0') {
        local_10 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,CONCAT22(extraout_var,local_c));
        local_10 = local_10 & 0xffff;
        if (local_11 == '\x01') {
          *(byte *)(param_1 + 0x350) = bVar7;
          *(uint *)(param_1 + 0x351) = (uint)local_c;
          FUN_00012bd0(local_30,&DAT_0014c604);
          FUN_00012ba0(local_30,*(int *)PTR_DAT_004c94d4 + 4 + local_10 * 0x1c3,0x14);
          FUN_000140d0(param_1 + 0x43c,local_30);
          *(undefined4 *)(param_1 + 0x440) = *(undefined4 *)(param_1 + 0x175 + uVar6 * 0x16);
          FUN_0014bec4(param_1,local_c,1);
          iVar3 = FUN_00478630(*(undefined4 *)PTR_DAT_004c8a78,*(undefined4 *)(param_1 + 0x150));
          iVar3 = iVar3 + *(int *)(param_1 + 0x17e + uVar6 * 0x16) + -4;
          iVar5 = FUN_00478644(*(undefined4 *)PTR_DAT_004c8a78,*(undefined4 *)(param_1 + 0x150));
          FUN_00020ca8(iVar5 + *(int *)(param_1 + 0x17a + uVar6 * 0x16) + -4,iVar3,local_38);
          puVar13 = local_38;
          uVar12 = 0;
          uVar11 = 0;
          uVar10 = 0x1e;
          uVar9 = 4;
          uVar8 = 1;
          uVar4 = 0;
          FUN_00020ca8(*(int *)(param_1 + 0x17a + uVar6 * 0x16) + -4,
                       *(int *)(param_1 + 0x17e + uVar6 * 0x16) + -4,local_40,0,1,4,0x1e,0,0,puVar13
                      );
          FUN_0014ec28(*(undefined4 *)(param_1 + 0x48c),*(undefined4 *)(param_1 + 0x150),local_40,
                       uVar4,uVar8,uVar9,uVar10,uVar11,uVar12,puVar13);
        }
        else if (local_11 == '\x02') {
          *(byte *)(param_1 + 0x33a + (uint)local_12 * 0x16) = bVar7;
          *(uint *)(param_1 + 0x33b + (uint)local_12 * 0x16) = (uint)local_c;
          FUN_00012bd0(local_30,&DAT_0014c60c);
          FUN_00012ba0(local_30,*(int *)PTR_DAT_004c94d4 + 4 + local_10 * 0x1c3,0x14);
          FUN_000140d0(param_1 + 0x430 + (uint)local_12 * 0xc,local_30);
          *(undefined4 *)(param_1 + 0x434 + (uint)local_12 * 0xc) =
               *(undefined4 *)(param_1 + 0x175 + uVar6 * 0x16);
          FUN_0014bec4(param_1,local_c,local_12);
          iVar3 = FUN_00478630(*(undefined4 *)PTR_DAT_004c8a78,*(undefined4 *)(param_1 + 0x154));
          iVar3 = iVar3 + *(int *)(param_1 + 0x17e + uVar6 * 0x16) + -4;
          iVar5 = FUN_00478644(*(undefined4 *)PTR_DAT_004c8a78,*(undefined4 *)(param_1 + 0x154));
          FUN_00020ca8(iVar5 + *(int *)(param_1 + 0x17a + uVar6 * 0x16) + -4,iVar3,local_38);
          puVar13 = local_38;
          uVar12 = 0;
          uVar11 = 0;
          uVar10 = 0x1e;
          uVar9 = 4;
          uVar8 = 1;
          uVar4 = 0;
          FUN_00020ca8(*(int *)(param_1 + 0x17a + uVar6 * 0x16) + -4,
                       *(int *)(param_1 + 0x17e + uVar6 * 0x16) + -4,local_40,0,1,4,0x1e,0,0,puVar13
                      );
          FUN_0014ec28(*(undefined4 *)(param_1 + 0x488 + (uint)local_12 * 4),
                       *(undefined4 *)(param_1 + 0x154),local_40,uVar4,uVar8,uVar9,uVar10,uVar11,
                       uVar12,puVar13);
          local_12 = local_12 + 1;
        }
        else if (local_11 == '\x03') {
          *(byte *)(param_1 + 0x33a + (uint)local_13 * 0x16) = bVar7;
          *(uint *)(param_1 + 0x33b + (uint)local_13 * 0x16) = (uint)local_c;
          FUN_00012bd0(local_30,&DAT_0014c614);
          FUN_00012ba0(local_30,*(int *)PTR_DAT_004c94d4 + 4 + local_10 * 0x1c3,0x14);
          FUN_000140d0(param_1 + 0x430 + (uint)local_13 * 0xc,local_30);
          *(undefined4 *)(param_1 + 0x434 + (uint)local_13 * 0xc) =
               *(undefined4 *)(param_1 + 0x175 + uVar6 * 0x16);
          FUN_0014bec4(param_1,local_c,local_13);
          iVar3 = FUN_00478630(*(undefined4 *)PTR_DAT_004c8a78,*(undefined4 *)(param_1 + 0x158));
          iVar3 = iVar3 + *(int *)(param_1 + 0x17e + uVar6 * 0x16) + -4;
          iVar5 = FUN_00478644(*(undefined4 *)PTR_DAT_004c8a78,*(undefined4 *)(param_1 + 0x158));
          FUN_00020ca8(iVar5 + *(int *)(param_1 + 0x17a + uVar6 * 0x16) + -4,iVar3,local_38);
          puVar13 = local_38;
          uVar12 = 0;
          uVar11 = 0;
          uVar10 = 0x1e;
          uVar9 = 4;
          uVar8 = 1;
          uVar4 = 0;
          FUN_00020ca8(*(int *)(param_1 + 0x17a + uVar6 * 0x16) + -4,
                       *(int *)(param_1 + 0x17e + uVar6 * 0x16) + -4,local_40,0,1,4,0x1e,0,0,puVar13
                      );
          FUN_0014ec28(*(undefined4 *)(param_1 + 0x488 + (uint)local_13 * 4),
                       *(undefined4 *)(param_1 + 0x158),local_40,uVar4,uVar8,uVar9,uVar10,uVar11,
                       uVar12,puVar13);
          local_13 = local_13 + 1;
        }
      }
      local_9 = local_9 + 1;
      bVar7 = bVar7 + 1;
    } while (bVar7 != 0x15);
    *(undefined1 *)(param_1 + 0x3d7) = 1;
    *(undefined1 *)(param_1 + 0x42e) = 0;
  }
  puVar13 = puStack_50;
  *in_FS_OFFSET = uStack_58;
  puStack_50 = &LAB_0014c5fd;
  puStack_54 = (undefined1 *)0x14c5ed;
  FUN_00013eac(&local_18,uStack_58,puVar13);
  puStack_54 = (undefined1 *)0x14c5f5;
  FUN_00013eac(&local_8);
  return;
}

