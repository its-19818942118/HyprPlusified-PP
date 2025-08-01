#include <print>
#include <format>
#include <string>
#include <string_view>

#include "mangle2.hpp"

void
    alt_monitorMangling2
    ( int num , std::string_view mon1 , std::string_view mon2 )
{
    
    for
        ( int i = 1; i <= num; ++i )
    {
        
        if
            ( i % 2 != 0 )
        {
            
            std::string cmd = std::format
                (
                    "hyprctl keyword \"workspace {} , monitor:{}\"" , i , mon1
                )
            ;
            
            std::println ( "{}" , cmd);
            
        }
        
        else
        {
            
            std::string cmd = std::format
            (
                "hyprctl keyword \"workspace {} , monitor:{}\"" , i , mon2
            )
            ;
            
            std::println ( "{}" , cmd );
            
            std::system ( cmd.c_str ( ) );
            
        }
        
    }
    
}
