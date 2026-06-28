/**
 * trade_shop.c - WLO Ticaret (Secure Trade), Tezgah/Pazar (Stall) ve NPC Dükkan Arayüz Mekanizmaları.
 * Extracted from aLogin.exe decompiled C code.
 */

/*******************************************************************************
 * @fonksiyon      FUN_002a1f14
 * @başlık         Güvenli Takas Slot Yükleyicisi (Secure Trade Slots Renderer)
 * @açıklama       Oyuncular arası takas arayüzündeki eşya slotlarını ve onay butonlarını hazırlar.
 * @ofsetler       Takas penceresindeki my_items (+0x18c) ve other_items (+0x21c) ofsetleri.
 * @paketler       Takas Durum/Kilit Paketleri (Opcode 20).
 * 
 * @detaylı_analiz 
 * * 1. Takas penceresi açıldığında slotlar oluşturulur.
 *  * 2. Oyuncunun kendi eklediği ve karşı tarafın eklediği eşyalar ofsetlere göre dizilir.
 *  * 3. Kilit butonuna basıldığında sunucuya takas kilit paketi gönderilir.
 *******************************************************************************/
void FUN_002a1f14(int *param_1,int param_2)

{
  ushort uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined1 *puVar4;
  char cVar5;
  byte bVar6;
  short sVar7;
  uint uVar8;
  uint uVar9;
  undefined3 uVar11;
  undefined4 uVar10;
  int iVar12;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined2 uVar14;
  undefined2 extraout_var_04;
  undefined2 extraout_var_05;
  undefined2 extraout_var_06;
  undefined2 extraout_var_07;
  undefined2 extraout_var_08;
  undefined2 extraout_var_09;
  undefined2 extraout_var_10;
  undefined2 extraout_var_11;
  undefined2 extraout_var_12;
  undefined2 extraout_var_13;
  undefined2 extraout_var_14;
  undefined2 extraout_var_15;
  undefined2 extraout_var_16;
  undefined2 extraout_var_17;
  undefined2 extraout_var_18;
  undefined2 extraout_var_19;
  undefined2 extraout_var_20;
  uint uVar13;
  undefined2 extraout_var_21;
  undefined2 extraout_var_22;
  undefined2 extraout_var_23;
  undefined2 extraout_var_24;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  int extraout_EDX_05;
  int extraout_EDX_06;
  int extraout_EDX_07;
  int extraout_EDX_08;
  int extraout_EDX_09;
  int extraout_EDX_10;
  int extraout_EDX_11;
  int extraout_EDX_12;
  int extraout_EDX_13;
  int extraout_EDX_14;
  int extraout_EDX_15;
  int extraout_EDX_16;
  undefined2 extraout_var_25;
  undefined2 extraout_var_26;
  undefined2 extraout_var_27;
  undefined2 extraout_var_28;
  undefined2 extraout_var_29;
  undefined2 extraout_var_30;
  undefined2 extraout_var_31;
  undefined2 extraout_var_32;
  undefined2 extraout_var_33;
  undefined2 extraout_var_34;
  undefined2 extraout_var_35;
  undefined2 extraout_var_36;
  int unaff_EBX;
  int unaff_ESI;
  int iVar15;
  int *piVar16;
  undefined4 *puVar17;
  ushort *puVar18;
  char *pcVar19;
  undefined4 *puVar20;
  int iVar21;
  undefined4 *in_FS_OFFSET;
  bool bVar22;
  undefined1 uVar23;
  float10 fVar24;
  int local_3a8;
  int local_3a4;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined4 local_398;
  undefined4 local_394;
  undefined4 local_390;
  undefined4 local_38c;
  undefined4 local_388;
  undefined4 local_384;
  undefined1 local_380 [4];
  char *local_37c;
  undefined4 local_378;
  char *local_374;
  undefined4 local_370;
  undefined4 local_36c;
  uint local_368;
  undefined1 local_364 [4];
  undefined4 local_360;
  undefined1 local_35c [4];
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  uint local_34c;
  uint local_348;
  char *local_344;
  undefined1 local_340 [4];
  char *local_33c;
  undefined1 local_338 [4];
  char *local_334;
  undefined1 local_330 [4];
  undefined4 local_32c;
  undefined4 local_328;
  undefined1 local_324 [4];
  undefined4 local_320;
  uint local_31c;
  undefined1 local_318 [4];
  undefined4 local_314;
  undefined4 local_310;
  undefined4 local_30c;
  undefined4 local_308;
  undefined4 local_304;
  int local_300;
  undefined4 local_2fc;
  int local_2f8;
  undefined4 local_2f4;
  int local_2f0;
  int local_2ec;
  undefined4 local_2e8;
  undefined4 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined4 local_2d8;
  int local_2d4;
  undefined4 local_2d0;
  undefined4 local_2cc;
  undefined4 local_2c8;
  undefined1 local_2c4 [4];
  char *local_2c0;
  undefined4 local_2bc;
  char *local_2b8;
  undefined1 local_2b4 [20];
  undefined4 local_2a0;
  undefined4 local_29c;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_28d;
  undefined4 local_280;
  undefined2 local_275;
  undefined4 local_25b [3];
  undefined1 local_24c;
  short local_24b;
  ushort local_23d [3];
  int local_237 [2];
  undefined1 local_22e;
  char local_22c;
  byte local_1ea;
  byte local_1e0;
  undefined1 local_1d3;
  short local_1d1;
  short local_1cf;
  short local_1cd;
  short local_1cb;
  undefined1 local_1c9 [275];
  ushort local_b6;
  int *local_98;
  ushort local_92;
  int local_90;
  int local_8c;
  char local_86 [4];
  char local_82;
  char local_81;
  char local_80;
  char local_7f;
  char local_7e;
  char local_7d;
  undefined4 local_7c;
  int local_78;
  int local_74;
  uint local_70;
  char *local_6c;
  uint local_68;
  int local_64;
  undefined4 local_60;
  double local_5c;
  undefined1 local_50 [4];
  char *local_4c;
  undefined4 uStack_48;
  uint local_44;
  undefined4 uStack_40;
  undefined2 local_3c;
  undefined2 uStack_3a;
  undefined2 local_38;
  undefined2 uStack_36;
  undefined *local_34;
  int local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  int *piStack_24;
  undefined1 *puStack_20;
  
  bVar6 = 0;
  puStack_20 = &stack0xfffffffc;
  iVar12 = 0x74;
  do {
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  piStack_24 = (int *)&LAB_002a483e;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puVar4 = &stack0xfffffffc;
  if ((((*(int *)(param_2 + 0xdc) == 99999) ||
       (puVar4 = &stack0xfffffffc, *(int *)(*(int *)PTR_DAT_004c8cf8 + 0x110) == param_2)) ||
      (puVar4 = &stack0xfffffffc, param_2 == 0)) ||
     (puVar4 = &stack0xfffffffc, param_1[0x51] == param_2)) goto LAB_002a47d1;
  if (*(int *)(param_2 + 0xdc) == 0) {
    uStack_2c = 0x2a1f8e;
    puStack_20 = &stack0xfffffffc;
    (**(code **)(*param_1 + 0x24))();
    uStack_2c = 0x2a1f9a;
    (**(code **)(**(int **)PTR_DAT_004c8630 + 0x24))();
    puVar4 = puStack_20;
    goto LAB_002a47d1;
  }
  param_1[0x51] = param_2;
  uStack_2c = 0x2a1fc1;
  uVar8 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xdc));
  uVar8 = uVar8 & 0xffff;
  puVar4 = puStack_20;
  if (uVar8 == 0) goto LAB_002a47d1;
  uStack_48 = uStack_48 & 0xffff;
  local_44 = 0;
  iVar15 = 0;
  uStack_2c = 0x2a1fe8;
  FUN_00013eac(&local_64);
  local_70 = 0;
  local_90 = 0;
  local_8c = 0;
  local_74 = 0;
  uStack_2c = 0x2a200a;
  FUN_00013eac(&local_68);
  uStack_2c = 0x2a2012;
  FUN_00013eac(&local_6c);
  uStack_2c = 0x2a201a;
  FUN_00013eac(&local_7c);
  iVar12 = 1;
  do {
    if (*(int *)(*(int *)PTR_DAT_004c914c + 0x1c0 + iVar12 * 4) == param_2) {
      uStack_48._0_3_ = CONCAT12(1,(undefined2)uStack_48);
      break;
    }
    iVar12 = iVar12 + 1;
  } while (iVar12 != 7);
  if (uStack_48._2_1_ != '\0') {
    iVar12 = 1;
    do {
      iVar21 = *(int *)(*(int *)PTR_DAT_004c914c + 0x1c0 + iVar12 * 4);
      if (*(int *)(iVar21 + 0xdc) != 0) {
        uStack_2c = 0x2a207e;
        uVar9 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(iVar21 + 0xdc));
        uVar9 = uVar9 & 0xffff;
        if (uVar9 != 0) {
          bVar22 = false;
          if (*(char *)(*(int *)PTR_DAT_004c94d4 + 0x85 + uVar9 * 0x1c3) != '\0') {
            if (local_44 == 0) {
              local_44 = (uint)*(byte *)(*(int *)PTR_DAT_004c94d4 + 0x85 + uVar9 * 0x1c3);
            }
            if (*(byte *)(*(int *)PTR_DAT_004c94d4 + 0x85 + uVar9 * 0x1c3) == local_44) {
              bVar22 = true;
            }
          }
          if (bVar22) {
            iVar15 = iVar15 + 1;
          }
        }
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 != 7);
    if (iVar15 < 5) {
      uStack_48 = uStack_48 & 0xffffff;
    }
    else if (4 < iVar15) {
      uStack_2c = 0x2a2102;
      cVar5 = FUN_0049ea98(local_44);
      if (cVar5 != '\0') {
        uStack_48 = CONCAT13(1,(undefined3)uStack_48);
      }
    }
  }
  puVar17 = (undefined4 *)(*(int *)PTR_DAT_004c94d4 + 4 + uVar8 * 0x1c3);
  puVar20 = local_25b;
  for (iVar12 = 0x70; iVar12 != 0; iVar12 = iVar12 + -1) {
    *puVar20 = *puVar17;
    puVar17 = puVar17 + (uint)bVar6 * -2 + 1;
    puVar20 = puVar20 + (uint)bVar6 * -2 + 1;
  }
  *(undefined2 *)puVar20 = *(undefined2 *)puVar17;
  *(undefined1 *)((int)puVar20 + (uint)bVar6 * -4 + 2) =
       *(undefined1 *)((int)puVar17 + (uint)bVar6 * -4 + 2);
  uStack_2c = 0x2a213b;
  (**(code **)(*(int *)param_1[0x4c] + 0x40))();
  uStack_2c = 0x2a214d;
  FUN_00012d10(local_86,10,0);
  iVar12 = 1;
  pcVar19 = local_86;
  do {
    bVar22 = iVar12 == 10;
    switch(iVar12) {
    case 1:
      uStack_2c = 0x2a21a9;
      cVar5 = FUN_004350d0(*(undefined4 *)PTR_DAT_004c94d4,local_24b);
      if (cVar5 == '\0') {
        *pcVar19 = '\x01';
      }
      break;
    case 2:
      *pcVar19 = '\x01';
      break;
    case 3:
      *pcVar19 = '\x01';
      break;
    case 4:
      uStack_2c = 0x2a21df;
      cVar5 = FUN_004357a4(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xdc));
      if (cVar5 != '\0') {
        *pcVar19 = '\x01';
      }
      break;
    case 5:
      uStack_2c = 0x2a2205;
      cVar5 = FUN_0043217c(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xdc));
      if ((cVar5 != '\0') && (local_86[3] == '\0')) {
        *pcVar19 = '\x01';
      }
      uStack_2c = 0x2a2228;
      cVar5 = FUN_004335bc(*(undefined4 *)PTR_DAT_004c94d4,
                           CONCAT22(extraout_var,*(undefined2 *)(param_2 + 0xdc)));
      if ((cVar5 == '\x02') && (*(short *)(param_2 + 0xfe) != 0)) {
        *pcVar19 = '\x01';
      }
      uStack_2c = 0x2a2252;
      cVar5 = FUN_004335bc(*(undefined4 *)PTR_DAT_004c94d4,
                           CONCAT22(extraout_var_00,*(undefined2 *)(param_2 + 0xdc)));
      if ((cVar5 == '\x03') && (*(short *)(param_2 + 0xfe) != 0)) {
        *pcVar19 = '\x01';
      }
      break;
    case 6:
      uStack_2c = 0x2a2289;
      cVar5 = FUN_0043217c(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xdc));
      if (cVar5 != '\0') {
        *pcVar19 = '\x01';
      }
      break;
    case 7:
      uStack_2c = 0x2a22af;
      sVar7 = FUN_004355f0(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xdc));
      if (sVar7 != 0) {
        *pcVar19 = '\x01';
      }
      break;
    case 8:
      if (*(short *)(param_2 + 0xfa) != 0) {
        *pcVar19 = '\x01';
      }
      break;
    case 9:
      uStack_2c = 0x2a22ef;
      cVar5 = FUN_004335bc(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xdc));
      if ((cVar5 == '\x02') && (*(short *)(param_2 + 0xfe) != 0)) {
        *pcVar19 = '\x01';
      }
      uStack_2c = 0x2a2319;
      cVar5 = FUN_004335bc(*(undefined4 *)PTR_DAT_004c94d4,
                           CONCAT22(extraout_var_01,*(undefined2 *)(param_2 + 0xdc)));
      if ((cVar5 == '\x03') && (*(short *)(param_2 + 0xfe) != 0)) {
        *pcVar19 = '\x01';
      }
      break;
    case 10:
      uStack_2c = 0x2a233f;
      FUN_0001423c(*(undefined4 *)(param_2 + 4),"TRe_CompoundForm");
      if (!bVar22) {
        uStack_2c = 0x2a2351;
        FUN_0001423c(*(undefined4 *)(param_2 + 4),"CompoundItem_Main");
        if (!bVar22) {
          uStack_2c = 0x2a2363;
          FUN_0001423c(*(undefined4 *)(param_2 + 4),"CompoundItem_Sub");
          if (!bVar22) {
            *pcVar19 = '\x01';
            break;
          }
        }
      }
      *pcVar19 = '\0';
    }
    iVar12 = iVar12 + 1;
    pcVar19 = pcVar19 + 1;
  } while (iVar12 != 0xb);
  if (local_86[0] != '\0') {
    uStack_2c = 0x2a239b;
    cVar5 = FUN_00430a0c(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xdc));
    uVar14 = extraout_var_02;
    if (((byte)(cVar5 - 1U) < 5) && (*(char *)(param_2 + 0xf8) != '\0')) {
      uStack_2c = 0x2a23c9;
      FUN_0001953c(*(undefined1 *)(param_2 + 0xf8),&local_294);
      uStack_2c = 0x2a23dc;
      FUN_00014178(&local_64,&DAT_002a48a8,local_294);
      iVar12 = 2;
      puVar18 = local_23d;
      piVar16 = local_237;
      do {
        uVar1 = *puVar18;
        if ((((((ushort)(uVar1 - 0x19) < 2) || ((ushort)(uVar1 - 0xcf) < 2)) ||
             ((ushort)(uVar1 - 0xd2) < 2)) || ((ushort)(uVar1 - 0xd6) < 3)) && (100 < *piVar16)) {
          local_74 = local_74 + 1;
        }
        piVar16 = piVar16 + 1;
        puVar18 = puVar18 + 1;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
      if (local_74 == 1) {
        local_70 = (uint)*(byte *)(param_2 + 0xf8) * 2;
      }
      uVar14 = extraout_var_03;
      if (local_74 == 2) {
        local_70 = (uint)*(byte *)(param_2 + 0xf8);
      }
    }
    uStack_2c = 0x2a2463;
    cVar5 = FUN_00430a0c(*(undefined4 *)PTR_DAT_004c94d4,
                         CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xdc)));
    if (cVar5 == '\x06') {
      uStack_2c = 0x2a247d;
      cVar5 = FUN_004362cc(*(undefined4 *)PTR_DAT_004c94d4,
                           CONCAT22(extraout_var_04,*(undefined2 *)(param_2 + 0xdc)));
      if ((cVar5 != '\0') && (*(char *)(param_2 + 0xfc) != '\0')) {
        uStack_2c = 0x2a24a2;
        FUN_0001953c(*(undefined1 *)(param_2 + 0xfc),&local_298);
        uStack_2c = 0x2a24b5;
        FUN_00014178(&local_64,&DAT_002a48a8,local_298);
      }
    }
  }
  uVar11 = (undefined3)((uint)param_2 >> 8);
  if (*(char *)(param_2 + 0xf9) != '\0') {
    uStack_2c = 0x2a24cf;
    local_90 = FUN_002a1ee8(CONCAT31(uVar11,*(undefined1 *)(param_2 + 0xf9)));
    local_8c = (uint)*(byte *)(param_2 + 0xf9) + (uint)(*(byte *)(param_2 + 0xf9) >> 4) * -0x10;
    uStack_2c = 0x2a2511;
    local_8c = FUN_002a1ee8(local_8c * 0x10);
  }
  uStack_2c = 0x2a2527;
  FUN_00012bd0(local_2b4,&DAT_002a48ac);
  uStack_2c = 0x2a253a;
  FUN_00012ba0(local_2b4,local_25b,0x10);
  uStack_2c = 0x2a254b;
  FUN_000140d0(&local_2a0,local_2b4);
  uStack_2c = local_2a0;
  local_30 = local_64;
  local_34 = &DAT_002a48b8;
  local_38 = 0x2569;
  uStack_36 = 0x2a;
  FUN_000141ec(&local_29c,3);
  local_38 = 0x257d;
  uStack_36 = 0x2a;
  (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_29c);
  local_38 = 0x2588;
  uStack_36 = 0x2a;
  cVar5 = FUN_002a6ba8(param_1,param_2);
  uVar14 = extraout_var_05;
  if (cVar5 == '\0') {
    local_38 = 0x259f;
    uStack_36 = 0x2a;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],"<Non-tradeable>");
    uVar14 = extraout_var_06;
  }
  local_38 = (undefined2)unaff_EBX;
  uVar2 = local_38;
  uStack_36 = (undefined2)((uint)unaff_EBX >> 0x10);
  uVar3 = uStack_36;
  if (local_86[0] != '\0') {
    uStack_40 = (char *)((uint)uStack_40 & 0xffffff);
    local_38 = 0x25c6;
    uStack_36 = 0x2a;
    cVar5 = FUN_0043217c(*(undefined4 *)PTR_DAT_004c94d4,
                         CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xdc)));
    if ((cVar5 != '\0') && (*(short *)(param_2 + 0xea) != 0)) {
      local_38 = 0x25f5;
      uStack_36 = 0x2a;
      cVar5 = FUN_004359d8(*(undefined4 *)PTR_DAT_004c94d4,
                           CONCAT22(extraout_var_07,*(undefined2 *)(param_2 + 0xea)));
      if (cVar5 != '\0') {
        local_38 = 0x2613;
        uStack_36 = 0x2a;
        uVar9 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,
                             CONCAT22(extraout_var_08,*(undefined2 *)(param_2 + 0xea)));
        if (*(char *)(*(int *)PTR_DAT_004c94d4 + 0x13 + (uVar9 & 0xffff) * 0x1c3) == '4') {
          iVar12 = 2;
          puVar18 = local_23d;
          piVar16 = local_237;
          do {
            if (((*puVar18 != 0) && (*puVar18 != 0xfa)) && (100 < *piVar16)) {
              uStack_40 = (char *)CONCAT13(uStack_40._3_1_ + '\x01',(undefined3)uStack_40);
            }
            piVar16 = piVar16 + 1;
            puVar18 = puVar18 + 1;
            iVar12 = iVar12 + -1;
          } while (iVar12 != 0);
          uVar14 = (undefined2)((uint)*(int *)PTR_DAT_004c94d4 >> 0x10);
          if (uStack_40._3_1_ == '\x01') {
            local_38 = 0x2681;
            uStack_36 = 0x2a;
            uVar9 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,
                                 CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xea)));
            uStack_40 = (char *)CONCAT13(*(char *)(*(int *)PTR_DAT_004c94d4 + 0x31 +
                                                  (uVar9 & 0xffff) * 0x1c3) * '\x02',
                                         (undefined3)uStack_40);
          }
          else if (uStack_40._3_1_ == '\x02') {
            local_38 = 0x26b3;
            uStack_36 = 0x2a;
            uVar9 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,
                                 CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xea)));
            uStack_40 = (char *)CONCAT13(*(undefined1 *)
                                          (*(int *)PTR_DAT_004c94d4 + 0x31 +
                                          (uVar9 & 0xffff) * 0x1c3),(undefined3)uStack_40);
          }
          else {
            uStack_40 = (char *)((uint)uStack_40 & 0xffffff);
          }
          if (uStack_48._3_1_ != '\0') {
            if (*(char *)(*(int *)PTR_DAT_004c94d4 + 0x85 + uVar8 * 0x1c3) == '\0') {
              if (((*(char *)(*(int *)PTR_DAT_004c94d4 + 0x33 + uVar8 * 0x1c3) == -0x72) &&
                  ((byte)(*(char *)(*(int *)PTR_DAT_004c98f4 + 0x1f9c) - 1U) < 6)) &&
                 (*(char *)(*(int *)PTR_DAT_004c94d4 + 0x32 + uVar8 * 0x1c3) == '\x06')) {
                local_38 = 0x2753;
                uStack_36 = 0x2a;
                cVar5 = FUN_0049eaa8(local_44,*(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x1f9c));
                if (cVar5 != '\0') {
                  uStack_40 = (char *)CONCAT13(uStack_40._3_1_ * '\x02',(undefined3)uStack_40);
                }
              }
            }
            else {
              uStack_40 = (char *)CONCAT13(uStack_40._3_1_ * '\x02',(undefined3)uStack_40);
            }
          }
        }
      }
    }
    iVar12 = 2;
    puVar18 = local_23d;
    piVar16 = local_237;
    local_98 = &local_90;
    do {
      uVar1 = *puVar18;
      if (uVar1 < 0xd1) {
        if (uVar1 == 0xd0) {
          local_38 = 0x2841;
          uStack_36 = 0x2a;
          FUN_00013f44(&stack0xffffffec,"MaxSp");
        }
        else if (uVar1 < 0x41) {
          if (uVar1 == 0x40) {
            local_38 = 0x289e;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,"Amity");
          }
          else if (uVar1 == 0x19) {
            local_38 = 0x280b;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,&DAT_002a48dc);
          }
          else if (uVar1 == 0x1a) {
            local_38 = 0x281d;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,&DAT_002a48e8);
          }
          else {
            if (uVar1 != 0x24) goto LAB_002a28be;
            local_38 = 0x28ad;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,&DAT_002a4968);
          }
        }
        else if (uVar1 == 100) {
          local_38 = 0x28bc;
          uStack_36 = 0x2a;
          FUN_00013f44(&stack0xffffffec,"Shoot RES");
        }
        else {
          if (uVar1 != 0xcf) goto LAB_002a28be;
          local_38 = 0x282f;
          uStack_36 = 0x2a;
          FUN_00013f44(&stack0xffffffec,"MaxHp");
        }
