/**
 * network_packet.c - WLO İstemci Ağ Soketi Sarmalayıcıları, Girdi/Çıktı (IO) ve Paket İletişim Fonksiyonları.
 * Extracted from aLogin.exe decompiled C code.
 */

/*******************************************************************************
 * @fonksiyon      FUN_000799c8
 * @başlık         Soket Bağlantısı (Socket Connect)
 * @açıklama       Asenkron soket modunu ve Winsock connect() API'sini tetikler.
 * @ofsetler       Soket tanımlayıcısı (socket descriptor) parametre olarak alınır. fcntl veya ioctlsocket ile asenkron mod setlenir.
 * @paketler       Düşük seviyeli TCP/IP soket bağlantısı.
 * 
 * @detaylı_analiz 
 * * 1. Parametre: Soket referansı.
 *  * 2. Bağlantı denemesi asenkron olarak başlatılır.
 *  * 3. Hata durumunda WSAGetLastError() kontrol edilir.
 *******************************************************************************/
void FUN_000799c8(int param_1)

{
  int iVar1;
  
  FUN_000798ec(param_1);
  FUN_00013320(param_1,param_1,1);
  iVar1 = connect(*(SOCKET *)(param_1 + 4),(sockaddr *)(param_1 + 0x18),0x10);
  FUN_0007920c(iVar1,"connect");
  *(undefined1 *)(param_1 + 0x29) = 0;
  if ((*(byte *)(param_1 + 0x28) & 0x10) == 0) {
    *(bool *)(param_1 + 8) = *(int *)(param_1 + 4) != -1;
    FUN_00013320(param_1,param_1,2);
  }
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0007a284
 * @başlık         Soket Okuma Sarmalayıcısı (Socket Recv Wrapper)
 * @açıklama       Soket üzerindeki tampon belleği (buffer) okumak için recv() tetikler.
 * @ofsetler       param_1 soket referansıdır. Okunan ham bayt dizisi buffer'a yazılır.
 * @paketler       Gelen tüm paketlerin ham okuma işlemi.
 * 
 * @detaylı_analiz 
 * * 1. Soket referansından recv() fonksiyonu çağrılır.
 *  * 2. Gelen verinin uzunluğu doğrulanır.
 *  * 3. Tampon verisi paket ayrıştırıcıya (dispatcher) gönderilir.
 *******************************************************************************/
void FUN_0007a284(int *param_1,char *param_2,int param_3)

{
  undefined1 *puVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_4c;
  undefined1 *puStack_48;
  undefined1 *puStack_44;
  undefined4 uStack_40;
  undefined1 *puStack_3c;
  undefined1 *puStack_38;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  int local_20;
  undefined1 local_1c;
  undefined1 *local_18;
  undefined1 local_14;
  int local_10;
  u_long local_c;
  int *local_8;
  
  puStack_38 = &stack0xfffffffc;
  local_2c = 0;
  puStack_3c = &LAB_0007a3ce;
  uStack_40 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_40;
  puStack_44 = (undefined1 *)0x7a2ae;
  local_8 = param_1;
  FUN_00079784(param_1);
  puStack_48 = &LAB_0007a3b1;
  uStack_4c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_4c;
  local_c = 0;
  if ((param_3 == -1) && ((char)local_8[2] != '\0')) {
    puStack_44 = &stack0xfffffffc;
    ioctlsocket(local_8[1],0x4004667f,&local_c);
  }
  else {
    if ((char)local_8[2] == '\0') {
      puStack_44 = &stack0xfffffffc;
      FUN_0001397c();
      puVar1 = puStack_38;
      *in_FS_OFFSET = uStack_40;
      puStack_38 = &LAB_0007a3d5;
      puStack_3c = (undefined1 *)0x7a3cd;
      FUN_00013eac(&local_2c,uStack_40,puVar1);
      return;
    }
    puStack_44 = &stack0xfffffffc;
    local_c = recv(local_8[1],param_2,param_3,0);
    if (local_c == 0xffffffff) {
      local_10 = WSAGetLastError();
      if (local_10 != 0x2733) {
        FUN_00013320(local_8,local_8,2,&local_10);
        (**(code **)(*local_8 + 8))(local_8,local_8[1]);
        if (local_10 != 0) {
          FUN_0001bb34(local_10,&local_2c);
          local_28 = local_2c;
          local_24 = 0xb;
          local_20 = local_10;
          local_1c = 0;
          local_18 = &LAB_0007a3e8;
          local_14 = 0xb;
          FUN_0001c478(&DAT_00078bcc,1,PTR_PTR_004c94bc,2,&local_28);
          FUN_000138dc();
        }
      }
    }
  }
  puVar1 = puStack_44;
  *in_FS_OFFSET = uStack_4c;
  puStack_44 = (undefined1 *)0x7a3b8;
  puStack_48 = (undefined1 *)0x7a3b0;
  FUN_00079790(local_8,uStack_4c,puVar1);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0012479c
 * @başlık         Soket Yazma Sarmalayıcısı 1 (Socket Send Wrapper 1)
 * @açıklama       Soket üzerinden sunucuya ham veri yollamak için send() tetikler.
 * @ofsetler       param_1 soket referansı, param_2 veri tamponu, param_3 yollanacak boyut.
 * @paketler       Giden tüm paketlerin alt seviye iletimi.
 * 
 * @detaylı_analiz 
 * * 1. send() API sarmalanarak çağrılır.
 *  * 2. Gönderilen bayt miktarı doğrulanır.
 *******************************************************************************/
void FUN_0012479c(int param_1,int param_2,uint param_3)

{
  undefined1 *puVar1;
  int iVar2;
  uint len;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  undefined1 *puStack_2c;
  undefined1 *puStack_28;
  undefined4 uStack_24;
  undefined1 *puStack_20;
  undefined1 *puStack_1c;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_10 = 0;
  puStack_20 = &LAB_001248d8;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  puStack_28 = (undefined1 *)0x1247ce;
  local_c = param_2;
  local_8 = param_1;
  FUN_00125e88(param_1,4,"Sending Buffer");
  puStack_28 = (undefined1 *)0x1247d6;
  FUN_00125718(local_8);
  puStack_2c = &LAB_001248bb;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  puStack_28 = &stack0xfffffffc;
  if (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] == 0) {
    puStack_28 = &stack0xfffffffc;
    if ((short)param_3 == 0) {
      puStack_28 = &stack0xfffffffc;
      param_3 = FUN_00019bc0(local_c);
      if (0xffff < param_3) {
        thunk_FUN_00012820();
      }
    }
    len = param_3 & 0xffff;
    while( true ) {
      iVar2 = send((uint)*(ushort *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x18),
                   (char *)(local_c + ((param_3 & 0xffff) - len)),len,0);
      if (iVar2 == 0) break;
      if (iVar2 < 0) {
        FUN_00125dbc(local_8,0x2733,&local_10);
      }
      else {
        len = len - iVar2;
      }
      if ((len == 0) || (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] != 0)) break;
    }
  }
  if (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] != 0) {
    IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] = 0;
    FUN_0001c380(&DAT_00123dd0,1,"Socket send aborted");
    FUN_000138dc();
    if (*(short *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x12) != 0) {
      (**(code **)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x10))
                (*(undefined4 *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x14),local_8);
    }
  }
  puVar1 = puStack_28;
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_001248c2;
  puStack_2c = (undefined1 *)0x1248ba;
  FUN_00125770(local_8,uStack_30,puVar1);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_00296660
 * @başlık         Soket Yazma Sarmalayıcısı 2 (Socket Send Wrapper 2)
 * @açıklama       İkincil paket kuyruğu ve soket gönderim yöneticisidir.
 * @ofsetler       param_1 soket referansı, param_2 veri yapısıdır.
 * @paketler       Giden paket tamponlama işlemleri.
 * 
 * @detaylı_analiz 
 * * 1. Giden veri paket kuyruğuna (queue) yazılır.
 *  * 2. Soket yazmaya hazır olduğunda send() çağrılır.
 *******************************************************************************/
void FUN_00296660(int *param_1,char param_2)

