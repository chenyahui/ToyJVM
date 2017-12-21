#include <jvm/instruction/base_instruction.h>
#include <jvm/instruction/compare_instructions.h>
#include <jvm/instruction/const_instructions.h>
#include <jvm/instruction/control_instructions.h>
#include <jvm/instruction/convert_instructions.h>
#include <jvm/instruction/extended_instructions.h>
#include <jvm/instruction/load_instructions.h>
#include <jvm/instruction/math_instructions.h>
#include <jvm/instruction/stack_instructions.h>
#include <jvm/instruction/store_instructions.h>

namespace cyh {
void BranchJump(JFrame& frame, int offset)
{
    auto thread = frame.Thread();
    auto nextpc = thread->Pc() + offset;

    thread->SetNextPc(nextpc);
}

Instruction* InstructionFactory(u8 opcode)
{
    switch (opcode) {
    case 0x00: {
	new NOP_Instruction();
	break;
    }
    case 0x01: {
	new ACONST_NULL_Instruction();
	break;
    }
    case 0x02: {
	new ICONST_M1_Instruction();
	break;
    }
    case 0x03: {
	new ICONST_0_Instruction();
	break;
    }
    case 0x04: {
	new ICONST_1_Instruction();
	break;
    }
    case 0x05: {
	new ICONST_2_Instruction();
	break;
    }
    case 0x06: {
	new ICONST_3_Instruction();
	break;
    }
    case 0x07: {
	new ICONST_4_Instruction();
	break;
    }
    case 0x08: {
	new ICONST_5_Instruction();
	break;
    }
    case 0x09: {
	new LCONST_0_Instruction();
	break;
    }
    case 0x0a: {
	new LCONST_1_Instruction();
	break;
    }
    case 0x0b: {
	new FCONST_0_Instruction();
	break;
    }
    case 0x0c: {
	new FCONST_1_Instruction();
	break;
    }
    case 0x0d: {
	new FCONST_2_Instruction();
	break;
    }
    case 0x0e: {
	new DCONST_0_Instruction();
	break;
    }
    case 0x0f: {
	new DCONST_1_Instruction();
	break;
    }
    case 0x10: {
	new BIPUSH_Instruction();
	break;
    }
    case 0x11: {
	new SIPUSH_Instruction();
	break;
    }
    case 0x15: {
	new ILOAD_Instruction();
	break;
    }
    case 0x16: {
	new LLOAD_Instruction();
	break;
    }
    case 0x17: {
	new FLOAD_Instruction();
	break;
    }
    case 0x18: {
	new DLOAD_Instruction();
	break;
    }
    case 0x19: {
	new ALOAD_Instruction();
	break;
    }
    case 0x1a: {
	new ILOAD_0_Instruction();
	break;
    }
    case 0x1b: {
	new ILOAD_1_Instruction();
	break;
    }
    case 0x1c: {
	new ILOAD_2_Instruction();
	break;
    }
    case 0x1d: {
	new ILOAD_3_Instruction();
	break;
    }
    case 0x1e: {
	new LLOAD_0_Instruction();
	break;
    }
    case 0x1f: {
	new LLOAD_1_Instruction();
	break;
    }
    case 0x20: {
	new LLOAD_2_Instruction();
	break;
    }
    case 0x21: {
	new LLOAD_3_Instruction();
	break;
    }
    case 0x22: {
	new FLOAD_0_Instruction();
	break;
    }
    case 0x23: {
	new FLOAD_1_Instruction();
	break;
    }
    case 0x24: {
	new FLOAD_2_Instruction();
	break;
    }
    case 0x25: {
	new FLOAD_3_Instruction();
	break;
    }
    case 0x26: {
	new DLOAD_0_Instruction();
	break;
    }
    case 0x27: {
	new DLOAD_1_Instruction();
	break;
    }
    case 0x28: {
	new DLOAD_2_Instruction();
	break;
    }
    case 0x29: {
	new DLOAD_3_Instruction();
	break;
    }
    case 0x2a: {
	new ALOAD_0_Instruction();
	break;
    }
    case 0x2b: {
	new ALOAD_1_Instruction();
	break;
    }
    case 0x2c: {
	new ALOAD_2_Instruction();
	break;
    }
    case 0x2d: {
	new ALOAD_3_Instruction();
	break;
    }
    case 0x36: {
	new ISTORE_Instruction();
	break;
    }
    case 0x37: {
	new LSTORE_Instruction();
	break;
    }
    case 0x38: {
	new FSTORE_Instruction();
	break;
    }
    case 0x39: {
	new DSTORE_Instruction();
	break;
    }
    case 0x3a: {
	new ASTORE_Instruction();
	break;
    }
    case 0x3b: {
	new ISTORE_0_Instruction();
	break;
    }
    case 0x3c: {
	new ISTORE_1_Instruction();
	break;
    }
    case 0x3d: {
	new ISTORE_2_Instruction();
	break;
    }
    case 0x3e: {
	new ISTORE_3_Instruction();
	break;
    }
    case 0x3f: {
	new LSTORE_0_Instruction();
	break;
    }
    case 0x40: {
	new LSTORE_1_Instruction();
	break;
    }
    case 0x41: {
	new LSTORE_2_Instruction();
	break;
    }
    case 0x42: {
	new LSTORE_3_Instruction();
	break;
    }
    case 0x43: {
	new FSTORE_0_Instruction();
	break;
    }
    case 0x44: {
	new FSTORE_1_Instruction();
	break;
    }
    case 0x45: {
	new FSTORE_2_Instruction();
	break;
    }
    case 0x46: {
	new FSTORE_3_Instruction();
	break;
    }
    case 0x47: {
	new DSTORE_0_Instruction();
	break;
    }
    case 0x48: {
	new DSTORE_1_Instruction();
	break;
    }
    case 0x49: {
	new DSTORE_2_Instruction();
	break;
    }
    case 0x4a: {
	new DSTORE_3_Instruction();
	break;
    }
    case 0x4b: {
	new ASTORE_0_Instruction();
	break;
    }
    case 0x4c: {
	new ASTORE_1_Instruction();
	break;
    }
    case 0x4d: {
	new ASTORE_2_Instruction();
	break;
    }
    case 0x4e: {
	new ASTORE_3_Instruction();
	break;
    }
    case 0x57: {
	new POP_Instruction();
	break;
    }
    case 0x58: {
	new POP2_Instruction();
	break;
    }
    case 0x59: {
	new DUP_Instruction();
	break;
    }
    case 0x5a: {
	new DUP_X1_Instruction();
	break;
    }
    case 0x5b: {
	new DUP_X2_Instruction();
	break;
    }
    case 0x5c: {
	new DUP2_Instruction();
	break;
    }
    case 0x5d: {
	new DUP2_X1_Instruction();
	break;
    }
    case 0x5e: {
	new DUP2_X2_Instruction();
	break;
    }
    case 0x5f: {
	new SWAP_Instruction();
	break;
    }
    case 0x60: {
	new IADD_Instruction();
	break;
    }
    case 0x61: {
	new LADD_Instruction();
	break;
    }
    case 0x62: {
	new FADD_Instruction();
	break;
    }
    case 0x63: {
	new DADD_Instruction();
	break;
    }
    case 0x64: {
	new ISUB_Instruction();
	break;
    }
    case 0x65: {
	new LSUB_Instruction();
	break;
    }
    case 0x66: {
	new FSUB_Instruction();
	break;
    }
    case 0x67: {
	new DSUB_Instruction();
	break;
    }
    case 0x68: {
	new IMUL_Instruction();
	break;
    }
    case 0x69: {
	new LMUL_Instruction();
	break;
    }
    case 0x6a: {
	new FMUL_Instruction();
	break;
    }
    case 0x6b: {
	new DMUL_Instruction();
	break;
    }
    case 0x6c: {
	new IDIV_Instruction();
	break;
    }
    case 0x6d: {
	new LDIV_Instruction();
	break;
    }
    case 0x6e: {
	new FDIV_Instruction();
	break;
    }
    case 0x6f: {
	new DDIV_Instruction();
	break;
    }
    case 0x70: {
	new IREM_Instruction();
	break;
    }
    case 0x71: {
	new LREM_Instruction();
	break;
    }
    case 0x72: {
	new FREM_Instruction();
	break;
    }
    case 0x73: {
	new DREM_Instruction();
	break;
    }
    case 0x74: {
	new INEG_Instruction();
	break;
    }
    case 0x75: {
	new LNEG_Instruction();
	break;
    }
    case 0x76: {
	new FNEG_Instruction();
	break;
    }
    case 0x77: {
	new DNEG_Instruction();
	break;
    }
    case 0x78: {
	new ISHL_Instruction();
	break;
    }
    case 0x79: {
	new LSHL_Instruction();
	break;
    }
    case 0x7a: {
	new ISHR_Instruction();
	break;
    }
    case 0x7b: {
	new LSHR_Instruction();
	break;
    }
    case 0x7c: {
	new IUSHR_Instruction();
	break;
    }
    case 0x7d: {
	new LUSHR_Instruction();
	break;
    }
    case 0x7e: {
	new IAND_Instruction();
	break;
    }
    case 0x7f: {
	new LAND_Instruction();
	break;
    }
    case 0x80: {
	new IOR_Instruction();
	break;
    }
    case 0x81: {
	new LOR_Instruction();
	break;
    }
    case 0x82: {
	new IXOR_Instruction();
	break;
    }
    case 0x83: {
	new LXOR_Instruction();
	break;
    }
    case 0x84: {
	new IINC_Instruction();
	break;
    }
    case 0x85: {
	new I2L_Instruction();
	break;
    }
    case 0x86: {
	new I2F_Instruction();
	break;
    }
    case 0x87: {
	new I2D_Instruction();
	break;
    }
    case 0x88: {
	new L2I_Instruction();
	break;
    }
    case 0x89: {
	new L2F_Instruction();
	break;
    }
    case 0x8a: {
	new L2D_Instruction();
	break;
    }
    case 0x8b: {
	new F2I_Instruction();
	break;
    }
    case 0x8c: {
	new F2L_Instruction();
	break;
    }
    case 0x8d: {
	new F2D_Instruction();
	break;
    }
    case 0x8e: {
	new D2I_Instruction();
	break;
    }
    case 0x8f: {
	new D2L_Instruction();
	break;
    }
    case 0x90: {
	new D2F_Instruction();
	break;
    }
    case 0x91: {
	new I2B_Instruction();
	break;
    }
    case 0x92: {
	new I2C_Instruction();
	break;
    }
    case 0x93: {
	new I2S_Instruction();
	break;
    }
    case 0x94: {
	new LCMP_Instruction();
	break;
    }
    case 0x95: {
	new FCMPL_Instruction();
	break;
    }
    case 0x96: {
	new FCMPG_Instruction();
	break;
    }
    case 0x97: {
	new DCMPL_Instruction();
	break;
    }
    case 0x98: {
	new DCMPG_Instruction();
	break;
    }
    case 0x99: {
	new IFEQ_Instruction();
	break;
    }
    case 0x9a: {
	new IFNE_Instruction();
	break;
    }
    case 0x9b: {
	new IFLT_Instruction();
	break;
    }
    case 0x9c: {
	new IFGE_Instruction();
	break;
    }
    case 0x9d: {
	new IFGT_Instruction();
	break;
    }
    case 0x9e: {
	new IFLE_Instruction();
	break;
    }
    case 0x9f: {
	new IF_ICMPEQ_Instruction();
	break;
    }
    case 0xa0: {
	new IF_ICMPNE_Instruction();
	break;
    }
    case 0xa1: {
	new IF_ICMPLT_Instruction();
	break;
    }
    case 0xa2: {
	new IF_ICMPGE_Instruction();
	break;
    }
    case 0xa3: {
	new IF_ICMPGT_Instruction();
	break;
    }
    case 0xa4: {
	new IF_ICMPLE_Instruction();
	break;
    }
    case 0xa5: {
	new IF_ACMPEQ_Instruction();
	break;
    }
    case 0xa6: {
	new IF_ACMPNE_Instruction();
	break;
    }
    case 0xa7: {
	new GOTO_Instruction();
	break;
    }
    case 0xaa: {
	new TABLE_SWITCH_Instruction();
	break;
    }
    case 0xab: {
	new LOOKUP_SWITCH_Instruction();
	break;
    }
    case 0xc4: {
	new WIDE_Instruction();
	break;
    }
    case 0xc6: {
	new IFNULL_Instruction();
	break;
    }
    case 0xc7: {
	new IFNONNULL_Instruction();
	break;
    }
    case 0xc8: {
	new GOTO_W_Instruction();
	break;
    }
    }
}
}
