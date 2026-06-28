/**
 * quest_journal.c - WLO Görev Günlüğü, NPC Diyalog Arayüzleri ve Opcode 39/20 Görev Akışları.
 * Extracted from aLogin.exe decompiled C code.
 */

/*******************************************************************************
 * @fonksiyon      FUN_0030859c
 * @başlık         Görev Günlüğü Form Yükleyici (Quest Journal Form Loader)
 * @açıklama       Görev günlüğü arayüzünü (form_taskview_1) başlatır ve listeleri çeker.
 * @ofsetler       Arayüz referans işaretçileri.
 * @paketler       Görev Listesi Talebi (Opcode 39 Sub-opcode 1).
 * 
 * @detaylı_analiz 
 * * 1. form_taskview_1 arayüz bileşenleri belleğe yüklenir.
 *  * 2. Görev listesini sunucudan istemek için Opcode 39 Sub 1 paketi tetiklenir.
 *******************************************************************************/
void FUN_0030859c(int *param_1,char param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 extraout_DL;
  undefined1 uVar5;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined *puVar8;
  undefined4 uStack_4c;
  undefined1 *puStack_48;
  undefined1 *puStack_44;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 uStack_8;
  
  uStack_8 = 0;
  local_c = 0;
  local_10 = 0;
  local_14 = 0;
  local_18 = 0;
  local_1c = 0;
  local_20 = 0;
  local_24 = 0;
  uVar5 = 0;
  if (param_2 != '\0') {
    puStack_44 = (undefined1 *)0x3085b8;
    param_1 = (int *)FUN_00013484();
    uVar5 = extraout_DL;
  }
  uStack_8 = CONCAT13(uVar5,(undefined3)uStack_8);
  puStack_48 = &LAB_00308c8e;
  uStack_4c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_4c;
  puStack_44 = &stack0xfffffffc;
  FUN_0048208c(param_1,0);
  (**(code **)(*param_1 + 8))(param_1,"form_taskview_1",0x50,0x16f,0x1b0,0,0,1,0x16f,0x1b0,0x3c);
  param_1[0x6a] = 0;
  piVar1 = (int *)FUN_00485a1c(&PTR_LAB_0047f938,1,param_1);
  param_1[0x5b] = (int)piVar1;
  FUN_00486d68(piVar1,0xeb,0x36,0x14,0xb4);
  *(undefined1 *)((int)piVar1 + 0x169) = 0;
  (**(code **)(*piVar1 + 4))(piVar1,CONCAT22(extraout_var,0x15));
  FUN_00485be4(param_1[0x5b],0);
  piVar1 = (int *)FUN_00308530(&PTR_LAB_00307fc0,1,param_1);
  param_1[0x5f] = (int)piVar1;
  (**(code **)(*piVar1 + 0x70))(piVar1,0x28,0x39,0xf0,0xaa);
  FUN_0048c810(piVar1,0x18);
  FUN_0048c35c(piVar1,0xf0);
  (**(code **)(*piVar1 + 4))(piVar1,CONCAT22(extraout_var_00,0xfc00));
  piVar1[0x3f] = (int)param_1;
  piVar1[0x3e] = (int)&LAB_0030910c;
  *(undefined1 *)(piVar1 + 0x4f) = 0;
  *(undefined1 *)(piVar1 + 0x5c) = 1;
  piVar1[0x4c] = -0x7ffffff1;
  *(undefined1 *)((int)piVar1 + 0x13d) = 0;
  piVar1[0x4d] = 0xffff;
  piVar1 = (int *)FUN_004909dc(&PTR_LAB_0047ed20,1,param_1);
  param_1[0x60] = (int)piVar1;
  (**(code **)(*piVar1 + 0x70))(piVar1,0xdb,0x55,0xee,0xbe);
  (**(code **)(*piVar1 + 4))(piVar1,0);
  *(undefined1 *)(piVar1 + 0x4f) = 0;
  piVar1 = (int *)FUN_0048cc5c(&PTR_LAB_0047ea38,1,param_1);
  param_1[0x62] = (int)piVar1;
  FUN_0048d850(piVar1,"bar_H4",0,100,9,0);
  FUN_0048d8d0(piVar1,9,9);
  (**(code **)(*piVar1 + 8))(piVar1,"rail_H4",0xff,0x98,0xd,0,0,1,0xe6,9,0x37);
  *(undefined1 *)((int)piVar1 + 0xb9) = 0;
  FUN_0048c2f0(param_1[0x5f],param_1[0x62]);
  (**(code **)(*(int *)param_1[0x62] + 0x24))();
  piVar1 = (int *)FUN_0048cc5c(&PTR_LAB_0047ea38,1,param_1);
  param_1[99] = (int)piVar1;
  FUN_0048d850(piVar1,"bar_H4",0,100,9,0);
  FUN_0048d8d0(piVar1,9,9);
  (**(code **)(*piVar1 + 8))(piVar1,"rail_H4",0x235,0x98,0xd,0,0,1,200,9,0x52);
  *(undefined1 *)((int)piVar1 + 0xb9) = 0;
  FUN_0048c2f0(param_1[0x60],param_1[99]);
  (**(code **)(*(int *)param_1[99] + 0x24))();
  piVar1 = (int *)FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x68] = (int)piVar1;
  (**(code **)(*piVar1 + 8))(piVar1,"Arrow_L3",0x4a,0x15,0x15,0,0,1,0x15,0x15,0x12a);
  piVar1[0x15] = (int)param_1;
  piVar1[0x14] = (int)&LAB_00308db0;
  piVar1 = (int *)FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x69] = (int)piVar1;
  (**(code **)(*piVar1 + 8))(piVar1,"Arrow_R3",0x89,0x15,0x15,0,0,1,0x15,0x15,0x12a);
  piVar1[0x15] = (int)param_1;
  piVar1[0x14] = (int)FUN_00308dbc;
  piVar1 = (int *)FUN_00485a1c(&PTR_LAB_0047f938,1,param_1);
  param_1[0x5d] = (int)piVar1;
  FUN_00486d68(piVar1,0xfa,0x19,0x14,100);
  (**(code **)(*piVar1 + 4))(piVar1,CONCAT22(extraout_var_01,0xffff));
  FUN_00016160(PTR_PTR_004c8fd0,&local_c);
  FUN_00485be4(param_1[0x5d],local_c);
  piVar1 = (int *)FUN_00488540(&PTR_LAB_0047ebe8,1,param_1);
  param_1[0x61] = (int)piVar1;
  (**(code **)(*piVar1 + 0x70))(piVar1,0xfa,0x32,300,100);
  (**(code **)(*piVar1 + 4))(piVar1,CONCAT22(extraout_var_02,0xfc00));
  piVar1 = (int *)FUN_00485a1c(&PTR_LAB_0047f938,1,param_1);
  param_1[0x5e] = (int)piVar1;
  FUN_00486d68(piVar1,0x50,300,0x14,0x46);
  (**(code **)(*piVar1 + 4))(piVar1,CONCAT22(extraout_var_03,0x1f));
  *(undefined1 *)(piVar1 + 0x56) = 1;
  *(undefined1 *)((int)piVar1 + 0x169) = 0;
  param_1[0x4c] = *(int *)(param_1[0x62] + 0xe4) / *(int *)(param_1[0x62] + 0xe8);
  if (0 < *(int *)(param_1[0x62] + 0xe4) % *(int *)(param_1[0x62] + 0xe8)) {
    param_1[0x4c] = param_1[0x4c] + 1;
  }
  param_1[0x4d] = 1;
  FUN_0001953c(1,&local_14);
  puVar8 = &DAT_00308d20;
  uVar7 = local_14;
  FUN_0001953c(param_1[0x4c],&local_18);
  uVar6 = local_18;
  FUN_000141ec(&local_10,3);
  FUN_00485be4(param_1[0x5e],local_10);
  (**(code **)(**(int **)(param_1[0x5e] + 0x14c) + 0xc))
            (*(int **)(param_1[0x5e] + 0x14c),0,&local_1c,uVar6,puVar8,uVar7);
  uVar2 = FUN_0001412c(local_1c);
  *(uint *)(param_1[0x5e] + 0x20) = uVar2 << 3;
  iVar3 = param_1[0x5e];
  *(uint *)(iVar3 + 0x18) = (uVar2 & 0x1fffffff) * -4 + 0x73;
  iVar3 = FUN_004853d8(&PTR_LAB_0047f28c,CONCAT31((int3)((uint)iVar3 >> 8),1),param_1);
  param_1[0x65] = iVar3;
  piVar1 = (int *)param_1[0x65];
  (**(code **)(*piVar1 + 8))(piVar1,"Btn_Close_s_1",0x17e,0x12,0x12,0,0,1,0x12,0x12,0x18);
  piVar1[0x15] = (int)param_1;
  piVar1[0x14] = *(int *)(*param_1 + 0x24);
  *(undefined1 *)((int)piVar1 + 0xb9) = 0;
  *(undefined1 *)((int)piVar1 + 0xca) = 1;
  FUN_00480734(piVar1,0);
  iVar3 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[100] = iVar3;
  piVar1 = (int *)param_1[100];
  (**(code **)(*piVar1 + 8))(piVar1,"Btn_Close_1",0xbb,0x14,0x38,0,0,1,0x14,0x38,0x14c);
  piVar1[0x15] = (int)param_1;
  piVar1[0x14] = *(int *)(*param_1 + 0x24);
  *(undefined1 *)((int)piVar1 + 0xb9) = 0;
  *(undefined1 *)((int)piVar1 + 0xca) = 1;
  FUN_00480734(piVar1,0);
  iVar3 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x66] = iVar3;
  piVar1 = (int *)param_1[0x66];
  (**(code **)(*piVar1 + 8))(piVar1,"Btn_Delete_1",0x122,0x14,0x38,0,0,1,0x14,0x38,0x14c);
  piVar1[0x15] = (int)param_1;
  piVar1[0x14] = (int)&LAB_0030c000;
  *(undefined1 *)((int)piVar1 + 0xb9) = 0;
  *(undefined1 *)((int)piVar1 + 0xca) = 1;
  FUN_00480734(piVar1,0);
  FUN_004802c0(piVar1,0);
  iVar3 = FUN_004853d8(&PTR_LAB_0047f28c,1,param_1);
  param_1[0x67] = iVar3;
  piVar1 = (int *)param_1[0x67];
  uVar7 = 0;
  uVar6 = 0x14;
  (**(code **)(*piVar1 + 8))(piVar1,"btn_Model_1",0x14a,0x14,0x38,0,0,1,0x14,0x38,0x14c);
  piVar1[0x15] = (int)param_1;
  piVar1[0x14] = (int)&LAB_0030c178;
  *(undefined1 *)((int)piVar1 + 0xb9) = 0;
  FUN_004802c0(piVar1,0);
  FUN_00016160(PTR_PTR_004c86b8,&local_20);
  FUN_004856e0(piVar1,local_20);
  iVar3 = 0;
  do {
    iVar4 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,0);
    param_1[iVar3 + 0x4e] = iVar4;
    iVar3 = iVar3 + 1;
  } while (iVar3 != 10);
  FUN_004802c0(param_1[0x5d],0);
  FUN_004802c0(param_1[0x61],0);
  iVar3 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"icon_start_1");
  param_1[0x6b] = iVar3;
  if (param_1[0x6b] == -1) {
    FUN_00014178(&local_24,*(undefined4 *)PTR_DAT_004c8c60,"menu\\skins\\default\\",1,0);
    FUN_0047caa8(*(undefined4 *)PTR_DAT_004c8a78,local_24,"icon_start_1");
    iVar3 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"icon_start_1");
    param_1[0x6b] = iVar3;
  }
  *in_FS_OFFSET = uVar6;
  FUN_00013ed0(&local_24,7,uVar7,&LAB_00308c95);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0041892c
 * @başlık         Görev İptal Paketi Göndericisi (Abandon Quest Sender)
 * @açıklama       Aktif bir görevi bırakma isteğini sunucuya gönderir.
 * @ofsetler       param_1 soket referansı, param_2 iptal edilmek istenen görev ID'si.
 * @paketler       Opcode 39 Sub-opcode 7 (Abandon Quest).
 * 
 * @detaylı_analiz 
 * * 1. Görev ID'si paket tamponuna yazılır.
 *  * 2. Sunucuya Opcode 39 Sub 7 yollanır.
 *******************************************************************************/