{
  int *piVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined2 extraout_var_04;
  undefined2 extraout_var_05;
  undefined4 *in_FS_OFFSET;
  float10 in_ST0;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 local_1b0;
  undefined4 local_1ac;
  DWORD local_1a8;
  undefined4 uStack_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  int local_18c;
  undefined4 local_188;
  int local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined *puStack_ac;
  int iStack_a8;
  char *pcStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  int iStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  int iStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  int iStack_3c;
  undefined4 uStack_38;
  undefined1 *puStack_34;
  undefined1 *puStack_30;
  int *local_28;
  int *local_24;
  int *local_20;
  
  iVar7 = 0x35;
  do {
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  if (param_2 != '\0') {
    puStack_30 = (undefined1 *)0x29667f;
    param_1 = (int *)FUN_00013484();
  }
  puStack_34 = &LAB_002982e2;
  uStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_38;
  iStack_3c = 0x29669b;
  puStack_30 = &stack0xfffffffc;
  FUN_0048e788(param_1,0);
  iStack_3c = 0x2966ac;
  iVar7 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"Num_Vip_3");
  param_1[0x162] = iVar7;
  iStack_3c = 0x2966c3;
  iVar7 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"Num_SVip_3");
  param_1[0x163] = iVar7;
  iStack_3c = 0x2966da;
  iVar7 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"Num_VVip_3");
  param_1[0x164] = iVar7;
  param_1[0x15e] = -1;
  iStack_3c = 0x2966fb;
  iVar7 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"Icon_Career");
  param_1[0x15e] = iVar7;
  iStack_3c = 0x296712;
  iVar7 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"icon_offline_1");
  param_1[0x157] = iVar7;
  iStack_3c = 0x296722;
  iVar7 = FUN_00012d30(2000);
  param_1[0x117] = iVar7 + 6000;
  iStack_3c = 0x296732;
  FUN_0001a92c();
  *(double *)(param_1 + 0x118) = (double)in_ST0;
  *(undefined1 *)(param_1 + 0x11a) = 0;
  if (-1 < *(int *)PTR_DAT_004c994c) {
    iVar7 = *(int *)PTR_DAT_004c994c + 1;
    puVar2 = PTR_DAT_004c8fa4 + 0x41;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 0x43;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  param_1[0x112] = 1;
  *(undefined1 *)(param_1 + 0x113) = 0;
  *(undefined1 *)(param_1 + 0xde) = 0;
  *(undefined1 *)((int)param_1 + 0x379) = 0;
  param_1[0xe4] = 1;
  *(undefined1 *)(param_1 + 0xe3) = 0;
  *(undefined1 *)(param_1 + 0xe1) = 0;
  param_1[0x42] = 0;
  iStack_3c = 0x2967a4;
  FUN_0029a0ac(param_1);
  uVar3 = *(int *)(*(int *)(*(int *)PTR_DAT_004c96ac + 0x2d0) + 0x3c) - 0x1ed;
  iStack_3c = (int)uVar3 >> 1;
  if (iStack_3c < 0) {
    iStack_3c = iStack_3c + (uint)((uVar3 & 1) != 0);
  }
  uStack_40 = 0x164;
  uStack_44 = 0x1ed;
  uStack_48 = 0;
  uStack_4c = 0;
  uStack_50 = 0;
  uStack_54 = 0;
  uStack_58 = 0;
  uVar3 = *(int *)(*(int *)(*(int *)PTR_DAT_004c96ac + 0x2d0) + 0x38) - 0x164;
  iVar7 = (int)uVar3 >> 1;
  if (iVar7 < 0) {
    iVar7 = iVar7 + (uint)((uVar3 & 1) != 0);
  }
  iStack_5c = 0x296805;
  (**(code **)(*param_1 + 8))(param_1,"Form_Emotion_1",iVar7);
  *(undefined1 *)(param_1 + 0x2a) = 0;
  iStack_5c = 0x296828;
  iVar7 = FUN_0029a214(&PTR_LAB_00278c28,1,param_1);
  param_1[0x9c] = iVar7;
  iVar7 = 1;
  do {
    iVar8 = iVar7 + -1;
    iVar4 = iVar8;
    if (iVar8 < 0) {
      iVar4 = iVar7 + 2;
    }
    iVar9 = (iVar4 >> 2) * 0x22 + 0xb4;
    iStack_5c = 0x296877;
    iVar5 = FUN_0029a214(&PTR_LAB_00278c28,CONCAT31((int3)((uint)iVar9 >> 8),1),param_1);
    param_1[iVar7 + 0x9c] = iVar5;
    uStack_60 = 0x20;
    uStack_64 = 0x20;
    uStack_68 = 1;
    uStack_6c = 0;
    uStack_70 = 0;
    uStack_74 = 0x20;
    uStack_78 = 0x20;
    uStack_7c = 0x2968a6;
    iStack_5c = iVar9;
    FUN_0001953c(iVar7 + 100,&local_17c);
    uStack_7c = 0x2968bc;
    FUN_00014178(&local_178,&DAT_00298394,local_17c);
    uStack_7c = 0x2968d0;
    (**(code **)(*(int *)param_1[iVar7 + 0x9c] + 8))
              ((int *)param_1[iVar7 + 0x9c],local_178,(iVar8 + (iVar4 >> 2) * -4) * 0x22 + 0x25);
    if (*(int *)(param_1[iVar7 + 0x9c] + 0x4c) != -1) {
      iStack_5c = 0x2968ee;
      uVar6 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"btn_blank4");
      *(undefined4 *)(param_1[iVar7 + 0x9c] + 0x124) = uVar6;
    }
    iVar4 = param_1[iVar7 + 0x9c];
    *(int *)(iVar4 + 0xb0) = iVar7;
    *(int **)(iVar4 + 0x5c) = param_1;
    *(undefined1 **)(iVar4 + 0x58) = &LAB_00296610;
    *(int **)(iVar4 + 0x74) = param_1;
    *(undefined1 **)(iVar4 + 0x70) = &LAB_002991a0;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 0x19);
  iStack_5c = 0x296934;
  iVar7 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
  param_1[0x4a] = iVar7;
  iStack_5c = 0x4b;
  uStack_60 = 0x82;
  uStack_64 = 0x13;
  uStack_68 = 1;
  uStack_6c = 0;
  uStack_70 = 0;
  uStack_74 = 0x68;
  uStack_78 = 0xe;
  uStack_7c = 0x296962;
  (**(code **)(*(int *)param_1[0x4a] + 8))((int *)param_1[0x4a],"Panel26",0x7d);
  uStack_7c = 1;
  uStack_80 = 1;
  iStack_84 = 0x29697b;
  (**(code **)(*(int *)param_1[0x4a] + 0x70))((int *)param_1[0x4a],1,1);
  iStack_84 = 0x29698a;
  (**(code **)(*(int *)param_1[0x4a] + 4))((int *)param_1[0x4a],CONCAT22(extraout_var,0x841));
  *(undefined2 *)(param_1[0x4a] + 0x2a) = 0xffff;
  *(undefined1 *)(param_1[0x4a] + 0xa8) = 0;
  *(undefined1 *)(param_1[0x4a] + 0x205) = 1;
  iStack_84 = 0x2969bd;
  FUN_0048268c(param_1[0x4a],0);
  iStack_84 = 0x2969cd;
  FUN_00482730(param_1[0x4a],0xe);
  iStack_84 = 0x2969da;
  FUN_004802c0(param_1[0x4a],0);
  iStack_84 = 0x2969e8;
  iVar7 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
  param_1[0x51] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x296a01;
    iVar4 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
    param_1[iVar7 + 0x51] = iVar4;
    iStack_84 = (iVar7 + -1) * 0x41 + 0x5f;
    uStack_88 = 0x82;
    uStack_8c = 10;
    uStack_90 = 0;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0;
    uStack_a0 = 0;
    pcStack_a4 = (char *)0x296a3a;
    (**(code **)(*(int *)param_1[iVar7 + 0x51] + 8))((int *)param_1[iVar7 + 0x51],0,0x84);
    pcStack_a4 = (char *)0x296a4a;
    (**(code **)(*(int *)param_1[iVar7 + 0x51] + 4))
              ((int *)param_1[iVar7 + 0x51],CONCAT22(extraout_var_00,0x841));
    iVar4 = param_1[iVar7 + 0x51];
    *(undefined2 *)(iVar4 + 0x2a) = 0;
    *(undefined1 *)(iVar4 + 0xa8) = 0;
    *(undefined1 *)(iVar4 + 0x205) = 0;
    iStack_84 = 0x296a6c;
    FUN_0048268c(iVar4,0);
    *(undefined1 *)(param_1[iVar7 + 0x51] + 0x211) = 1;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x296a92;
  iVar7 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
  param_1[0x4b] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x296aab;
    iVar4 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
    param_1[iVar7 + 0x4b] = iVar4;
    iStack_84 = (iVar7 + -1) * 0x41 + 0x71;
    uStack_88 = 0x82;
    uStack_8c = 10;
    uStack_90 = 0;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0;
    uStack_a0 = 0;
    pcStack_a4 = (char *)0x296ae4;
    (**(code **)(*(int *)param_1[iVar7 + 0x4b] + 8))((int *)param_1[iVar7 + 0x4b],0,0x84);
    pcStack_a4 = (char *)0x296af4;
    (**(code **)(*(int *)param_1[iVar7 + 0x4b] + 4))
              ((int *)param_1[iVar7 + 0x4b],CONCAT22(extraout_var_01,0x841));
    iVar4 = param_1[iVar7 + 0x4b];
    *(undefined2 *)(iVar4 + 0x2a) = 0;
    *(undefined1 *)(iVar4 + 0xa8) = 0;
    *(undefined1 *)(iVar4 + 0x205) = 0;
    iStack_84 = 0x296b16;
    FUN_0048268c(iVar4,0);
    *(undefined1 *)(param_1[iVar7 + 0x4b] + 0x211) = 1;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x296b3c;
  iVar7 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
  param_1[0x158] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x296b55;
    iVar4 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
    param_1[iVar7 + 0x158] = iVar4;
    iStack_84 = (iVar7 + -1) * 0x41 + 0x49;
    uStack_88 = 0x10;
    uStack_8c = 0x10;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x10;
    uStack_a0 = 0x10;
    pcStack_a4 = (char *)0x296b8b;
    (**(code **)(*(int *)param_1[iVar7 + 0x158] + 8))((int *)param_1[iVar7 + 0x158],0,0xb5);
    *(undefined1 *)(param_1[iVar7 + 0x158] + 0x101) = 0;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x296bad;
  iVar7 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
  param_1[0x88] = iVar7;
  iVar7 = 1;
  local_28 = &DAT_004bc740;
  do {
    iStack_84 = 0x296bcd;
    iVar4 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
    param_1[iVar7 + 0x88] = iVar4;
    iStack_84 = *local_28;
    uStack_88 = 0xef;
    uStack_8c = 0x11;
    uStack_90 = 0;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0;
    uStack_a0 = 0;
    pcStack_a4 = (char *)0x296bfe;
    (**(code **)(*(int *)param_1[iVar7 + 0x88] + 8))((int *)param_1[iVar7 + 0x88],0,0x4d);
    pcStack_a4 = (char *)0x296c0e;
    (**(code **)(*(int *)param_1[iVar7 + 0x88] + 4))
              ((int *)param_1[iVar7 + 0x88],CONCAT22(extraout_var_02,0x841));
    iVar4 = param_1[iVar7 + 0x88];
    *(undefined2 *)(iVar4 + 0x2a) = 0;
    *(undefined1 *)(iVar4 + 0xa8) = 0;
    *(undefined1 *)(iVar4 + 0x205) = 1;
    iStack_84 = 0x296c30;
    FUN_0048268c(iVar4,0);
    iVar4 = param_1[iVar7 + 0x88];
    *(int **)(iVar4 + 0x1e4) = param_1;
    *(code **)(iVar4 + 0x1e0) = FUN_00295210;
    iStack_84 = 0x296c51;
    FUN_00482730(iVar4,0x1d);
    iVar7 = iVar7 + 1;
    local_28 = local_28 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x296c7b;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0xd8] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x296c94;
    iVar4 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
    param_1[iVar7 + 0xd8] = iVar4;
    iStack_84 = 400;
    uStack_88 = 0x2b;
    uStack_8c = 0x14;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x2b;
    uStack_a0 = 0x14;
    pcStack_a4 = "Btn_onstate";
    iStack_a8 = 0x296cc8;
    FUN_0001953c(iVar7,&local_184);
    iStack_a8 = local_184;
    puStack_ac = &DAT_002983d8;
    uStack_b0 = 0x296ce3;
    FUN_000141ec(&local_180,3);
    uStack_b0 = 0x296d04;
    (**(code **)(*(int *)param_1[iVar7 + 0xd8] + 8))
              ((int *)param_1[iVar7 + 0xd8],local_180,(iVar7 + -1) * 0x2d + 0x8c);
    iStack_84 = 0x296d12;
    FUN_00485738(param_1[iVar7 + 0xd8],0);
    iVar4 = param_1[iVar7 + 0xd8];
    *(int **)(iVar4 + 0x5c) = param_1;
    *(undefined1 **)(iVar4 + 0x58) = &LAB_00296610;
    *(int *)(iVar4 + 0xb0) = iVar7;
    *(int **)(iVar4 + 0x74) = param_1;
    *(code **)(iVar4 + 0x70) = FUN_00295144;
    iStack_84 = 0x296d3a;
    FUN_004802c0(iVar4,0);
    iVar7 = iVar7 + 1;
  } while (iVar7 != 5);
  *(undefined1 *)(param_1[0xd9] + 0xf8) = 1;
  iStack_84 = 0x296d6d;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x94] = iVar7;
  iVar7 = 1;
  local_28 = &DAT_004bc740;
  do {
    iStack_84 = 0x296d8d;
    iVar4 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
    param_1[iVar7 + 0x94] = iVar4;
    iStack_84 = *local_28;
    uStack_88 = 0x2a;
    uStack_8c = 0x10;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x2a;
    uStack_a0 = 0x10;
    pcStack_a4 = "Btn_ctrl";
    iStack_a8 = 0x296dc2;
    FUN_0001953c(iVar7,&local_18c);
    iStack_a8 = local_18c;
    puStack_ac = &DAT_002983d8;
    uStack_b0 = 0x296ddd;
    FUN_000141ec(&local_188,3);
    uStack_b0 = 0x296df4;
    (**(code **)(*(int *)param_1[iVar7 + 0x94] + 8))((int *)param_1[iVar7 + 0x94],local_188,0x22);
    iStack_84 = 0x296e02;
    FUN_00485738(param_1[iVar7 + 0x94],0);
    iVar4 = param_1[iVar7 + 0x94];
    *(int **)(iVar4 + 0x5c) = param_1;
    *(undefined1 **)(iVar4 + 0x58) = &LAB_00296610;
    *(int *)(iVar4 + 0xb0) = iVar7;
    *(int **)(iVar4 + 0x74) = param_1;
    *(undefined1 **)(iVar4 + 0x70) = &LAB_002990fc;
    iVar7 = iVar7 + 1;
    local_28 = local_28 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x296e4d;
  iVar7 = FUN_0029a214(&PTR_LAB_00278c28,1,param_1);
  param_1[0x75] = iVar7;
  iVar7 = 1;
  local_28 = &DAT_004bc71c;
  do {
    iVar4 = *local_28;
    iStack_84 = 0x296e79;
    iVar8 = FUN_0029a214(&PTR_LAB_00278c28,1,param_1);
    param_1[iVar7 + 0x75] = iVar8;
    iStack_84 = 0x194;
    uStack_88 = 0x20;
    uStack_8c = 0x20;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x20;
    uStack_a0 = 0x20;
    pcStack_a4 = (char *)0x296eaf;
    (**(code **)(*(int *)param_1[iVar7 + 0x75] + 8))
              ((int *)param_1[iVar7 + 0x75],"btn_blank4",iVar4 + 1);
    if (*(int *)(param_1[iVar7 + 0x75] + 0x4c) != -1) {
      iStack_84 = 0x296ecd;
      uVar6 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"btn_blank4");
      *(undefined4 *)(param_1[iVar7 + 0x75] + 0x124) = uVar6;
    }
    iVar4 = param_1[iVar7 + 0x75];
    *(int *)(iVar4 + 0xb0) = iVar7;
    *(int **)(iVar4 + 0x5c) = param_1;
    *(undefined1 **)(iVar4 + 0x58) = &LAB_00296610;
    *(int **)(iVar4 + 0x74) = param_1;
    *(code **)(iVar4 + 0x70) = FUN_00299204;
    iVar7 = iVar7 + 1;
    local_28 = local_28 + 1;
  } while (iVar7 != 9);
  iStack_84 = 0x296f17;
  iVar7 = FUN_0029a214(&PTR_LAB_00278dc0,1,param_1);
  param_1[0xce] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x296f30;
    iVar4 = FUN_0029a214(&PTR_LAB_00278dc0,1,param_1);
    param_1[iVar7 + 0xce] = iVar4;
    iStack_84 = (iVar7 / 5) * 0x3b + 0x120;
    uStack_88 = 0x20;
    uStack_8c = 0x20;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x20;
    uStack_a0 = 0x20;
    pcStack_a4 = (char *)0x296f65;
    FUN_0001953c(iVar7,&local_194);
    pcStack_a4 = (char *)0x296f78;
    FUN_00014178(&local_190,0,local_194);
    pcStack_a4 = (char *)0x296fa1;
    (**(code **)(*(int *)param_1[iVar7 + 0xce] + 8))
              ((int *)param_1[iVar7 + 0xce],local_190,(iVar7 % 5) * 0x24 + 0x19);
    iVar4 = param_1[iVar7 + 0xce];
    *(int **)(iVar4 + 0x5c) = param_1;
    *(undefined1 **)(iVar4 + 0x58) = &LAB_00296638;
    *(undefined4 *)(iVar4 + 0xb0) = 0xffffffff;
    iStack_84 = 0x296fc3;
    FUN_004802c0(iVar4,0);
    iVar7 = iVar7 + 1;
  } while (iVar7 != 10);
  iStack_84 = 0x296fe9;
  iVar7 = FUN_0029a214(&PTR_LAB_00278cf4,1,param_1);
  param_1[0xb5] = iVar7;
  iVar7 = 1;
  do {
    iVar4 = iVar7 + -1;
    if (iVar4 < 0) {
      iVar4 = iVar7 + 2;
    }
    iVar5 = (iVar4 >> 2) * 0x22 + 0xb4;
    iStack_84 = 0x29703a;
    iVar8 = FUN_0029a214(&PTR_LAB_00278cf4,CONCAT31((int3)((uint)iVar5 >> 8),1),param_1);
    param_1[iVar7 + 0xb5] = iVar8;
    uStack_88 = 0x20;
    uStack_8c = 0x20;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x20;
    uStack_a0 = 0x20;
    pcStack_a4 = (char *)0x297068;
    iStack_84 = iVar5;
    FUN_0001953c(iVar7,&local_19c);
    pcStack_a4 = (char *)0x29707e;
    FUN_00014178(&local_198,"btn_Action_",local_19c);
    pcStack_a4 = (char *)0x297092;
    (**(code **)(*(int *)param_1[iVar7 + 0xb5] + 8))
              ((int *)param_1[iVar7 + 0xb5],local_198,(iVar7 + -1 + (iVar4 >> 2) * -4) * 0x22 + 0xb4
              );
    if (*(int *)(param_1[iVar7 + 0xb5] + 0x4c) != -1) {
      iStack_84 = 0x2970b0;
      uVar6 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"btn_blank4");
      *(undefined4 *)(param_1[iVar7 + 0xb5] + 0x124) = uVar6;
    }
    iVar4 = param_1[iVar7 + 0xb5];
    *(int *)(iVar4 + 0xb0) = iVar7;
    *(int **)(iVar4 + 0x5c) = param_1;
    *(undefined1 **)(iVar4 + 0x58) = &LAB_00296610;
    *(int **)(iVar4 + 0x74) = param_1;
    *(undefined1 **)(iVar4 + 0x70) = &LAB_002987d0;
    iStack_84 = 0x2970e5;
    FUN_004802c0(iVar4,0);
    iVar7 = iVar7 + 1;
  } while (iVar7 != 0x19);
  iStack_84 = 0x297100;
  iVar7 = FUN_003c7c48(&PTR_FUN_003c6850,1,0xfffffffe);
  param_1[0xe6] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x29711c;
    iVar4 = FUN_003c7c48(&PTR_FUN_003c6850,1,0xfffffffe);
    param_1[iVar7 + 0xe6] = iVar4;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x297145;
  iVar7 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
  param_1[0xec] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x29715e;
    iVar4 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
    param_1[iVar7 + 0xec] = iVar4;
    iStack_84 = (iVar7 + -1) * 0x42 + 0x49;
    uStack_88 = 0x1e;
    uStack_8c = 0x1e;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x1e;
    uStack_a0 = 0x1e;
    pcStack_a4 = (char *)0x297198;
    (**(code **)(*(int *)param_1[iVar7 + 0xec] + 8))((int *)param_1[iVar7 + 0xec],0,0x10e);
    *(undefined1 *)(param_1[iVar7 + 0xec] + 0x101) = 0;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x2971c8;
  iVar7 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
  param_1[0xf2] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x2971e1;
    iVar4 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
    param_1[iVar7 + 0xf2] = iVar4;
    iStack_84 = (iVar7 + -1) * 0x41 + 0x3d;
    uStack_88 = 0x5a;
    uStack_8c = 0x28;
    uStack_90 = 0;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0;
    uStack_a0 = 0;
    pcStack_a4 = (char *)0x29721b;
    (**(code **)(*(int *)param_1[iVar7 + 0xf2] + 8))((int *)param_1[iVar7 + 0xf2],0,0x57);
    pcStack_a4 = (char *)0x29722b;
    (**(code **)(*(int *)param_1[iVar7 + 0xf2] + 4))
              ((int *)param_1[iVar7 + 0xf2],CONCAT22(extraout_var_03,0x841));
    iVar4 = param_1[iVar7 + 0xf2];
    *(undefined2 *)(iVar4 + 0x2a) = 0;
    *(undefined1 *)(iVar4 + 0xa8) = 0;
    *(undefined1 *)(iVar4 + 0x205) = 1;
    iStack_84 = 0x29724d;
    FUN_0048268c(iVar4,0);
    *(undefined1 *)(param_1[iVar7 + 0xf2] + 0x211) = 1;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x297281;
  iVar7 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
  param_1[0x104] = iVar7;
  iVar7 = 1;
  do {
    iStack_84 = 0x29729a;
    iVar4 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
    param_1[iVar7 + 0x104] = iVar4;
    iStack_84 = (iVar7 + -1) * 0x42 + 0x68;
    uStack_88 = 0x20;
    uStack_8c = 0x10;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x20;
    uStack_a0 = 0x10;
    pcStack_a4 = (char *)0x2972d4;
    (**(code **)(*(int *)param_1[iVar7 + 0x104] + 8))((int *)param_1[iVar7 + 0x104],0,0x104);
    *(undefined1 *)(param_1[iVar7 + 0x104] + 0x101) = 0;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  iStack_84 = 0x297304;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x110] = iVar7;
  if (*PTR_DAT_004c8a48 == '\0') {
    iStack_84 = 0x188;
    uStack_88 = 0x15;
    uStack_8c = 0x15;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x15;
    uStack_a0 = 0x15;
    pcStack_a4 = (char *)0x297344;
    (**(code **)(*(int *)param_1[0x110] + 8))((int *)param_1[0x110],"Btn_ArrowL_8",0x86);
  }
  else {
    iStack_84 = 0x188;
    uStack_88 = 0x15;
    uStack_8c = 0x15;
    uStack_90 = 1;
    uStack_94 = 0;
    uStack_98 = 0;
    uStack_9c = 0x15;
    uStack_a0 = 0x15;
    pcStack_a4 = (char *)0x297376;
    (**(code **)(*(int *)param_1[0x110] + 8))((int *)param_1[0x110],"Btn_ArrowL_8",0x7d);
  }
  pcStack_a4 = (char *)0x297383;
  FUN_004802c0(param_1[0x110],0);
  iVar7 = param_1[0x110];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_00292fd8;
  pcStack_a4 = (char *)0x2973af;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x111] = iVar7;
  if (*PTR_DAT_004c8a48 == '\0') {
    pcStack_a4 = (char *)0x188;
    iStack_a8 = 0x15;
    puStack_ac = (undefined *)0x15;
    uStack_b0 = 1;
    uStack_b4 = 0;
    uStack_b8 = 0;
    uStack_bc = 0x15;
    uStack_c0 = 0x15;
    uStack_c4 = 0x2973ef;
    (**(code **)(*(int *)param_1[0x111] + 8))((int *)param_1[0x111],"Btn_ArrowR_8",0xc5);
  }
  else {
    pcStack_a4 = (char *)0x188;
    iStack_a8 = 0x15;
    puStack_ac = (undefined *)0x15;
    uStack_b0 = 1;
    uStack_b4 = 0;
    uStack_b8 = 0;
    uStack_bc = 0x15;
    uStack_c0 = 0x15;
    uStack_c4 = 0x297421;
    (**(code **)(*(int *)param_1[0x111] + 8))((int *)param_1[0x111],"Btn_ArrowR_8",0xcf);
  }
  uStack_c4 = 0x29742e;
  FUN_004802c0(param_1[0x111],0);
  iVar7 = param_1[0x111];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_002930e0;
  uStack_c4 = 0x29745a;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x43] = iVar7;
  uStack_c4 = 0x2b;
  uStack_c8 = 0x42;
  uStack_cc = 0x15;
  uStack_d0 = 1;
  uStack_d4 = 0;
  uStack_d8 = 0;
  uStack_dc = 0x42;
  uStack_e0 = 0x15;
  uStack_e4 = 0x29748d;
  (**(code **)(*(int *)param_1[0x43] + 8))((int *)param_1[0x43],"Btn_setup_2",0x97);
  iVar7 = param_1[0x43];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_00298aa0;
  uStack_e4 = 0x2974b9;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x44] = iVar7;
  uStack_e4 = 0x6b;
  uStack_e8 = 0x10;
  uStack_ec = 0x10;
  uStack_f0 = 1;
  uStack_f4 = 0;
  uStack_f8 = 0;
  uStack_fc = 0x10;
  uStack_100 = 0x10;
  uStack_104 = 0x2974ec;
  (**(code **)(*(int *)param_1[0x44] + 8))((int *)param_1[0x44],"btn_check_1",0x90);
  iVar7 = param_1[0x44];
  *(int **)(iVar7 + 0x54) = param_1;
  *(code **)(iVar7 + 0x50) = FUN_00293628;
  uStack_104 = 0x297509;
  FUN_004802c0(param_1[0x44],0);
  uStack_104 = 0x297525;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x45] = iVar7;
  uStack_104 = 0x6b;
  uStack_108 = 0x10;
  uStack_10c = 0x10;
  uStack_110 = 1;
  uStack_114 = 0;
  uStack_118 = 0;
  uStack_11c = 0x10;
  uStack_120 = 0x10;
  uStack_124 = 0x297558;
  (**(code **)(*(int *)param_1[0x45] + 8))((int *)param_1[0x45],"btn_Uncheck_1",199);
  iVar7 = param_1[0x45];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_002936b0;
  uStack_124 = 0x297575;
  FUN_004802c0(param_1[0x45],0);
  *(undefined1 *)(param_1 + 0x47) = 1;
  *(undefined1 *)((int)param_1 + 0x11d) = 0;
  uStack_124 = 0x29759f;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x48] = iVar7;
  uStack_124 = 0x1a4;
  uStack_128 = 0x3d;
  uStack_12c = 0x14;
  uStack_130 = 1;
  uStack_134 = 0;
  uStack_138 = 0;
  uStack_13c = 0x3d;
  uStack_140 = 0x14;
  uStack_144 = 0x2975d5;
  (**(code **)(*(int *)param_1[0x48] + 8))((int *)param_1[0x48],"btn_sendmail_3",0x6f);
  uStack_144 = 0x2975e2;
  FUN_004802c0(param_1[0x48],0);
  iVar7 = param_1[0x48];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_0029500c;
  uStack_144 = 0x29760e;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x49] = iVar7;
  uStack_144 = 0x1a4;
  uStack_148 = 0x3d;
  uStack_14c = 0x14;
  uStack_150 = 1;
  uStack_154 = 0;
  uStack_158 = 0;
  uStack_15c = 0x3d;
  uStack_160 = 0x14;
  uStack_164 = 0x297644;
  (**(code **)(*(int *)param_1[0x49] + 8))((int *)param_1[0x49],"btn_delFriend_1",0xb3);
  uStack_164 = 0x297651;
  FUN_004802c0(param_1[0x49],0);
  iVar7 = param_1[0x49];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_00294d5c;
  uStack_164 = 0x29767d;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x46] = iVar7;
  uStack_164 = 0x2b;
  uStack_168 = 0x42;
  uStack_16c = 0x15;
  uStack_170 = 1;
  uStack_174 = 0;
  local_178 = 0;
  local_17c = 0x42;
  local_180 = 0x15;
  local_184 = 0x2976b0;
  (**(code **)(*(int *)param_1[0x46] + 8))((int *)param_1[0x46],"Btn_Marry",0xd9);
  local_184 = 0x2976bd;
  FUN_004802c0(param_1[0x46],1);
  iVar7 = param_1[0x46];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_00298e1c;
  local_184 = 0x2976e9;
  iVar7 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
  param_1[0x5d] = iVar7;
  iVar7 = 1;
  do {
    local_184 = 0x297702;
    iVar4 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
    param_1[iVar7 + 0x5d] = iVar4;
    local_184 = (iVar7 + -1) * 0x42 + 0x49;
    local_188 = 0x14;
    local_18c = 0xf;
    local_190 = 1;
    local_194 = 0;
    local_198 = 0;
    local_19c = 0x14;
    local_1a0 = 0xf;
    uStack_1a4 = 0x29773f;
    (**(code **)(*(int *)param_1[iVar7 + 0x5d] + 8))
              ((int *)param_1[iVar7 + 0x5d],"icon_mail_1",0x131);
    iVar4 = param_1[iVar7 + 0x5d];
    *(int *)(iVar4 + 0xb0) = iVar7;
    *(undefined1 *)(iVar4 + 0x101) = 0;
    local_184 = 0x29775a;
    FUN_004802c0(iVar4,0);
    iVar4 = param_1[iVar7 + 0x5d];
    *(int **)(iVar4 + 0x74) = param_1;
    *(undefined1 **)(iVar4 + 0x70) = &LAB_00293204;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  local_184 = 0x29778d;
  iVar7 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
  param_1[99] = iVar7;
  iVar7 = 1;
  do {
    local_184 = 0x2977a6;
    iVar4 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
    param_1[iVar7 + 99] = iVar4;
    local_184 = (iVar7 + -1) * 0x42 + 0x49;
    local_188 = 0x14;
    local_18c = 0xf;
    local_190 = 1;
    local_194 = 0;
    local_198 = 0;
    local_19c = 0x14;
    local_1a0 = 0xf;
    uStack_1a4 = 0x2977e3;
    (**(code **)(*(int *)param_1[iVar7 + 99] + 8))
              ((int *)param_1[iVar7 + 99],"icon_mailGary_1",0x131);
    *(int *)(param_1[iVar7 + 99] + 0xb0) = iVar7;
    local_184 = 0x2977fe;
    FUN_004802c0(param_1[iVar7 + 99],0);
    *(undefined1 *)(param_1[iVar7 + 99] + 0x101) = 0;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  local_184 = 0x29782e;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x6f] = iVar7;
  iVar7 = 1;
  do {
    local_184 = 0x297847;
    iVar4 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
    param_1[iVar7 + 0x6f] = iVar4;
    local_184 = (iVar7 + -1) * 0x42 + 0x67;
    local_188 = 0x2b;
    local_18c = 0x14;
    local_190 = 1;
    local_194 = 0;
    local_198 = 0;
    local_19c = 0x2b;
    local_1a0 = 0x14;
    uStack_1a4 = 0x297884;
    (**(code **)(*(int *)param_1[iVar7 + 0x6f] + 8))
              ((int *)param_1[iVar7 + 0x6f],"Btn_Delete_1",0x11c);
    *(int *)(param_1[iVar7 + 0x6f] + 0xb0) = iVar7;
    local_184 = 0x29789f;
    FUN_004802c0(param_1[iVar7 + 0x6f],0);
    iVar4 = param_1[iVar7 + 0x6f];
    *(int **)(iVar4 + 0x74) = param_1;
    *(code **)(iVar4 + 0x70) = FUN_00293298;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  local_184 = 0x2978d2;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x3a] = iVar7;
  iVar7 = 1;
  do {
    *(undefined1 *)((int)param_1 + iVar7 + 0x100) = 0;
    local_184 = 0x2978f3;
    iVar4 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
    param_1[iVar7 + 0x3a] = iVar4;
    local_184 = (iVar7 + -1) * 0x41 + 0x6b;
    local_188 = 0x10;
    local_18c = 0x10;
    local_190 = 1;
    local_194 = 0;
    local_198 = 0;
    local_19c = 0x10;
    local_1a0 = 0x10;
    uStack_1a4 = 0x297934;
    (**(code **)(*(int *)param_1[iVar7 + 0x3a] + 8))
              ((int *)param_1[iVar7 + 0x3a],"btn_UnCheck_1",0x131);
    *(int *)(param_1[iVar7 + 0x3a] + 0xb0) = iVar7;
    local_184 = 0x29794f;
    FUN_004802c0(param_1[iVar7 + 0x3a],0);
    iVar4 = param_1[iVar7 + 0x3a];
    *(int **)(iVar4 + 0x74) = param_1;
    *(undefined1 **)(iVar4 + 0x70) = &LAB_00295078;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  local_184 = 0x297986;
  iVar7 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
  param_1[0x69] = iVar7;
  iVar7 = 1;
  do {
    local_184 = 0x29799f;
    iVar4 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
    param_1[iVar7 + 0x69] = iVar4;
    local_184 = (iVar7 + -1) * 0x42 + 0x67;
    local_188 = 0x2b;
    local_18c = 0x14;
    local_190 = 1;
    local_194 = 0;
    local_198 = 0;
    local_19c = 0x2b;
    local_1a0 = 0x14;
    uStack_1a4 = 0x2979dc;
    (**(code **)(*(int *)param_1[iVar7 + 0x69] + 8))
              ((int *)param_1[iVar7 + 0x69],"Btn_Delete_Gray_1",0x11c);
    *(int *)(param_1[iVar7 + 0x69] + 0xb0) = iVar7;
    local_184 = 0x2979f7;
    FUN_004802c0(param_1[iVar7 + 0x69],0);
    *(undefined1 *)(param_1[iVar7 + 0x69] + 0x101) = 0;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 6);
  local_184 = 0x297a27;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x59] = iVar7;
  local_184 = 0x2b;
  local_188 = 0x42;
  local_18c = 0x15;
  local_190 = 1;
  local_194 = 0;
  local_198 = 0;
  local_19c = 0x42;
  local_1a0 = 0x15;
  uStack_1a4 = 0x297a5a;
  (**(code **)(*(int *)param_1[0x59] + 8))((int *)param_1[0x59],"Btn_EmuationalIcon_1",0x55);
  iVar7 = param_1[0x59];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_0029884c;
  *(undefined1 *)(param_1[0x59] + 0xb9) = 0;
  *(undefined1 *)(param_1[0x59] + 0xca) = 1;
  *(undefined1 *)(param_1[0x59] + 0xf8) = 1;
  uStack_1a4 = 0x297aad;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x5c] = iVar7;
  uStack_1a4 = 0x2b;
  local_1a8 = 0x42;
  local_1ac = 0x15;
  local_1b0 = 1;
  (**(code **)(*(int *)param_1[0x5c] + 8))
            ((int *)param_1[0x5c],"Btn_FriendIcon_1",0x14,0x15,0x42,0,0);
  iVar7 = param_1[0x5c];
  *(int **)(iVar7 + 0x54) = param_1;
  *(code **)(iVar7 + 0x50) = FUN_00298e70;
  *(undefined1 *)(param_1[0x5c] + 0xb9) = 0;
  *(undefined1 *)(param_1[0x5c] + 0xca) = 1;
  *(undefined1 *)(param_1[0x5c] + 0xf8) = 0;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x5a] = iVar7;
  (**(code **)(*(int *)param_1[0x5a] + 8))
            ((int *)param_1[0x5a],0,0x4d,0x15,0x2c,0,0,1,0x15,0x2c,0xb2);
  iVar7 = param_1[0x5a];
  *(int **)(iVar7 + 0x54) = param_1;
  *(code **)(iVar7 + 0x50) = FUN_00292f90;
  *(undefined1 *)(param_1[0x5a] + 0xb9) = 0;
  *(undefined1 *)(param_1[0x5a] + 0xca) = 1;
  *(undefined1 *)(param_1[0x5a] + 0xf8) = 0;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x5b] = iVar7;
  (**(code **)(*(int *)param_1[0x5b] + 8))
            ((int *)param_1[0x5b],0,0x22,0x15,0x2c,0,0,1,0x15,0x2c,0xb2);
  iVar7 = param_1[0x5b];
  *(int **)(iVar7 + 0x54) = param_1;
  *(code **)(iVar7 + 0x50) = FUN_00292fb0;
  *(undefined1 *)(param_1[0x5b] + 0xb9) = 0;
  *(undefined1 *)(param_1[0x5b] + 0xca) = 1;
  *(undefined1 *)(param_1[0x5b] + 0xf8) = 1;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x58] = iVar7;
  (**(code **)(*(int *)param_1[0x58] + 8))
            ((int *)param_1[0x58],"Btn_Close_1",0x98,0x14,0x38,0,0,1,0x14,0x38,0x1ca);
  iVar7 = param_1[0x58];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_0029a108;
  *(undefined1 *)(param_1[0x58] + 0xb9) = 0;
  *(undefined1 *)(param_1[0x58] + 0xca) = 1;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x57] = iVar7;
  (**(code **)(*(int *)param_1[0x57] + 8))
            ((int *)param_1[0x57],"Btn_Close_s_1",0x130,0x12,0x12,0,0,1,0x12,0x12,0x18);
  iVar7 = param_1[0x57];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined1 **)(iVar7 + 0x50) = &LAB_0029a108;
  *(undefined1 *)(param_1[0x57] + 0xb9) = 0;
  *(undefined1 *)(param_1[0x57] + 0xca) = 1;
  iVar7 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"icon_anim_Gotmail_1");
  param_1[0x114] = iVar7;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x11b] = iVar7;
  iVar7 = 1;
  do {
    iVar4 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
    param_1[iVar7 + 0x11b] = iVar4;
    (**(code **)(*(int *)param_1[iVar7 + 0x11b] + 8))
              ((int *)param_1[iVar7 + 0x11b],"btn_UnCheck_1",(iVar7 + -1) * 0x32 + 0x55,0x10,0x10,0,
               0,1,0x10,0x10,0x146);
    *(int *)(param_1[iVar7 + 0x11b] + 0xb0) = iVar7;
    FUN_004802c0(param_1[iVar7 + 0x11b],0);
    iVar4 = param_1[iVar7 + 0x11b];
    *(int **)(iVar4 + 0x74) = param_1;
    *(code **)(iVar4 + 0x70) = FUN_00294198;
    *(undefined1 *)((int)param_1 + iVar7 + 0x480) = 0;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 5);
  *(undefined1 *)((int)param_1 + 0x485) = 0;
  iVar7 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
  param_1[0x122] = iVar7;
  iVar7 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
  param_1[0x123] = iVar7;
  (**(code **)(*(int *)param_1[0x123] + 8))((int *)param_1[0x123],0,0x46,0,0,0,0,0,0x12,0x28,0x88);
  (**(code **)(*(int *)param_1[0x123] + 4))((int *)param_1[0x123],CONCAT22(extraout_var_04,0x841));
  *(undefined1 *)(param_1[0x123] + 0xa8) = 0;
  *(undefined1 *)(param_1[0x123] + 0x205) = 1;
  FUN_0048268c(param_1[0x123],0);
  FUN_00482750(param_1[0x123],1);
  FUN_004802c0(param_1[0x123],0);
  FUN_00482730(param_1[0x123],4);
  iVar7 = param_1[0x123];
  *(int **)(iVar7 + 0x1e4) = param_1;
  *(undefined1 **)(iVar7 + 0x1e0) = &LAB_00293c30;
  iVar7 = 2;
  do {
    iVar4 = FUN_004824f0(&PTR_LAB_0047f370,1,param_1);
    param_1[iVar7 + 0x122] = iVar4;
    (**(code **)(*(int *)param_1[iVar7 + 0x122] + 8))
              ((int *)param_1[iVar7 + 0x122],0,(iVar7 + -2) * 0x2a + 0x83,0,0,0,0,0,0x12,0x17,0x88);
    (**(code **)(*(int *)param_1[iVar7 + 0x122] + 4))
              ((int *)param_1[iVar7 + 0x122],CONCAT22(extraout_var_05,0x841));
    iVar4 = param_1[iVar7 + 0x122];
    *(undefined1 *)(iVar4 + 0xa8) = 0;
    *(undefined1 *)(iVar4 + 0x205) = 1;
    FUN_0048268c(iVar4,0);
    FUN_00482750(param_1[iVar7 + 0x122],1);
    FUN_004802c0(param_1[iVar7 + 0x122],0);
    FUN_00482730(param_1[iVar7 + 0x122],2);
    iVar4 = param_1[iVar7 + 0x122];
    *(int **)(iVar4 + 0x1e4) = param_1;
    *(undefined1 **)(iVar4 + 0x1e0) = &LAB_00293c30;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 4);
  iVar7 = 1;
  do {
    param_1[iVar7 + 0x126] = 0;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 4);
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x12a] = iVar7;
  piVar1 = (int *)param_1[0x12a];
  (**(code **)(*piVar1 + 8))(piVar1,"Btn_on_1",0x68,0x14,0x27,0,0,1,0x14,0x27,0x162);
  piVar1[0x15] = (int)param_1;
  piVar1[0x14] = (int)&LAB_00294244;
  FUN_004802c0(piVar1,0);
  *(undefined1 *)(param_1 + 299) = 0;
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x133] = iVar7;
  local_20 = (int *)param_1[0x133];
  (**(code **)(*local_20 + 8))(local_20,"Btn_OK_2",0x7a,0x14,0x27,0,0,1,0x14,0x27,0x1ca);
  local_20[0x15] = (int)param_1;
  local_20[0x14] = (int)&LAB_00294660;
  FUN_004802c0(local_20,0);
  iVar7 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x134] = iVar7;
  local_24 = (int *)param_1[0x134];
  (**(code **)(*local_24 + 8))(local_24,"Btn_Cancel_3",200,0x14,0x27,0,0,1,0x14,0x27,0x1ca);
  local_24[0x15] = (int)param_1;
  local_24[0x14] = (int)&LAB_002949d0;
  FUN_004802c0(local_24,0);
  iVar7 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"icon_Jumpheart_1");
  param_1[0x136] = iVar7;
  if (param_1[0x136] == -1) {
    FUN_00014178(&local_1a0,*(undefined4 *)PTR_DAT_004c8c60,"Menu\\Skins\\default\\",1,0);
    FUN_0047caa8(*(undefined4 *)PTR_DAT_004c8a78,local_1a0,"icon_Jumpheart_1");
    iVar7 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"icon_Jumpheart_1");
    param_1[0x136] = iVar7;
  }
  iVar7 = FUN_00478644(*(undefined4 *)PTR_DAT_004c8a78,param_1[0x136]);
  param_1[0x137] = iVar7;
  uVar3 = FUN_00478630(*(undefined4 *)PTR_DAT_004c8a78,param_1[0x136]);
  iVar7 = (int)uVar3 >> 1;
  if (iVar7 < 0) {
    iVar7 = iVar7 + (uint)((uVar3 & 1) != 0);
  }
  param_1[0x138] = iVar7;
  local_1a8 = GetTickCount();
  uStack_1a4 = 0;
  *(double *)(param_1 + 0x13a) = (double)local_1a8;
  param_1[0x139] = 0;
  iVar7 = FUN_00484584(&PTR_LAB_0047f0a4,1,param_1);
  param_1[300] = iVar7;
  (**(code **)(*(int *)param_1[300] + 8))((int *)param_1[300],0,0x24,0x8f,0xae,0,0,1,0x8f,0xae,0xa8)
  ;
  FUN_004802c0(param_1[300],0);
  *(undefined1 *)(param_1[300] + 0x101) = 0;
  iVar7 = param_1[300];
  *(int **)(iVar7 + 0x54) = param_1;
  *(undefined **)(iVar7 + 0x50) = &DAT_0029a188;
  param_1[0x7f] = 2;
  uVar16 = 0x194;
  uVar15 = 0x20;
  uVar14 = 0x20;
  uVar13 = 1;
  uVar12 = 0;
  uVar11 = 0;
  uVar10 = 0x20;
  uVar6 = 0x20;
  FUN_0001953c(0xd,&local_1b0);
  FUN_00014178(&local_1ac,"btn_Action_",local_1b0,uVar6,uVar10,uVar11,uVar12,uVar13,uVar14,uVar15,
               uVar16);
  (**(code **)(*(int *)param_1[0x76] + 8))((int *)param_1[0x76],local_1ac,DAT_004bc71c + 1);
  *(undefined4 *)(param_1[0x76] + 0x158) = 0xd;
  *in_FS_OFFSET = uVar6;
  FUN_00013ed0(&local_1b0,2,uVar11,&LAB_002982e9);
  FUN_00013ed0(&local_1a0,0xb);
  FUN_00013eac(&stack0xffffffe8);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_00436178
 * @başlık         Port Doğrulayıcı (Port Validator)
 * @açıklama       Bağlanılmak istenen portun Wonderland Online varsayılan portları olup olmadığını denetler.
 * @ofsetler       param_1 port değeridir. 25221 (0x6285) or 25620 (0x6414) olması beklenir.
 * @paketler       Login ve oyun sunucusu port kontrolleri.
 * 
 * @detaylı_analiz 
 * * 1. Gelen port parametresi 0x6285 (25221) ile karşılaştırılır.
 *  * 2. Eşleşmezse 0x6414 (25620) ile karşılaştırılır.
 *  * 3. İki porttan biri değilse bağlantıyı engellemek için 0 döndürür.
 *******************************************************************************/
        ((((cVar1 = FUN_00436178(param_1,param_2), cVar1 == '\0' &&
           (cVar1 = FUN_00433d8c(param_1,param_2), cVar1 != '\x03')) &&
          ((cVar1 = FUN_00435d04(param_1,param_2), cVar1 == '\0' &&
           ((cVar1 = FUN_004342fc(param_1,param_2), cVar1 == '\0' &&
            (cVar1 = FUN_004343d8(param_1,param_2), cVar1 == '\0')))))) &&
         (cVar1 = FUN_00435e74(param_1,param_2), cVar1 == '\0')))) &&
       (((cVar1 = FUN_00435ed0(param_1,param_2), cVar1 == '\0' &&
         (cVar1 = FUN_00435530(param_1,param_2 & 0xffff), cVar1 == '\0')) &&
        (cVar1 = FUN_00435fe8(param_1,param_2), cVar1 == '\0')))) {
      return 0;
    }

