#include <regex>
#include <string>
#include <sstream>
#include <iostream>

int
    f_Int_exec
    ( const std::string &command )
{
    
    int
        v_Int_exitCode = 
        0
    ;
    
    FILE*
        pipe =
        popen
        ( command.c_str ( ) , "r" )
    ;
    
    if
        ( !pipe )
    {
        
        std::cerr
            <<  "Error: popen () Failed!"
        ;
        
    }
    
    int
        status =
        // WEXITSTATUS
        // ( v_Int_exitCode )
        pclose ( pipe )
    ;
    
    return
        status
    ;
    
}

std::string
    f_Str_exec
    ( const std::string &command )
{
    
    FILE*
        pipe =
        popen
        ( command.c_str ( ) , "w" )
    ; // Open a pipe to the command's stdout

    if ( !pipe )
    {
        return "Error: popen() failed!";
    }

    // Use std::stringstream to accumulate output line by line
    std::stringstream
        v_Ss_result
    ;
    
    char
        ch
    ;
    
    // Read data from the pipe until end of file (EOF)
    while
        ( ( ch = fgetc ( pipe ) ) != EOF )
    {
        
        v_Ss_result.put ( ch ); // Write the character into the stringstream
        
    }
    
    pclose ( pipe ); // Close the pipe
    
    return
        v_Ss_result.str ( )
    ; // Return the accumulated output as a string
    
}

std::string
    f_Str_getMenuStr
    ( )
{
    
    std::string
        v_Str_menuStr =
        f_Str_exec ( "cat" )
    ;
    
    /* Regular expression to match everything before the first space. */
    std::regex
        v_Reg_pattern
        ( "^\\S+" )
    ;
    
    std::stringstream
        v_Sstrm_lnStream
        ( v_Str_menuStr )
    ;
    
    std::string
        v_Str_line
    ;
    
    while
        ( std::getline ( v_Sstrm_lnStream , v_Str_line ) )
    {
        
        if
            ( v_Str_line.empty ( ) )
        {
            
            std::cout
                <<  "Skipping empty trailing newline."
                <<  std::endl
            ;
            
            continue;
            
        }
        
        std::smatch
            v_Smtch_matchedLine
        ;
        
        std::cout
            <<  "Found the following menu strings:"
        ;
        
        if
            ( 
                std::regex_search
                ( v_Str_line , v_Smtch_matchedLine , v_Reg_pattern )
            )
        {
            
            std::cout
                <<  v_Smtch_matchedLine.str ( )
                <<  std::endl
            ;
            
        }
        
        else
        {
            
            std::cout
                <<  "No menu string found in line: "
                <<  v_Smtch_matchedLine.str ( )
                <<  std::endl
            ;
            
        }
        
    }
    
    return "";
    
}

std::string
    f_Str_useMenu
    ( )
{
    
    return "";
    
}

int
    main
    ( )
{
    
    std::cout
        <<  f_Str_getMenuStr ( )
    ;
    
}