void FUN_0041892c(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0x27,7,0);
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0041894c
 * @başlık         Klan/Birlik Üye Listesi Talebi (Guild Member List Requester)
 * @açıklama       Görev veya klan arayüzü için klan üye listesini çeker.
 * @ofsetler       Soket referansı.
 * @paketler       Opcode 39 Sub-opcode 12 (Guild Members Request).
 * 
 * @detaylı_analiz 
 * * 1. Sunucuya klan üye detaylarını istemek için Opcode 39 Sub 12 paketi yollanır.
 *******************************************************************************/
void FUN_0041894c(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0x27,0xc,0);
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0041896c
 * @başlık         Görev Detay Sorgulama 11 (Quest Action sub-11)
 * @açıklama       Görev arayüzünde detaylı durum sorgulaması yollar.
 * @ofsetler       Soket referansı.
 * @paketler       Opcode 39 Sub-opcode 11.
 * 
 * @detaylı_analiz 
 * * 1. Sunucuya görev durum sorgusu yollanır.
 *******************************************************************************/
void FUN_0041896c(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0x27,0xb,0);
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0041898c
 * @başlık         Görev Detay Sorgulama 10 (Quest Action sub-10)
 * @açıklama       Görev arayüzünde alternatif durum veya takip sorgulaması yollar.
 * @ofsetler       Soket referansı.
 * @paketler       Opcode 39 Sub-opcode 10.
 * 
 * @detaylı_analiz 
 * * 1. Sunucuya görev takip/güncelleme paketi yollanır.
 *******************************************************************************/