/*******************************************************************************
 * @fonksiyon      FUN_00124a1c
 * @başlık         Alım Tamponu Çerçeveleyicisi (Recv Buffer Framer)
 * @açıklama       Ağdan gelen ham baytları istemci paket sınırlarına göre ayırarak çerçeveler.
 * @ofsetler       Verinin depolandığı dinamik bellek dizisi (+0x24).
 * @paketler       Paket Ayrıştırma ve Çerçeveleme.
 * 
 * @detaylı_analiz 
 * * 1. Ağdan okunan ham bayt akışı sıraya eklenir.
 *  * 2. Paketlerin başlık uzunluk tanımlayıcıları taranarak tam paket sınırları belirlenir.
 *  * 3. Hazır olan paketler işletilmek üzere ilgili handler fonksiyonlarına yollanır.
 *******************************************************************************/
void FUN_00124a1c(int param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  uint uVar2;
  uint extraout_EDX;
  int iVar3;
  uint uVar4;
  undefined4 *in_FS_OFFSET;
  int iVar5;
  int iVar6;
  undefined4 uStack_38;
  undefined1 *puStack_34;
  undefined1 *puStack_30;
  undefined4 uStack_2c;
  undefined1 *puStack_28;
  undefined1 *puStack_24;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  puStack_24 = &stack0xfffffffc;
  local_14 = 0;
  puStack_28 = &LAB_00124c54;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  puStack_30 = (undefined1 *)0x124a4d;
  local_c = param_2;
  local_8 = param_1;
  FUN_00125e88(param_1,8,"ReadLn");
  uVar4 = 0;
  puStack_30 = (undefined1 *)0x124a59;
  FUN_00125718(local_8);
  puStack_34 = &LAB_00124c37;
  uStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_38;
  puStack_30 = &stack0xfffffffc;
  do {
    iVar3 = 0;
    iVar6 = 2;
    iVar5 = 0x10000;
    if (0x10000 < uVar4) {
      thunk_FUN_00012820();
    }
    iVar5 = recv((uint)*(ushort *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x18),
                 (char *)(local_8 + 0x24 + uVar4),iVar5,iVar6);
    if (iVar5 == 0) {
      FUN_00013eac(local_c);
      FUN_00125770(local_8);
      FUN_0001397c();
      puVar1 = puStack_24;
      *in_FS_OFFSET = uStack_2c;
      puStack_24 = &LAB_00124c5b;
      puStack_28 = (undefined1 *)0x124c53;
      FUN_00013eac(&local_14,uStack_2c,puVar1);
      return;
    }
    if (iVar5 < 1) {
      iVar5 = WSAGetLastError();
      *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x4c) = iVar5;
      if (iVar5 == 0x2749) break;
      FUN_00125dbc(local_8,0x2733,&local_14);
    }
    else {
      iVar3 = 0;
      if (-1 < (int)(uVar4 + iVar5)) {
        local_10 = uVar4 + iVar5 + 1;
        uVar2 = 0;
        do {
          if (0x10000 < uVar2) {
            uVar2 = thunk_FUN_00012820();
          }
          if (*(char *)(local_8 + 0x24 + uVar2) == '\n') {
            iVar3 = local_8 + 0x24 + uVar2;
            break;
          }
          uVar2 = uVar2 + 1;
          local_10 = local_10 + -1;
        } while (local_10 != 0);
      }
      if ((iVar3 != 0) && (iVar3 < (int)(local_8 + 0x24 + iVar5 + uVar4))) break;
      FUN_00014460(local_c,iVar5 + uVar4);
      iVar6 = 0;
      iVar3 = FUN_000142fc(local_c);
      uVar2 = uVar4;
      if (*(uint *)(iVar3 + -4) <= uVar4) {
        iVar3 = thunk_FUN_00012820();
        uVar2 = extraout_EDX;
      }
      iVar3 = recv((uint)*(ushort *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x18),
                   (char *)(iVar3 + uVar2),iVar5,iVar6);
      uVar4 = uVar4 + iVar3;
    }
    iVar3 = 0;
    FUN_00060eb4(*(undefined4 *)PTR_DAT_004c9208);
  } while (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] == 0);
  if (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] == 0) {
    FUN_00014460(local_c,(iVar3 + 1) - (local_8 + 0x24));
    iVar6 = 0;
    iVar5 = ((iVar3 + 1) - (local_8 + 0x24)) - uVar4;
    iVar3 = FUN_000142fc(local_c);
    if (*(uint *)(iVar3 + -4) <= uVar4) {
      iVar3 = thunk_FUN_00012820();
    }
    recv((uint)*(ushort *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x18),
         (char *)(iVar3 + uVar4),iVar5,iVar6);
  }
  else {
    IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] = 0;
    FUN_0001c380(&DAT_00123dd0,1,"Socket readln aborted");
    FUN_000138dc();
    if (*(short *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x12) != 0) {
      (**(code **)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x10))
                (*(undefined4 *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x14),local_8);
    }
  }
  puVar1 = puStack_30;
  *in_FS_OFFSET = uStack_38;
  puStack_30 = (undefined1 *)0x124c3e;
  puStack_34 = (undefined1 *)0x124c36;
  FUN_00125770(local_8,uStack_38,puVar1);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_00124ff0
 * @başlık         Soket Alım İşçi İpliği (Socket Recv Worker Thread Loop)
 * @açıklama       Arka planda çalışan ve soketten sürekli veri okuyup tampona kopyalayan döngüdür.
 * @ofsetler       Soket referansı ve 0x10000 (65536) boyutunda okuma tamponu.
 * @paketler       Asenkron Ağ Alım Döngüsü.
 * 
 * @detaylı_analiz 
 * * 1. İstemci ağ ipliği (thread) soketi dinler.
 *  * 2. recv() ile gelen verileri 64KB'lık bloklar halinde okur.
 *  * 3. Okunan verileri kopyalama fonksiyonu (FUN_00023f24) ile ana tampon belleğe yazar.
 *******************************************************************************/
