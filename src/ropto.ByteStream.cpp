
#include "ropto/ByteStream.hpp"

namespace ropto
{
    
    byte_stream::byte_stream() {}
    
    void byte_stream::append(uint8_t byte)
    {
        bytes.push_back(byte);
    }
    
    uint8_t byte_stream::fetch()
    {
        return bytes[index++];
    }
    
    std::vector<uint8_t>& byte_stream::iterate() {return bytes;}
    
    auto byte_stream::begin() -> decltype(bytes.begin()) const
    {
        return std::begin(bytes);
    }
    
    auto byte_stream::end() -> decltype(bytes.end()) const
    {
        return std::end(bytes);
    }
    
    size_t byte_stream::size() const
    {
        return bytes.size();
    }
    
    bool byte_stream::fit(size_t size) const
    {
        return index + size < this->size();
    }

}