LAB_002a28c6:
        if (unaff_EBX != 0) {
          local_38 = 0x28d9;
          uStack_36 = 0x2a;
          FUN_00014134(&stack0xffffffec,&DAT_002a498c);
        }
        iVar15 = *piVar16;
        if ((iVar15 != 0) && (iVar15 != 100)) {
          if (iVar15 + -100 + *local_98 < 1) {
            if (*piVar16 + -100 + *local_98 < 0) {
              local_38 = 0x2959;
              uStack_36 = 0x2a;
              FUN_0001953c(*piVar16 + -100 + *local_98,&local_2bc);
              local_38 = 0x2967;
              uStack_36 = 0x2a;
              FUN_00014134(&stack0xffffffec,local_2bc);
            }
            else {
              local_3c = 0x48a8;
              uStack_3a = 0x2a;
              uStack_40 = (char *)0x2a297e;
              local_38 = uVar2;
              uStack_36 = uVar3;
              FUN_0001953c(0,&local_2c0);
              uStack_40 = local_2c0;
              local_44 = 0x2a2991;
              FUN_000141ec(&stack0xffffffec,3);
            }
          }
          else {
            local_3c = 0x48a8;
            uStack_3a = 0x2a;
            uStack_40 = (char *)0x2a291b;
            local_38 = uVar2;
            uStack_36 = uVar3;
            FUN_0001953c(*piVar16 + -100 + *local_98,&local_2b8);
            uStack_40 = local_2b8;
            local_44 = 0x2a292e;
            FUN_000141ec(&stack0xffffffec,3);
          }
          if ((local_22c == 'q') && (*puVar18 == 0x24)) {
            local_38 = 0x29b5;
            uStack_36 = 0x2a;
            FUN_00014134(&stack0xffffffec,&DAT_002a4998);
            local_38 = 0x29d7;
            uStack_36 = 0x2a;
            uVar10 = FUN_0049ed34(*(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x1f98),
                                  *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x1f99));
            local_38 = (undefined2)uVar10;
            uStack_36 = (undefined2)((uint)uVar10 >> 0x10);
            local_3c = 0x29e7;
            uStack_3a = 0x2a;
            iVar15 = FUN_0049ed34(0xa2,1);
            if (iVar15 <= CONCAT22(uStack_36,local_38)) {
              local_78 = ((*piVar16 + -100) * 20000000) / 1000000;
              local_38 = 0x49a4;
              uStack_36 = 0x2a;
              local_3c = 0x2a23;
              uStack_3a = 0x2a;
              FUN_0001953c(local_78,local_2c4);
              local_3c = local_2c4._0_2_;
              uStack_3a = local_2c4._2_2_;
              uStack_40 = &DAT_002a49c0;
              local_44 = 0x2a2a3b;
              FUN_000141ec(&local_7c,3);
            }
          }
          if ((local_22c == 'w') && (*puVar18 == 100)) {
            local_38 = 0x2a57;
            uStack_36 = 0x2a;
            FUN_00014134(&stack0xffffffec,&DAT_002a4998);
          }
          local_38 = 0x2a5f;
          uStack_36 = 0x2a;
          FUN_00013eac(&local_68);
          if ((0 < (int)local_70) && (*piVar16 != 100 && -1 < *piVar16 + -100)) {
            if ((*puVar18 == 0xcf) &&
               ((*(int *)(param_2 + 0xdc) == 0x2bd5 || (*(int *)(param_2 + 0xdc) == 0x2bd6)))) {
              local_38 = 0x2aa4;
              uStack_36 = 0x2a;
              FUN_0001953c(local_70 * 3,&local_2c8);
              local_38 = 0x2ab7;
              uStack_36 = 0x2a;
              FUN_00014178(&local_68,&DAT_002a48a8,local_2c8);
            }
            else {
              local_38 = 0x2ac7;
              uStack_36 = 0x2a;
              FUN_0001953c(local_70,&local_2cc);
              local_38 = 0x2ada;
              uStack_36 = 0x2a;
              FUN_00014178(&local_68,&DAT_002a48a8,local_2cc);
            }
          }
          local_38 = 0x2ae2;
          uStack_36 = 0x2a;
          FUN_00013eac(&local_6c);
          if ((uStack_40._3_1_ != '\0') && (*piVar16 != 100 && -1 < *piVar16 + -100)) {
            local_38 = 0x2b01;
            uStack_36 = 0x2a;
            FUN_0001953c(uStack_40._3_1_,&local_2d0);
            local_38 = 0x2b14;
            uStack_36 = 0x2a;
            FUN_00014178(&local_6c,&DAT_002a48a8,local_2d0);
          }
          local_3c = 0x49cc;
          uStack_3a = 0x2a;
          uStack_40 = local_6c;
          local_44 = local_68;
          uStack_48 = 0x2a2b2f;
          local_38 = uVar2;
          uStack_36 = uVar3;
          FUN_000141ec(&stack0xffffffec,4);
          uStack_48 = 0x2a2b40;
          (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],unaff_EBX);
        }
      }
      else {
        if (uVar1 < 0xd8) {
          if (uVar1 == 0xd7) {
            local_38 = 0x2871;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,&DAT_002a492c);
          }
          else if (uVar1 == 0xd2) {
            local_38 = 0x2853;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,&DAT_002a4914);
          }
          else if (uVar1 == 0xd3) {
            local_38 = 0x2862;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,&DAT_002a4920);
          }
          else {
            if (uVar1 != 0xd6) goto LAB_002a28be;
            local_38 = 0x288f;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,&DAT_002a494c);
          }
          goto LAB_002a28c6;
        }
        if (uVar1 == 0xd8) {
          local_38 = 0x2880;
          uStack_36 = 0x2a;
          FUN_00013f44(&stack0xffffffec,&DAT_002a493c);
          goto LAB_002a28c6;
        }
        if (uVar1 != 0xfa) {
LAB_002a28be:
          local_38 = 0x28c6;
          uStack_36 = 0x2a;
          FUN_00013eac(&stack0xffffffec);
          goto LAB_002a28c6;
        }
      }
      local_98 = local_98 + 1;
      piVar16 = piVar16 + 1;
      puVar18 = puVar18 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  local_38 = 0x2b65;
  uStack_36 = 0x2a;
  FUN_0049f2c4(local_24c,&local_2d4);
  uVar23 = local_2d4 == 0;
  if (!(bool)uVar23) {
    local_38 = 0x2b7f;
    uStack_36 = 0x2a;
    FUN_0049f2c4(local_24c,&local_2dc);
    local_38 = 0x2b95;
    uStack_36 = 0x2a;
    FUN_00014178(&local_2d8,"Type: ",local_2dc);
    local_38 = 0x2ba9;
    uStack_36 = 0x2a;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_2d8);
  }
  local_38 = 0x2bb9;
  uStack_36 = 0x2a;
  FUN_0001423c(*(undefined4 *)(param_2 + 4),"TRe_CompoundForm");
  if ((bool)uVar23) {
LAB_002a2be3:
    local_38 = 0x2bf6;
    uStack_36 = 0x2a;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],"Alch Type: ");
    local_38 = 0x2c03;
    uStack_36 = 0x2a;
    FUN_00013f44(&stack0xffffffec,"Alch Type: ");
    local_38 = 0x2c16;
    uStack_36 = 0x2a;
    cVar5 = FUN_00432ae4(*(undefined4 *)PTR_DAT_004c94d4,CONCAT22(extraout_var_09,local_24b));
    if (cVar5 == '\0') {
      local_38 = 0x2c27;
      uStack_36 = 0x2a;
      FUN_00013f44(&stack0xffffffec,"Not a material");
    }
    else {
      local_38 = 0x2c36;
      uStack_36 = 0x2a;
      FUN_00013f44(&stack0xffffffec,"Not for crafting");
    }
    local_38 = 0x2c49;
    uStack_36 = 0x2a;
    FUN_00014178(&local_2e0,&DAT_002a4a30,unaff_EBX);
    local_38 = 0x2c5d;
    uStack_36 = 0x2a;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_2e0);
    if ((local_1e0 & 8) == 0) {
      local_38 = 0x2c73;
      uStack_36 = 0x2a;
      FUN_00013f44(&stack0xffffffec,"Can\'t compound");
    }
    else {
      local_38 = 0x2c82;
      uStack_36 = 0x2a;
      FUN_00013f44(&stack0xffffffec,"Can\'t craft");
    }
    local_38 = 0x2c95;
    uStack_36 = 0x2a;
    FUN_00014178(&local_2e4,&DAT_002a4a30,unaff_EBX);
    local_38 = 0x2ca9;
    uStack_36 = 0x2a;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_2e4);
    local_38 = 0x2cbc;
    uStack_36 = 0x2a;
    cVar5 = FUN_00432ae4(*(undefined4 *)PTR_DAT_004c94d4,CONCAT22(extraout_var_10,local_24b));
    if (cVar5 == '\0') {
      local_38 = 0x2cd2;
      uStack_36 = 0x2a;
      FUN_0049f5e8(local_1d3,&stack0xffffffec);
      local_38 = 0x2cda;
      uStack_36 = 0x2a;
      FUN_00013eac(&stack0xffffffe8);
      local_38 = 0x2ce2;
      uStack_36 = 0x2a;
      FUN_00013eac(&stack0xffffffe4);
      if (unaff_EBX != 0) {
        local_38 = 0x2cfb;
        uStack_36 = 0x2a;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],"Alch Mat: ");
        local_38 = 0x2d0e;
        uStack_36 = 0x2a;
        FUN_00014178(&local_2e8,&DAT_002a4a80,unaff_EBX);
        local_38 = 0x2d22;
        uStack_36 = 0x2a;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_2e8);
      }
      if (local_1d1 != 0) {
        local_38 = 0x2d3d;
        uStack_36 = 0x2a;
        FUN_0049f5e8((undefined1)local_1d1,&local_2ec);
        if (local_2ec != 0) {
          local_38 = 0x2d54;
          uStack_36 = 0x2a;
          FUN_0049f5e8((undefined1)local_1d1,&stack0xffffffe8);
        }
      }
      if (local_1cf != 0) {
        local_38 = 0x2d6f;
        uStack_36 = 0x2a;
        FUN_0049f5e8((undefined1)local_1cf,&local_2f0);
        if (local_2f0 != 0) {
          local_38 = 0x2d8b;
          uStack_36 = 0x2a;
          FUN_00014178(&local_2f4,&DAT_002a4a90,unaff_ESI);
          local_38 = 0x2d9f;
          uStack_36 = 0x2a;
          (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_2f4);
          local_38 = 0x2dad;
          uStack_36 = 0x2a;
          FUN_0049f5e8((undefined1)local_1cf,&stack0xffffffe8);
        }
      }
      if (local_1cd != 0) {
        local_38 = 0x2dc8;
        uStack_36 = 0x2a;
        FUN_0049f5e8((undefined1)local_1cd,&local_2f8);
        if (local_2f8 != 0) {
          local_38 = 0x2de4;
          uStack_36 = 0x2a;
          FUN_00014178(&local_2fc,&DAT_002a4a90,unaff_ESI);
          local_38 = 0x2df8;
          uStack_36 = 0x2a;
          (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_2fc);
          local_38 = 0x2e06;
          uStack_36 = 0x2a;
          FUN_0049f5e8((undefined1)local_1cd,&stack0xffffffe8);
        }
      }
      if (local_1cb != 0) {
        local_38 = 0x2e21;
        uStack_36 = 0x2a;
        FUN_0049f5e8((undefined1)local_1cb,&local_300);
        if (local_300 != 0) {
          local_38 = 0x2e3d;
          uStack_36 = 0x2a;
          FUN_00014178(&local_304,&DAT_002a4a90,unaff_ESI);
          local_38 = 0x2e51;
          uStack_36 = 0x2a;
          (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_304);
          local_38 = 0x2e5f;
          uStack_36 = 0x2a;
          FUN_0049f5e8((undefined1)local_1cb,&stack0xffffffe8);
        }
      }
      if (unaff_ESI != 0) {
        local_38 = 0x2e78;
        uStack_36 = 0x2a;
        FUN_00014178(&local_308,&DAT_002a4a90,unaff_ESI);
        local_38 = 0x2e8c;
        uStack_36 = 0x2a;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_308);
      }
    }
  }
  else {
    local_38 = 0x2bcb;
    uStack_36 = 0x2a;
    FUN_0001423c(*(undefined4 *)(param_2 + 4),"CompoundItem_Main");
    if ((bool)uVar23) goto LAB_002a2be3;
    local_38 = 0x2bdd;
    uStack_36 = 0x2a;
    FUN_0001423c(*(undefined4 *)(param_2 + 4),"CompoundItem_Sub");
    if ((bool)uVar23) goto LAB_002a2be3;
  }
  local_38 = 0x2e9f;
  uStack_36 = 0x2a;
  FUN_0001953c(local_22e,&local_310);
  local_38 = 0x2eb5;
  uStack_36 = 0x2a;
  FUN_00014178(&local_30c,"Rank: ",local_310);
  local_38 = 0x2ec9;
  uStack_36 = 0x2a;
  (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_30c);
  uVar14 = extraout_var_11;
  if (local_24b == -0x78a7) {
    local_38 = 0x4ab0;
    uStack_36 = 0x2a;
    local_3c = 0x2ef2;
    uStack_3a = 0x2a;
    FUN_0001953c(*(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x5710),local_318);
    local_3c = local_318._0_2_;
    uStack_3a = local_318._2_2_;
    uStack_40 = "/";
    local_44 = 0x2a2f0d;
    FUN_0001953c(0xfa,&local_31c);
    local_44 = local_31c;
    uStack_48 = 0x2a2f23;
    FUN_000141ec(&local_314,4);
    uStack_48 = 0x2a2f37;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_314);
    uVar14 = extraout_var_12;
  }
  if (local_86[2] != '\0') {
    if (local_22c == 'r') {
      if (199 < local_1ea) {
        local_1ea = 199;
      }
      if (local_1ea != 0) {
        local_38 = 0x4acc;
        uStack_36 = 0x2a;
        local_3c = 0x2f7f;
        uStack_3a = 0x2a;
        FUN_0001953c(local_1ea,local_324);
        local_3c = local_324._0_2_;
        uStack_3a = local_324._2_2_;
        uStack_40 = "Below ";
        local_44 = 0x2a2f9a;
        FUN_000141ec(&local_320,3);
        local_44 = 0x2a2fae;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_320);
        uVar14 = extraout_var_13;
      }
    }
    else if (local_1ea != 0) {
      local_38 = 0x2fcc;
      uStack_36 = 0x2a;
      FUN_0001953c(local_1ea,&local_32c);
      local_38 = 0x2fe2;
      uStack_36 = 0x2a;
      FUN_00014178(&local_328,"LV Req: ",local_32c);
      local_38 = 0x2ff6;
      uStack_36 = 0x2a;
      (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_328);
      uVar14 = extraout_var_14;
    }
  }
  local_38 = 0x3009;
  uStack_36 = 0x2a;
  cVar5 = FUN_004350d0(*(undefined4 *)PTR_DAT_004c94d4,CONCAT22(uVar14,local_24b));
  if ((byte)(cVar5 - 1U) < 2) {
    local_3c = 0;
    uStack_3a = 0;
    iVar12 = 0;
    local_38 = 0x3031;
    uStack_36 = 0x2a;
    FUN_00012d10(&local_28d,0x32,0);
    uVar23 = *(char *)(param_2 + 0xd8) == '\v';
    if ((bool)uVar23) {
      iVar12 = *(int *)(*(int *)PTR_DAT_004c98f4 + 0x51bc + *(int *)(param_2 + 0xb0) * 4);
    }
    else {
      uVar23 = *(char *)(param_2 + 0xd8) == '\x0f';
      if ((bool)uVar23) {
        iVar12 = *(int *)(*(int *)PTR_DAT_004c98f4 + 0x54dc + *(int *)(param_2 + 0xb0) * 4);
      }
      else {
        local_38 = 0x3090;
        uStack_36 = 0x2a;
        FUN_0001423c("StallUtenSil",*(undefined4 *)(param_2 + 4));
        if ((bool)uVar23) {
          iVar12 = *(int *)(*(int *)PTR_DAT_004c98f4 + 0x27e8 +
                           *(int *)(*(int *)PTR_DAT_004c8cf8 + 0x14c + *(int *)(param_2 + 0xb0) * 4)
                           * 4);
        }
        else {
          local_38 = 0x30cb;
          uStack_36 = 0x2a;
          FUN_0001423c("Capsule",*(undefined4 *)(param_2 + 4));
          if ((bool)uVar23) {
            iVar12 = *(int *)(*(int *)PTR_DAT_004c98f4 + 0x27e8 + *(int *)(param_2 + 0xb0) * 4);
          }
        }
      }
    }
    local_38 = 0x30f5;
    uStack_36 = 0x2a;
    FUN_0001423c("SelectUitem",*(undefined4 *)(param_2 + 4));
    if ((bool)uVar23) {
      local_28d._1_2_ = *(short *)(*(int *)(*(int *)PTR_DAT_004c8cf8 + 0x110) + 0xdc);
      local_280 = *(undefined4 *)(*(int *)(*(int *)PTR_DAT_004c8cf8 + 0x110) + 0xe0);
      local_275 = *(undefined2 *)(*(int *)(*(int *)PTR_DAT_004c8cf8 + 0x110) + 0xe4);
    }
    else {
      local_38 = 0x315b;
      uStack_36 = 0x2a;
      FUN_0001423c("BeStallUtenSil",*(undefined4 *)(param_2 + 4));
      if ((bool)uVar23) {
        local_28d._1_2_ =
             *(short *)(*(int *)(*(int *)PTR_DAT_004c94b4 + 0xec + *(int *)(param_2 + 0xb0) * 4) +
                       0xdc);
        local_280 = *(undefined4 *)
                     (*(int *)(*(int *)PTR_DAT_004c94b4 + 0xec + *(int *)(param_2 + 0xb0) * 4) +
                     0xe0);
        local_275 = *(undefined2 *)
                     (*(int *)(*(int *)PTR_DAT_004c94b4 + 0xec + *(int *)(param_2 + 0xb0) * 4) +
                     0xe4);
      }
      else {
        local_38 = 0x31e2;
        uStack_36 = 0x2a;
        FUN_0001423c("CarCase",*(undefined4 *)(param_2 + 4));
        if ((bool)uVar23) {
          iVar15 = 1;
          do {
            if ((uint)*(byte *)(*(int *)PTR_DAT_004c98dc + 0x16f1 + iVar15 * 0x35) ==
                *(uint *)(param_2 + 0xb0)) {
              local_38 = (undefined2)iVar12;
              uStack_36 = (undefined2)((uint)iVar12 >> 0x10);
              puVar17 = (undefined4 *)(*(int *)PTR_DAT_004c98dc + 0x16f2 + iVar15 * 0x35);
              puVar20 = &local_28d;
              for (iVar12 = 0xc; iVar12 != 0; iVar12 = iVar12 + -1) {
                *puVar20 = *puVar17;
                puVar17 = puVar17 + (uint)bVar6 * -2 + 1;
                puVar20 = puVar20 + (uint)bVar6 * -2 + 1;
              }
              *(undefined2 *)puVar20 = *(undefined2 *)puVar17;
              iVar12 = CONCAT22(uStack_36,local_38);
            }
            iVar15 = iVar15 + 1;
          } while (iVar15 != 5);
        }
        else {
          local_38 = 0x3245;
          uStack_36 = 0x2a;
          FUN_0001423c("CupBoardItem",*(undefined4 *)(param_2 + 4));
          if ((bool)uVar23) {
            iVar15 = 1;
            do {
              if (*(int *)(*(int *)(*(int *)PTR_DAT_004c929c + 0xf4 + iVar15 * 4) + 0xb0) ==
                  *(int *)(param_2 + 0xb0)) {
                local_28d._1_2_ =
                     *(short *)(*(int *)(*(int *)PTR_DAT_004c929c + 0xf4 + iVar15 * 4) + 0xdc);
                local_280 = *(undefined4 *)
                             (*(int *)(*(int *)PTR_DAT_004c929c + 0xf4 + iVar15 * 4) + 0xe0);
                local_275 = *(undefined2 *)
                             (*(int *)(*(int *)PTR_DAT_004c929c + 0xf4 + iVar15 * 4) + 0xe4);
              }
              iVar15 = iVar15 + 1;
            } while (iVar15 != 0xb);
          }
          else {
            local_38 = 0x32dc;
            uStack_36 = 0x2a;
            FUN_0001423c("Express",*(undefined4 *)(param_2 + 4));
            if ((bool)uVar23) {
              local_28d._1_2_ =
                   *(short *)(*(int *)(*(int *)PTR_DAT_004c98f4 + 0x27e8 +
                                      *(int *)(*(int *)PTR_DAT_004c8b2c + 0x21c +
                                              *(int *)(param_2 + 0xb0) * 4) * 4) + 4);
              local_280 = *(undefined4 *)
                           (*(int *)(*(int *)PTR_DAT_004c98f4 + 0x27e8 +
                                    *(int *)(*(int *)PTR_DAT_004c8b2c + 0x21c +
                                            *(int *)(param_2 + 0xb0) * 4) * 4) + 0x20);
              local_275 = *(undefined2 *)
                           (*(int *)(*(int *)PTR_DAT_004c98f4 + 0x27e8 +
                                    *(int *)(*(int *)PTR_DAT_004c8b2c + 0x21c +
                                            *(int *)(param_2 + 0xb0) * 4) * 4) + 0x24);
            }
            else {
              local_38 = 0x338b;
              uStack_36 = 0x2a;
              FUN_0001423c("BankItem",*(undefined4 *)(param_2 + 4));
              if ((bool)uVar23) {
                local_28d._1_2_ =
                     *(short *)(*(int *)(*(int *)PTR_DAT_004c98f4 + 0x295c +
                                        *(int *)(param_2 + 0xb0) * 4) + 6);
                local_280 = *(undefined4 *)
                             (*(int *)(*(int *)PTR_DAT_004c98f4 + 0x295c +
                                      *(int *)(param_2 + 0xb0) * 4) + 0x24);
                local_275 = *(undefined2 *)
                             (*(int *)(*(int *)PTR_DAT_004c98f4 + 0x295c +
                                      *(int *)(param_2 + 0xb0) * 4) + 0x28);
              }
              else {
                local_38 = 0x3409;
                uStack_36 = 0x2a;
                FUN_0001423c("ParkCase",*(undefined4 *)(param_2 + 4));
                if ((bool)uVar23) {
                  iVar15 = 1;
                  do {
                    if ((*(int *)(*(int *)(*(int *)PTR_DAT_004c8b38 + 0xf8 + iVar15 * 4) + 0xb0) ==
                         param_1[0x2c]) &&
                       (*(int *)(*(int *)(*(int *)PTR_DAT_004c8b38 + 0xf8 + iVar15 * 4) + 0xdc) != 0
                       )) {
                      local_28d._1_2_ =
                           *(short *)(*(int *)(*(int *)PTR_DAT_004c8b38 + 0xf8 + iVar15 * 4) + 0xdc)
                      ;
                      local_280 = *(undefined4 *)
                                   (*(int *)(*(int *)PTR_DAT_004c8b38 + 0xf8 + iVar15 * 4) + 0xe0);
                      local_275 = *(undefined2 *)
                                   (*(int *)(*(int *)PTR_DAT_004c8b38 + 0xf8 + iVar15 * 4) + 0xe4);
                    }
                    iVar15 = iVar15 + 1;
                  } while (iVar15 != 5);
                }
                else {
                  local_38 = 0x34bb;
                  uStack_36 = 0x2a;
                  FUN_0001423c(*(undefined4 *)(param_2 + 4),"FixTrafficSpace");
                  if ((bool)uVar23) {
                    if (*(int *)(*(int *)(*(int *)PTR_DAT_004c943c + 0xf4) + 0xdc) != 0) {
                      local_28d._1_2_ = *(short *)(*(int *)(*(int *)PTR_DAT_004c943c + 0xf4) + 0xdc)
                      ;
                      local_280 = *(undefined4 *)(*(int *)(*(int *)PTR_DAT_004c943c + 0xf4) + 0xe0);
                      local_275 = *(undefined2 *)(*(int *)(*(int *)PTR_DAT_004c943c + 0xf4) + 0xe4);
                    }
                  }
                  else {
                    local_38 = 0x353b;
                    uStack_36 = 0x2a;
                    FUN_0001423c(*(undefined4 *)(param_2 + 4),"TradeLeftItem");
                    if ((bool)uVar23) {
                      local_28d._1_2_ =
                           *(short *)(*(int *)(*(int *)PTR_DAT_004c93d0 + 0x1d0 +
                                              *(int *)(param_2 + 0xb0) * 4) + 0xdc);
                      local_280 = *(undefined4 *)
                                   (*(int *)(*(int *)PTR_DAT_004c93d0 + 0x1d0 +
                                            *(int *)(param_2 + 0xb0) * 4) + 0xe0);
                      local_275 = *(undefined2 *)
                                   (*(int *)(*(int *)PTR_DAT_004c93d0 + 0x1d0 +
                                            *(int *)(param_2 + 0xb0) * 4) + 0xe4);
                    }
                    else {
                      local_38 = 0x35c2;
                      uStack_36 = 0x2a;
                      FUN_0001423c(*(undefined4 *)(param_2 + 4),"OtherSafeTradeItem");
                      if ((bool)uVar23) {
                        local_28d._1_2_ =
                             *(short *)(*(int *)(*(int *)PTR_DAT_004c8f1c + 0x1c0 +
                                                *(int *)(param_2 + 0xb0) * 4) + 0xdc);
                        local_280 = *(undefined4 *)
                                     (*(int *)(*(int *)PTR_DAT_004c8f1c + 0x1c0 +
                                              *(int *)(param_2 + 0xb0) * 4) + 0xe0);
                        local_275 = *(undefined2 *)
                                     (*(int *)(*(int *)PTR_DAT_004c8f1c + 0x1c0 +
                                              *(int *)(param_2 + 0xb0) * 4) + 0xe4);
                      }
                      else {
                        local_38 = 0x3649;
                        uStack_36 = 0x2a;
                        FUN_0001423c(*(undefined4 *)(param_2 + 4),"MySafeTradeItem");
                        if ((bool)uVar23) {
                          local_28d._1_2_ =
                               *(short *)(*(int *)(*(int *)PTR_DAT_004c8f1c + 0x3dc +
                                                  *(int *)(param_2 + 0xb0) * 4) + 0xdc);
                          local_280 = *(undefined4 *)
                                       (*(int *)(*(int *)PTR_DAT_004c8f1c + 0x3dc +
                                                *(int *)(param_2 + 0xb0) * 4) + 0xe0);
                          local_275 = *(undefined2 *)
                                       (*(int *)(*(int *)PTR_DAT_004c8f1c + 0x3dc +
                                                *(int *)(param_2 + 0xb0) * 4) + 0xe4);
                        }
                        else {
                          local_38 = 0x36d0;
                          uStack_36 = 0x2a;
                          FUN_0001423c(*(undefined4 *)(param_2 + 4),"VenderItemImage");
                          if ((bool)uVar23) {
                            local_28d._1_2_ =
                                 *(short *)(*(int *)(*(int *)PTR_DAT_004c883c + 0x1cc +
                                                    *(int *)(param_2 + 0xb0) * 4) + 0xdc);
                            local_280 = *(undefined4 *)
                                         (*(int *)(*(int *)PTR_DAT_004c883c + 0x1cc +
                                                  *(int *)(param_2 + 0xb0) * 4) + 0xe0);
                            local_275 = *(undefined2 *)
                                         (*(int *)(*(int *)PTR_DAT_004c883c + 0x1cc +
                                                  *(int *)(param_2 + 0xb0) * 4) + 0xe4);
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    if (iVar12 == 0) {
      if (local_28d._1_2_ == 0) {
        uVar10 = *(undefined4 *)
                  (*(int *)(*(int *)PTR_DAT_004c98f4 + 0x27e8 + *(int *)(param_2 + 0xb0) * 4) + 0x20
                  );
        local_3c = (undefined2)uVar10;
        uStack_3a = (undefined2)((uint)uVar10 >> 0x10);
      }
      else {
        local_3c = (undefined2)local_280;
        uStack_3a = (undefined2)((uint)local_280 >> 0x10);
      }
    }
    else {
      local_3c = (undefined2)*(undefined4 *)(iVar12 + 0x20);
      uStack_3a = (undefined2)((uint)*(undefined4 *)(iVar12 + 0x20) >> 0x10);
    }
    local_38 = 0x37cb;
    uStack_36 = 0x2a;
    FUN_0001953c((local_237[0] + -100) - CONCAT22(uStack_3a,local_3c),local_330);
    local_38 = local_330._0_2_;
    uStack_36 = local_330._2_2_;
    local_3c = 0x4ac0;
    uStack_3a = 0x2a;
    uStack_40 = (char *)0x2a37ea;
    FUN_0001953c(local_237[0] + -100,&local_334);
    uStack_40 = local_334;
    local_44 = 0x2a37fd;
    FUN_000141ec(&stack0xffffffec,3);
    local_44 = 0x2a380e;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],unaff_EBX);
    uVar14 = extraout_var_16;
  }
  else {
    local_38 = 0x3826;
    uStack_36 = 0x2a;
    cVar5 = FUN_004350d0(*(undefined4 *)PTR_DAT_004c94d4,CONCAT22(extraout_var_15,local_24b));
    if (cVar5 == '\x03') {
      local_38 = 0x3842;
      uStack_36 = 0x2a;
      FUN_0001953c(*(undefined4 *)(*(int *)PTR_DAT_004c98f4 + 0x5770),local_338);
      local_38 = local_338._0_2_;
      uStack_36 = local_338._2_2_;
      local_3c = 0x4ac0;
      uStack_3a = 0x2a;
      uStack_40 = (char *)0x2a385d;
      FUN_0001953c(&LAB_001e8480,&local_33c);
      uStack_40 = local_33c;
      local_44 = 0x2a3870;
      FUN_000141ec(&stack0xffffffec,3);
      local_44 = 0x2a3881;
      (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],unaff_EBX);
      uVar14 = extraout_var_18;
    }
    else {
      local_38 = 0x3896;
      uStack_36 = 0x2a;
      cVar5 = FUN_004350d0(*(undefined4 *)PTR_DAT_004c94d4,CONCAT22(extraout_var_17,local_24b));
      uVar14 = extraout_var_19;
      if (cVar5 == '\x04') {
        local_38 = 0x38b2;
        uStack_36 = 0x2a;
        FUN_0001953c(*(undefined4 *)(*(int *)PTR_DAT_004c98f4 + 0x5774),local_340);
        local_38 = local_340._0_2_;
        uStack_36 = local_340._2_2_;
        local_3c = 0x4ac0;
        uStack_3a = 0x2a;
        uStack_40 = (char *)0x2a38cd;
        FUN_0001953c(&LAB_001e8480,&local_344);
        uStack_40 = local_344;
        local_44 = 0x2a38e0;
        FUN_000141ec(&stack0xffffffec,3);
        local_44 = 0x2a38f1;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],unaff_EBX);
        uVar14 = extraout_var_20;
      }
    }
  }
  if (local_80 != '\0') {
    local_38 = 0x3903;
    uStack_36 = 0x2a;
    FUN_00013eac(local_50);
    local_38 = 0x390b;
    uStack_36 = 0x2a;
    FUN_00013eac(&local_4c);
    local_5c = (*(double *)(param_2 + 0xf0) - *(double *)PTR_DAT_004c8b08) * 24.0;
    local_348 = (uint)local_b6;
    fVar24 = (float10)local_348 + (float10)local_5c;
    uStack_40 = SUB104(fVar24,0);
    local_3c = (undefined2)((unkuint10)fVar24 >> 0x20);
    uStack_3a = (undefined2)((unkuint10)fVar24 >> 0x30);
    local_38 = (undefined2)((unkuint10)fVar24 >> 0x40);
    local_44 = 0x2a3947;
    iVar12 = FUN_00034b68();
    uVar9 = iVar12 / 0x18;
    local_348 = (uint)local_b6;
    fVar24 = (float10)local_348 + (float10)local_5c;
    uStack_40 = SUB104(fVar24,0);
    local_3c = (undefined2)((unkuint10)fVar24 >> 0x20);
    uStack_3a = (undefined2)((unkuint10)fVar24 >> 0x30);
    local_38 = (undefined2)((unkuint10)fVar24 >> 0x40);
    local_44 = 0x2a3973;
    iVar12 = FUN_00034b68(local_348,iVar12 % 0x18);
    uVar13 = iVar12 % 0x18;
    if (0 < (int)uVar9) {
      local_348 = (uint)local_b6;
      local_34c = (uint)local_b6;
      if ((double)local_34c < (double)local_348 + local_5c) {
        uVar9 = local_b6 / 0x18;
        uVar13 = (uint)local_b6 % 0x18;
      }
      local_38 = 0x39e2;
      uStack_36 = 0x2a;
      FUN_0001953c(uVar9,&local_350);
      local_38 = 0x39f5;
      uStack_36 = 0x2a;
      FUN_00014178(local_50,local_350,&DAT_002a4c28);
    }
    if (0 < (int)uVar13) {
      local_38 = 0x3a06;
      uStack_36 = 0x2a;
      FUN_0001953c(uVar13,&local_354);
      local_38 = 0x3a19;
      uStack_36 = 0x2a;
      FUN_00014178(&local_4c,local_354,&DAT_002a4c34);
    }
    if (((int)uVar9 < 1) && ((int)uVar13 < 1)) {
      local_38 = 0x3a2e;
      uStack_36 = 0x2a;
      FUN_00013f44(&local_4c,"1 hour ");
    }
    local_38 = 0x4c54;
    uStack_36 = 0x2a;
    local_3c = local_50._0_2_;
    uStack_3a = local_50._2_2_;
    uStack_40 = local_4c;
    local_44 = 0x2a3a49;
    FUN_000141ec(&local_358,3);
    local_44 = 0x2a3a5d;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_358);
    uVar14 = extraout_var_21;
  }
  if (local_86[3] != '\0') {
    local_38 = 0x4ab0;
    uStack_36 = 0x2a;
    local_348 = (uint)*(ushort *)(*(int *)PTR_DAT_004c94d4 + 0x1ab + uVar8 * 0x1c3);
    local_34c = 0xfa - *(byte *)(param_2 + 0xe6);
    fVar24 = (float10)(int)local_34c / ((float10)250.0 / (float10)local_348);
    local_44 = SUB104(fVar24,0);
    uStack_40 = (char *)((unkuint10)fVar24 >> 0x20);
    local_3c = (undefined2)((unkuint10)fVar24 >> 0x40);
    uStack_48 = 0x2a3ac0;
    uVar10 = FUN_00034b38();
    local_3c = 0x3acb;
    uStack_3a = 0x2a;
    FUN_0001953c(uVar10,local_35c);
    local_3c = local_35c._0_2_;
    uStack_3a = local_35c._2_2_;
    uStack_40 = " ";
    local_44 = 0x2a3ae3;
    FUN_000141ec(&local_60,3);
    local_44 = 0x2a3af4;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_60);
    uVar14 = extraout_var_22;
  }
  if (local_7e != '\0') {
    local_38 = 0x3b14;
    uStack_36 = 0x2a;
    local_92 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,
                            CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xfe)));
    uVar14 = extraout_var_23;
    if (local_92 != 0) {
      if (*(char *)(param_2 + 0xf8) == '\0') {
        local_38 = 0x3bbe;
        uStack_36 = 0x2a;
        FUN_004309d4(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xfe),&local_370);
        local_38 = 0x3bd4;
        uStack_36 = 0x2a;
        FUN_00014178(&local_36c,&DAT_002a4c74,local_370);
        local_38 = 0x3be8;
        uStack_36 = 0x2a;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_36c);
      }
      else {
        local_38 = 0x4c74;
        uStack_36 = 0x2a;
        local_3c = 0x3b56;
        uStack_3a = 0x2a;
        FUN_004309d4(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xfe),local_364);
        local_3c = local_364._0_2_;
        uStack_3a = local_364._2_2_;
        uStack_40 = "+";
        local_44 = 0x2a3b76;
        FUN_0001953c(*(undefined1 *)(param_2 + 0xf8),&local_368);
        local_44 = local_368;
        uStack_48 = 0x2a3b8c;
        FUN_000141ec(&local_360,4);
        uStack_48 = 0x2a3ba0;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_360);
      }
      iVar12 = 1;
      do {
        iVar15 = *(int *)PTR_DAT_004c94d4;
        sVar7 = *(short *)(iVar15 + (uint)local_92 * 0x1c3 + 0x20 + iVar12 * 2);
        if ((((((ushort)(sVar7 - 0x19U) < 2) || ((ushort)(sVar7 - 0xcfU) < 2)) ||
             ((ushort)(sVar7 - 0xd2U) < 2)) || ((ushort)(sVar7 - 0xd6U) < 3)) &&
           (iVar15 = *(int *)PTR_DAT_004c94d4,
           100 < *(int *)(iVar15 + (uint)local_92 * 0x1c3 + 0x24 + iVar12 * 4))) {
          local_74 = local_74 + 1;
        }
        uVar14 = (undefined2)((uint)iVar15 >> 0x10);
        iVar12 = iVar12 + 1;
      } while (iVar12 != 3);
      if (local_74 == 1) {
        local_70 = (uint)*(byte *)(param_2 + 0xf8) * 2;
      }
      if (local_74 == 2) {
        local_70 = (uint)*(byte *)(param_2 + 0xf8);
      }
      if (*(char *)(param_2 + 0xf9) != '\0') {
        local_38 = 0x3c98;
        uStack_36 = 0x2a;
        local_90 = FUN_002a1ee8(CONCAT31(uVar11,*(undefined1 *)(param_2 + 0xf9)));
        local_8c = (uint)*(byte *)(param_2 + 0xf9) + (uint)(*(byte *)(param_2 + 0xf9) >> 4) * -0x10;
        local_38 = 0x3cda;
        uStack_36 = 0x2a;
        local_8c = FUN_002a1ee8(local_8c * 0x10);
        uVar14 = extraout_var_24;
      }
      uStack_40 = (char *)((uint)uStack_40 & 0xffffff);
      local_38 = 0x3cfa;
      uStack_36 = 0x2a;
      cVar5 = FUN_0043217c(*(undefined4 *)PTR_DAT_004c94d4,
                           CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xfe)));
      iVar12 = extraout_EDX;
      if ((cVar5 != '\0') && (*(short *)(param_2 + 0xea) != 0)) {
        local_38 = 0x3d29;
        uStack_36 = 0x2a;
        cVar5 = FUN_004359d8(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xea));
        iVar12 = extraout_EDX_00;
        if (cVar5 != '\0') {
          local_38 = 0x3d47;
          uStack_36 = 0x2a;
          uVar8 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xea));
          iVar12 = *(int *)PTR_DAT_004c94d4;
          if (*(char *)(iVar12 + 0x13 + (uVar8 & 0xffff) * 0x1c3) == '4') {
            iVar15 = 1;
            do {
              iVar12 = *(int *)PTR_DAT_004c94d4;
              if (((*(short *)(iVar12 + (uint)local_92 * 0x1c3 + 0x20 + iVar15 * 2) != 0) &&
                  (iVar12 = *(int *)PTR_DAT_004c94d4,
                  *(short *)(iVar12 + (uint)local_92 * 0x1c3 + 0x20 + iVar15 * 2) != 0xfa)) &&
                 (iVar12 = *(int *)PTR_DAT_004c94d4,
                 100 < *(int *)(iVar12 + (uint)local_92 * 0x1c3 + 0x24 + iVar15 * 4))) {
                uStack_40 = (char *)CONCAT13(uStack_40._3_1_ + '\x01',(undefined3)uStack_40);
              }
              iVar15 = iVar15 + 1;
            } while (iVar15 != 3);
            uVar14 = (undefined2)((uint)iVar12 >> 0x10);
            if (uStack_40._3_1_ == '\x01') {
              local_38 = 0x3df4;
              uStack_36 = 0x2a;
              uVar8 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,
                                   CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xea)));
              iVar12 = *(int *)PTR_DAT_004c94d4;
              uStack_40 = (char *)CONCAT13(*(char *)(iVar12 + 0x31 + (uVar8 & 0xffff) * 0x1c3) *
                                           '\x02',(undefined3)uStack_40);
            }
            else if (uStack_40._3_1_ == '\x02') {
              local_38 = 0x3e26;
              uStack_36 = 0x2a;
              uVar8 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,
                                   CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xea)));
              iVar12 = *(int *)PTR_DAT_004c94d4;
              uStack_40 = (char *)CONCAT13(*(undefined1 *)(iVar12 + 0x31 + (uVar8 & 0xffff) * 0x1c3)
                                           ,(undefined3)uStack_40);
            }
            else {
              uStack_40 = (char *)((uint)uStack_40 & 0xffffff);
            }
            if (uStack_48._3_1_ != '\0') {
              iVar12 = *(int *)PTR_DAT_004c94d4;
              if (*(char *)(iVar12 + 0x85 + (uint)local_92 * 0x1c3) == '\0') {
                iVar12 = *(int *)PTR_DAT_004c94d4;
                if (((*(char *)(iVar12 + 0x33 + (uint)local_92 * 0x1c3) == -0x72) &&
                    ((byte)(*(char *)(*(int *)PTR_DAT_004c98f4 + 0x1f9c) - 1U) < 6)) &&
                   (iVar12 = *(int *)PTR_DAT_004c94d4,
                   *(char *)(iVar12 + 0x32 + (uint)local_92 * 0x1c3) == '\x06')) {
                  local_38 = 0x3ed8;
                  uStack_36 = 0x2a;
                  cVar5 = FUN_0049eaa8(local_44,*(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x1f9c));
                  iVar12 = extraout_EDX_01;
                  if (cVar5 != '\0') {
                    uStack_40 = (char *)CONCAT13(uStack_40._3_1_ * '\x02',(undefined3)uStack_40);
                  }
                }
              }
              else {
                uStack_40 = (char *)CONCAT13(uStack_40._3_1_ * '\x02',(undefined3)uStack_40);
              }
            }
          }
        }
      }
      iVar15 = 1;
      local_98 = &local_90;
      puVar18 = local_23d;
      do {
        iVar21 = (uint)local_92 * 0x1c3;
        uVar1 = *(ushort *)(*(int *)PTR_DAT_004c94d4 + iVar21 + 0x20 + iVar15 * 2);
        if (uVar1 < 0xd1) {
          if (uVar1 == 0xd0) {
            local_38 = 0x3fd8;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,"MaxSp");
            iVar12 = extraout_EDX_05;
          }
          else if (uVar1 < 0x41) {
            if (uVar1 == 0x40) {
              local_38 = 0x4035;
              uStack_36 = 0x2a;
              FUN_00013f44(&stack0xffffffec,"Amity");
              iVar12 = extraout_EDX_11;
            }
            else if (uVar1 == 0x19) {
              local_38 = 0x3fa2;
              uStack_36 = 0x2a;
              FUN_00013f44(&stack0xffffffec,&DAT_002a48dc);
              iVar12 = extraout_EDX_02;
            }
            else if (uVar1 == 0x1a) {
              local_38 = 0x3fb4;
              uStack_36 = 0x2a;
              FUN_00013f44(&stack0xffffffec,&DAT_002a48e8);
              iVar12 = extraout_EDX_03;
            }
            else {
              if (uVar1 != 0x24) goto LAB_002a4055;
              local_38 = 0x4044;
              uStack_36 = 0x2a;
              FUN_00013f44(&stack0xffffffec,&DAT_002a4968);
              iVar12 = extraout_EDX_12;
            }
          }
          else if (uVar1 == 100) {
            local_38 = 0x4053;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,"Shoot RES");
            iVar12 = extraout_EDX_13;
          }
          else {
            if (uVar1 != 0xcf) goto LAB_002a4055;
            local_38 = 0x3fc6;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,"MaxHp");
            iVar12 = extraout_EDX_04;
          }