void FUN_00124ff0(int param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined2 extraout_var;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_40;
  undefined1 *puStack_3c;
  undefined1 *puStack_38;
  undefined4 uStack_34;
  undefined1 *puStack_30;
  undefined1 *puStack_2c;
  undefined4 uStack_28;
  undefined1 *puStack_24;
  undefined1 *puStack_20;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_14 = 0;
  puStack_20 = (undefined1 *)0x12500b;
  local_c = param_2;
  local_8 = param_1;
  FUN_000142e0(param_2);
  puStack_24 = &LAB_001251c6;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puStack_2c = (undefined1 *)0x125028;
  puStack_20 = &stack0xfffffffc;
  FUN_00125e88(local_8,8,"CaptureFile");
  pbVar1 = IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x74;
  pbVar1[0] = 0;
  pbVar1[1] = 0;
  pbVar1[2] = 0;
  pbVar1[3] = 0;
  puStack_2c = (undefined1 *)0x12503b;
  FUN_00125718(local_8);
  puStack_30 = &LAB_001251a1;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  puStack_38 = (undefined1 *)0xffff;
  puStack_3c = (undefined1 *)0x12505d;
  puStack_2c = &stack0xfffffffc;
  local_10 = FUN_00024290(&PTR_FUN_000204bc,1,local_c);
  puStack_3c = &LAB_00125139;
  uStack_40 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_40;
  puStack_38 = &stack0xfffffffc;
  while (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] == 0) {
    iVar3 = recv((uint)*(ushort *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x18),
                 (char *)(local_8 + 0x24),0x10000,0);
    if (0 < iVar3) {
      FUN_00023f24(local_10,local_8 + 0x24,iVar3);
      *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x74) =
           *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x74) + iVar3;
      if (*(short *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x7a) != 0) {
        (**(code **)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x78))
                  (*(undefined4 *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x7c),local_8);
      }
      FUN_00125718(local_8);
    }
    if (iVar3 == -1) {
      iVar4 = WSAGetLastError();
      *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x4c) = iVar4;
      if (iVar4 == 0x2749) break;
      FUN_00125dbc(local_8,CONCAT22(extraout_var,0x2733),&local_14);
    }
    if (iVar3 == 0) break;
    FUN_00060eb4(*(undefined4 *)PTR_DAT_004c9208);
  }
  puVar2 = puStack_38;
  *in_FS_OFFSET = uStack_40;
  puStack_38 = &LAB_00125140;
  puStack_3c = (undefined1 *)0x125138;
  FUN_00013144(local_10,uStack_40,puVar2);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_00125204
 * @başlık         Soket Uzunluk Okuyucusu (Socket Recv Length Reader)
 * @açıklama       Soketten belirli bir uzunluğa kadar veri okumayı garanti eden yardımcıdır.
 * @ofsetler       Parametre olarak okuma yapılacak tampon işaretçisi ve hedef boyut aktarılır.
 * @paketler       Blok Veri Okuma.
 * 
 * @detaylı_analiz 
 * * 1. Talep edilen uzunluk tamponda birikene kadar döngü içinde recv() çağrılır.
 *  * 2. WSA bağlantı kopma veya bloke olma hataları WSAGetLastError() ile kontrol edilir.
 *******************************************************************************/
