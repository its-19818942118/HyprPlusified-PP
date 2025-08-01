#include <print>
#include <string_view>

#include "mangle3.hpp"

void
    alt_monitorMangling3
    ( int num , std::string_view mon1 , std::string_view mon2 , std::string_view mon3 )
{
    
    for
        ( int i = 1; i <= num; ++i )
    {
        
        if
            ( ( i - 1 ) % 3 == 0 )
        {
            
            std::println ( "{} , {}" , i , mon1 );
            
        }
        
        else if
            ( ( i - 1 ) % 3 == 1 )
        {
            
            std::println ( "{} , {}" , i , mon2 );
            
        }
        
        else if
            ( ( i - 1 ) % 3 == 2 )
        {
            
            std::println ( "{} , {}" , i , mon3 );
            
        }
        
    }
    
}