LAB_002a405d:
          if (unaff_EBX != 0) {
            local_38 = 0x4070;
            uStack_36 = 0x2a;
            FUN_00014134(&stack0xffffffec,&DAT_002a498c);
            iVar12 = extraout_EDX_15;
          }
          if ((*(int *)(*(int *)PTR_DAT_004c94d4 + iVar21 + 0x24 + iVar15 * 4) != 0) &&
             (iVar12 = *(int *)PTR_DAT_004c94d4,
             *(int *)(iVar12 + (uint)local_92 * 0x1c3 + 0x24 + iVar15 * 4) != 100)) {
            if (*(int *)(*(int *)PTR_DAT_004c94d4 + (uint)local_92 * 0x1c3 + 0x24 + iVar15 * 4) +
                -100 + *local_98 < 1) {
              if (*(int *)(*(int *)PTR_DAT_004c94d4 + (uint)local_92 * 0x1c3 + 0x24 + iVar15 * 4) +
                  -100 + *local_98 < 0) {
                local_38 = 0x4181;
                uStack_36 = 0x2a;
                FUN_0001953c(*(int *)(*(int *)PTR_DAT_004c94d4 + (uint)local_92 * 0x1c3 + 0x24 +
                                     iVar15 * 4) + -100 + *local_98,&local_378);
                local_38 = 0x418f;
                uStack_36 = 0x2a;
                FUN_00014134(&stack0xffffffec,local_378);
              }
              else {
                local_3c = 0x48a8;
                uStack_3a = 0x2a;
                uStack_40 = (char *)0x2a41a6;
                local_38 = uVar2;
                uStack_36 = uVar3;
                FUN_0001953c(0,&local_37c);
                uStack_40 = local_37c;
                local_44 = 0x2a41b9;
                FUN_000141ec(&stack0xffffffec,3);
              }
            }
            else {
              local_3c = 0x48a8;
              uStack_3a = 0x2a;
              uStack_40 = (char *)0x2a410c;
              local_38 = uVar2;
              uStack_36 = uVar3;
              FUN_0001953c(*(int *)(*(int *)PTR_DAT_004c94d4 + (uint)local_92 * 0x1c3 + 0x24 +
                                   iVar15 * 4) + -100 + *local_98,&local_374);
              uStack_40 = local_374;
              local_44 = 0x2a411f;
              FUN_000141ec(&stack0xffffffec,3);
            }
            if ((local_22c == 'q') && (*puVar18 == 0x24)) {
              local_38 = 0x41dd;
              uStack_36 = 0x2a;
              FUN_00014134(&stack0xffffffec,&DAT_002a4998);
              local_38 = 0x41ff;
              uStack_36 = 0x2a;
              uVar10 = FUN_0049ed34(*(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x1f98),
                                    *(undefined1 *)(*(int *)PTR_DAT_004c98f4 + 0x1f99));
              local_38 = (undefined2)uVar10;
              uStack_36 = (undefined2)((uint)uVar10 >> 0x10);
              local_3c = 0x420f;
              uStack_3a = 0x2a;
              iVar12 = FUN_0049ed34(0xa2,1);
              if (iVar12 <= CONCAT22(uStack_36,local_38)) {
                local_78 = ((*(int *)(*(int *)PTR_DAT_004c94d4 + iVar21 + 0x24 + iVar15 * 4) + -100)
                           * 20000000) / 1000000;
                local_38 = 0x49a4;
                uStack_36 = 0x2a;
                local_3c = 0x4256;
                uStack_3a = 0x2a;
                FUN_0001953c(local_78,local_380);
                local_3c = local_380._0_2_;
                uStack_3a = local_380._2_2_;
                uStack_40 = &DAT_002a49c0;
                local_44 = 0x2a426e;
                FUN_000141ec(&local_7c,3);
              }
            }
            if ((local_22c == 'w') &&
               (*(short *)(*(int *)PTR_DAT_004c94d4 + iVar21 + 0x20 + iVar15 * 2) == 100)) {
              local_38 = 0x4295;
              uStack_36 = 0x2a;
              FUN_00014134(&stack0xffffffec,&DAT_002a4998);
            }
            local_38 = 0x429d;
            uStack_36 = 0x2a;
            FUN_00013eac(&local_68);
            if ((0 < (int)local_70) &&
               (iVar12 = *(int *)(*(int *)PTR_DAT_004c94d4 + iVar21 + 0x24 + iVar15 * 4),
               iVar12 != 100 && -1 < iVar12 + -100)) {
              local_38 = 0x42c5;
              uStack_36 = 0x2a;
              FUN_0001953c(local_70,&local_384);
              local_38 = 0x42d8;
              uStack_36 = 0x2a;
              FUN_00014178(&local_68,&DAT_002a48a8,local_384);
            }
            local_38 = 0x42e0;
            uStack_36 = 0x2a;
            FUN_00013eac(&local_6c);
            if ((uStack_40._3_1_ != '\0') &&
               (iVar12 = *(int *)(*(int *)PTR_DAT_004c94d4 + iVar21 + 0x24 + iVar15 * 4),
               iVar12 != 100 && -1 < iVar12 + -100)) {
              local_38 = 0x430a;
              uStack_36 = 0x2a;
              FUN_0001953c(uStack_40._3_1_,&local_388);
              local_38 = 0x431d;
              uStack_36 = 0x2a;
              FUN_00014178(&local_6c,&DAT_002a48a8,local_388);
            }
            local_3c = 0x49cc;
            uStack_3a = 0x2a;
            uStack_40 = local_6c;
            local_44 = local_68;
            uStack_48 = 0x2a4338;
            local_38 = uVar2;
            uStack_36 = uVar3;
            FUN_000141ec(&stack0xffffffec,4);
            uStack_48 = 0x2a4349;
            (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],unaff_EBX);
            iVar12 = extraout_EDX_16;
          }
        }
        else {
          if (uVar1 < 0xd8) {
            if (uVar1 == 0xd7) {
              local_38 = 0x4008;
              uStack_36 = 0x2a;
              FUN_00013f44(&stack0xffffffec,&DAT_002a492c);
              iVar12 = extraout_EDX_08;
            }
            else if (uVar1 == 0xd2) {
              local_38 = 0x3fea;
              uStack_36 = 0x2a;
              FUN_00013f44(&stack0xffffffec,&DAT_002a4914);
              iVar12 = extraout_EDX_06;
            }
            else if (uVar1 == 0xd3) {
              local_38 = 0x3ff9;
              uStack_36 = 0x2a;
              FUN_00013f44(&stack0xffffffec,&DAT_002a4920);
              iVar12 = extraout_EDX_07;
            }
            else {
              if (uVar1 != 0xd6) goto LAB_002a4055;
              local_38 = 0x4026;
              uStack_36 = 0x2a;
              FUN_00013f44(&stack0xffffffec,&DAT_002a494c);
              iVar12 = extraout_EDX_10;
            }
            goto LAB_002a405d;
          }
          if (uVar1 == 0xd8) {
            local_38 = 0x4017;
            uStack_36 = 0x2a;
            FUN_00013f44(&stack0xffffffec,&DAT_002a493c);
            iVar12 = extraout_EDX_09;
            goto LAB_002a405d;
          }
          if (uVar1 != 0xfa) {
LAB_002a4055:
            local_38 = 0x405d;
            uStack_36 = 0x2a;
            FUN_00013eac(&stack0xffffffec);
            iVar12 = extraout_EDX_14;
            goto LAB_002a405d;
          }
        }
        uVar14 = (undefined2)((uint)iVar12 >> 0x10);
        iVar15 = iVar15 + 1;
        puVar18 = puVar18 + 1;
        local_98 = local_98 + 1;
      } while (iVar15 != 3);
    }
  }
  param_1[0x4e] = -1;
  param_1[0x50] = -1;
  if (local_82 != '\0') {
    local_38 = 0x438f;
    uStack_36 = 0x2a;
    iVar12 = (**(code **)(*(int *)param_1[0x4c] + 0x14))();
    param_1[0x4e] = iVar12;
    uVar8 = (uint)*(byte *)(param_2 + 0xe6);
    if (uVar8 < 0x65) {
      if (uVar8 == 0) {
        param_1[0x50] = 0xffe0;
        local_38 = 0x43fb;
        uStack_36 = 0x2a;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],&DAT_002a4c84);
        uVar14 = extraout_var_25;
      }
      else {
        if (uVar8 - 1 < 99) goto LAB_002a4400;
        if (uVar8 - 1 == 99) {
          local_38 = 0x4474;
          uStack_36 = 0x2a;
          cVar5 = FUN_0043ad4c(*(undefined4 *)PTR_DAT_004c8d88,local_24b);
          if (cVar5 == '\0') {
            local_38 = 0x44b0;
            uStack_36 = 0x2a;
            cVar5 = FUN_0043ad50(*(undefined4 *)PTR_DAT_004c8d88,local_24b);
            if (cVar5 == '\0') {
              param_1[0x50] = 0xffe0;
              local_38 = 0x44f9;
              uStack_36 = 0x2a;
              (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],&DAT_002a4c84);
              uVar14 = extraout_var_30;
            }
            else {
              param_1[0x50] = 0xffe0;
              local_38 = 0x44d4;
              uStack_36 = 0x2a;
              (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],"Usable");
              uVar14 = extraout_var_29;
            }
          }
          else {
            param_1[0x50] = 0xffe0;
            local_38 = 0x4498;
            uStack_36 = 0x2a;
            (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],"Usable");
            uVar14 = extraout_var_28;
          }
        }
        else {
LAB_002a453f:
          param_1[0x50] = 0xf800;
          local_38 = 0x455f;
          uStack_36 = 0x2a;
          (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],"Broken");
          uVar14 = extraout_var_33;
        }
      }
    }
    else if (uVar8 - 0x65 < 0x31) {
LAB_002a4400:
      local_38 = 0x4413;
      uStack_36 = 0x2a;
      cVar5 = FUN_0043ad50(*(undefined4 *)PTR_DAT_004c8d88,local_24b);
      if (cVar5 == '\0') {
        param_1[0x50] = 0xffe0;
        local_38 = 0x445c;
        uStack_36 = 0x2a;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],&DAT_002a4c84);
        uVar14 = extraout_var_27;
      }
      else {
        param_1[0x50] = 0xffe0;
        local_38 = 0x4437;
        uStack_36 = 0x2a;
        (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],"Usable");
        uVar14 = extraout_var_26;
      }
    }
    else if (uVar8 - 0x96 < 0x32) {
      param_1[0x50] = 0xffe0;
      local_38 = 0x451b;
      uStack_36 = 0x2a;
      (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],&DAT_002a4ca4);
      uVar14 = extraout_var_31;
    }
    else {
      if (0x31 < uVar8 - 200) goto LAB_002a453f;
      param_1[0x50] = 0xf800;
      local_38 = 0x453d;
      uStack_36 = 0x2a;
      (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],"Wearing");
      uVar14 = extraout_var_32;
    }
  }
  if ((local_81 != '\0') && (*(short *)(param_2 + 0xea) != 0)) {
    local_38 = 0x4588;
    uStack_36 = 0x2a;
    cVar5 = FUN_004359d8(*(undefined4 *)PTR_DAT_004c94d4,
                         CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xea)));
    uVar14 = extraout_var_34;
    if (cVar5 != '\0') {
      local_38 = 0x45a8;
      uStack_36 = 0x2a;
      FUN_004309d4(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xea),&local_390);
      local_38 = 0x45be;
      uStack_36 = 0x2a;
      FUN_00014178(&local_38c,&DAT_002a4cd4,local_390);
      local_38 = 0x45d2;
      uStack_36 = 0x2a;
      (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_38c);
      uVar14 = extraout_var_35;
    }
  }
  if (local_7f != '\0') {
    local_38 = 0x45ee;
    uStack_36 = 0x2a;
    sVar7 = FUN_00430694(*(undefined4 *)PTR_DAT_004c94d4,
                         CONCAT22(uVar14,*(undefined2 *)(param_2 + 0xfa)));
    if (sVar7 != 0) {
      local_38 = 0x460f;
      uStack_36 = 0x2a;
      FUN_004309d4(*(undefined4 *)PTR_DAT_004c94d4,*(undefined2 *)(param_2 + 0xfa),&local_398);
      local_38 = 0x4625;
      uStack_36 = 0x2a;
      FUN_00014178(&local_394,"Model: ",local_398);
      local_38 = 0x4639;
      uStack_36 = 0x2a;
      (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_394);
    }
  }
  bVar6 = 0;
  if (local_7d != '\0') {
    local_38 = 0x4652;
    uStack_36 = 0x2a;
    FUN_000140d0(&local_39c,local_1c9);
    local_38 = 0x4660;
    uStack_36 = 0x2a;
    FUN_00014134(&local_39c,local_7c);
    local_38 = 0x466b;
    uStack_36 = 0x2a;
    bVar6 = FUN_0001412c(local_39c);
    local_38 = 0x467e;
    uStack_36 = 0x2a;
    FUN_000140d0(&local_3a0,local_1c9);
    local_38 = 0x468c;
    uStack_36 = 0x2a;
    FUN_00014134(&local_3a0,local_7c);
    local_38 = 0x46a0;
    uStack_36 = 0x2a;
    (**(code **)(*(int *)param_1[0x4c] + 0x34))((int *)param_1[0x4c],local_3a0);
  }
  local_38 = 0x46c6;
  uStack_36 = 0x2a;
  iVar12 = (**(code **)(*(int *)param_1[0x4c] + 0x14))();
  param_1[9] = (int)(((ulonglong)bVar6 << 3) / 0x82) * 0x14 + iVar12 * 0x14 + 0x14;
  param_1[8] = 0xc4;
  local_38 = 0x46ed;
  uStack_36 = 0x2a;
  FUN_00020ca8(0,0,&local_34);
  local_34 = (undefined *)(*(int *)(param_2 + 0x38) + 2);
  local_38 = 0x4707;
  uStack_36 = 0x2a;
  FUN_00480158(param_2,&local_3a8);
  param_1[6] = (int)(local_34 + local_3a8);
  local_38 = 0x471e;
  uStack_36 = 0x2a;
  iVar12 = FUN_004801ac(param_1);
  if (800 < iVar12) {
    local_38 = 0x4733;
    uStack_36 = 0x2a;
    FUN_00480158(param_2,&local_3a8);
    param_1[6] = (local_3a8 - param_1[8]) + -2;
  }
  local_38 = 0x4756;
  uStack_36 = 0x2a;
  FUN_00480158(param_2,&local_3a8);
  param_1[7] = local_3a4 + local_30;
  local_38 = 0x476d;
  uStack_36 = 0x2a;
  iVar12 = FUN_00480110(param_1);
  if (600 < iVar12) {
    param_1[7] = 600 - param_1[9];
  }
  local_38 = 0x478d;
  uStack_36 = 0x2a;
  (**(code **)(*param_1 + 0x20))();
  FUN_00480158(param_2,&local_3a8);
  puStack_20 = (undefined1 *)0x20;
  uStack_28 = CONCAT31(uVar11,*(undefined1 *)(param_2 + 0x135));
  uStack_2c = 0x2a47d1;
  piStack_24 = param_1;
  FUN_001c5cb0(*(undefined4 *)PTR_DAT_004c8630,
               CONCAT22(extraout_var_36,*(undefined2 *)(param_2 + 0xdc)),
               *(undefined1 *)(param_2 + 0xd8));
  puVar4 = puStack_20;
