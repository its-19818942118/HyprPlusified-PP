#include <print>
#include <cctype>
#include <format>
#include <string>
// #include "mangle2.hpp"
#include "mangle3.hpp"

int
    main
    ( int argc , char* argv [ ] )
{
    
    if
        ( 3 < argc )
    {
        
        std::string arguments;
        
        int workspaceN { };
        std::string mon1 { } , mon2 { } , mon3 { };
        
        for
            ( int i { 1 }; i < argc; ++i )
        {
            
            arguments = argv [ i ];
            
            if
                (
                    i == 1 &&
                    !arguments.empty ( ) &&
                    std::all_of
                    (
                        arguments.begin ( ) ,
                        arguments.end ( ) ,
                        ::isdigit
                    )
                )
            {
                
                workspaceN = std::stoi ( arguments );
                
            }
            
            else if
                (
                    i == 2 &&
                    !arguments.empty ( ) &&
                    std::all_of
                    (
                        arguments.begin ( ) ,
                        arguments.end ( ) ,
                        ::isprint
                    )
                )
            {
                
                mon1 = arguments;
                
            }
            
            else if
                (
                    i == 3 &&
                    !arguments.empty ( ) &&
                    std::all_of
                    (
                        arguments.begin ( ) ,
                        arguments.end ( ) ,
                        ::isprint
                    )
                )
            {
                
                mon2 = arguments;
                
            }
            
            else if
                (
                    i == 4 &&
                    !arguments.empty ( ) &&
                    std::all_of
                    (
                        arguments.begin ( ) ,
                        arguments.end ( ) ,
                        ::isprint
                    )
                )
            {
                
                mon3 = arguments;
                
            }
            
        }
        
            alt_monitorMangling3 ( workspaceN , mon1 , mon2 , mon3 );
        
        
    }
    
    else {
        
        std::print ( "at least 1 arg" );
        
        return -1;
        
    }
    
}
