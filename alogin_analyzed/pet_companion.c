/**
 * pet_companion.c - Pet Çağırma/Gizleme, Binek Durumları ve AI Mod Dönüşüm Mekanizmaları.
 * Extracted from aLogin.exe decompiled C code.
 */

/*******************************************************************************
 * @fonksiyon      FUN_003de310
 * @başlık         Evcil Hayvan Çağırma Yöneticisi (Active Pet Summoner)
 * @açıklama       Karakterin petini haritaya çağırma veya geri gönderme durumlarını günceller.
 * @ofsetler       Oyuncunun en fazla 4 pet slotu taranır (+0x21e8). Pet yapısındaki +0x1efc summoned durumudur.
 * @paketler       Pet Çağırma Paketeti (Opcode 15 Sub-opcode 4).
 * 
 * @detaylı_analiz 
 * * 1. 4 pet yuvası sırayla taranarak aktif pet aranır.
 *  * 2. Seçilen petin +0x1efc çağrılma bayrağı 1 setlenir.
 *  * 3. Sunucuya pet çağırma paketi gönderilir.
 *******************************************************************************/
void FUN_003de310(int param_1)

{
  int iVar1;
  
  iVar1 = 1;
  do {
    *(undefined1 *)(*(int *)(param_1 + 0x21e8 + iVar1 * 4) + 0x1efc) = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 5);
  if (((*(char *)(param_1 + 0x1f16) == '\0') || (*(char *)(param_1 + 0x1f16) == '\x04')) &&
     (*(char *)(param_1 + 0x1eff) == '\0')) {
    *(undefined1 *)(*(int *)(param_1 + 0x21e8 + (uint)*(byte *)(param_1 + 0x2230) * 4) + 0x1efc) = 1
    ;
  }
  return;
}

/*******************************************************************************
 * @fonksiyon      FUN_003e9898
 * @başlık         Pet Yapay Zeka AI Mod Dönüştürücü (Pet Mode Transition Mapper)
 * @açıklama       Arayüzden gelen geçici pet mod durumlarını sunucu/istemci veri modlarına (0-7) eşler.
 * @ofsetler       active_pet + 0x121 ofsetindeki pet AI durum modu kodunu (Savaş, Dinlenme vb.) günceller.
 * @paketler       Pet AI Mod Güncelleme Paketi.
 * 
 * @detaylı_analiz 
 * * 1. Arayüzden gelen geçici durum kodları (8-15) kontrol edilir.
 *  * 2. Bunlar tablodan geçirilerek gerçek pet durumlarına (0: Savaş, 1: Dinlenme vb.) dönüştürülür.
 *  * 3. Değer pet + 0x121 ofsetine yazılarak güncellenir.
 *******************************************************************************/
