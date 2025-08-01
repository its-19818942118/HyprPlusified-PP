#include <cstddef>
#include <cstdlib>
#include <print>

int
    main
    ( int argc , char* argv [ ] )
{
    
    std::string
        cmd ,
        arguments
    ;
    
    for
        ( size_t i { 1 }; i < argc; ++i )
    {
        
        arguments = argv [ i ];
        
    }
    
    if
        ( arguments == "-d" )
    {
        
        system ( cmd.c_str() );
        
    }
    
}
