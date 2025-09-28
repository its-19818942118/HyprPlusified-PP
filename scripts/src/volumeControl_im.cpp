#include <cctype>
#include <cstdio>
#include <memory>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <fmt/base.h>
#include <fmt/format.h>

using namespace std::string_literals;

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

enum class
    e_act
    {
        /// @e Increase Volume
        incr ,
        /// @e Decrease Volume
        decr ,
        /// @e Toggle Volume Mute
        tmute ,
        /// @e Volume Mute Status
        ismute ,
        /// @e Human Redable Volume
        hvolume ,
        /// @e Only Volume
        ovolume
    }
;

std::string
    fstr_getVolume
    ( e_act act = e_act::ovolume )
{
    
    std::string volume = VolCpp::system ( "pamixer --get-volume"s );
    
    volume.erase ( volume.find ( "\n" ) );
    
    if
        ( act == e_act::hvolume )
    {
        
        volume = volume + '%';
        
    }
    
    return volume;
    
}

// std::string
//     fstr_getVolMute
//     ( e_act act = e_act::ismute )
// {
    
    
    
// }

void
    f_printHelp
    ( void )
{
    
    std::string
        helpStr =
        fmt::format
        (
            "\x1b[34m[\x1b[0m"
            " \x1b[32m" "VolumeControl++" "\x1b[0m "
            "\x1b[34m]\x1b[0m\n"
            "\x1b[35m"
            "  \"A Volume Controller Program written in C++ for hyprland.\""
            "\x1b[0m\n"
            "\x1b[34m::\x1b[0m"
            " \x1b[38;2;235;170;255mUsage Options\x1b[34m:\x1b[0m"
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
                arguments == "-h" ||
                arguments == "--help"
            )
        {
            
            f_printHelp ( );
            
            break;
            
        }
        
        if
            ( incrF == false && arguments == "-i" )
        {
            
            incrF = true;
            is_incr = true;
            fmt::println ( "volume incr ({1:s}) pos: {0:d}" , argsPos , arguments );
            
        }
        
        else if
            ( decrF == false && arguments == "-d" )
        {
            
            decrF = true;
            is_decr = true;
            fmt::println ( "volume decr ({1:s}) pos: {0:d}" , argsPos , arguments );
            
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
            fmt::println ( "volume incr number is: {:s}" , arguments );
            
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
            fmt::println ( "volume decr number is: {:s}" , arguments );
            
        }
        
        else if
            (
                is_incr == true && is_decr == true &&
                std::all_of
                ( arguments.begin ( ) , arguments.end ( ) , isdigit )
            )
        {
            
            fmt::println ( "volume incr by: {}" , arguments );
            fmt::println ( "volume decr by: {}" , arguments );
            
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
    
    // fmt::println ( "{}" , fStr_getVolume ( ) );
    
    // f_ctrlVolume("Hello World" , "-d");
    
    // std::cout << fstr_getVolume ( e_act::hvolume );
    
    // f_ctrlVolume ( 10 , e_act::incr );
    
    return
        fInt_argsIterator
        ( argC , argV )
    ;
    
}
