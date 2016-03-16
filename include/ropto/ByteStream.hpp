//
//  ByteStream.hpp
//  ropto
//
//  Created by Kimmy  on 11/7/15.
//  Copyright (c) 2015 TDCA. All rights reserved.
//

#ifndef ropto_ByteStream_hpp
#define ropto_ByteStream_hpp

#include <vector>

namespace ropto
{
    
    typedef std::vector<uint8_t> bytes_t;
    
    class byte_stream
    {
        bytes_t bytes {};
        int index = 0;
    public:
        byte_stream();
        
        byte_stream(const byte_stream& stream) = delete;
        
        void append(uint8_t byte);
        
        uint8_t fetch();
        
        bytes_t& iterate();
        
        auto begin() -> decltype(bytes.begin()) const;
        
        auto end() -> decltype(bytes.end()) const;
        
        size_t size() const;
        
        bool fit(size_t size) const;
        
        template<class T>
        bool fit() const
        {
            return fit(sizeof(T));
        }
    };
    

}

#endif
