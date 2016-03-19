//
//  Header.h
//  canvas
//
//  Created by Kimmy  on 3/20/16.
//  Copyright (c) 2016 TDCA. All rights reserved.
//

#ifndef trusct_Header_h
#define trusct_Header_h

namespace trusct
{
    enum class type
    {
        null,
        integer,
        
    };
    
    enum class specifier {
        pre_defined,
    };
    
    template<class... Args>
    struct schema {};
    
    
}

#endif
