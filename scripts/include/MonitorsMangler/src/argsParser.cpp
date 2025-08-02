#include <print>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

#include "mangler.hpp"
#include "argsParser.hpp"

int
    fInt_argsIterator
    ( int argc , char* argv [ ] )
{
    
    std::string
        arguments
        { }
    ;
    
    int
        workspacesN
        { }
    ;
    
    std::vector<std::string> monitors { };
    
    bool wrkspcN { false } , monN { false };
    
    for
        ( size_t i { 1 }; i < argc; ++i )
    {
        
        arguments = argv [ i ];
        
        if
            (
                // i &&
                !arguments.empty ( ) &&
                std::all_of
                (
                    arguments.begin ( ) ,
                    arguments.end ( ) ,
                    isdigit
                )
            )
        {
            
            workspacesN = std::stoi ( arguments );
            wrkspcN = true;
            
        }
        
        else if
            (
                // i &&
                !arguments.empty ( ) &&
                std::all_of
                (
                    arguments.begin ( ) ,
                    arguments.end ( ) ,
                    isprint
                )
            )
        {
            
            monitors.emplace_back ( arguments );
            monN = true;
            
        }
        
    }
    
    if
        ( workspacesN != false && monN != false )
    {
        
        alt_monitorMangling ( workspacesN , monitors );
        
        return 0;
        
    }
    
    else
    {
        
        std::println
            (
                "\033[31mError:\033[0m "
                "\033[33mAtleast 1 workspace count and monitor name required.\033[0m"
            )
        ;
        std::println
            (
                "\033[34mUsage:\033[0m {{ {} }} "
                "[ workspace number ] , [ Monitor 1 ] [ Monitor 2 ]\n"
                "\033[35mHint:\033[0m "
                "To get Monitor names use \033[36mhyprctl monitors\033[0m.\n"
                "\033[32mExample:\033[0m "
                "\033[36m{} eDP-1 HDMI-A-1\033[0m"
                , argv [ 0 ] , argv [ 0 ]
            )
        ;
        return 1;
        
    }
    
}
