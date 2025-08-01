#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

std::string
    f_Str_sanitizeOut
    ( const std::string& str )
{
    
    std::string
        result =
        str
    ;
    
    // Remove all trailing newline characters and spaces
    result.erase
        (
            std::remove
            (
                result.begin ( ) ,
                result.end ( ) ,
                '\n'
            ) ,
            result.end ( )
        )
    ;
    
    // result.erase
    //     (
    //         std::remove
    //         (
    //             result.begin ( ) ,
    //             result.end ( ) ,
    //             ' '
    //         ) ,
    //         result.end ( )
    //     )
    // ;
    
    return
        result
    ;
    
}

std::string
    f_Str_readCmd
    ( const std::string &command )
{
    
    FILE*
        pipe =
        popen
        ( command.c_str ( ), "r" )
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
    f_Str_checkOut
    ( const std::string &result )
{
    
    if ( f_Str_sanitizeOut ( result ) == "honey bunny" )
    {
        
        return
            "Bye!"
        ;
        
    }
    
    return "Did not Match!";
    
}

int
    main
    ( )
{
    
    std::string cmd;
    std::getline ( std::cin , cmd );
    
    std::cout
        <<  f_Str_checkOut ( f_Str_readCmd( cmd ) )
    ;
    
    return 0;
    
}