void FUN_0041898c(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0x27,10,0);
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0041a110
 * @başlık         Görev Günlüğü Durum Kaydı (Quest Action sub-16)
 * @açıklama       Görev günlüğünde yapılan filtre veya arama ayarlarını günceller.
 * @ofsetler       Soket referansı ve filtre değerleri.
 * @paketler       Opcode 39 Sub-opcode 16.
 * 
 * @detaylı_analiz 
 * * 1. Görev günlüğü arama/filtre parametreleri paketlenir.
 *  * 2. Sunucuya Opcode 39 Sub 16 yollanır.
 *******************************************************************************/
void FUN_0041a110(int param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  *(undefined1 *)(param_1 + 0x85) = param_4;
  *(undefined1 *)(param_1 + 0x84) = param_3;
  FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0x27,0x10,0);
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined1 *)(param_1 + 0x85) = 0;
  *(undefined1 *)(param_1 + 0x84) = 0;
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_004896f4
 * @başlık         NPC Diyalog Arayüz Yöneticisi (NPC Dialogue Form Manager)
 * @açıklama       NPC ile konuşurken diyalog kutularını (Form_Talk_1, Form_Talk_2, Form_Talk_3) yükler ve yönetir.
 * @ofsetler       Diyalog türlerine göre arayüz butonları ve karakter portresi ofsetleri.
 * @paketler       Diyalog ve Seçim Paketleri (Opcode 20).
 * 
 * @detaylı_analiz 
 * * 1. Sunucudan gelen diyalog paketi türüne göre Form_Talk_1 (tek seçenek), Form_Talk_2 (çoktan seçmeli diyalog) veya Form_Talk_3 (chat balonu) oluşturulur.
 *  * 2. Diyalog seçenekleri butonlara atanır.
 *  * 3. Oyuncu seçim yaptığında sunucuya cevap paketi gönderilir.
 *******************************************************************************/
void FUN_004896f4(int *param_1,undefined4 param_2,int param_3,undefined1 param_4,char param_5)

