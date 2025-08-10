#include <cctype>
#include <memory>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <fmt/base.h>
#include <fmt/format.h>

namespace
    VolCpp
{
    
    std::string
        system
        ( const std::string& cmd )
    {
        
        std::array <char , 128> buffer;
        std::string result;
        
        // Explicitly define the deleter type (function pointer)
        std::unique_ptr <FILE , int(*)(FILE*)>
            pipe
            ( popen ( cmd.c_str ( ) , "r" ) , pclose )
        ;
        
        if
            ( !pipe )
        {
            
            throw
                std::runtime_error
                ( "popen ( ) failed!" )
            ;
            
        }
        
        while
            (
                fgets
                (
                    buffer.data ( ) ,
                    buffer.size ( ) ,
                    pipe.get ( )
                ) != nullptr
            )
        {
            
            result += buffer.data();
            
        }
        
        return result;
        
    }
    
}

std::string
    fStr_getVolume
    ( bool onlyVol = true )
{
    
    std::string
        volume
        {
            fmt::format
            (
                "{}" ,
                VolCpp::system("pamixer --get-volume-human")
            )
        }
    ;
    
    if
        ( onlyVol )
    {
        
        return
            volume =
            volume.replace ( volume.find ( "%" ) , 1 , "\033[P" )
        ;
        
    }
    
    return
        volume.replace // remove the return value...
        ( volume.end ( ) - 1 , volume.end ( ) , "\033[K" )
    ;
    
}

void
    f_printHelp
    ( void )
{
    
    std::string
        helpStr =
        fmt::format
        (
            "\033[34m[\033[0m"
            " \033[32m" "VolumeControl++" "\033[0m "
            "\033[34m]\033[0m\n"
            "\033[35m"
            "  \"A Volume Controller Program written in C++ for hyprland.\""
            "\033[0m\n"
            "\033[34m::\033[0m"
            " \033[38;2;235;170;255mUsage Options\033[34m:\033[0m"
        )
    ;
    
    fmt::println ( "{:s}" , helpStr );
    
}

int
    fInt_argsIterator
    ( int argc , char* argv [ ] )
{
    
    std::string
        arguments
    ;
    
    bool
        incrF = false ,
        is_incr = false ,
        is_decr = false ,
        decrF = false
    ;
    
    int
        is_incrN { } ,
        is_decrN { }
    ;
    
    for
        ( size_t argsPos { 1 }; argsPos < argc; ++argsPos )
    {
        
        arguments =
            argv [ argsPos ]
        ;
        
        if
            (
                !arguments.empty ( ) &&
                std::all_of
                (
                    arguments.begin ( ) ,
                    arguments.end ( ) ,
                    isprint
                ) &&
                arguments == "-h" ||
                arguments == "--help"
            )
        {
            
            f_printHelp ( );
            
            break;
            
        }
        
        else if
            (
                !arguments.empty ( ) &&
                std::all_of
                ( arguments.begin ( ) , arguments.end ( ) , isprint )
            )
        {
            
            if
                ( incrF == false && arguments == "-i" )
            {
                
                incrF = true;
                is_incr = true;
                fmt::println ( "incr pos: {:d}" , argsPos );
                
            }
            
            else if
                ( decrF == false && arguments == "-d" )
            {
                
                decrF = true;
                is_decr = true;
                fmt::println ( "decr pos: {:d}" , argsPos );
                
            }
            
            else if
                (
                    incrF == true &&
                    decrF == false &&
                    std::all_of
                    ( arguments.begin ( ) , arguments.end ( ) , isdigit )
                )
            {
                
                incrF = false;
                fmt::println ( "incr number is: {:s}" , arguments );
                
            }
            
            else if
                (
                    decrF == true &&
                    incrF == false &&
                    std::all_of
                    ( arguments.begin ( ) , arguments.end ( ) , isdigit )
                )
            {
                
                decrF = false;
                fmt::println ( "decr number is: {:s}" , arguments );
                
            }
            
            else if
                (
                    is_incr == true && is_decr == true &&
                    std::all_of
                    ( arguments.begin ( ) , arguments.end ( ) , isdigit )
                )
            {
                
                fmt::println ( "incr by: {}" , arguments );
                fmt::println ( "decr by: {}" , arguments );
                
            }
            
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
        
        f_printHelp ( );
        
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
    
    for
        ( int i { 30 }; i <= 37; ++i )
    {
        fmt::println("\033[{}mHI!\033[0m",i);
    }
    
}
