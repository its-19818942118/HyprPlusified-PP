#include <algorithm>
#include <cctype>
#include <print>
#include <format>
#include <string>
#include <cstddef>
#include <cstdlib>

int
    fInt_argsIterator
    ( int argc , char* argv [ ] )
{
    
    std::string
        arguments
    ;
    
    bool is_incr = false , is_decr = false , incrF = false , decrF = false;
    int is_incrN { } , is_decrN { };
    
    for
        ( size_t argsPos { 1 }; argsPos < argc; ++argsPos )
    {
        
        arguments =
            ( argv [ argsPos ] )
        ;
        
        if
            (
                !arguments.empty ( ) &&
                std::all_of
                (
                    arguments.begin ( ) ,
                    arguments.end ( ) ,
                    ::isprint
                ) &&
                arguments == "-i"
            )
        {
            
            is_incr = true;
            
        }
        
        else if
            (
                !arguments.empty ( ) &&
                std::all_of
                (
                    arguments.begin ( ) ,
                    arguments.end ( ) ,
                    ::isprint
                )
            )
        {
            
        }
        
    }
    
    return 0;
    
}

int
    fInt_argsParser
    ( int argc , char* argv [ ] )
{
    
    if
        ( 1 < argc )
    {
        
        return
            fInt_argsIterator
            ( argc , argv )
        ;
        
    }
    
    else
    {
        
        return
            EXIT_FAILURE
        ;
        
    }
    
    return 0;
    
}

int
    main
    ( int argC , char* argV [ ] )
{
    
    return
        fInt_argsParser
        ( argC , argV )
    ;
    
}
