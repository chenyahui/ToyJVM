//
// Created by cyhone on 18-1-30.
//

#ifndef NEWJVM_UNCOPYABLE_H
#define NEWJVM_UNCOPYABLE_H

namespace jvm {
    class UnCopyable {
    public:
        UnCopyable() = default;

        ~UnCopyable() = default;

        UnCopyable(const UnCopyable &) = delete;

        UnCopyable &operator=(const UnCopyable &) = delete;
    };
}

#endif //NEWJVM_UNCOPYABLE_H
