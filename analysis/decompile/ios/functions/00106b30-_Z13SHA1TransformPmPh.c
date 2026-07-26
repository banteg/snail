/*
 * mangled: _Z13SHA1TransformPmPh
 * demangled: SHA1Transform(unsigned long*, unsigned char*)
 * address: 00106b30
 * size: 5636
 */

/* SHA1Transform(unsigned long*, unsigned char*) */

void SHA1Transform(ulong *param_1,uchar *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;

  uVar9 = *param_1;
  uVar17 = *(uint *)param_2;
  uVar11 = param_1[2];
  uVar7 = param_1[3];
  uVar1 = uVar17 >> 0x18 | (uVar17 & 0xff00) << 8 | uVar17 >> 8 & 0xff00ff00 | uVar17 << 0x18;
  uVar17 = param_1[1];
  uVar18 = *(uint *)(param_2 + 4);
  uVar24 = uVar1 + 0x5a827999 + param_1[4] + (uVar9 >> 0x1b | uVar9 << 5) +
           ((uVar7 ^ uVar11) & uVar17 ^ uVar7);
  uVar18 = uVar18 >> 0x18 | (uVar18 & 0xff00) << 8 | uVar18 >> 8 & 0xff00ff00 | uVar18 << 0x18;
  uVar17 = uVar17 >> 2 | uVar17 << 0x1e;
  uVar19 = *(uint *)(param_2 + 8);
  uVar8 = uVar18 + 0x5a827999 + uVar7 + ((uVar17 ^ uVar11) & uVar9 ^ uVar11) +
          (uVar24 >> 0x1b | uVar24 * 0x20);
  uVar19 = uVar19 >> 0x18 | (uVar19 & 0xff00) << 8 | uVar19 >> 8 & 0xff00ff00 | uVar19 << 0x18;
  uVar7 = uVar9 >> 2 | uVar9 << 0x1e;
  uVar9 = *(uint *)(param_2 + 0xc);
  uVar14 = uVar19 + 0x5a827999 + uVar11 + (uVar24 & (uVar17 ^ uVar7) ^ uVar17) +
           (uVar8 >> 0x1b | uVar8 * 0x20);
  uVar2 = uVar9 >> 0x18 | (uVar9 & 0xff00) << 8 | uVar9 >> 8 & 0xff00ff00 | uVar9 << 0x18;
  uVar9 = uVar24 >> 2 | uVar24 * 0x40000000;
  uVar24 = *(uint *)(param_2 + 0x10);
  uVar11 = uVar2 + 0x5a827999 + uVar17 + ((uVar9 ^ uVar7) & uVar8 ^ uVar7) +
           (uVar14 >> 0x1b | uVar14 * 0x20);
  uVar24 = uVar24 >> 0x18 | (uVar24 & 0xff00) << 8 | uVar24 >> 8 & 0xff00ff00 | uVar24 << 0x18;
  uVar17 = uVar8 >> 2 | uVar8 * 0x40000000;
  uVar20 = *(uint *)(param_2 + 0x14);
  uVar8 = uVar24 + 0x5a827999 + uVar7 + ((uVar17 ^ uVar9) & uVar14 ^ uVar9) +
          (uVar11 >> 0x1b | uVar11 * 0x20);
  uVar20 = uVar20 >> 0x18 | (uVar20 & 0xff00) << 8 | uVar20 >> 8 & 0xff00ff00 | uVar20 << 0x18;
  uVar7 = uVar14 >> 2 | uVar14 * 0x40000000;
  uVar14 = *(uint *)(param_2 + 0x18);
  uVar25 = uVar20 + 0x5a827999 + uVar9 + ((uVar7 ^ uVar17) & uVar11 ^ uVar17) +
           (uVar8 >> 0x1b | uVar8 * 0x20);
  uVar14 = uVar14 >> 0x18 | (uVar14 & 0xff00) << 8 | uVar14 >> 8 & 0xff00ff00 | uVar14 << 0x18;
  uVar9 = uVar11 >> 2 | uVar11 * 0x40000000;
  uVar11 = *(uint *)(param_2 + 0x1c);
  uVar15 = uVar14 + 0x5a827999 + uVar17 + ((uVar9 ^ uVar7) & uVar8 ^ uVar7) +
           (uVar25 >> 0x1b | uVar25 * 0x20);
  uVar3 = uVar11 >> 0x18 | (uVar11 & 0xff00) << 8 | uVar11 >> 8 & 0xff00ff00 | uVar11 << 0x18;
  uVar17 = uVar8 >> 2 | uVar8 * 0x40000000;
  uVar8 = *(uint *)(param_2 + 0x20);
  uVar11 = uVar3 + 0x5a827999 + uVar7 + ((uVar17 ^ uVar9) & uVar25 ^ uVar9) +
           (uVar15 >> 0x1b | uVar15 * 0x20);
  uVar4 = uVar8 >> 0x18 | (uVar8 & 0xff00) << 8 | uVar8 >> 8 & 0xff00ff00 | uVar8 << 0x18;
  uVar7 = uVar25 >> 2 | uVar25 * 0x40000000;
  uVar25 = *(uint *)(param_2 + 0x24);
  uVar8 = uVar4 + 0x5a827999 + uVar9 + ((uVar7 ^ uVar17) & uVar15 ^ uVar17) +
          (uVar11 >> 0x1b | uVar11 * 0x20);
  uVar25 = uVar25 >> 0x18 | (uVar25 & 0xff00) << 8 | uVar25 >> 8 & 0xff00ff00 | uVar25 << 0x18;
  uVar9 = uVar15 >> 2 | uVar15 * 0x40000000;
  uVar15 = *(uint *)(param_2 + 0x28);
  uVar12 = uVar25 + 0x5a827999 + uVar17 + ((uVar9 ^ uVar7) & uVar11 ^ uVar7) +
           (uVar8 >> 0x1b | uVar8 * 0x20);
  uVar15 = uVar15 >> 0x18 | (uVar15 & 0xff00) << 8 | uVar15 >> 8 & 0xff00ff00 | uVar15 << 0x18;
  uVar17 = uVar11 >> 2 | uVar11 * 0x40000000;
  uVar21 = *(uint *)(param_2 + 0x2c);
  uVar11 = uVar15 + 0x5a827999 + uVar7 + ((uVar17 ^ uVar9) & uVar8 ^ uVar9) +
           (uVar12 >> 0x1b | uVar12 * 0x20);
  uVar21 = uVar21 >> 0x18 | (uVar21 & 0xff00) << 8 | uVar21 >> 8 & 0xff00ff00 | uVar21 << 0x18;
  uVar7 = uVar8 >> 2 | uVar8 * 0x40000000;
  uVar8 = *(uint *)(param_2 + 0x30);
  uVar16 = uVar21 + 0x5a827999 + uVar9 + ((uVar7 ^ uVar17) & uVar12 ^ uVar17) +
           (uVar11 >> 0x1b | uVar11 * 0x20);
  uVar5 = uVar8 >> 0x18 | (uVar8 & 0xff00) << 8 | uVar8 >> 8 & 0xff00ff00 | uVar8 << 0x18;
  uVar9 = uVar12 >> 2 | uVar12 * 0x40000000;
  uVar8 = *(uint *)(param_2 + 0x34);
  uVar13 = uVar5 + 0x5a827999 + uVar17 + ((uVar9 ^ uVar7) & uVar11 ^ uVar7) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar12 = uVar8 >> 0x18 | (uVar8 & 0xff00) << 8 | uVar8 >> 8 & 0xff00ff00 | uVar8 << 0x18;
  uVar17 = uVar11 >> 2 | uVar11 * 0x40000000;
  uVar11 = *(uint *)(param_2 + 0x38);
  uVar8 = uVar12 + 0x5a827999 + uVar7 + ((uVar17 ^ uVar9) & uVar16 ^ uVar9) +
          (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar6 = uVar11 >> 0x18 | (uVar11 & 0xff00) << 8 | uVar11 >> 8 & 0xff00ff00 | uVar11 << 0x18;
  uVar7 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar11 = *(uint *)(param_2 + 0x3c);
  uVar10 = uVar6 + 0x5a827999 + uVar9 + ((uVar7 ^ uVar17) & uVar13 ^ uVar17) +
           (uVar8 >> 0x1b | uVar8 * 0x20);
  uVar16 = uVar11 >> 0x18 | (uVar11 & 0xff00) << 8 | uVar11 >> 8 & 0xff00ff00 | uVar11 << 0x18;
  uVar9 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar11 = uVar8 >> 2 | uVar8 * 0x40000000;
  uVar8 = uVar16 + 0x5a827999 + uVar17 + ((uVar9 ^ uVar7) & uVar8 ^ uVar7) +
          (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar1 = uVar4 ^ uVar12 ^ uVar19 ^ uVar1;
  uVar17 = uVar1 >> 0x1f | uVar1 << 1;
  uVar1 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar10 = uVar17 + 0x5a827999 + uVar7 + ((uVar11 ^ uVar9) & uVar10 ^ uVar9) +
           (uVar8 >> 0x1b | uVar8 * 0x20);
  uVar18 = uVar25 ^ uVar6 ^ uVar2 ^ uVar18;
  uVar7 = uVar18 >> 0x1f | uVar18 << 1;
  uVar18 = uVar8 >> 2 | uVar8 * 0x40000000;
  uVar13 = uVar7 + 0x5a827999 + uVar9 + ((uVar1 ^ uVar11) & uVar8 ^ uVar11) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar9 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar19 = uVar15 ^ uVar16 ^ uVar24 ^ uVar19;
  uVar8 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar19 = uVar19 >> 0x1f | uVar19 << 1;
  uVar10 = uVar19 + 0x5a827999 + uVar11 + ((uVar18 ^ uVar1) & uVar10 ^ uVar1) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar2 = uVar21 ^ uVar17 ^ uVar20 ^ uVar2;
  uVar11 = uVar2 >> 0x1f | uVar2 << 1;
  uVar13 = uVar11 + 0x5a827999 + uVar1 + ((uVar8 ^ uVar18) & uVar13 ^ uVar18) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar24 = uVar5 ^ uVar7 ^ uVar14 ^ uVar24;
  uVar1 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar2 = uVar24 >> 0x1f | uVar24 << 1;
  uVar22 = uVar2 + 0x6ed9eba1 + uVar18 + (uVar9 ^ uVar8 ^ uVar10) + (uVar13 >> 0x1b | uVar13 * 0x20)
  ;
  uVar20 = uVar12 ^ uVar19 ^ uVar3 ^ uVar20;
  uVar18 = uVar20 >> 0x1f | uVar20 << 1;
  uVar24 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar10 = uVar18 + 0x6ed9eba1 + uVar8 + (uVar1 ^ uVar9 ^ uVar13) + (uVar22 >> 0x1b | uVar22 * 0x20)
  ;
  uVar14 = uVar6 ^ uVar11 ^ uVar4 ^ uVar14;
  uVar8 = uVar14 >> 0x1f | uVar14 << 1;
  uVar13 = uVar8 + 0x6ed9eba1 + uVar9 + (uVar24 ^ uVar1 ^ uVar22) + (uVar10 >> 0x1b | uVar10 * 0x20)
  ;
  uVar9 = uVar22 >> 2 | uVar22 * 0x40000000;
  uVar3 = uVar16 ^ uVar2 ^ uVar25 ^ uVar3;
  uVar20 = uVar3 >> 0x1f | uVar3 << 1;
  uVar26 = uVar20 + 0x6ed9eba1 + uVar1 + (uVar9 ^ uVar24 ^ uVar10) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar1 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar4 = uVar17 ^ uVar18 ^ uVar15 ^ uVar4;
  uVar14 = uVar4 >> 0x1f | uVar4 << 1;
  uVar22 = uVar14 + 0x6ed9eba1 + uVar24 + (uVar1 ^ uVar9 ^ uVar13) +
           (uVar26 >> 0x1b | uVar26 * 0x20);
  uVar24 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar25 = uVar7 ^ uVar8 ^ uVar21 ^ uVar25;
  uVar3 = uVar25 >> 0x1f | uVar25 << 1;
  uVar23 = uVar3 + 0x6ed9eba1 + uVar9 + (uVar24 ^ uVar1 ^ uVar26) + (uVar22 >> 0x1b | uVar22 * 0x20)
  ;
  uVar9 = uVar26 >> 2 | uVar26 * 0x40000000;
  uVar15 = uVar19 ^ uVar20 ^ uVar5 ^ uVar15;
  uVar4 = uVar15 >> 0x1f | uVar15 << 1;
  uVar10 = uVar4 + 0x6ed9eba1 + uVar1 + (uVar9 ^ uVar24 ^ uVar22) + (uVar23 >> 0x1b | uVar23 * 0x20)
  ;
  uVar1 = uVar22 >> 2 | uVar22 * 0x40000000;
  uVar21 = uVar11 ^ uVar14 ^ uVar12 ^ uVar21;
  uVar25 = uVar21 >> 0x1f | uVar21 << 1;
  uVar13 = uVar25 + 0x6ed9eba1 + uVar24 + (uVar1 ^ uVar9 ^ uVar23) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar24 = uVar23 >> 2 | uVar23 * 0x40000000;
  uVar5 = uVar2 ^ uVar3 ^ uVar6 ^ uVar5;
  uVar15 = uVar5 >> 0x1f | uVar5 << 1;
  uVar22 = uVar15 + 0x6ed9eba1 + uVar9 + (uVar24 ^ uVar1 ^ uVar10) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar9 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar12 = uVar18 ^ uVar4 ^ uVar16 ^ uVar12;
  uVar21 = uVar12 >> 0x1f | uVar12 << 1;
  uVar10 = uVar21 + 0x6ed9eba1 + uVar1 + (uVar9 ^ uVar24 ^ uVar13) +
           (uVar22 >> 0x1b | uVar22 * 0x20);
  uVar1 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar6 = uVar8 ^ uVar25 ^ uVar17 ^ uVar6;
  uVar5 = uVar6 >> 0x1f | uVar6 << 1;
  uVar6 = uVar5 + 0x6ed9eba1 + uVar24 + (uVar1 ^ uVar9 ^ uVar22) + (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar24 = uVar22 >> 2 | uVar22 * 0x40000000;
  uVar16 = uVar20 ^ uVar15 ^ uVar7 ^ uVar16;
  uVar12 = uVar16 >> 0x1f | uVar16 << 1;
  uVar16 = uVar12 + 0x6ed9eba1 + uVar9 + (uVar24 ^ uVar1 ^ uVar10) + (uVar6 >> 0x1b | uVar6 * 0x20);
  uVar9 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar17 = uVar14 ^ uVar21 ^ uVar19 ^ uVar17;
  uVar17 = uVar17 >> 0x1f | uVar17 << 1;
  uVar10 = uVar17 + 0x6ed9eba1 + uVar1 + (uVar9 ^ uVar24 ^ uVar6) + (uVar16 >> 0x1b | uVar16 * 0x20)
  ;
  uVar1 = uVar6 >> 2 | uVar6 * 0x40000000;
  uVar7 = uVar3 ^ uVar5 ^ uVar11 ^ uVar7;
  uVar6 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar7 = uVar7 >> 0x1f | uVar7 << 1;
  uVar13 = uVar7 + 0x6ed9eba1 + uVar24 + (uVar1 ^ uVar9 ^ uVar16) + (uVar10 >> 0x1b | uVar10 * 0x20)
  ;
  uVar19 = uVar4 ^ uVar12 ^ uVar2 ^ uVar19;
  uVar19 = uVar19 >> 0x1f | uVar19 << 1;
  uVar16 = uVar19 + 0x6ed9eba1 + uVar9 + (uVar6 ^ uVar1 ^ uVar10) + (uVar13 >> 0x1b | uVar13 * 0x20)
  ;
  uVar9 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar11 = uVar25 ^ uVar17 ^ uVar18 ^ uVar11;
  uVar24 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar11 = uVar11 >> 0x1f | uVar11 << 1;
  uVar10 = uVar11 + 0x6ed9eba1 + uVar1 + (uVar9 ^ uVar6 ^ uVar13) + (uVar16 >> 0x1b | uVar16 * 0x20)
  ;
  uVar2 = uVar15 ^ uVar7 ^ uVar8 ^ uVar2;
  uVar1 = uVar2 >> 0x1f | uVar2 << 1;
  uVar22 = uVar1 + 0x6ed9eba1 + uVar6 + (uVar24 ^ uVar9 ^ uVar16) + (uVar10 >> 0x1b | uVar10 * 0x20)
  ;
  uVar2 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar6 = uVar22 >> 2 | uVar22 * 0x40000000;
  uVar18 = uVar21 ^ uVar19 ^ uVar20 ^ uVar18;
  uVar16 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar18 = uVar18 >> 0x1f | uVar18 << 1;
  uVar13 = uVar18 + 0x6ed9eba1 + uVar9 + (uVar2 ^ uVar24 ^ uVar10) +
           (uVar22 >> 0x1b | uVar22 * 0x20);
  uVar8 = uVar5 ^ uVar11 ^ uVar14 ^ uVar8;
  uVar9 = uVar8 >> 0x1f | uVar8 << 1;
  uVar22 = uVar9 + 0x6ed9eba1 + uVar24 + (uVar16 ^ uVar2 ^ uVar22) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar20 = uVar12 ^ uVar1 ^ uVar3 ^ uVar20;
  uVar8 = uVar20 >> 0x1f | uVar20 << 1;
  uVar10 = uVar8 + 0x6ed9eba1 + uVar2 + (uVar6 ^ uVar16 ^ uVar13) + (uVar22 >> 0x1b | uVar22 * 0x20)
  ;
  uVar2 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar14 = uVar17 ^ uVar18 ^ uVar4 ^ uVar14;
  uVar24 = uVar22 >> 2 | uVar22 * 0x40000000;
  uVar20 = uVar14 >> 0x1f | uVar14 << 1;
  uVar13 = uVar20 + 0x8f1bbcdc + uVar16 + ((uVar22 | uVar2) & uVar6 | uVar22 & uVar2) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar3 = uVar7 ^ uVar9 ^ uVar25 ^ uVar3;
  uVar14 = uVar3 >> 0x1f | uVar3 << 1;
  uVar3 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar16 = uVar14 + 0x8f1bbcdc + uVar6 + ((uVar10 | uVar24) & uVar2 | uVar10 & uVar24) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar4 = uVar19 ^ uVar8 ^ uVar15 ^ uVar4;
  uVar4 = uVar4 >> 0x1f | uVar4 << 1;
  uVar6 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar10 = uVar4 + 0x8f1bbcdc + uVar2 + ((uVar13 | uVar3) & uVar24 | uVar13 & uVar3) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar25 = uVar11 ^ uVar20 ^ uVar21 ^ uVar25;
  uVar2 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar25 = uVar25 >> 0x1f | uVar25 << 1;
  uVar13 = uVar25 + 0x8f1bbcdc + uVar24 + ((uVar16 | uVar6) & uVar3 | uVar16 & uVar6) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar15 = uVar1 ^ uVar14 ^ uVar5 ^ uVar15;
  uVar24 = uVar15 >> 0x1f | uVar15 << 1;
  uVar16 = uVar24 + 0x8f1bbcdc + uVar3 + ((uVar10 | uVar2) & uVar6 | uVar10 & uVar2) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar3 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar21 = uVar18 ^ uVar4 ^ uVar12 ^ uVar21;
  uVar15 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar21 = uVar21 >> 0x1f | uVar21 << 1;
  uVar13 = uVar21 + 0x8f1bbcdc + uVar6 + ((uVar13 | uVar3) & uVar2 | uVar13 & uVar3) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar5 = uVar9 ^ uVar25 ^ uVar17 ^ uVar5;
  uVar5 = uVar5 >> 0x1f | uVar5 << 1;
  uVar6 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar10 = uVar5 + 0x8f1bbcdc + uVar2 + ((uVar16 | uVar15) & uVar3 | uVar16 & uVar15) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar12 = uVar8 ^ uVar24 ^ uVar7 ^ uVar12;
  uVar2 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar12 = uVar12 >> 0x1f | uVar12 << 1;
  uVar16 = uVar12 + 0x8f1bbcdc + uVar3 + ((uVar13 | uVar6) & uVar15 | uVar13 & uVar6) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar17 = uVar20 ^ uVar21 ^ uVar19 ^ uVar17;
  uVar17 = uVar17 >> 0x1f | uVar17 << 1;
  uVar13 = uVar17 + 0x8f1bbcdc + uVar15 + ((uVar10 | uVar2) & uVar6 | uVar10 & uVar2) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar3 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar7 = uVar14 ^ uVar5 ^ uVar11 ^ uVar7;
  uVar7 = uVar7 >> 0x1f | uVar7 << 1;
  uVar10 = uVar7 + 0x8f1bbcdc + uVar6 + ((uVar16 | uVar3) & uVar2 | uVar16 & uVar3) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar15 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar19 = uVar4 ^ uVar12 ^ uVar1 ^ uVar19;
  uVar6 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar19 = uVar19 >> 0x1f | uVar19 << 1;
  uVar16 = uVar19 + 0x8f1bbcdc + uVar2 + ((uVar13 | uVar15) & uVar3 | uVar13 & uVar15) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar11 = uVar25 ^ uVar17 ^ uVar18 ^ uVar11;
  uVar2 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar11 = uVar11 >> 0x1f | uVar11 << 1;
  uVar13 = uVar11 + 0x8f1bbcdc + uVar3 + ((uVar10 | uVar6) & uVar15 | uVar10 & uVar6) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar3 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar1 = uVar24 ^ uVar7 ^ uVar9 ^ uVar1;
  uVar1 = uVar1 >> 0x1f | uVar1 << 1;
  uVar10 = uVar1 + 0x8f1bbcdc + uVar15 + ((uVar16 | uVar3) & uVar6 | uVar16 & uVar3) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar18 = uVar21 ^ uVar19 ^ uVar8 ^ uVar18;
  uVar18 = uVar18 >> 0x1f | uVar18 << 1;
  *(uint *)(param_2 + 0x14) = uVar18;
  uVar16 = uVar18 + 0x8f1bbcdc + uVar6 + ((uVar13 | uVar2) & uVar3 | uVar13 & uVar2) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar15 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar9 = uVar5 ^ uVar11 ^ uVar20 ^ uVar9;
  uVar6 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar9 = uVar9 >> 0x1f | uVar9 << 1;
  *(uint *)(param_2 + 0x18) = uVar9;
  uVar10 = uVar9 + 0x8f1bbcdc + uVar3 + ((uVar10 | uVar15) & uVar2 | uVar10 & uVar15) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar8 = uVar12 ^ uVar1 ^ uVar14 ^ uVar8;
  uVar3 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar8 = uVar8 >> 0x1f | uVar8 << 1;
  *(uint *)(param_2 + 0x1c) = uVar8;
  uVar16 = uVar8 + 0x8f1bbcdc + uVar2 + ((uVar16 | uVar6) & uVar15 | uVar16 & uVar6) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar2 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar20 = uVar17 ^ uVar18 ^ uVar4 ^ uVar20;
  uVar20 = uVar20 >> 0x1f | uVar20 << 1;
  *(uint *)(param_2 + 0x20) = uVar20;
  uVar13 = uVar20 + 0x8f1bbcdc + uVar15 + ((uVar10 | uVar3) & uVar6 | uVar10 & uVar3) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar15 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar14 = uVar7 ^ uVar9 ^ uVar25 ^ uVar14;
  uVar14 = uVar14 >> 0x1f | uVar14 << 1;
  *(uint *)(param_2 + 0x24) = uVar14;
  uVar10 = uVar14 + 0x8f1bbcdc + uVar6 + ((uVar16 | uVar15) & uVar3 | uVar16 & uVar15) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar6 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar4 = uVar19 ^ uVar8 ^ uVar24 ^ uVar4;
  uVar4 = uVar4 >> 0x1f | uVar4 << 1;
  *(uint *)(param_2 + 0x28) = uVar4;
  uVar16 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar13 = uVar4 + 0x8f1bbcdc + uVar3 + ((uVar13 | uVar2) & uVar15 | uVar13 & uVar2) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar25 = uVar11 ^ uVar20 ^ uVar21 ^ uVar25;
  uVar3 = uVar25 >> 0x1f | uVar25 << 1;
  *(uint *)(param_2 + 0x2c) = uVar3;
  uVar22 = uVar3 + 0x8f1bbcdc + uVar15 + ((uVar10 | uVar16) & uVar2 | uVar10 & uVar16) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar24 = uVar1 ^ uVar14 ^ uVar5 ^ uVar24;
  uVar25 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar24 = uVar24 >> 0x1f | uVar24 << 1;
  *(uint *)(param_2 + 0x30) = uVar24;
  uVar10 = uVar24 + 0xca62c1d6 + uVar2 + (uVar6 ^ uVar16 ^ uVar13) +
           (uVar22 >> 0x1b | uVar22 * 0x20);
  uVar21 = uVar18 ^ uVar4 ^ uVar12 ^ uVar21;
  uVar2 = uVar21 >> 0x1f | uVar21 << 1;
  *(uint *)(param_2 + 0x34) = uVar2;
  uVar15 = uVar22 >> 2 | uVar22 * 0x40000000;
  uVar16 = uVar2 + 0xca62c1d6 + uVar16 + (uVar25 ^ uVar6 ^ uVar22) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar5 = uVar9 ^ uVar3 ^ uVar17 ^ uVar5;
  uVar21 = uVar5 >> 0x1f | uVar5 << 1;
  *(uint *)(param_2 + 0x38) = uVar21;
  uVar6 = uVar21 + 0xca62c1d6 + uVar6 + (uVar15 ^ uVar25 ^ uVar10) +
          (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar5 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar12 = uVar8 ^ uVar24 ^ uVar7 ^ uVar12;
  uVar12 = uVar12 >> 0x1f | uVar12 << 1;
  *(uint *)(param_2 + 0x3c) = uVar12;
  uVar13 = uVar12 + 0xca62c1d6 + uVar25 + (uVar5 ^ uVar15 ^ uVar16) + (uVar6 >> 0x1b | uVar6 * 0x20)
  ;
  uVar25 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar17 = uVar20 ^ uVar2 ^ uVar19 ^ uVar17;
  uVar17 = uVar17 >> 0x1f | uVar17 << 1;
  *(uint *)param_2 = uVar17;
  uVar16 = uVar17 + 0xca62c1d6 + uVar15 + (uVar25 ^ uVar5 ^ uVar6) +
           (uVar13 >> 0x1b | uVar13 * 0x20);
  uVar15 = uVar6 >> 2 | uVar6 * 0x40000000;
  uVar7 = uVar14 ^ uVar21 ^ uVar11 ^ uVar7;
  uVar7 = uVar7 >> 0x1f | uVar7 << 1;
  *(uint *)(param_2 + 4) = uVar7;
  uVar10 = uVar7 + 0xca62c1d6 + uVar5 + (uVar15 ^ uVar25 ^ uVar13) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar5 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar19 = uVar4 ^ uVar12 ^ uVar1 ^ uVar19;
  uVar19 = uVar19 >> 0x1f | uVar19 << 1;
  *(uint *)(param_2 + 8) = uVar19;
  uVar6 = uVar19 + 0xca62c1d6 + uVar25 + (uVar5 ^ uVar15 ^ uVar16) +
          (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar25 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar11 = uVar3 ^ uVar17 ^ uVar18 ^ uVar11;
  uVar11 = uVar11 >> 0x1f | uVar11 << 1;
  *(uint *)(param_2 + 0xc) = uVar11;
  uVar16 = uVar11 + 0xca62c1d6 + uVar15 + (uVar25 ^ uVar5 ^ uVar10) + (uVar6 >> 0x1b | uVar6 * 0x20)
  ;
  uVar15 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar1 = uVar24 ^ uVar7 ^ uVar9 ^ uVar1;
  uVar1 = uVar1 >> 0x1f | uVar1 << 1;
  *(uint *)(param_2 + 0x10) = uVar1;
  uVar10 = uVar1 + 0xca62c1d6 + uVar5 + (uVar15 ^ uVar25 ^ uVar6) + (uVar16 >> 0x1b | uVar16 * 0x20)
  ;
  uVar18 = uVar2 ^ uVar19 ^ uVar8 ^ uVar18;
  uVar5 = uVar6 >> 2 | uVar6 * 0x40000000;
  uVar18 = uVar18 >> 0x1f | uVar18 << 1;
  *(uint *)(param_2 + 0x14) = uVar18;
  uVar6 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar16 = uVar18 + 0xca62c1d6 + uVar25 + (uVar5 ^ uVar15 ^ uVar16) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar9 = uVar21 ^ uVar11 ^ uVar20 ^ uVar9;
  uVar9 = uVar9 >> 0x1f | uVar9 << 1;
  *(uint *)(param_2 + 0x18) = uVar9;
  uVar13 = uVar9 + 0xca62c1d6 + uVar15 + (uVar6 ^ uVar5 ^ uVar10) + (uVar16 >> 0x1b | uVar16 * 0x20)
  ;
  uVar25 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar8 = uVar12 ^ uVar1 ^ uVar14 ^ uVar8;
  uVar15 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar8 = uVar8 >> 0x1f | uVar8 << 1;
  *(uint *)(param_2 + 0x1c) = uVar8;
  uVar16 = uVar8 + 0xca62c1d6 + uVar5 + (uVar25 ^ uVar6 ^ uVar16) + (uVar13 >> 0x1b | uVar13 * 0x20)
  ;
  uVar20 = uVar17 ^ uVar18 ^ uVar4 ^ uVar20;
  uVar20 = uVar20 >> 0x1f | uVar20 << 1;
  *(uint *)(param_2 + 0x20) = uVar20;
  uVar10 = uVar20 + 0xca62c1d6 + uVar6 + (uVar15 ^ uVar25 ^ uVar13) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar5 = uVar13 >> 2 | uVar13 * 0x40000000;
  uVar14 = uVar7 ^ uVar9 ^ uVar3 ^ uVar14;
  uVar6 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar14 = uVar14 >> 0x1f | uVar14 << 1;
  *(uint *)(param_2 + 0x24) = uVar14;
  uVar16 = uVar14 + 0xca62c1d6 + uVar25 + (uVar5 ^ uVar15 ^ uVar16) +
           (uVar10 >> 0x1b | uVar10 * 0x20);
  uVar4 = uVar19 ^ uVar8 ^ uVar24 ^ uVar4;
  uVar19 = uVar4 >> 0x1f | uVar4 << 1;
  *(uint *)(param_2 + 0x28) = uVar19;
  uVar4 = uVar10 >> 2 | uVar10 * 0x40000000;
  uVar25 = uVar19 + 0xca62c1d6 + uVar15 + (uVar6 ^ uVar5 ^ uVar10) +
           (uVar16 >> 0x1b | uVar16 * 0x20);
  uVar3 = uVar11 ^ uVar20 ^ uVar2 ^ uVar3;
  uVar11 = uVar16 >> 2 | uVar16 * 0x40000000;
  uVar20 = uVar3 >> 0x1f | uVar3 << 1;
  *(uint *)(param_2 + 0x2c) = uVar20;
  uVar3 = uVar20 + 0xca62c1d6 + uVar5 + (uVar4 ^ uVar6 ^ uVar16) + (uVar25 >> 0x1b | uVar25 * 0x20);
  uVar24 = uVar1 ^ uVar14 ^ uVar21 ^ uVar24;
  uVar1 = uVar24 >> 0x1f | uVar24 << 1;
  *(uint *)(param_2 + 0x30) = uVar1;
  uVar24 = uVar25 >> 2 | uVar25 * 0x40000000;
  uVar14 = uVar1 + 0xca62c1d6 + uVar6 + (uVar11 ^ uVar4 ^ uVar25) + (uVar3 >> 0x1b | uVar3 * 0x20);
  uVar2 = uVar18 ^ uVar19 ^ uVar12 ^ uVar2;
  uVar18 = uVar2 >> 0x1f | uVar2 << 1;
  *(uint *)(param_2 + 0x34) = uVar18;
  uVar19 = uVar18 + 0xca62c1d6 + uVar4 + (uVar24 ^ uVar11 ^ uVar3) +
           (uVar14 >> 0x1b | uVar14 * 0x20);
  uVar18 = uVar3 >> 2 | uVar3 * 0x40000000;
  uVar21 = uVar9 ^ uVar20 ^ uVar17 ^ uVar21;
  uVar17 = uVar21 >> 0x1f | uVar21 << 1;
  *(uint *)(param_2 + 0x38) = uVar17;
  uVar9 = uVar17 + 0xca62c1d6 + uVar11 + (uVar18 ^ uVar24 ^ uVar14) +
          (uVar19 >> 0x1b | uVar19 * 0x20);
  uVar17 = uVar14 >> 2 | uVar14 * 0x40000000;
  uVar12 = uVar8 ^ uVar1 ^ uVar7 ^ uVar12;
  uVar7 = uVar12 >> 0x1f | uVar12 << 1;
  *(uint *)(param_2 + 0x3c) = uVar7;
  *param_1 = *param_1 + 0xca62c1d6 + uVar7 + uVar24 + (uVar17 ^ uVar18 ^ uVar19) +
             (uVar9 >> 0x1b | uVar9 * 0x20);
  param_1[1] = param_1[1] + uVar9;
  param_1[2] = param_1[2] + (uVar19 >> 2 | uVar19 * 0x40000000);
  param_1[3] = param_1[3] + uVar17;
  param_1[4] = param_1[4] + uVar18;
  return;
}