LAB_002a47d1:
  puStack_20 = puVar4;
  puVar4 = puStack_20;
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_002a4845;
  piStack_24 = (int *)0x2a47ee;
  FUN_00013ed0(&local_3a0,0x15,puVar4);
  piStack_24 = (int *)0x2a47fe;
  FUN_00013ed0(&local_344,0x24);
  piStack_24 = (int *)0x2a480e;
  FUN_00013ed0(&local_2a0,4);
  piStack_24 = (int *)0x2a4816;
  FUN_00013eac(&local_7c);
  piStack_24 = (int *)0x2a4823;
  FUN_00013ed0(&local_6c,4);
  piStack_24 = (int *)0x2a4830;
  FUN_00013ed0(local_50,2);
  piStack_24 = (int *)0x2a483d;
  FUN_00013ed0(&stack0xffffffe4,3);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0033ace0
 * @başlık         Simya ve Eşya Sentezleme Paketleyicisi (Item Mix / Alchemy Compound)
 * @açıklama       Simya kutusuna konulan eşyaların birleştirilmesi (mix) işlemini doğrular ve sunucuya gönderir.
 * @ofsetler       Eşyanın envanter slotu (+0x165) ve sentezlenecek slot adedi (+0x15c) okunur.
 * @paketler       Eşya Sentezleme Paketi (Opcode 23 Sub-opcode 33 / 0x21).
 * 
 * @detaylı_analiz 
 * * 1. Oyuncunun simya seviyesinin (Alchemy Level) yeterliliği sorgulanır.
 *  * 2. Sentezlenecek slot ve eşya adedi (+0x15c) paket tamponuna yazılır.
 *  * 3. Sunucuya Opcode 23 Sub-opcode 33 (0x21) paketi yollanır.
 *******************************************************************************/