{
  int iVar1;
  undefined1 *puVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_34;
  undefined1 *puStack_30;
  undefined1 *puStack_2c;
  int local_14;
  int local_10;
  undefined4 local_8;
  
  puStack_2c = (undefined1 *)0x48970d;
  local_8 = param_2;
  FUN_000142e0(param_2);
  puStack_30 = &LAB_0048a6b8;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  *(undefined1 *)(param_1 + 0xad) = 0;
  cVar3 = *(char *)(*(int *)PTR_DAT_004c91d4 + 0x1d);
  if ((cVar3 == '\x01') || ((byte)(cVar3 - 3U) < 2)) {
    local_14 = 0x19;
  }
  else {
    local_14 = 0;
  }
  if ((cVar3 == '\0') || (cVar3 == '\x02')) {
    *PTR_DAT_004c8db0 = 0;
  }
  *(undefined1 *)(param_1 + 0xaa) = 0;
  puStack_2c = &stack0xfffffffc;
  FUN_004919e4(param_1,&local_8);
  *(undefined1 *)((int)param_1 + 0x2a9) = 0;
  *(undefined1 *)((int)param_1 + 0x2aa) = 0;
  if (param_1 == *(int **)PTR_DAT_004c935c) {
    *(undefined1 *)(*(int *)PTR_DAT_004c935c + 0x31b) = *(undefined1 *)((int)param_1 + 0x2a9);
    *(undefined1 *)(*(int *)PTR_DAT_004c935c + 0x31c) = *(undefined1 *)((int)param_1 + 0x2aa);
  }
  else {
    *(undefined1 *)(*(int *)PTR_DAT_004c8838 + 0x31b) = *(undefined1 *)((int)param_1 + 0x2a9);
    *(undefined1 *)(*(int *)PTR_DAT_004c8838 + 0x31c) = *(undefined1 *)((int)param_1 + 0x2aa);
  }
  if (param_1 == *(int **)PTR_DAT_004c8838) {
    uVar4 = FUN_0049e7c4(CONCAT31((int3)((uint)PTR_DAT_004c8838 >> 8),
                                  *(undefined1 *)(*(int *)(*(int *)PTR_DAT_004c8838 + 0x30c) + 8)),
                         *(undefined1 *)(*(int *)(*(int *)PTR_DAT_004c8838 + 0x30c) + 0xb4));
    if ((((*PTR_DAT_004c8db0 == '\0') &&
         (*(char *)(*(int *)(*(int *)PTR_DAT_004c8838 + 0x30c) + 0xb1) == '\x01')) &&
        (*(char *)(*(int *)PTR_DAT_004c8838 + 0x319) != '\0')) &&
       (((char)param_1[0xaa] == '\0' &&
        (*(short *)(PTR_DAT_004c9650 + (uVar4 & 0xff) * 0xe + 4) ==
         *(short *)(*(int *)(*(int *)(*(int *)PTR_DAT_004c8838 + 0x30c) + 0x6c) + 4))))) {
      *(undefined1 *)(param_1 + 0xaa) = 1;
    }
    *(char *)(*(int *)PTR_DAT_004c8838 + 0x31a) = (char)param_1[0xaa];
    if (((*(char *)(*(int *)PTR_DAT_004c8838 + 0x331) == '\0') && (*PTR_DAT_004c8db0 == '\0')) &&
       ((char)param_1[0xaa] == '\0')) {
      if (*(char *)(*(int *)PTR_DAT_004c8838 + 0x38c) == '\x01') {
        (**(code **)(*param_1 + 8))(param_1,"panel22",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,0x19);
      }
      else {
        (**(code **)(*param_1 + 8))(param_1,"Form_Talk_3",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,0x19);
      }
      FUN_004915d0(param_1,0x32,0x1f,0x1f,0x32);
      *(undefined4 *)(*(int *)PTR_DAT_004c8838 + 0x294) = 0x28;
      (**(code **)(**(int **)PTR_DAT_004c8838 + 0x94))();
      FUN_00490470(*(undefined4 *)PTR_DAT_004c8838,1);
    }
    else {
      if (*(char *)(*(int *)PTR_DAT_004c8838 + 0x38c) == '\x01') {
        (**(code **)(**(int **)PTR_DAT_004c8838 + 8))
                  (*(int **)PTR_DAT_004c8838,"Form_Talk_1",0x23,0xa9,0x300,0,0,1,0xa9,0x300,
                   local_14 + 0x195);
      }
      else {
        (**(code **)(**(int **)PTR_DAT_004c8838 + 8))
                  (*(int **)PTR_DAT_004c8838,"Form_Talk_2",0x23,0xa9,0x300,0,0,1,0xa9,0x300,
                   local_14 + 0x195);
      }
      FUN_00490470(*(undefined4 *)PTR_DAT_004c8838,1);
      if (*(char *)(*(int *)(*(int *)PTR_DAT_004c8838 + 0x30c) + 8) == '\0') {
        FUN_004915d0(*(undefined4 *)PTR_DAT_004c8838,10,0x2d,0x2d,100);
      }
      else {
        FUN_004915d0(*(undefined4 *)PTR_DAT_004c8838,200,0x2d,0x2d,10);
      }
      *(undefined4 *)(*(int *)PTR_DAT_004c8838 + 0x294) = 0x2d;
    }
    if ((*(char *)(*(int *)PTR_DAT_004c91d4 + 0x1d) == '\x01') ||
       ((byte)(*(char *)(*(int *)PTR_DAT_004c91d4 + 0x1d) - 3U) < 2)) {
      iVar5 = *(int *)(*(int *)PTR_DAT_004c92f4 + 0x20);
      if (0 < iVar5) {
        local_10 = 1;
        do {
          if (*(char *)((int)param_1 + 0x2a9) == '\0') {
            iVar1 = *(int *)(*(int *)(*(int *)PTR_DAT_004c92f4 + 0x40 + local_10 * 4) + 0x74);
            if ((0x1863c < iVar1) && (iVar1 < 0x18641)) {
              *(undefined1 *)(param_1 + 0xaa) = 0;
              *(undefined1 *)(*(int *)PTR_DAT_004c8838 + 0x31a) = 0;
              *(undefined1 *)((int)param_1 + 0x2a9) = 1;
              *(undefined1 *)(*(int *)PTR_DAT_004c8838 + 0x31b) = 1;
              if (*(char *)(*(int *)PTR_DAT_004c8838 + 0x38c) == '\x01') {
                (**(code **)(*param_1 + 8))
                          (param_1,"panel22",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,local_14 + 0x1a9);
              }
              else {
                (**(code **)(*param_1 + 8))
                          (param_1,"Form_Talk_3",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,local_14 + 0x1a9);
              }
              FUN_004915d0(param_1,0x32,0x1f,0x1f,0x32);
              *(undefined4 *)(*(int *)PTR_DAT_004c8838 + 0x294) = 0x28;
              (**(code **)(**(int **)PTR_DAT_004c8838 + 0x94))();
              FUN_00490470(*(undefined4 *)PTR_DAT_004c8838,1);
            }
          }
          local_10 = local_10 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      if (*PTR_DAT_004c8db0 != '\0') {
        *(undefined1 *)((int)param_1 + 0x2aa) = 1;
        *(undefined1 *)(*(int *)PTR_DAT_004c8838 + 0x31c) = 1;
        if (*(char *)(*(int *)PTR_DAT_004c8838 + 0x319) == '\0') {
          (**(code **)(*param_1 + 8))(param_1,"panel22",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,0x19);
          FUN_004915d0(param_1,0x32,0x1f,0x1f,0x32);
          *(undefined4 *)(*(int *)PTR_DAT_004c8838 + 0x294) = 0x28;
          (**(code **)(**(int **)PTR_DAT_004c8838 + 0x94))();
          FUN_00490470(*(undefined4 *)PTR_DAT_004c8838,1);
        }
        else {
          if (*(char *)(*(int *)PTR_DAT_004c8838 + 0x38c) == '\x01') {
            (**(code **)(**(int **)PTR_DAT_004c8838 + 8))
                      (*(int **)PTR_DAT_004c8838,"Form_Talk_1",0x34,0xa9,0x300,0,0,1,0xa9,0x300,
                       local_14 + 0x195);
          }
          else {
            (**(code **)(**(int **)PTR_DAT_004c8838 + 8))
                      (*(int **)PTR_DAT_004c8838,"Form_Talk_2",0x34,0xa9,0x300,0,0,1,0xa9,0x300,
                       local_14 + 0x195);
          }
          FUN_00490470(*(undefined4 *)PTR_DAT_004c8838,1);
          if (*(char *)(*(int *)(*(int *)PTR_DAT_004c8838 + 0x30c) + 8) == '\0') {
            FUN_004915d0(*(undefined4 *)PTR_DAT_004c8838,10,0x2d,0x2d,100);
          }
          else {
            FUN_004915d0(*(undefined4 *)PTR_DAT_004c8838,200,0x2d,0x2d,10);
          }
          *(undefined4 *)(*(int *)PTR_DAT_004c8838 + 0x294) = 0x2d;
        }
      }
    }
    if (*(char *)(*(int *)PTR_DAT_004c8838 + 0x331) != '\0') {
      if (*(char *)(*(int *)PTR_DAT_004c8838 + 0x319) == '\0') {
        (**(code **)(*param_1 + 8))(param_1,"panel22",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,0x19);
        FUN_004915d0(param_1,0x32,0x1f,0x1f,0x32);
        *(undefined4 *)(*(int *)PTR_DAT_004c8838 + 0x294) = 0x28;
        (**(code **)(**(int **)PTR_DAT_004c8838 + 0x94))();
        FUN_00490470(*(undefined4 *)PTR_DAT_004c8838,1);
      }
      else {
        if (*(char *)(*(int *)PTR_DAT_004c8838 + 0x38c) == '\x01') {
          (**(code **)(**(int **)PTR_DAT_004c8838 + 8))
                    (*(int **)PTR_DAT_004c8838,"Form_Talk_1",0x34,0xa9,0x300,0,0,1,0xa9,0x300,
                     local_14 + 0x195);
        }
        else {
          (**(code **)(**(int **)PTR_DAT_004c8838 + 8))
                    (*(int **)PTR_DAT_004c8838,"Form_Talk_2",0x34,0xa9,0x300,0,0,1,0xa9,0x300,
                     local_14 + 0x195);
        }
        FUN_00490470(*(undefined4 *)PTR_DAT_004c8838,1);
        if (*(char *)(*(int *)(*(int *)PTR_DAT_004c8838 + 0x30c) + 8) == '\0') {
          FUN_004915d0(*(undefined4 *)PTR_DAT_004c8838,10,0x2d,0x2d,100);
        }
        else {
          FUN_004915d0(*(undefined4 *)PTR_DAT_004c8838,200,0x2d,0x2d,10);
        }
        *(undefined4 *)(*(int *)PTR_DAT_004c8838 + 0x294) = 0x2d;
      }
    }
  }
  if (param_1 == *(int **)PTR_DAT_004c935c) {
    uVar4 = FUN_0049e7c4(*(undefined1 *)(*(int *)(*(int *)PTR_DAT_004c935c + 0x30c) + 8),
                         *(undefined1 *)(*(int *)(*(int *)PTR_DAT_004c935c + 0x30c) + 0xb4));
    if ((((*PTR_DAT_004c8db0 == '\0') &&
         (*(char *)(*(int *)(*(int *)PTR_DAT_004c935c + 0x30c) + 0xb1) == '\x01')) &&
        (*(char *)(*(int *)PTR_DAT_004c935c + 0x319) != '\0')) &&
       (((char)param_1[0xaa] == '\0' &&
        (*(short *)(PTR_DAT_004c9650 + (uVar4 & 0xff) * 0xe + 4) ==
         *(short *)(*(int *)(*(int *)(*(int *)PTR_DAT_004c935c + 0x30c) + 0x6c) + 4))))) {
      *(undefined1 *)(param_1 + 0xaa) = 1;
    }
    if (*(char *)(*(int *)(*(int *)PTR_DAT_004c935c + 0x30c) + 8) == -6) {
      *(undefined1 *)(param_1 + 0xaa) = 1;
    }
    *(char *)(*(int *)PTR_DAT_004c935c + 0x31a) = (char)param_1[0xaa];
    if (((*(char *)(*(int *)PTR_DAT_004c935c + 0x331) == '\0') && (*PTR_DAT_004c8db0 == '\0')) &&
       ((char)param_1[0xaa] == '\0')) {
      if (*(char *)(*(int *)PTR_DAT_004c935c + 0x38c) == '\x01') {
        (**(code **)(*param_1 + 8))(param_1,"panel22",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,0x19);
      }
      else {
        (**(code **)(*param_1 + 8))(param_1,"Form_Talk_3",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,0x19);
      }
      FUN_004915d0(param_1,0x32,0x1f,0x1f,0x32);
      *(undefined4 *)(*(int *)PTR_DAT_004c935c + 0x294) = 0x28;
      (**(code **)(**(int **)PTR_DAT_004c935c + 0x94))();
      FUN_00490470(*(undefined4 *)PTR_DAT_004c935c,1);
    }
    else {
      if (*(char *)(*(int *)PTR_DAT_004c935c + 0x38c) == '\x01') {
        (**(code **)(**(int **)PTR_DAT_004c935c + 8))
                  (*(int **)PTR_DAT_004c935c,"Form_Talk_1",0x23,0xa9,0x300,0,0,1,0xa9,0x300,
                   local_14 + 0x195);
      }
      else {
        (**(code **)(**(int **)PTR_DAT_004c935c + 8))
                  (*(int **)PTR_DAT_004c935c,"Form_Talk_2",0x23,0xa9,0x300,0,0,1,0xa9,0x300,
                   local_14 + 0x195);
      }
      FUN_00490470(*(undefined4 *)PTR_DAT_004c935c,1);
      if (*(char *)(*(int *)(*(int *)PTR_DAT_004c935c + 0x30c) + 8) == '\0') {
        FUN_004915d0(*(undefined4 *)PTR_DAT_004c935c,10,0x2d,0x2d,100);
      }
      else {
        FUN_004915d0(*(undefined4 *)PTR_DAT_004c935c,200,0x2d,0x2d,10);
      }
      *(undefined4 *)(*(int *)PTR_DAT_004c935c + 0x294) = 0x2d;
    }
    if ((*(char *)(*(int *)PTR_DAT_004c91d4 + 0x1d) == '\x01') ||
       ((byte)(*(char *)(*(int *)PTR_DAT_004c91d4 + 0x1d) - 3U) < 2)) {
      iVar5 = *(int *)(*(int *)PTR_DAT_004c92f4 + 0x20);
      if (0 < iVar5) {
        local_10 = 1;
        do {
          if (*(char *)((int)param_1 + 0x2a9) == '\0') {
            iVar1 = *(int *)(*(int *)(*(int *)PTR_DAT_004c92f4 + 0x40 + local_10 * 4) + 0x74);
            if ((0x1863c < iVar1) && (iVar1 < 0x18641)) {
              *(undefined1 *)(param_1 + 0xaa) = 0;
              *(undefined1 *)(*(int *)PTR_DAT_004c935c + 0x31a) = 0;
              *(undefined1 *)((int)param_1 + 0x2a9) = 1;
              *(undefined1 *)(*(int *)PTR_DAT_004c935c + 0x31b) = 1;
              if (*(char *)(*(int *)PTR_DAT_004c935c + 0x38c) == '\x01') {
                (**(code **)(*param_1 + 8))
                          (param_1,"panel22",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,local_14 + 0x1a9);
              }
              else {
                (**(code **)(*param_1 + 8))
                          (param_1,"Form_Talk_3",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,local_14 + 0x1a9);
              }
              FUN_004915d0(param_1,0x32,0x1f,0x1f,0x32);
              *(undefined4 *)(*(int *)PTR_DAT_004c935c + 0x294) = 0x28;
              (**(code **)(**(int **)PTR_DAT_004c935c + 0x94))();
              FUN_00490470(*(undefined4 *)PTR_DAT_004c935c,1);
            }
          }
          local_10 = local_10 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      if (*PTR_DAT_004c8db0 != '\0') {
        *(undefined1 *)((int)param_1 + 0x2aa) = 1;
        *(undefined1 *)(*(int *)PTR_DAT_004c935c + 0x31c) = 1;
        if (*(char *)(*(int *)PTR_DAT_004c935c + 0x319) == '\0') {
          (**(code **)(*param_1 + 8))(param_1,"panel22",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,0x19);
          FUN_004915d0(param_1,0x32,0x1f,0x1f,0x32);
          *(undefined4 *)(*(int *)PTR_DAT_004c935c + 0x294) = 0x28;
          (**(code **)(**(int **)PTR_DAT_004c935c + 0x94))();
          FUN_00490470(*(undefined4 *)PTR_DAT_004c935c,1);
        }
        else {
          if (*(char *)(*(int *)PTR_DAT_004c935c + 0x38c) == '\x01') {
            (**(code **)(**(int **)PTR_DAT_004c935c + 8))
                      (*(int **)PTR_DAT_004c935c,"Form_Talk_1",0x34,0xa9,0x300,0,0,1,0xa9,0x300,
                       local_14 + 0x195);
          }
          else {
            (**(code **)(**(int **)PTR_DAT_004c935c + 8))
                      (*(int **)PTR_DAT_004c935c,"Form_Talk_2",0x34,0xa9,0x300,0,0,1,0xa9,0x300,
                       local_14 + 0x195);
          }
          FUN_00490470(*(undefined4 *)PTR_DAT_004c935c,1);
          if (*(char *)(*(int *)(*(int *)PTR_DAT_004c935c + 0x30c) + 8) == '\0') {
            FUN_004915d0(*(undefined4 *)PTR_DAT_004c935c,10,0x2d,0x2d,100);
          }
          else {
            FUN_004915d0(*(undefined4 *)PTR_DAT_004c935c,200,0x2d,0x2d,10);
          }
          *(undefined4 *)(*(int *)PTR_DAT_004c935c + 0x294) = 0x2d;
        }
      }
    }
    if (*(char *)(*(int *)PTR_DAT_004c935c + 0x331) != '\0') {
      if (*(char *)(*(int *)PTR_DAT_004c935c + 0x319) == '\0') {
        (**(code **)(*param_1 + 8))(param_1,"panel22",0xfa,0xa8,0x14c,0,0,1,0x44,0xaa,0x19);
        FUN_004915d0(param_1,0x32,0x1f,0x1f,0x32);
        *(undefined4 *)(*(int *)PTR_DAT_004c935c + 0x294) = 0x28;
        (**(code **)(**(int **)PTR_DAT_004c935c + 0x94))();
        FUN_00490470(*(undefined4 *)PTR_DAT_004c935c,1);
      }
      else {
        if (*(char *)(*(int *)PTR_DAT_004c935c + 0x38c) == '\x01') {
          (**(code **)(**(int **)PTR_DAT_004c935c + 8))
                    (*(int **)PTR_DAT_004c935c,"Form_Talk_1",0x34,0xa9,0x300,0,0,1,0xa9,0x300,
                     local_14 + 0x195);
        }
        else {
          (**(code **)(**(int **)PTR_DAT_004c935c + 8))
                    (*(int **)PTR_DAT_004c935c,"Form_Talk_2",0x34,0xa9,0x300,0,0,1,0xa9,0x300,
                     local_14 + 0x195);
        }
        FUN_00490470(*(undefined4 *)PTR_DAT_004c935c,1);
        if (*(char *)(*(int *)(*(int *)PTR_DAT_004c935c + 0x30c) + 8) == '\0') {
          FUN_004915d0(*(undefined4 *)PTR_DAT_004c935c,10,0x2d,0x2d,100);
        }
        else {
          FUN_004915d0(*(undefined4 *)PTR_DAT_004c935c,200,0x2d,0x2d,10);
        }
        *(undefined4 *)(*(int *)PTR_DAT_004c935c + 0x294) = 0x2d;
      }
    }
  }
  param_1[0x5a] = 0;
  param_1[0x5b] = 0;
  *(double *)(param_1 + 0x4c) = (double)*(uint *)PTR_DAT_004c87cc;
  *(double *)(param_1 + 0x48) = (double)*(uint *)PTR_DAT_004c87cc;
  *(double *)(param_1 + 0x4e) = (double)*(uint *)PTR_DAT_004c87cc;
  (**(code **)(*param_1 + 0x98))(param_1,0);
  *(undefined1 *)((int)param_1 + 0x196) = 1;
  FUN_0048bbe8(param_1,local_8,param_4);
  if (param_3 < 1) {
    *(undefined1 *)(param_1 + 0x5e) = 0;
  }
  else {
    *(double *)(param_1 + 0x4a) = (double)param_3;
    *(undefined1 *)(param_1 + 0x5e) = 1;
  }
  *(undefined1 *)(param_1 + 0x65) = 0;
  *(undefined1 *)((int)param_1 + 0x195) = 0;
  *(char *)((int)param_1 + 0x197) = param_5;
  iVar5 = *(int *)(*(int *)(param_1[0x2f] + 0x1c) + 0x14);
  cVar3 = FUN_000132bc(iVar5,&PTR_LAB_00439ad4);
  if (cVar3 == '\0') {
    param_1[0xa8] = iVar5;
  }
  if (param_5 == '\0') {
    (**(code **)(*param_1 + 0x20))();
  }
  else {
    FUN_0048bdf8(param_1);
  }
  puVar2 = puStack_2c;
  *in_FS_OFFSET = uStack_34;
  puStack_2c = &LAB_0048a6bf;
  puStack_30 = (undefined1 *)0x48a6b7;
  FUN_00013eac(&local_8,uStack_34,puVar2);
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_0040d550
 * @başlık         Görev Diyalog Form Başlatıcısı (Quest TalkForm Loader)
 * @açıklama       Görevlerle ilişkili özel diyalog pencerelerini (TalkForm1) belleğe yükler.
 * @ofsetler       Arayüz referansları.
 * @paketler       Görev Diyalog Akışı.
 * 
 * @detaylı_analiz 
 * * 1. Görev tetiklendiğinde TalkForm1 formunu belleğe yükler.
 *  * 2. Görev metin dizisini ve diyalog avatarını çizer.
 *******************************************************************************/
void FUN_0040d550(int param_1)

{
  undefined1 *puVar1;
  char cVar2;
  short sVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  BOOL BVar7;
  byte bVar8;
  ushort uVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_74;
  undefined1 *puStack_70;
  undefined1 *puStack_6c;
  undefined4 local_68;
  undefined1 *puStack_64;
  undefined1 *puStack_60;
  undefined1 *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 local_34 [18];
  char local_22;
  char local_21;
  undefined4 local_20;
  byte local_19;
  undefined1 *local_18;
  uint local_14;
  byte local_d;
  int local_c;
  int local_8;
  
  puStack_60 = &stack0xfffffffc;
  puStack_6c = &stack0xfffffffc;
  local_50 = (undefined1 *)0x0;
  local_48 = 0;
  local_4c = 0;
  local_40 = 0;
  local_44 = 0;
  local_3c = 0;
  local_38 = 0;
  local_18 = (undefined1 *)0x0;
  puStack_64 = &LAB_0040dc22;
  local_68 = *in_FS_OFFSET;
  *in_FS_OFFSET = &local_68;
  puStack_70 = &LAB_0040dbf5;
  uStack_74 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_74;
  local_8 = param_1;
  if (*(int *)(param_1 + 0x2318) == 0) {
    *(undefined4 *)(param_1 + 0x2310) = 0;
    *(undefined4 *)(param_1 + 0x2314) = 0;
    *in_FS_OFFSET = uStack_74;
    puStack_6c = &stack0xfffffffc;
    puStack_60 = &stack0xfffffffc;
  }
  else {
    uVar4 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,"TalkForm1");
    *(undefined2 *)(local_8 + 0x230c) = 0;
    *(undefined2 *)(local_8 + 0x230e) = 0;
    local_d = 1;
    FUN_00013eac(&local_18);
    *(undefined4 *)(local_8 + 0x2130) = 0;
    cVar2 = FUN_00466684(5000);
    if (cVar2 == '\0') {
      *(int *)(local_8 + 0x2320) = *(int *)(local_8 + 0x2320) + 1;
      if (*(int *)(local_8 + 0x2320) % 7 == 0) {
        *(undefined4 *)(local_8 + 0x2320) = 0;
        *(int *)(local_8 + 0x2324) = *(int *)(local_8 + 0x2324) + 1;
        if (1 < *(int *)(local_8 + 0x2324)) {
          *(undefined4 *)(local_8 + 0x2324) = 0;
        }
      }
      sVar3 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318));
      uVar9 = sVar3 << 3;
      if (0xa0 < uVar9) {
        uVar9 = 0xa0;
      }
      uVar5 = FUN_003ee8d0(local_8);
      iVar6 = (int)uVar5 >> 1;
      if (iVar6 < 0) {
        iVar6 = iVar6 + (uint)((uVar5 & 1) != 0);
      }
      *(uint *)(local_8 + 0x2130) = ((*(int *)(local_8 + 0x8c) - iVar6) + 0xf) - (uint)(uVar9 >> 1);
      iVar6 = FUN_003ee750(local_8);
      *(int *)(local_8 + 0x2134) = (*(int *)(local_8 + 0x90) - iVar6) + -0x3a;
      uVar5 = FUN_003ee8d0(local_8);
      iVar6 = (int)uVar5 >> 1;
      if (iVar6 < 0) {
        iVar6 = iVar6 + (uint)((uVar5 & 1) != 0);
      }
      iVar10 = (*(int *)(local_8 + 0x8c) - iVar6) + -0x28;
      iVar11 = *(int *)(local_8 + 0x2134) + -10;
      iVar6 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318));
      if ((0x50 < iVar6 * 8) &&
         (iVar6 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318)), iVar6 * 8 < 0xa1)) {
        iVar10 = *(int *)(local_8 + 0x2130) + -0xf;
        iVar11 = *(int *)(local_8 + 0x2134) + -10;
        sVar3 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318));
        *(short *)(local_8 + 0x230c) = sVar3 * 8 + -0x50;
      }
      iVar6 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318));
      if (0xa0 < iVar6 * 8) {
        *(undefined2 *)(local_8 + 0x230c) = 0x50;
        iVar10 = *(int *)(local_8 + 0x2130) + -0xf;
        iVar6 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318));
        local_d = (byte)(iVar6 / 0x14);
        iVar6 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318),iVar6 % 0x14);
        if (iVar6 % 0x14 != 0) {
          local_d = local_d + 1;
        }
        *(ushort *)(local_8 + 0x230e) = (local_d - 1) * 0x17;
      }
      FUN_0040dc64(local_8,uVar4,iVar10,iVar11);
      FUN_0040dcbc(local_8,uVar4,iVar10,iVar11);
      FUN_0040dd60(local_8,uVar4,iVar10,iVar11);
      FUN_0040ddc0(local_8,uVar4,iVar10,iVar11);
      FUN_0040de2c(local_8,uVar4,iVar10,iVar11);
      FUN_0040de9c(local_8,uVar4,iVar10,iVar11);
      FUN_0040df78(local_8,uVar4,iVar10,iVar11);
      local_19 = 1;
      uVar5 = (uint)local_d;
      if (local_d != 0) {
        do {
          local_14 = uVar5;
          local_50 = (undefined1 *)0x40d855;
          FUN_00013eac(&local_18);
          bVar8 = 1;
          local_c = *(int *)(local_8 + 0x2134) + (local_14 - 1) * -0x17;
          uVar4 = *in_FS_OFFSET;
          *in_FS_OFFSET = &stack0xffffffa8;
          local_50 = &stack0xfffffffc;
          while( true ) {
            iVar6 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318));
            uVar5 = (uint)local_19;
            if (((iVar6 < (int)uVar5) || (0x3c < local_19)) || (0x14 < bVar8)) break;
            puStack_60 = (undefined1 *)0x40d8a5;
            BVar7 = IsDBCSLeadByte(*(BYTE *)(*(int *)(local_8 + 0x2318) + -1 + uVar5));
            if (BVar7 == 0) {
              local_21 = '\x01';
              local_22 = '\0';
              iVar6 = 1;
              piVar12 = (int *)PTR_DAT_004c9954;
              do {
                piVar12 = piVar12 + 1;
                iVar10 = FUN_0001412c(*(undefined4 *)(local_8 + 0x2318));
                if (iVar10 < (int)(local_19 + 1)) break;
                if ((*(char *)(*(int *)(local_8 + 0x2318) + -1 + (uint)local_19) ==
                     *(char *)*piVar12) &&
                   (*(char *)(*(int *)(local_8 + 0x2318) + (uint)local_19) ==
                    *(char *)(*piVar12 + 1))) {
                  if ((uint)bVar8 % 0x14 == 0) {
                    FUN_00014134(&local_18,&DAT_0040dc4c);
                    FUN_00014134(&local_18,&DAT_0040dc4c);
                    FUN_0001953c(iVar6,&local_44);
                    FUN_00014178(&local_40,"icon_expre_",local_44);
                    local_20 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,local_40);
                    puStack_60 = local_34;
                    puStack_64 = (undefined1 *)0x40d9fc;
                    FUN_00020cc0(0,*(int *)(local_8 + 0x2324) << 4,0x10);
                    puStack_60 = local_34;
                    puStack_64 = (undefined1 *)0x1;
                    local_68 = 0;
                    puStack_6c = (undefined1 *)0x40da2a;
                    FUN_004778ec(*(undefined4 *)PTR_DAT_004c8a78,local_20,
                                 *(int *)(local_8 + 0x2130) + (bVar8 - 1) * 8);
                    local_21 = '\0';
                    local_19 = local_19 + 2;
                    bVar8 = bVar8 + 2;
                    break;
                  }
                  if ((uint)bVar8 % 0x15 == 0) {
                    local_22 = '\x01';
                    break;
                  }
                  FUN_0001953c(iVar6,&local_4c);
                  FUN_00014178(&local_48,"icon_expre_",local_4c);
                  local_20 = FUN_004784ac(*(undefined4 *)PTR_DAT_004c8a78,local_48);
                  puStack_60 = local_34;
                  puStack_64 = (undefined1 *)0x40daa8;
                  FUN_00020cc0(0,*(int *)(local_8 + 0x2324) << 4,0x10);
                  puStack_60 = local_34;
                  puStack_64 = (undefined1 *)0x1;
                  local_68 = 0;
                  puStack_6c = (undefined1 *)0x40dad6;
                  FUN_004778ec(*(undefined4 *)PTR_DAT_004c8a78,local_20,
                               *(int *)(local_8 + 0x2130) + (bVar8 - 1) * 8);
                  FUN_00014134(&local_18,&DAT_0040dc4c);
                  FUN_00014134(&local_18,&DAT_0040dc4c);
                  local_21 = '\0';
                  local_19 = local_19 + 2;
                  bVar8 = bVar8 + 2;
                }
                iVar6 = iVar6 + 1;
              } while (iVar6 != 0x20);
              if (local_22 != '\0') break;
              if (local_21 != '\0') {
                FUN_00014054(&local_50,
                             *(undefined1 *)(*(int *)(local_8 + 0x2318) + -1 + (uint)local_19));
                FUN_00014134(&local_18,local_50);
                local_19 = local_19 + 1;
                bVar8 = bVar8 + 1;
              }
            }
            else {
              if ((uint)bVar8 % 0x14 == 0) break;
              FUN_00014054(&local_38,
                           CONCAT31((int3)((uint)*(int *)(local_8 + 0x2318) >> 8),
                                    *(undefined1 *)(*(int *)(local_8 + 0x2318) + -1 + uVar5)));
              FUN_00014134(&local_18,local_38);
              FUN_00014054(&local_3c,*(undefined1 *)(*(int *)(local_8 + 0x2318) + (uint)local_19));
              FUN_00014134(&local_18,local_3c);
              local_19 = local_19 + 2;
              bVar8 = bVar8 + 2;
            }
          }
          puVar1 = local_50;
          *in_FS_OFFSET = uVar4;
          local_50 = (undefined1 *)0x0;
          FUN_0001412c(local_18,uVar4,puVar1);
          puStack_60 = (undefined1 *)0xc;
          puStack_64 = local_18;
          local_68 = *(undefined4 *)(*(int *)(*(int *)PTR_DAT_004c96ac + 0x2d0) + 0x270);
          puStack_6c = &DAT_00000001;
          puStack_70 = (undefined1 *)0x0;
          uStack_74 = 0;
          FUN_004a2ff8(*(undefined4 *)PTR_DAT_004c9518,*(undefined4 *)(local_8 + 0x2130),local_c);
          uVar5 = local_14 - 1;
        } while (local_14 - 1 != 0);
        local_14 = 0;
      }
    }
    else {
      *(undefined4 *)(local_8 + 0x2310) = 0;
      *(undefined4 *)(local_8 + 0x2314) = 0;
      FUN_00013eac(local_8 + 0x2318);
    }
    *in_FS_OFFSET = uStack_74;
  }
  puVar1 = puStack_60;
  *in_FS_OFFSET = local_68;
  puStack_60 = &LAB_0040dc29;
  puStack_64 = (undefined1 *)0x40dc19;
  FUN_00013ed0(&local_50,7,puVar1);
  puStack_64 = (undefined1 *)0x40dc21;
  FUN_00013eac(&local_18);
  return;
}

