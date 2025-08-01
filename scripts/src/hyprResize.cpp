#include <algorithm>
#include <format>
#include <print>
#include <string>
#include <sstream>

std::string
    f_Str_exec
    ( const std::string& command )
{
    
    FILE*
        pipe =
            popen
        ( command.c_str ( ) , "r" )
    ; // Open a pipe to the command's stdout

    if
        ( !pipe )
    {
        return
            "Error: `popen ( )` failed!"
        ;
    }

    // Use std::stringstream to accumulate output line by line
    std::stringstream
        v_Ss_result
    ;
    
    signed
      char
        itr
    ;
    
    // Read data from the pipe until end of file (EOF)
    while
        ( ( itr = fgetc ( pipe ) ) != EOF )
    {
        
        v_Ss_result.put ( itr ); // Write the character into the stringstream
        
    }
    
    pclose ( pipe ); // Close the pipe
    
    return
        v_Ss_result.str ( )
    ; // Return the accumulated output as a string
    
}

std::string subtract_substring(const std::string& base, const std::string& to_remove) {
    std::string result = base;
    size_t pos = result.find(to_remove);
    if (pos != std::string::npos) {
        result.erase(pos, to_remove.length());
    }
    return result;
}

std::string
    f_Str_get_layoutModes
    ( bool formatted = true )
{
    
    std::string
            layouts =
        f_Str_exec ( "hyprctl layouts" );
    ;
    
    if
        ( formatted )
    {    
        size_t pos = 0;
        while
            ( ( pos = layouts.find ( "\n" , pos ) ) != std::string::npos )
        {
            // Check if the newline is not empty (i.e., it's not the beginning or end of the string, or followed by another newline)
            if
                (
                    pos > 0 &&
                    pos + 1 < layouts.size ( ) &&
                    layouts [ pos + 1 ] != '\n'
                )
            {
                
                layouts.replace
                    ( pos, 1, "\n  \033[34m->\033[36m ")
                ;  // Replace the newline with "->"
                
                pos += 6;  // Move past the "->" that was just inserted
                
            }
            
            else
            {
                pos++;  // Skip this newline, it's an empty one
            }
        }
        
        std::replace ( layouts.end()-2 , layouts.end()-1 , '\n' , ' ' );
        
        return
            "  \033[34m->\033[36m " + layouts + "\033[0m"
        ;
        
    }
    
    else
    {    
        size_t pos = 0;
        while
            ( ( pos = layouts.find ( "\n" , pos ) ) != std::string::npos )
        {
            // Check if the newline is not empty (i.e., it's not the beginning or end of the string, or followed by another newline)
            if
                (
                    pos > 0 &&
                    pos + 1 < layouts.size ( ) &&
                    layouts [ pos + 1 ] != '\n'
                )
            {
                
                layouts.replace
                    ( pos, 1, "\n  -> ")
                ;  // Replace the newline with "->"
                
                pos += 6;  // Move past the "->" that was just inserted
                
            }
            
            else
            {
                pos++;  // Skip this newline, it's an empty one
            }
        }
        
        std::replace ( layouts.end()-2 , layouts.end()-1 , '\n' , ' ' );
        
        return
            "  -> " + layouts
        ;
        
    }
    
}

std::string
    f_Str_suprtLayoutModes
    ( void )
{
    
    std::string
        supportedLayouts =
        std::format
        (
            "{}\n{}\n{}" ,
            "  -> master" ,
            "  -> dwindle" ,
            "  -> scroller" ,
            "  -> scrolling"
        )
    ;
    
    // supportedLayouts = subtract_substring ( f_Str_get_layoutModes(false) ,supportedLayouts );
    supportedLayouts = subtract_substring ( supportedLayouts , f_Str_get_layoutModes(false) );
    
    return
        supportedLayouts + '\n'
    ;
    
}

std::string
    cur_layoutMode
    ( bool format = true )
{
    
    
    if
        ( format )
    {
        
        std::string layoutStr = f_Str_exec ( "hyprctl getoption general:layout" );
        
        // size_t pos = 0;
        
        // while
        //     ( ( pos = layoutStr.find ( "str:" ) ) != std::string::npos )
        // {
            
        //     layoutStr.replace ( 1 , 4 , "\033[34mstr:\033[0m" );
        //     pos += 5;
            
        // }
        
        layoutStr.replace ( layoutStr.find ( "str:" ) , 4 ,  "  \033[34mstr:\033[0m" );
        layoutStr.replace ( layoutStr.find ( "set:" ) , 4 ,  "  \033[34mset:\033[0m" );
        
        return
            layoutStr
        ;
        
    }
    
    else
    {
        
        std::string layoutStr = f_Str_exec ( "hyprctl getoption general:layout" );
        return
            layoutStr
        ;
        
    }
    
}

void
    handle_resize
    ( void )
{
    
    std::string layout = cur_layoutMode();
    
    if
        ( layout.find ( "str: dwindle" ) != std::string::npos )
    {
        
        std::println ( "dwindle available" );
        
    }
    
    else if
        ( layout.find ( "str: scroller" ) )
    {
        
        std::println ( "scroller available" );
        
    }
    
    else if
        ( layout.find ( "str: scrolling" ) )
    {
        
        std::println ( "scrolling available" );
        
    }
    
}

void
    f_printHelp
    ( void )
{
    
    const
      std::string&
            HelpStr =
            std::format
        (
            "\033[34m[\033[0m \033[1;4;32m{}\033[0m \033[34m]\033[0m\n"
            "\033[1;3m{}{}\033[0m\n"
            "\033[34m::\033[0m \033[35m{}\033[0m\n{}"
            "\033[34m::\033[0m \033[35m{}\033[0m\n{}"
            "\033[34m::\033[0m \033[35m{}\033[0m\n{}"
            ,
            "hyprResize" ,
            "  An utility for dynamic resizing of Windows in Hyprland , " ,
            "across various window layout" ,
            "Available Layout Modes:" ,
            f_Str_get_layoutModes ( ) ,
            "Supported Layout Modes:" ,
            f_Str_suprtLayoutModes ( ) ,
            "Current Layout Mode:" ,
            cur_layoutMode ( )
        )
    ;
    
    std::println ( "{}" , HelpStr );
    
}

int
    f_Int_argsParser
    ( int argc , char* argv [ ] )
{
    
    std::string
        arguments
        { }
    ;
    
    if
        ( 1 < argc )
    {
        
        for
            ( int itr { }; itr < argc; ++itr )
        {
            
            arguments =
                argv [ itr ]
            ; // no concatination. for positional arguments
            
            std::print
                ( "{}->" , arguments )
            ;
            
        }
        
    }
    
    else
    {
        
        f_printHelp ( );
        
        return 1;
        
    }
    
    return 0;
    
}

int
    main
    ( int argc , char* argv [ ] )
{
    
    std::string str = "hi";
    
    std::println ( "{}" , str.find ( "hi" ) );
    
    return
        f_Int_argsParser
        ( argc , argv )
    ;
    
}
