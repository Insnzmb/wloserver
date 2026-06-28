/**
 * combat_battle.c - WLO Savaş Başlatma, PK Doğrulama ve Sıra Tabanlı Savaş Paket Gönderimleri.
 * Extracted from aLogin.exe decompiled C code.
 */

/*******************************************************************************
 * @fonksiyon      FUN_003a6f18
 * @başlık         PK Davet Yöneticisi (PK Challenge Checker)
 * @açıklama       Başka bir oyuncuya PK düellosu daveti yollamadan önceki durum kontrollerini yapar.
 * @ofsetler       Hedef oyuncunun meşguliyet (savaşta/ticarette olma) durumunu kontrol eder.
 * @paketler       PK Davet İsteği (Opcode 11 Sub-opcode 2, PK Type 3).
 * 
 * @detaylı_analiz 
 * * 1. Haritanın PK yapılabilir alan olup olmadığı doğrulanır.
 *  * 2. Karşı oyuncunun uygunluğu kontrol edilir.
 *  * 3. Sunucuya düello paketi yollanır.
 *******************************************************************************/
void FUN_003a6f18(int param_1)

{
  uint uVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  
  uVar1 = FUN_0049606c(*(undefined4 *)PTR_DAT_004c89f0,
                       *(undefined2 *)(*(int *)PTR_DAT_004c98f4 + 0x235c));
  if ((uVar1 & 1) == 0) {
    if (*(char *)(*(int *)PTR_DAT_004c98f4 + 0x20b5) == '\0') {
      if (*(char *)(*(int *)PTR_DAT_004c98f4 + 0x20eb) == '\0') {
        if (*PTR_DAT_004c8810 == '\x01') {
          iVar4 = 1;
          psVar5 = (short *)PTR_DAT_004c9044;
          do {
            iVar3 = 9;
            psVar2 = psVar5;
            do {
              if ((*psVar2 != 0) && (*psVar2 == *(short *)(*(int *)PTR_DAT_004c98f4 + 0x235c))) {
                (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                          (*(int **)PTR_DAT_004c8d24,"Can\'t PK here",2000,0,0);
                return;
              }
              psVar2 = psVar2 + 1;
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            psVar5 = psVar5 + 9;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
          if (*(char *)(*(int *)PTR_DAT_004c98f4 + 0x20f6) == '\0') {
            iVar4 = *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b);
            if (iVar4 != 0) {
              uVar1 = FUN_0049b0a0(*(undefined4 *)PTR_DAT_004c88fc,
                                   *(undefined2 *)(*(int *)(PTR_DAT_004c976c + iVar4 * 4) + 4));
              if (*(char *)(*(int *)PTR_DAT_004c88fc + 0x68 + (uVar1 & 0xffff) * 0x8a) == '\x01') {
                (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                          (*(int **)PTR_DAT_004c8d24,&LAB_003a714c,0x4b0,0,0);
              }
              else {
                *(undefined4 *)(param_1 + 0x1e) =
                     *(undefined4 *)(*(int *)(PTR_DAT_004c976c + iVar4 * 4) + 4);
                *(short *)(param_1 + 0x22) = (short)iVar4;
                *(undefined1 *)(param_1 + 0x24) = 3;
                FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0xb,2,0);
              }
            }
          }
          else {
            (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                      (*(int **)PTR_DAT_004c8d24,"Collecting, can\'t act",2000,0,0);
          }
        }
      }
      else {
        (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                  (*(int **)PTR_DAT_004c8d24,"Bathing, can\'t act",2000,0,0);
      }
    }
    else {
      (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                (*(int **)PTR_DAT_004c8d24,"Fishing, can\'t act",2000,0,0);
    }
  }
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_003a7154
 * @başlık         PK Düello Doğrulayıcı (PK Validator & Distance Check)
 * @açıklama       PK düellosu başlatmak için hedef oyuncuya olan mesafeyi doğrular.
 * @ofsetler       Maksimum düello başlama mesafesi 0x10f (271 piksel) olarak sınırlandırılmıştır.
 * @paketler       Savaş Talep Paketi (Opcode 11 Sub-opcode 2).
 * 
 * @detaylı_analiz 
 * * 1. Hedef oyuncuya olan mesafe 271 piksel sınırına göre karşılaştırılır.
 *  * 2. Hedefin pazar açıp açmadığı (Stall durumu) doğrulanır.
 *  * 3. Koşullar uygunsa savaş paketi gönderilir.
 *******************************************************************************/
void FUN_003a7154(int param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  
  puVar3 = PTR_DAT_004c9110;
  if (*PTR_DAT_004c8810 == '\0') {
    uVar5 = FUN_0049606c(*(undefined4 *)PTR_DAT_004c89f0,
                         *(undefined2 *)(*(int *)PTR_DAT_004c98f4 + 0x235c));
    if ((uVar5 & 1) == 0) {
      if (*(char *)(*(int *)PTR_DAT_004c98f4 + 0x20b5) == '\0') {
        if (*(char *)(*(int *)PTR_DAT_004c98f4 + 0x20f6) == '\0') {
          if (*(char *)(*(int *)(puVar3 + *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b) * 4) + 0x20eb)
              == '\0') {
            if (*(char *)(*(int *)PTR_DAT_004c98f4 + 0x20eb) == '\0') {
              *(undefined4 *)(param_1 + 0x1e) = 0;
              *(undefined2 *)(param_1 + 0x22) = 0;
              iVar1 = *(int *)(*(int *)PTR_DAT_004c87e0 + 0x7b);
              if (*(char *)(*(int *)(puVar3 + iVar1 * 4) + 0x20b5) == '\0') {
                if (*(char *)(*(int *)(puVar3 + iVar1 * 4) + 0x20f6) == '\0') {
                  if (*(char *)(*(int *)(puVar3 + iVar1 * 4) + 0x2091) == '\0') {
                    uVar5 = *(int *)(*(int *)(puVar3 + iVar1 * 4) + 0x20) -
                            *(int *)(*(int *)PTR_DAT_004c98f4 + 0x20);
                    uVar6 = (int)uVar5 >> 0x1f;
                    if (((int)((uVar5 ^ uVar6) - uVar6) < 0x10f) &&
                       (uVar5 = *(int *)(*(int *)(puVar3 + iVar1 * 4) + 0x24) -
                                *(int *)(*(int *)PTR_DAT_004c98f4 + 0x24),
                       uVar6 = (int)uVar5 >> 0x1f, (int)((uVar5 ^ uVar6) - uVar6) < 0x10f)) {
                      if (*(char *)(*(int *)(puVar3 + iVar1 * 4) + 0x1f16) == '\x04') {
                        (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                  (*(int **)PTR_DAT_004c8d24,&DAT_003a7650,0x5dc,0,0);
                      }
                      else {
                        cVar4 = FUN_0010e1ac(*(undefined4 *)(*(int *)(puVar3 + iVar1 * 4) + 4));
                        if ((byte)(cVar4 + 0x97U) < 6) {
                          (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                    (*(int **)PTR_DAT_004c8d24,"Can\'t PK Cupid",1000,0,0);
                        }
                        else {
                          cVar4 = FUN_001a4930(*(undefined4 *)PTR_DAT_004c8d3c);
                          if ((cVar4 == '\0') &&
                             (*(char *)(*(int *)PTR_DAT_004c8b88 + 0x205) == '\x02')) {
                            (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                      (*(int **)PTR_DAT_004c8d24,"You PK is turned off",1000,0,0);
                          }
                          else if (*(char *)(*(int *)(puVar3 + iVar1 * 4) + 0x2231) == '\0') {
                            if (*(char *)(*(int *)(puVar3 + iVar1 * 4) + 0x2232) == '\0') {
                              if (*(char *)(*(int *)(puVar3 + iVar1 * 4) + 0x2233) == '\0') {
                                if (*(char *)(*(int *)PTR_DAT_004c98f4 + 0x3b18) == '\0') {
                                  iVar2 = *(int *)(puVar3 + iVar1 * 4);
                                  if (*(char *)(iVar2 + 0x1eff) == '\x02') {
                                    if (*(int *)(iVar2 + 0x21bc) ==
                                        *(int *)(*(int *)PTR_DAT_004c98f4 + 4)) {
                                      (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                                (*(int **)PTR_DAT_004c8d24,"Can\'t PK teammate",1000
                                                 ,0,0);
                                      return;
                                    }
                                    *(int *)(param_1 + 0x1e) = *(int *)(iVar2 + 0x21bc);
                                  }
                                  else {
                                    *(undefined4 *)(param_1 + 0x1e) = *(undefined4 *)(iVar2 + 4);
                                  }
                                  if (*(int *)(param_1 + 0x1e) != 0) {
                                    if (*(char *)(*(int *)(puVar3 + iVar1 * 4) + 0x1f16) == '\0') {
                                      *(undefined1 *)(param_1 + 0x24) = 2;
                                    }
                                    else {
                                      *(undefined1 *)(param_1 + 0x24) = 5;
                                    }
                                    FUN_002d6994(*(undefined4 *)PTR_DAT_004c87e4,0xb,2,0);
                                  }
                                }
                                else {
                                  (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                            (*(int **)PTR_DAT_004c8d24,"Can\'t PK here",0x4b0,0,0);
                                }
                              }
                              else {
                                (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                          (*(int **)PTR_DAT_004c8d24,"Can\'t PK Stall user",1000,0,0
                                          );
                              }
                            }
                            else {
                              (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                        (*(int **)PTR_DAT_004c8d24,"Can\'t PK Stall user",1000,0,0);
                            }
                          }
                          else {
                            (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                      (*(int **)PTR_DAT_004c8d24,"Can\'t PK Stall user",1000,0,0);
                          }
                        }
                      }
                    }
                    else {
                      (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                                (*(int **)PTR_DAT_004c8d24,&DAT_003a763c,0x5dc,0,0);
                    }
                  }
                  else {
                    (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                              (*(int **)PTR_DAT_004c8d24,"Unable to apply, player is busy",0x5dc,0,0
                              );
                  }
                }
                else {
                  (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                            (*(int **)PTR_DAT_004c8d24,"Player busy",2000,0,0);
                }
              }
              else {
                (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                          (*(int **)PTR_DAT_004c8d24,"In fishing",2000,0,0);
              }
            }
            else {
              (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                        (*(int **)PTR_DAT_004c8d24,"Bathing, can\'t act",2000,0,0);
            }
          }
          else {
            (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                      (*(int **)PTR_DAT_004c8d24,&DAT_003a75ac,2000,0,0);
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
    }
    else {
      (**(code **)(**(int **)PTR_DAT_004c8d24 + 0x9c))
                (*(int **)PTR_DAT_004c8d24,"Can\'t PK here",2000,0,0);
    }
  }
  return;
}

