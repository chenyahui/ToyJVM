//
// Created by cyhone on 18-4-26.
//
#include <toyjvm/instruction/instruction_factory.h>
#include <toyjvm/instruction/const_instructions.h>
#include <toyjvm/instruction/compare_instructions.h>
#include <toyjvm/instruction/load_instructions.h>
#include <toyjvm/instruction/store_instructions.h>
#include <toyjvm/instruction/stack_instructions.h>
#include <toyjvm/instruction/math_instructions.h>
#include <toyjvm/instruction/ref_instructions.h>
#include <toyjvm/instruction/extend_instructions.h>
#include <toyjvm/instruction/convert_instructions.h>
#include <toyjvm/instruction/control_instructions.h>
#include <toyjvm/instruction/array_instructions.h>
#include <toyjvm/instruction/return_instructions.h>

namespace jvm {
#define MakeInst(INST) \
    case InstructionTag::INST:{ \
        return new INST##_Instruction(); \
    }

    std::shared_ptr<BaseInstruction> instructionFactory(InstructionTag tag)
    {
        switch (tag) {
            MakeInst(NOP);
            MakeInst(ACONST_NULL);
            MakeInst(ICONST_M1);
            MakeInst(ICONST_0);
            MakeInst(ICONST_1);
            MakeInst(ICONST_2);
            MakeInst(ICONST_3);
            MakeInst(ICONST_4);
            MakeInst(ICONST_5);
            MakeInst(LCONST_0);
            MakeInst(LCONST_1);
            MakeInst(FCONST_0);
            MakeInst(FCONST_1);
            MakeInst(FCONST_2);
            MakeInst(DCONST_0);
            MakeInst(DCONST_1);
            MakeInst(BIPUSH);
            MakeInst(SIPUSH);
            MakeInst(ILOAD);
            MakeInst(LLOAD);
            MakeInst(FLOAD);
            MakeInst(DLOAD);
            MakeInst(ALOAD);
            MakeInst(ILOAD_0);
            MakeInst(ILOAD_1);
            MakeInst(ILOAD_2);
            MakeInst(ILOAD_3);
            MakeInst(LLOAD_0);
            MakeInst(LLOAD_1);
            MakeInst(LLOAD_2);
            MakeInst(LLOAD_3);
            MakeInst(FLOAD_0);
            MakeInst(FLOAD_1);
            MakeInst(FLOAD_2);
            MakeInst(FLOAD_3);
            MakeInst(DLOAD_0);
            MakeInst(DLOAD_1);
            MakeInst(DLOAD_2);
            MakeInst(DLOAD_3);
            MakeInst(ALOAD_0);
            MakeInst(ALOAD_1);
            MakeInst(ALOAD_2);
            MakeInst(ALOAD_3);
            MakeInst(ISTORE);
            MakeInst(LSTORE);
            MakeInst(FSTORE);
            MakeInst(DSTORE);
            MakeInst(ASTORE);
            MakeInst(ISTORE_0);
            MakeInst(ISTORE_1);
            MakeInst(ISTORE_2);
            MakeInst(ISTORE_3);
            MakeInst(LSTORE_0);
            MakeInst(LSTORE_1);
            MakeInst(LSTORE_2);
            MakeInst(LSTORE_3);
            MakeInst(FSTORE_0);
            MakeInst(FSTORE_1);
            MakeInst(FSTORE_2);
            MakeInst(FSTORE_3);
            MakeInst(DSTORE_0);
            MakeInst(DSTORE_1);
            MakeInst(DSTORE_2);
            MakeInst(DSTORE_3);
            MakeInst(ASTORE_0);
            MakeInst(ASTORE_1);
            MakeInst(ASTORE_2);
            MakeInst(ASTORE_3);
            MakeInst(POP);
            MakeInst(POP2);
            MakeInst(DUP);
            MakeInst(DUP_X1);
            MakeInst(DUP_X2);
            MakeInst(DUP2);
            MakeInst(DUP2_X1);
            MakeInst(DUP2_X2);
            MakeInst(SWAP);
            MakeInst(IADD);
            MakeInst(LADD);
            MakeInst(FADD);
            MakeInst(DADD);
            MakeInst(ISUB);
            MakeInst(LSUB);
            MakeInst(FSUB);
            MakeInst(DSUB);
            MakeInst(IMUL);
            MakeInst(LMUL);
            MakeInst(FMUL);
            MakeInst(DMUL);
            MakeInst(IDIV);
            MakeInst(LDIV);
            MakeInst(FDIV);
            MakeInst(DDIV);
            MakeInst(IREM);
            MakeInst(LREM);
            MakeInst(FREM);
            MakeInst(DREM);
            MakeInst(INEG);
            MakeInst(LNEG);
            MakeInst(FNEG);
            MakeInst(DNEG);
            MakeInst(ISHL);
            MakeInst(LSHL);
            MakeInst(ISHR);
            MakeInst(LSHR);
            MakeInst(IUSHR);
            MakeInst(LUSHR);
            MakeInst(IAND);
            MakeInst(LAND);
            MakeInst(IOR);
            MakeInst(LOR);
            MakeInst(IXOR);
            MakeInst(LXOR);
            MakeInst(IINC);
            MakeInst(I2L);
            MakeInst(I2F);
            MakeInst(I2D);
            MakeInst(L2I);
            MakeInst(L2F);
            MakeInst(L2D);
            MakeInst(F2I);
            MakeInst(F2L);
            MakeInst(F2D);
            MakeInst(D2I);
            MakeInst(D2L);
            MakeInst(D2F);
            MakeInst(I2B);
            MakeInst(I2C);
            MakeInst(I2S);
            MakeInst(LCMP);
            MakeInst(FCMPL);
            MakeInst(FCMPG);
            MakeInst(DCMPL);
            MakeInst(DCMPG);
            MakeInst(IFEQ);
            MakeInst(IFNE);
            MakeInst(IFLT);
            MakeInst(IFGE);
            MakeInst(IFGT);
            MakeInst(IFLE);
            MakeInst(IF_ICMPEQ);
            MakeInst(IF_ICMPNE);
            MakeInst(IF_ICMPLT);
            MakeInst(IF_ICMPGE);
            MakeInst(IF_ICMPGT);
            MakeInst(IF_ICMPLE);
            MakeInst(IF_ACMPEQ);
            MakeInst(IF_ACMPNE);
            MakeInst(GOTO);
            MakeInst(TABLESWITCH);
            MakeInst(LOOKUPSWITCH);
            MakeInst(WIDE);
            MakeInst(IFNULL);
            MakeInst(IFNONNULL);
            MakeInst(GOTO_W);
            MakeInst(NEW);
            MakeInst(PUTFIELD);
            MakeInst(PUTSTATIC);
            MakeInst(GETFIELD);
            MakeInst(GETSTATIC);
            MakeInst(LDC);
            MakeInst(LDC_W);
            MakeInst(LDC2_W);
            MakeInst(INSTANCEOF);
            MakeInst(CHECKCAST);
//            MakeInst(INVOKE_SPECIAL);
//            MakeInst(INVOKE_INTERFACE);
//            MakeInst(INVOKE_STATIC);
//            MakeInst(INVOKE_VIRTUAL);
            MakeInst(IRETURN);
            MakeInst(LRETURN);
            MakeInst(FRETURN);
            MakeInst(DRETURN);
            MakeInst(ARETURN);
            MakeInst(RETURN);
            MakeInst(NEWARRAY);
            MakeInst(ANEWARRAY);
            MakeInst(ARRAYLENGTH);
//            MakeInst(IALOAD);
//            MakeInst(LALOAD);
//            MakeInst(FALOAD);
//            MakeInst(DALOAD);
//            MakeInst(AALOAD);
//            MakeInst(BALOAD);
//            MakeInst(CALOAD);
//            MakeInst(SALOAD);
//            MakeInst(IASTORE);
//            MakeInst(LASTORE);
//            MakeInst(FASTORE);
//            MakeInst(DASTORE);
//            MakeInst(AASTORE);
//            MakeInst(BASTORE);
//            MakeInst(CASTORE);
//            MakeInst(SASTORE);
//            MakeInst(MULTI_ANEW_ARRAY);
//            MakeInst(INVOKE_NATIVE);
//            MakeInst(ATHROW);
        }
    }

#undef MakeInst
}