void FUN_00125204(int param_1,undefined4 *param_2,int param_3)

{
  byte *pbVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  uint extraout_EDX;
  uint uVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_34;
  undefined1 *puStack_30;
  undefined1 *puStack_2c;
  undefined4 uStack_28;
  undefined1 *puStack_24;
  undefined1 *puStack_20;
  undefined4 local_10;
  uint local_c;
  int local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_10 = 0;
  puStack_24 = &LAB_001253d8;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puStack_2c = (undefined1 *)0x125236;
  local_8 = param_1;
  FUN_00125e88(param_1,8,"Capture String");
  puStack_2c = (undefined1 *)0x12523d;
  FUN_00013eac(param_2);
  pbVar1 = IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x74;
  pbVar1[0] = 0;
  pbVar1[1] = 0;
  pbVar1[2] = 0;
  pbVar1[3] = 0;
  puStack_2c = (undefined1 *)0x125250;
  FUN_00125718(local_8);
  puStack_30 = &LAB_001253bb;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  puStack_2c = &stack0xfffffffc;
  while (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] == 0) {
    if (param_3 != -1) {
      iVar4 = FUN_0001412c(*param_2);
      if (param_3 <= iVar4) break;
    }
    iVar4 = recv((uint)*(ushort *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x18),
                 (char *)(local_8 + 0x24),0x10000,0);
    if (iVar4 == 0) break;
    if (iVar4 < 2) {
      if (iVar4 == -1) {
        iVar4 = WSAGetLastError();
        *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x4c) = iVar4;
        if (iVar4 == 0x2749) break;
        FUN_00125dbc(local_8,0x2733,&local_10);
      }
    }
    else {
      local_c = FUN_0001412c(*param_2);
      FUN_00014460(param_2,local_c + iVar4);
      iVar3 = FUN_000142fc(param_2);
      uVar5 = local_c;
      if (*(uint *)(iVar3 + -4) <= local_c) {
        iVar3 = thunk_FUN_00012820();
        uVar5 = extraout_EDX;
      }
      FUN_000128fc(local_8 + 0x24,iVar3 + uVar5,iVar4);
      *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x74) =
           *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x74) + iVar4;
      if (*(short *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x7a) != 0) {
        (**(code **)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x78))
                  (*(undefined4 *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x7c),local_8);
      }
      FUN_00125718(local_8);
    }
    FUN_00060eb4(*(undefined4 *)PTR_DAT_004c9208);
  }
  if (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] != 0) {
    IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] = 0;
    FUN_0001c380(&DAT_00123dd0,1,"Socket capture aborted");
    FUN_000138dc();
    if (*(short *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x12) != 0) {
      (**(code **)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x10))
                (*(undefined4 *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x14),local_8);
    }
  }
  puVar2 = puStack_2c;
  *in_FS_OFFSET = uStack_34;
  puStack_2c = &LAB_001253c2;
  puStack_30 = (undefined1 *)0x1253ba;
  FUN_00125770(local_8,uStack_34,puVar2);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_00125f30
 * @başlık         Soket Veri Durumu Denetleyicisi (Socket MSG_PEEK Checker)
 * @açıklama       Soket tamponunda okunabilir veri olup olmadığını MSG_PEEK bayrağı ile denetler.
 * @ofsetler       Soket referansı ve flags=2 (MSG_PEEK).
 * @paketler       Soket Durum Denetimi.
 * 
 * @detaylı_analiz 
 * * 1. recv() fonksiyonu 1 bayt okuyacak ve flags=2 (MSG_PEEK) olacak şekilde çağrılır.
 *  * 2. Veri varsa 1 döndürür, soket boşsa 0 döndürür. Tampondan veri silinmez.
 *******************************************************************************/
