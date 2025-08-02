#include <print>
#include <string>
#include <vector>

#include "mangler.hpp"

void
    alt_monitorMangling
    ( int workspaceN , const std::vector<std::string>& monitors )
{
    
    for
        ( int i { 1 }; i <= workspaceN; ++i )
    {
        
        std::println
            (
                "{} , {}" ,
                i ,
                monitors [ ( i - 1 ) % monitors.size ( ) ]
            )
        ;
        
    }
    
}