void FUN_0033ace0(int param_1,undefined1 param_2)

{
  char cVar1;
  int iVar2;
  undefined2 extraout_var;
  
  iVar2 = FUN_003cd528(*(undefined4 *)PTR_DAT_004c98f4,0x28);
  if (iVar2 < 0x19) {
    (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
              (*(int **)PTR_DAT_004c8d24,&DAT_0033add0,2000,0,0);
    return;
  }
  if (*(char *)(*(int *)PTR_DAT_004c8878 + 4) != '\0') {
    (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
              (*(int **)PTR_DAT_004c8d24,&DAT_0033adec,0x4b0,0,0);
    return;
  }
  cVar1 = FUN_0043bba8(*(undefined4 *)PTR_DAT_004c8d88,
                       CONCAT22(extraout_var,
                                *(undefined2 *)
                                 (param_1 + 0x165 + (uint)*(byte *)(param_1 + 0x15c) * 0x27)));
  if (cVar1 == '\0') {
    (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
              (*(int **)PTR_DAT_004c8d24,&DAT_0033ae04,0x4b0,0,0);
    return;
  }
  *(undefined1 *)(param_1 + 0x134) = param_2;
  FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0x17,0x21,0);
  if (*(char *)(param_1 + 0x164 + (uint)*(byte *)(param_1 + 0x15c) * 0x27) == '\x1a') {
    *(undefined1 *)(param_1 + 0x15c) = 1;
  }
  return;
}