undefined4 FUN_00125f30(int param_1)

{
  int iVar1;
  
  FUN_00125e88(param_1,8,"Data Available");
  iVar1 = recv((uint)*(ushort *)(IMAGE_SECTION_HEADER_00010270.Name + param_1 + 0x18),
               (char *)(param_1 + 0x24),1,2);
  if (0 < iVar1) {
    return 1;
  }
  return 0;
}

/*******************************************************************************
 * @fonksiyon      FUN_00079f88
 * @başlık         Soket Gönderim Kuyruğu Boşaltıcısı (Socket Queue Buffer Flusher)
 * @açıklama       Kuyrukta bekleyen giden paket tamponlarını soket üzerinden sunucuya pompalar.
 * @ofsetler       Kuyruk tampon işaretçisi (local_1014).
 * @paketler       Toplu Paket Gönderimi.
 * 
 * @detaylı_analiz 
 * * 1. Giden veri kuyruğu kontrol edilir.
 *  * 2. send() ile birikmiş baytlar sunucuya iletilir.
 *  * 3. Hata durumunda (0xffffffff) WSAGetLastError() kontrol edilerek gerekirse paket yeniden kuyruğa eklenir.
 *******************************************************************************/
undefined1 FUN_00079f88(int *param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined1 *puVar4;
  undefined4 uStack_1024;
  undefined1 *puStack_1020;
  undefined1 *puStack_101c;
  char local_1014 [16];
  int *piStack_1004;
  int local_14;
  int local_10;
  undefined1 local_9;
  int *local_8;
  
  puVar4 = &stack0xfffffffc;
  puStack_101c = (undefined1 *)0x79fa1;
  piStack_1004 = param_1;
  local_8 = param_1;
  FUN_00079784(param_1);
  puStack_1020 = &LAB_0007a0e8;
  uStack_1024 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1024;
  local_9 = 0;
  puStack_101c = &stack0xfffffffc;
  if (local_8[3] != 0) {
    if ((local_8[1] == -1) || (puStack_101c = &stack0xfffffffc, (char)local_8[2] == '\0')) {
      puStack_101c = &stack0xfffffffc;
      FUN_0001397c();
      return local_9;
    }
    do {
      while( true ) {
        local_10 = FUN_00023e98(local_8[3]);
        iVar2 = (**(code **)(*(int *)local_8[3] + 4))((int *)local_8[3],local_1014,0x1000);
        if (iVar2 < 1) {
          FUN_00079f40();
          goto LAB_0007a0ce;
        }
        iVar3 = send(local_8[1],local_1014,iVar2,0);
        if (iVar3 == -1) {
          local_14 = WSAGetLastError();
          if (local_14 == 0x2733) {
            FUN_00023ea8(local_8[3],local_10);
          }
          else {
            FUN_00013320(local_8,local_8,1,&local_14);
            (**(code **)(*local_8 + 8))(local_8,local_8[1]);
            FUN_00079f40();
            if ((char)local_8[10] != '\0') {
              FUN_0001c318(local_8,extraout_EDX & 0xffffff00,puVar4);
            }
          }
          goto LAB_0007a0ce;
        }
        if (iVar2 <= iVar3) break;
        FUN_00023ea8(local_8[3],local_10 + iVar3);
      }
      iVar2 = FUN_00023e98(local_8[3]);
      iVar3 = FUN_00023eb4(local_8[3]);
    } while (iVar2 != iVar3);
    FUN_00079f40();
LAB_0007a0ce:
    local_9 = 1;
  }
  puVar4 = puStack_101c;
  *in_FS_OFFSET = uStack_1024;
  puStack_101c = (undefined1 *)0x7a0ef;
  puStack_1020 = (undefined1 *)0x7a0e7;
  uVar1 = FUN_00079790(local_8,uStack_1024,puVar4);
  return uVar1;
}