undefined1 FUN_003e9898(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  undefined1 local_1c8 [22];
  ushort local_1b2;
  ushort local_1b0;
  ushort local_1ae;
  ushort local_1ac;
  char local_29;
  
  if (param_2 == 0) {
    return 0;
  }
  uVar2 = 0;
  cVar1 = *(char *)(param_1 + 8);
  if (cVar1 == '\x01') {
    FUN_00431c8c(*(undefined4 *)PTR_DAT_004c94d4,param_2,local_1c8);
    uVar2 = (uint)local_1b2;
  }
  else if (cVar1 == '\x02') {
    FUN_00431c8c(*(undefined4 *)PTR_DAT_004c94d4,param_2,local_1c8);
    uVar2 = (uint)local_1b0;
  }
  else if (cVar1 == '\x03') {
    FUN_00431c8c(*(undefined4 *)PTR_DAT_004c94d4,param_2,local_1c8);
    uVar2 = (uint)local_1ae;
  }
  else if (cVar1 == '\x04') {
    FUN_00431c8c(*(undefined4 *)PTR_DAT_004c94d4,param_2,local_1c8);
    uVar2 = (uint)local_1ac;
  }
  if (uVar2 < 0x1089) {
    if (uVar2 == 0x1088) {
      return 1;
    }
    if (uVar2 < 0xca1) {
      if (uVar2 == 0xca0) {
        return 1;
      }
      if (uVar2 < 0xaff) {
        if (uVar2 == 0xafe) {
          return 6;
        }
        if (uVar2 < 0x93e) {
          if (uVar2 < 0x91c) {
            if (uVar2 == 0x91b) {
              return 2;
            }
            if (uVar2 == 0x8b8) {
              return 1;
            }
            if (uVar2 == 0x8d4) {
              return 1;
            }
          }
          else {
            if (uVar2 - 0x91c < 4) {
              return 6;
            }
            if (uVar2 - 0x91c == 0xf) {
              return 6;
            }
          }
          goto switchD_003e9a71_caseD_b23;
        }
        if (0x958 < uVar2) {
          if (uVar2 - 0x959 < 3) {
            return 6;
          }
          if (uVar2 == 0x95e) {
            return 6;
          }
          if (uVar2 - 0xaf4 < 7) {
            return 6;
          }
          goto switchD_003e9a71_caseD_b23;
        }
        if (uVar2 - 0x93e < 4) {
          return 6;
        }
        if (uVar2 - 0x94c < 9) {
          return 6;
        }
        uVar2 = uVar2 - 0x956;
      }
      else {
        if (0xb1a < uVar2) {
          switch(uVar2) {
          case 0xb22:
          case 0xb24:
          case 0xb27:
          case 0xb28:
          case 0xb29:
          case 0xb2b:
          case 0xb2c:
          case 0xb30:
          case 0xb31:
            return 6;
          }
          goto switchD_003e9a71_caseD_b23;
        }
        if (uVar2 == 0xb1a) {
          return 6;
        }
        if (0xb09 < uVar2) {
          if (uVar2 - 0xb0a < 2) {
            return 6;
          }
          uVar2 = uVar2 - 0xb0d;
          goto joined_r0x003e9bb1;
        }
        if (uVar2 - 0xb00 < 2) {
          return 6;
        }
        uVar2 = uVar2 - 0xb03;
      }
    }
    else {
      if (uVar2 < 0xee8) {
        if (0xd33 < uVar2) {
          if (0xd46 < uVar2) {
            uVar2 = uVar2 - 0xedc;
            goto joined_r0x003e9b56;
          }
          if (uVar2 == 0xd46) {
            return 6;
          }
          if (uVar2 - 0xd34 < 9) {
            return 6;
          }
          if (uVar2 - 0xd3e < 2) {
            return 6;
          }
          uVar2 = uVar2 - 0xd41;
          goto joined_r0x003e9cb7;
        }
        if (uVar2 < 0xd04) {
          if (uVar2 == 0xcbc) {
            return 1;
          }
          if (uVar2 == 0xd03) {
            return 2;
          }
          goto switchD_003e9a71_caseD_b23;
        }
        if (uVar2 - 0xd04 < 4) {
          return 6;
        }
        if (uVar2 == 0xd13) {
          return 6;
        }
        uVar2 = uVar2 - 0xd26;
        goto joined_r0x003e9b0c;
      }
      if (0xf02 < uVar2) {
        switch(uVar2) {
        case 0xf0a:
        case 0xf0c:
        case 0xf0f:
        case 0xf10:
        case 0xf11:
        case 0xf13:
        case 0xf14:
        case 0xf18:
        case 0xf19:
          return 6;
        }
        goto switchD_003e9a71_caseD_b23;
      }
      if (uVar2 == 0xf02) {
        return 6;
      }
      if (0xef1 < uVar2) {
        if (uVar2 - 0xef2 < 2) {
          return 6;
        }
        uVar2 = uVar2 - 0xef5;
        goto joined_r0x003e9bb1;
      }
      if (uVar2 - 0xee8 < 2) {
        return 6;
      }
      uVar2 = uVar2 - 0xeeb;
    }
  }
  else {
    if (uVar2 < 0x1471) {
      if (uVar2 == 0x1470) {
        return 1;
      }
      if (uVar2 < 0x12d0) {
        if (uVar2 < 0x111c) {
          if (uVar2 < 0x10ec) {
            if (uVar2 == 0x10a4) {
              return 1;
            }
            if (uVar2 == 0x10eb) {
              return 2;
            }
          }
          else {
            if (uVar2 - 0x10ec < 4) {
              return 6;
            }
            if (uVar2 == 0x10fb) {
              return 6;
            }
            if (uVar2 - 0x110e < 4) {
              return 6;
            }
          }
          goto switchD_003e9a71_caseD_b23;
        }
        if (uVar2 < 0x112f) {
          if (uVar2 == 0x112e) {
            return 6;
          }
          if (uVar2 - 0x111c < 9) {
            return 6;
          }
          if (uVar2 - 0x1126 < 2) {
            return 6;
          }
          uVar2 = uVar2 - 0x1129;
          goto joined_r0x003e9cb7;
        }
        uVar2 = uVar2 - 0x12c4;
joined_r0x003e9b56:
        if (uVar2 < 7) {
          return 6;
        }
      }
      else {
        if (0x12ea < uVar2) {
          switch(uVar2) {
          case 0x12f2:
          case 0x12f4:
          case 0x12f7:
          case 0x12f8:
          case 0x12f9:
          case 0x12fb:
          case 0x12fc:
          case 0x1300:
          case 0x1301:
            return 6;
          }
          goto switchD_003e9a71_caseD_b23;
        }
        if (uVar2 == 0x12ea) {
          return 6;
        }
        if (uVar2 < 0x12da) {
          if (uVar2 - 0x12d0 < 2) {
            return 6;
          }
          uVar2 = uVar2 - 0x12d3;
          goto joined_r0x003e9d08;
        }
        if (uVar2 - 0x12da < 2) {
          return 6;
        }
        uVar2 = uVar2 - 0x12dd;
joined_r0x003e9bb1:
        if (uVar2 < 4) {
          return 6;
        }
      }
      if (uVar2 == 10) {
        return 6;
      }
      goto switchD_003e9a71_caseD_b23;
    }
    if (uVar2 < 0x16b8) {
      if (0x1503 < uVar2) {
        if (0x1516 < uVar2) {
          uVar2 = uVar2 - 0x16ac;
          goto joined_r0x003e9b56;
        }
        if (uVar2 == 0x1516) {
          return 6;
        }
        if (uVar2 - 0x1504 < 9) {
          return 6;
        }
        if (uVar2 - 0x150e < 2) {
          return 6;
        }
        uVar2 = uVar2 - 0x1511;
joined_r0x003e9cb7:
        if (uVar2 < 3) {
          return 6;
        }
        goto switchD_003e9a71_caseD_b23;
      }
      if (uVar2 < 0x14d4) {
        if (uVar2 == 0x148c) {
          return 1;
        }
        if (uVar2 == 0x14d3) {
          return 2;
        }
        goto switchD_003e9a71_caseD_b23;
      }
      if (uVar2 - 0x14d4 < 4) {
        return 6;
      }
      if (uVar2 == 0x14e3) {
        return 6;
      }
      uVar2 = uVar2 - 0x14f6;
joined_r0x003e9b0c:
      if (uVar2 < 4) {
        return 6;
      }
      goto switchD_003e9a71_caseD_b23;
    }
    if (0x16d2 < uVar2) {
      switch(uVar2) {
      case 0x16da:
      case 0x16dc:
      case 0x16df:
      case 0x16e0:
      case 0x16e1:
      case 0x16e3:
      case 0x16e4:
      case 0x16e8:
      case 0x16e9:
        return 6;
      }
      goto switchD_003e9a71_caseD_b23;
    }
    if (uVar2 == 0x16d2) {
      return 6;
    }
    if (0x16c1 < uVar2) {
      if (uVar2 - 0x16c2 < 2) {
        return 6;
      }
      uVar2 = uVar2 - 0x16c5;
      goto joined_r0x003e9bb1;
    }
    if (uVar2 - 0x16b8 < 2) {
      return 6;
    }
    uVar2 = uVar2 - 0x16bb;
  }
joined_r0x003e9d08:
  if (uVar2 < 2) {
    return 6;
  }
switchD_003e9a71_caseD_b23:
  FUN_00431c8c(*(undefined4 *)PTR_DAT_004c94d4,param_2,local_1c8);
  if ((byte)(local_29 - 1U) < 4) {
    return 6;
  }
  return 0;
}

