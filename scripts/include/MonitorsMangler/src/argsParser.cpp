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
        
        else if
            ( wrkspcN == false || monN == false )
        {
            
            std::println
            (
                "usage: {{ {} }} [workspace number] , [monitor name]" ,
                argv [ 0 ]
            )
            ;
            
            return  1;
            
        }
        
    }
    
    if
    ( workspacesN || monN )
        alt_monitorMangling ( workspacesN , monitors );
    else
        std::println ( "Atleast 1 workspace count and monitor name." );
    return 0;
    
}