/*******************************************************************************
 * @fonksiyon      FUN_0007a0fc
 * @başlık         Soket Doğrudan Gönderim Sarmalayıcısı (Socket Immediate Send Wrapper)
 * @açıklama       Kuyruğa almadan veriyi doğrudan send() ile sunucuya yollar.
 * @ofsetler       Soket ID ve yollanacak ham bayt dizisi.
 * @paketler       Anlık Paket Gönderimi.
 * 
 * @detaylı_analiz 
 * * 1. Gelen parametre doğrudan send() API'sine iletilir.
 *  * 2. Gönderim başarısız olursa soket hatası (WSAGetLastError) işlenir ve soket kapatılabilir.
 *******************************************************************************/
void FUN_0007a0fc(int *param_1,char *param_2,int param_3)

{
  undefined1 *puVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_4c;
  undefined1 *puStack_48;
  undefined1 *puStack_44;
  undefined4 uStack_40;
  undefined1 *puStack_3c;
  undefined1 *puStack_38;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  int local_20;
  undefined1 local_1c;
  undefined *local_18;
  undefined1 local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  puStack_38 = &stack0xfffffffc;
  local_2c = 0;
  puStack_3c = &LAB_0007a21e;
  uStack_40 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_40;
  puStack_44 = (undefined1 *)0x7a126;
  local_8 = param_1;
  FUN_00079784(param_1);
  puStack_48 = &LAB_0007a201;
  uStack_4c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_4c;
  local_c = 0;
  if ((char)local_8[2] == '\0') {
    puStack_44 = &stack0xfffffffc;
    FUN_0001397c();
    puVar1 = puStack_38;
    *in_FS_OFFSET = uStack_40;
    puStack_38 = &LAB_0007a225;
    puStack_3c = (undefined1 *)0x7a21d;
    FUN_00013eac(&local_2c,uStack_40,puVar1);
    return;
  }
  puStack_44 = &stack0xfffffffc;
  local_c = send(local_8[1],param_2,param_3,0);
  if (local_c == -1) {
    local_10 = WSAGetLastError();
    if (local_10 != 0x2733) {
      FUN_00013320(local_8,local_8,1,&local_10);
      (**(code **)(*local_8 + 8))(local_8,local_8[1]);
      if (local_10 != 0) {
        FUN_0001bb34(local_10,&local_2c);
        local_28 = local_2c;
        local_24 = 0xb;
        local_20 = local_10;
        local_1c = 0;
        local_18 = &DAT_0007a238;
        local_14 = 0xb;
        FUN_0001c478(&DAT_00078bcc,1,PTR_PTR_004c94bc,2,&local_28);
        FUN_000138dc();
      }
    }
  }
  puVar1 = puStack_44;
  *in_FS_OFFSET = uStack_4c;
  puStack_44 = (undefined1 *)0x7a208;
  puStack_48 = (undefined1 *)0x7a200;
  FUN_00079790(local_8,uStack_4c,puVar1);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_00124df4
 * @başlık         Soket Gönderim İşçi İpliği (Socket Send Worker Thread Loop)
 * @açıklama       Arka planda çalışan ve gönderim sırasındaki paketleri sürekli sunucuya pompalayan döngüdür.
 * @ofsetler       0x10000 (65536) boyutunda yazma tamponu.
 * @paketler       Asenkron Ağ Gönderim Döngüsü.
 * 
 * @detaylı_analiz 
 * * 1. Gönderim ipliği giden sırasını kontrol eder.
 *  * 2. send() çağrısı ile veriler parça parça ağa yazılır.
 *  * 3. Gönderilen veri miktarı kaydedilir ve sıradan düşürülür.
 *******************************************************************************/
void FUN_00124df4(int param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined2 extraout_var;
  int iVar5;
  undefined4 *in_FS_OFFSET;
  int flags;
  undefined4 uStack_38;
  undefined1 *puStack_34;
  undefined1 *puStack_30;
  undefined4 uStack_2c;
  undefined1 *puStack_28;
  undefined1 *puStack_24;
  undefined4 local_14;
  int *local_10;
  undefined4 local_c;
  int local_8;
  
  local_14 = 0;
  puStack_24 = (undefined1 *)0x124e10;
  local_c = param_2;
  local_8 = param_1;
  FUN_000142e0(param_2);
  puStack_28 = &LAB_00124fb1;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  puStack_30 = (undefined1 *)0x124e2d;
  puStack_24 = &stack0xfffffffc;
  FUN_00125e88(local_8,8,"SendFile");
  puStack_30 = (undefined1 *)0x0;
  puStack_34 = (undefined1 *)0x124e3e;
  local_10 = (int *)FUN_00024290(&PTR_FUN_000204bc,1,local_c);
  puStack_34 = &LAB_00124f41;
  uStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_38;
  puStack_30 = &stack0xfffffffc;
  do {
    if (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] == 0) {
      iVar2 = (**(code **)(*local_10 + 4))(local_10,local_8 + 0x24,0x10000);
      iVar5 = iVar2;
      while( true ) {
        flags = 0;
        uVar3 = iVar2 - iVar5;
        iVar4 = iVar5;
        if (0x10000 < uVar3) {
          uVar3 = thunk_FUN_00012820();
        }
        iVar4 = send((uint)*(ushort *)(IMAGE_SECTION_HEADER_00010270.Name + local_8 + 0x18),
                     (char *)(local_8 + 0x24 + uVar3),iVar4,flags);
        if (iVar4 == 0) break;
        if (iVar4 < 0) {
          FUN_00125dbc(local_8,CONCAT22(extraout_var,0x2733),&local_14);
        }
        else {
          iVar5 = iVar5 - iVar4;
          *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x44) =
               *(int *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x44) + iVar4;
          if (*(short *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x82) != 0) {
            (**(code **)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x80))
                      (*(undefined4 *)(IMAGE_DOS_HEADER_00010000.e_program + local_8 + 0x84),local_8
                      );
          }
        }
        FUN_00060eb4(*(undefined4 *)PTR_DAT_004c9208);
        if ((iVar5 == 0) || (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] != 0)) break;
      }
    }
    iVar5 = FUN_00023e98(local_10);
    iVar2 = FUN_00023eb4(local_10);
    puVar1 = puStack_30;
    if ((iVar5 == iVar2) || (IMAGE_DOS_HEADER_00010000.e_program[local_8 + 0x48] != 0)) {
      *in_FS_OFFSET = uStack_38;
      puStack_30 = &LAB_00124f48;
      puStack_34 = (undefined1 *)0x124f40;
      FUN_00013144(local_10,uStack_38,puVar1);
      return;
    }
  } while( true );
}

