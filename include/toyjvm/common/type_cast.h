//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_TYPE_CAST_H
#define TOYJVM_TYPE_CAST_H

#include <assert.h>

namespace jvm {
    template<typename From, typename To>
    To bits_cast(From from)
    {
        assert(sizeof(From) == sizeof(To));
        return *((To *) &from);
    }
    
};
}
#endif //TOYJVM_TYPE_CAST_H
