#include <jvm/instruction/array_instructions.h>
#include <jvm/instruction/base_instruction.h>
#include <jvm/instruction/compare_instructions.h>
#include <jvm/instruction/const_instructions.h>
#include <jvm/instruction/control_instructions.h>
#include <jvm/instruction/convert_instructions.h>
#include <jvm/instruction/extended_instructions.h>
#include <jvm/instruction/invoke_instructions.h>
#include <jvm/instruction/load_instructions.h>
#include <jvm/instruction/math_instructions.h>
#include <jvm/instruction/ref_instructions.h>
#include <jvm/instruction/return_instructions.h>
#include <jvm/instruction/stack_instructions.h>
#include <jvm/instruction/store_instructions.h>
#include <jvm/rtdata/jvm_thread.h>

namespace cyh {
void BranchJump(JFrame* frame, int offset)
{
    auto thread = frame->Thread();
    auto nextpc = thread->Pc() + offset;

    frame->SetNextPc(nextpc);
}

Instruction* InstructionFactory(u1 opcode)
{
    switch (opcode) {
    case 0x00: {
	return new NOP_Instruction();
    }
    case 0x01: {
	return new ACONST_NULL_Instruction();
    }
    case 0x02: {
	return new ICONST_M1_Instruction();
    }
    case 0x03: {
	return new ICONST_0_Instruction();
    }
    case 0x04: {
	return new ICONST_1_Instruction();
    }
    case 0x05: {
	return new ICONST_2_Instruction();
    }
    case 0x06: {
	return new ICONST_3_Instruction();
    }
    case 0x07: {
	return new ICONST_4_Instruction();
    }
    case 0x08: {
	return new ICONST_5_Instruction();
    }
    case 0x09: {
	return new LCONST_0_Instruction();
    }
    case 0x0a: {
	return new LCONST_1_Instruction();
    }
    case 0x0b: {
	return new FCONST_0_Instruction();
    }
    case 0x0c: {
	return new FCONST_1_Instruction();
    }
    case 0x0d: {
	return new FCONST_2_Instruction();
    }
    case 0x0e: {
	return new DCONST_0_Instruction();
    }
    case 0x0f: {
	return new DCONST_1_Instruction();
    }
    case 0x10: {
	return new BIPUSH_Instruction();
    }
    case 0x11: {
	return new SIPUSH_Instruction();
    }
    case 0x15: {
	return new ILOAD_Instruction();
    }
    case 0x16: {
	return new LLOAD_Instruction();
    }
    case 0x17: {
	return new FLOAD_Instruction();
    }
    case 0x18: {
	return new DLOAD_Instruction();
    }
    case 0x19: {
	return new ALOAD_Instruction();
    }
    case 0x1a: {
	return new ILOAD_0_Instruction();
    }
    case 0x1b: {
	return new ILOAD_1_Instruction();
    }
    case 0x1c: {
	return new ILOAD_2_Instruction();
    }
    case 0x1d: {
	return new ILOAD_3_Instruction();
    }
    case 0x1e: {
	return new LLOAD_0_Instruction();
    }
    case 0x1f: {
	return new LLOAD_1_Instruction();
    }
    case 0x20: {
	return new LLOAD_2_Instruction();
    }
    case 0x21: {
	return new LLOAD_3_Instruction();
    }
    case 0x22: {
	return new FLOAD_0_Instruction();
    }
    case 0x23: {
	return new FLOAD_1_Instruction();
    }
    case 0x24: {
	return new FLOAD_2_Instruction();
    }
    case 0x25: {
	return new FLOAD_3_Instruction();
    }
    case 0x26: {
	return new DLOAD_0_Instruction();
    }
    case 0x27: {
	return new DLOAD_1_Instruction();
    }
    case 0x28: {
	return new DLOAD_2_Instruction();
    }
    case 0x29: {
	return new DLOAD_3_Instruction();
    }
    case 0x2a: {
	return new ALOAD_0_Instruction();
    }
    case 0x2b: {
	return new ALOAD_1_Instruction();
    }
    case 0x2c: {
	return new ALOAD_2_Instruction();
    }
    case 0x2d: {
	return new ALOAD_3_Instruction();
    }
    case 0x36: {
	return new ISTORE_Instruction();
    }
    case 0x37: {
	return new LSTORE_Instruction();
    }
    case 0x38: {
	return new FSTORE_Instruction();
    }
    case 0x39: {
	return new DSTORE_Instruction();
    }
    case 0x3a: {
	return new ASTORE_Instruction();
    }
    case 0x3b: {
	return new ISTORE_0_Instruction();
    }
    case 0x3c: {
	return new ISTORE_1_Instruction();
    }
    case 0x3d: {
	return new ISTORE_2_Instruction();
    }
    case 0x3e: {
	return new ISTORE_3_Instruction();
    }
    case 0x3f: {
	return new LSTORE_0_Instruction();
    }
    case 0x40: {
	return new LSTORE_1_Instruction();
    }
    case 0x41: {
	return new LSTORE_2_Instruction();
    }
    case 0x42: {
	return new LSTORE_3_Instruction();
    }
    case 0x43: {
	return new FSTORE_0_Instruction();
    }
    case 0x44: {
	return new FSTORE_1_Instruction();
    }
    case 0x45: {
	return new FSTORE_2_Instruction();
    }
    case 0x46: {
	return new FSTORE_3_Instruction();
    }
    case 0x47: {
	return new DSTORE_0_Instruction();
    }
    case 0x48: {
	return new DSTORE_1_Instruction();
    }
    case 0x49: {
	return new DSTORE_2_Instruction();
    }
    case 0x4a: {
	return new DSTORE_3_Instruction();
    }
    case 0x4b: {
	return new ASTORE_0_Instruction();
    }
    case 0x4c: {
	return new ASTORE_1_Instruction();
    }
    case 0x4d: {
	return new ASTORE_2_Instruction();
    }
    case 0x4e: {
	return new ASTORE_3_Instruction();
    }
    case 0x57: {
	return new POP_Instruction();
    }
    case 0x58: {
	return new POP2_Instruction();
    }
    case 0x59: {
	return new DUP_Instruction();
    }
    case 0x5a: {
	return new DUP_X1_Instruction();
    }
    case 0x5b: {
	return new DUP_X2_Instruction();
    }
    case 0x5c: {
	return new DUP2_Instruction();
    }
    case 0x5d: {
	return new DUP2_X1_Instruction();
    }
    case 0x5e: {
	return new DUP2_X2_Instruction();
    }
    case 0x5f: {
	return new SWAP_Instruction();
    }
    case 0x60: {
	return new IADD_Instruction();
    }
    case 0x61: {
	return new LADD_Instruction();
    }
    case 0x62: {
	return new FADD_Instruction();
    }
    case 0x63: {
	return new DADD_Instruction();
    }
    case 0x64: {
	return new ISUB_Instruction();
    }
    case 0x65: {
	return new LSUB_Instruction();
    }
    case 0x66: {
	return new FSUB_Instruction();
    }
    case 0x67: {
	return new DSUB_Instruction();
    }
    case 0x68: {
	return new IMUL_Instruction();
    }
    case 0x69: {
	return new LMUL_Instruction();
    }
    case 0x6a: {
	return new FMUL_Instruction();
    }
    case 0x6b: {
	return new DMUL_Instruction();
    }
    case 0x6c: {
	return new IDIV_Instruction();
    }
    case 0x6d: {
	return new LDIV_Instruction();
    }
    case 0x6e: {
	return new FDIV_Instruction();
    }
    case 0x6f: {
	return new DDIV_Instruction();
    }
    case 0x70: {
	return new IREM_Instruction();
    }
    case 0x71: {
	return new LREM_Instruction();
    }
    case 0x72: {
	return new FREM_Instruction();
    }
    case 0x73: {
	return new DREM_Instruction();
    }
    case 0x74: {
	return new INEG_Instruction();
    }
    case 0x75: {
	return new LNEG_Instruction();
    }
    case 0x76: {
	return new FNEG_Instruction();
    }
    case 0x77: {
	return new DNEG_Instruction();
    }
    case 0x78: {
	return new ISHL_Instruction();
    }
    case 0x79: {
	return new LSHL_Instruction();
    }
    case 0x7a: {
	return new ISHR_Instruction();
    }
    case 0x7b: {
	return new LSHR_Instruction();
    }
    case 0x7c: {
	return new IUSHR_Instruction();
    }
    case 0x7d: {
	return new LUSHR_Instruction();
    }
    case 0x7e: {
	return new IAND_Instruction();
    }
    case 0x7f: {
	return new LAND_Instruction();
    }
    case 0x80: {
	return new IOR_Instruction();
    }
    case 0x81: {
	return new LOR_Instruction();
    }
    case 0x82: {
	return new IXOR_Instruction();
    }
    case 0x83: {
	return new LXOR_Instruction();
    }
    case 0x84: {
	return new IINC_Instruction();
    }
    case 0x85: {
	return new I2L_Instruction();
    }
    case 0x86: {
	return new I2F_Instruction();
    }
    case 0x87: {
	return new I2D_Instruction();
    }
    case 0x88: {
	return new L2I_Instruction();
    }
    case 0x89: {
	return new L2F_Instruction();
    }
    case 0x8a: {
	return new L2D_Instruction();
    }
    case 0x8b: {
	return new F2I_Instruction();
    }
    case 0x8c: {
	return new F2L_Instruction();
    }
    case 0x8d: {
	return new F2D_Instruction();
    }
    case 0x8e: {
	return new D2I_Instruction();
    }
    case 0x8f: {
	return new D2L_Instruction();
    }
    case 0x90: {
	return new D2F_Instruction();
    }
    case 0x91: {
	return new I2B_Instruction();
    }
    case 0x92: {
	return new I2C_Instruction();
    }
    case 0x93: {
	return new I2S_Instruction();
    }
    case 0x94: {
	return new LCMP_Instruction();
    }
    case 0x95: {
	return new FCMPL_Instruction();
    }
    case 0x96: {
	return new FCMPG_Instruction();
    }
    case 0x97: {
	return new DCMPL_Instruction();
    }
    case 0x98: {
	return new DCMPG_Instruction();
    }
    case 0x99: {
	return new IFEQ_Instruction();
    }
    case 0x9a: {
	return new IFNE_Instruction();
    }
    case 0x9b: {
	return new IFLT_Instruction();
    }
    case 0x9c: {
	return new IFGE_Instruction();
    }
    case 0x9d: {
	return new IFGT_Instruction();
    }
    case 0x9e: {
	return new IFLE_Instruction();
    }
    case 0x9f: {
	return new IF_ICMPEQ_Instruction();
    }
    case 0xa0: {
	return new IF_ICMPNE_Instruction();
    }
    case 0xa1: {
	return new IF_ICMPLT_Instruction();
    }
    case 0xa2: {
	return new IF_ICMPGE_Instruction();
    }
    case 0xa3: {
	return new IF_ICMPGT_Instruction();
    }
    case 0xa4: {
	return new IF_ICMPLE_Instruction();
    }
    case 0xa5: {
	return new IF_ACMPEQ_Instruction();
    }
    case 0xa6: {
	return new IF_ACMPNE_Instruction();
    }
    case 0xa7: {
	return new GOTO_Instruction();
    }
    case 0xaa: {
	return new TABLE_SWITCH_Instruction();
    }
    case 0xab: {
	return new LOOKUP_SWITCH_Instruction();
    }
    case 0xc4: {
	return new WIDE_Instruction();
    }
    case 0xc6: {
	return new IFNULL_Instruction();
    }
    case 0xc7: {
	return new IFNONNULL_Instruction();
    }
    case 0xc8: {
	return new GOTO_W_Instruction();
    }
    case 0xbb: {
	return new NEW_Instruction();
    }
    case 0xb5: {
	return new PUTFIELD_Instruction();
    }
    case 0xb3: {
	return new PUTSTATIC_Instruction();
    }
    case 0xb4: {
	return new GETFIELD_Instruction();
    }
    case 0xb2: {
	return new GETSTATIC_Instruction();
    }
    case 0x12: {
	return new LDC_Instruction();
    }
    case 0x13: {
	return new LDC_W_Instruction();
    }
    case 0x14: {
	return new LDC2_W_Instruction();
    }
    case 0xc1: {
	return new INSTANCEOF_Instruction();
    }
    case 0xc0: {
	return new CHECKCAST_Instruction();
    }
    case 0xb7: {
	return new INVOKE_SPECIAL_Instruction();
    }
    case 0xb9: {
	return new INVOKE_INTERFACE_Instruction();
    }
    case 0xb8: {
	return new INVOKE_STATIC_Instruction();
    }
    case 0xb6: {
	return new INVOKE_VIRTUAL_Instruction();
    }
    case 0xac: {
	return new IRETURN_Instruction();
    }
    case 0xad: {
	return new LRETURN_Instruction();
    }
    case 0xae: {
	return new FRETURN_Instruction();
    }
    case 0xaf: {
	return new DRETURN_Instruction();
    }
    case 0xb0: {
	return new ARETURN_Instruction();
    }
    case 0xb1: {
	return new RETURN_Instruction();
    }
    case 0xbc: {
	return new NEW_ARRAY_Instruction();
    }
    case 0xbd: {
	return new ANEW_ARRAY_Instruction();
    }
    case 0xbe: {
	return new ARRAY_LENGTH_Instruction();
    }
    case 0x2e: {
	return new IALOAD_Instruction();
    }
    case 0x2f: {
	return new LALOAD_Instruction();
    }
    case 0x30: {
	return new FALOAD_Instruction();
    }
    case 0x31: {
	return new DALOAD_Instruction();
    }
    case 0x32: {
	return new AALOAD_Instruction();
    }
    case 0x33: {
	return new BALOAD_Instruction();
    }
    case 0x34: {
	return new CALOAD_Instruction();
    }
    case 0x35: {
	return new SALOAD_Instruction();
    }
    case 0x4f: {
	return new IASTORE_Instruction();
    }
    case 0x50: {
	return new LASTORE_Instruction();
    }
    case 0x51: {
	return new FASTORE_Instruction();
    }
    case 0x52: {
	return new DASTORE_Instruction();
    }
    case 0x53: {
	return new AASTORE_Instruction();
    }
    case 0x54: {
	return new BASTORE_Instruction();
    }
    case 0x55: {
	return new CASTORE_Instruction();
    }
    case 0x56: {
	return new SASTORE_Instruction();
    }
    case 0xc5: {
	return new MULTI_ANEW_ARRAY_Instruction();
    }
    case 0xfe: {
	return new INVOKE_NATIVE_Instruction();
    }
    }

    throw "unknown inst";
}
}