/*******************************************************************************
 * @fonksiyon      FUN_00115a38
 * @başlık         Ana Paket Dağıtıcısı 1 (Main Packet Dispatcher 1)
 * @açıklama       Sunucudan gelen tüm paketlerin OPCODE değerlerini çözümler ve ilgili alt sistemlere yönlendirir.
 * @ofsetler       param_1 ağ paketi nesnesidir.
 * @paketler       Ana Ağ Paket Dağıtım Yöneticisi.
 * 
 * @detaylı_analiz 
 * * 1. Gelen paketin ilk baytı olan OPCODE değeri okunur.
 *  * 2. switch-case yapısı ile Chat (0x02), Movement (0x06), Action (0x13), Interaction (0x14), Item (0x17), Trade (0x19), Quest (0x27), Battle (0x32) ve Login (0x3f) sistemlerine yönlendirilir.
 *******************************************************************************/
undefined4 FUN_00115a38(undefined1 param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  switch(param_1) {
  case 1:
    return 0x1b;
  case 2:
    return 0x31;
  case 3:
    return 0x32;
  case 4:
    return 0x33;
  case 5:
    return 0x34;
  case 6:
    return 0x35;
  case 7:
    return 0x36;
  case 8:
    return 0x37;
  case 9:
    return 0x38;
  case 10:
    return 0x39;
  case 0xb:
    return 0x30;
  case 0xd:
    return 0x3d;
  case 0xe:
    return 8;
  case 0xf:
    return 9;
  case 0x10:
    return 0x51;
  case 0x11:
    return 0x57;
  case 0x12:
    return 0x45;
  case 0x13:
    return 0x52;
  case 0x14:
    return 0x54;
  case 0x15:
    return 0x59;
  case 0x16:
    return 0x55;
  case 0x17:
    return 0x49;
  case 0x18:
    return 0x4f;
  case 0x19:
    return 0x50;
  case 0x1a:
    return 0x5b;
  case 0x1b:
    return 0x5d;
  case 0x1c:
    return 0xd;
  case 0x1d:
    return 0x11;
  case 0x1e:
    return 0x41;
  case 0x1f:
    return 0x53;
  case 0x20:
    return 0x44;
  case 0x21:
    return 0x46;
  case 0x22:
    return 0x47;
  case 0x23:
    return 0x48;
  case 0x24:
    return 0x4a;
  case 0x25:
    return 0x4b;
  case 0x26:
    return 0x4c;
  case 0x27:
    return 0x3b;
  case 0x28:
    return 0x27;
  case 0x2a:
    return 0x10;
  case 0x2b:
    return 0x5c;
  case 0x2c:
    return 0x5a;
  case 0x2d:
    return 0x58;
  case 0x2e:
    return 0x43;
  case 0x2f:
    return 0x56;
  case 0x30:
    return 0x42;
  case 0x31:
    return 0x4e;
  case 0x32:
    return 0x4d;
  case 0x33:
    return 0x2c;
  case 0x34:
    return 0x2e;
  case 0x35:
    return 0x2f;
  case 0x36:
    return 0x10;
  case 0x37:
    return 0x2a;
  case 0x38:
    return 0x12;
  case 0x39:
    return 0x20;
  case 0x3a:
    return 0x14;
  case 0x3b:
    return 0x70;
  case 0x3c:
    return 0x71;
  case 0x3d:
    return 0x72;
  case 0x3e:
    return 0x73;
  case 0x3f:
    return 0x74;
  case 0x40:
    return 0x75;
  case 0x41:
    return 0x76;
  case 0x42:
    return 0x77;
  case 0x43:
    return 0x78;
  case 0x44:
    return 0x79;
  case 0x45:
    return 0x90;
  case 0x46:
    return 0x91;
  case 0x47:
    return 0x67;
  case 0x48:
    return 0x68;
  case 0x49:
    return 0x69;
  case 0x4a:
    return 0x6d;
  case 0x4b:
    return 100;
  case 0x4c:
    return 0x65;
  case 0x4d:
    return 0x66;
  case 0x4e:
    return 0x6b;
  case 0x4f:
    return 0x61;
  case 0x50:
    return 0x62;
  case 0x51:
    return 99;
  case 0x52:
    return 0x60;
  case 0x53:
    return 0x6e;
  case 0x57:
    return 0x7a;
  case 0x58:
    return 0x7b;
  case 0x9c:
    return 0xd;
  case 0x9d:
    return 0x11;
  case 0xb5:
    return 0x6f;
  case 0xb8:
    return 0x12;
  case 199:
    return 0x24;
  case 200:
    return 0x26;
  case 0xc9:
    return 0x21;
  case 0xcb:
    return 0x25;
  case 0xcd:
    return 0x27;
  case 0xcf:
    return 0x23;
  case 0xd0:
    return 0x28;
  case 0xd1:
    return 0x22;
  case 0xd2:
    return 0x2d;
  case 0xd3:
    return 0x2e;
  case 0xdb:
    return 0x5b;
  case 0xdc:
    return 0x5c;
  case 0xdd:
    uVar1 = 0x5d;
  }
  return uVar1;
}

/*******************************************************************************
 * @fonksiyon      FUN_0010e218
 * @başlık         Ana Paket Dağıtıcısı 2 (Main Packet Dispatcher 2)
 * @açıklama       Oyun içi arayüz ve form etkileşimlerine ait paketleri işleyen ikincil dağıtıcıdır.
 * @ofsetler       Arayüz bileşen referansları.
 * @paketler       Arayüz Paket Dağıtım Yöneticisi.
 * 
 * @detaylı_analiz 
 * * 1. Arayüz eylemleriyle eşleşen OPCODE (Action 19, Interaction 20, Item 23, Trade 25, Battle 50) değerlerini kontrol eder.
 *  * 2. Form çizimleri ve yerel arayüz verilerini günceller.
 *******************************************************************************/
undefined4 FUN_0010e218(undefined4 param_1,undefined1 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  FUN_0049eb9c();
  cVar1 = FUN_0010e1ac();
  switch(param_2) {
  case 0:
    uVar2 = 0;
    break;
  case 1:
    if ((((byte)(cVar1 - 2U) < 3) || (cVar1 == '\v')) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 2:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 3:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 4:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 2)) {
      uVar2 = 1;
    }
    break;
  case 5:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 6:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 7:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == 'i')) {
      uVar2 = 1;
    }
    break;
  case 8:
    if ((((byte)(cVar1 - 2U) < 2) || (cVar1 == 'i')) || (cVar1 == 'k')) {
      uVar2 = 1;
    }
    break;
  case 9:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 2)) {
      uVar2 = 1;
    }
    break;
  case 10:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0xb:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == 'i')) {
      uVar2 = 1;
    }
    break;
  case 0xc:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0xd:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0xe:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0xf:
    if (((cVar1 == '\x02') || (cVar1 == 'i')) || (cVar1 == 'k')) {
      uVar2 = 1;
    }
    break;
  case 0x10:
    if (((cVar1 == '\x02') || (cVar1 == 'i')) || (cVar1 == 'k')) {
      uVar2 = 1;
    }
    break;
  case 0x11:
    if ((cVar1 == '\x02') || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x12:
    if ((cVar1 == '\x02') || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x13:
    if ((cVar1 == '\x02') || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x14:
    if ((byte)(cVar1 + 0x97U) < 4) {
      uVar2 = 1;
    }
    break;
  case 0x15:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x16:
    if (((byte)(cVar1 + 0x97U) < 2) || (cVar1 == 'l')) {
      uVar2 = 1;
    }
    break;
  case 0x17:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x18:
    if ((cVar1 == '\x02') || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x19:
    if ((cVar1 == '\x02') || ((byte)(cVar1 + 0x97U) < 2)) {
      uVar2 = 1;
    }
    break;
  case 0x1a:
    if ((cVar1 == '\x02') || ((byte)(cVar1 + 0x97U) < 2)) {
      uVar2 = 1;
    }
    break;
  case 0x1b:
    if ((cVar1 == '\x02') || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x1c:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == 'i')) {
      uVar2 = 1;
    }
    break;
  case 0x1d:
    if ((cVar1 == '\x02') || (cVar1 == 'i')) {
      uVar2 = 1;
    }
    break;
  case 0x1e:
    if ((byte)(cVar1 + 0x97U) < 6) {
      uVar2 = 1;
    }
    break;
  default:
    uVar2 = 0;
    break;
  case 0x32:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == '\v')) {
      uVar2 = 1;
    }
    break;
  case 0x33:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == '\v')) {
      uVar2 = 1;
    }
    break;
  case 0x46:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == '\v')) {
      uVar2 = 1;
    }
    break;
  case 0x47:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == '\v')) {
      uVar2 = 1;
    }
    break;
  case 0x48:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == '\v')) {
      uVar2 = 1;
    }
    break;
  case 0x49:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == '\v')) {
      uVar2 = 1;
    }
    break;
  case 100:
    if (((byte)(cVar1 - 2U) < 2) || (cVar1 == '\v')) {
      uVar2 = 1;
    }
    break;
  case 0x65:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x66:
    if ((((byte)(cVar1 - 2U) < 3) || (cVar1 == '\v')) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x67:
    if (((byte)(cVar1 - 2U) < 2) || ((byte)(cVar1 + 0x97U) < 4)) {
      uVar2 = 1;
    }
    break;
  case 0x68:
    if ((byte)(cVar1 - 2U) < 2) {
      uVar2 = 1;
    }
    break;
  case 0x69:
    if ((byte)(cVar1 - 2U) < 2) {
      uVar2 = 1;
    }
    break;
  case 0x6a:
    if ((byte)(cVar1 - 2U) < 2) {
      uVar2 = 1;
    }
  }
  return uVar2;
}

