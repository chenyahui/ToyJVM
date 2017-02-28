//
// Created by cyhone on 17-2-22.
//

#pragma once
#include <vector>

#include "classpath/entry.h"

namespace cyh {

    class DirEntry : public Entry {
    public:
        DirEntry(std::string);

        Bytes readClass(std::string className) override;

        std::string toString() override;

    private :
        std::string absDir;
    };

    class CompositeEntry : public Entry {
    public:
        CompositeEntry();

        CompositeEntry(const std::string);

        Bytes readClass(std::string className) override;

        std::string toString() override;

        void appendEntry(Entry* entry);

    private:
        std::vector<Entry*> entrys;
    };

    class ZipEntry : public Entry {
    public:
        ZipEntry(std::string);

        Bytes readClass(std::string className) override;

        std::string toString() override;

    private:
        std::string absPath;
    };

    class WildcardEntry : public Entry {
    public:
        WildcardEntry(std::string);

        Bytes readClass(std::string className) override;

        std::string toString() override;

    private :
        CompositeEntry compositeEntry;
    };
}

