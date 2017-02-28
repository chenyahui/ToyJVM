//
// Created by cyh on 17-2-22.
//

#pragma once
#include "types.h"
#include "util/stringutils.h"


#include <vector>

namespace cyh {
    class Entry {
    public:
        virtual Bytes readClass(std::string className) { return std::vector<Byte>(); }

        virtual std::string toString() { return ""; }
    };

    Entry* newEntry(std::string path);
}


