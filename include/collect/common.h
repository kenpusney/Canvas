
#ifndef __COLLECT_COMMON_H__
#define __COLLECT_COMMON_H__

namespace collect{
    namespace category{
        namespace iter{
            struct forward{};
            struct reverse{};
            struct bidirectional:forward, reverse{};
            struct indexed{};
            struct random:indexed, bidirectional{};
        }
    }
}

#endif // __COLLECT_COMMON_H__
