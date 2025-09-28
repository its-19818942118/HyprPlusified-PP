/**
    @file: volumeContol.cpp
    @remarks: A simple C++ program to handle Volume Control.
    @author: its_19818942118 ( izumi )
    @site: https://github.com/its-1981942118
**/

#include <print>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <iostream>

/// @signature: int
/// @function: f_Int_exec
/// @param: const std::string& command
/// @return: int value `status`
/// @remarks: A simple clone of system() function from <cstdlib>
/// @version: 0.1 (Garbage)
int
    f_Int_exec
    ( const std::string& command )
{
    
    int
        v_Int_exitCode = 
        0
    ;
    
    FILE*
        pipe =
        popen
        ( command.c_str ( ) , "r" )
    ; // opens a shell pipe. to execute commands
    
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
    ; // close shell pipe
    
    return
        status
    ; // return status
    
}

/// @remarks: String type return for function `f_Int_exec()`
std::string
    f_Str_exec
    ( const std::string &command )
{
    
    FILE*
        pipe =
        popen
        ( command.c_str ( ) , "r" )
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
    f_Str_getVolume
    ( bool ov = false )
{
    
    std::string
        volume =
        f_Str_exec
        ("pamixer --get-volume")
    ; // get volume information.
    
    if
        ( ov == true )
        return
            volume
        ; // check if `ov = true` ov == only volume. so no `%` raw `int` type.
    
    std::string
        muted =
        f_Str_exec
        ("pamixer --get-mute")
    ; // get mute inforation.
    
    std::string
        volumeStr =
        " "
        "\""
        "Volume: " +
        volume +
        "\\n"
        "Muted: " +
        muted +
        "\""
    ; // some fancy string manipulation.
    
    // std::cout  <<  volumeStr; // comment to see the output of volumestr
    
    std::string toremove = "\n";
    size_t pos = volumeStr.find ( toremove );// set to find the occurance of \n
    
    while
        ( pos != std::string::npos )
    {
        
        volumeStr.erase ( pos , toremove.length ( ) );
        pos = volumeStr.find ( toremove );  // Find the next occurrence after erasing
    }
    
    std::string toReplace = "\\n"; // to replace string.
    pos = volumeStr.find ( toReplace );
    std::string replace = "\n";
    {
        
        while
            ( pos != std::string::npos )
        {
            
            volumeStr.replace ( pos , toReplace.length ( ) , replace );
            pos = volume.find ( replace , pos + toReplace.length ( ) );
            
        }
        
    } // replace all instances. to format nicely.
    
    return volumeStr; // return formated string. for notifcation display.
    
}

int defstp = 5; // set the increamental step to incr/decr volume.
int exprTime = 10000; // set notification expiration time.

// function to call and display notifcation.
void
    f_Str_sendVolNotif
    ( char ctrl )
{
    
    std::string
        cmd
    ;
    
    if
        ( ctrl == 'i' || ctrl == 'd' ) // check if volume needs to be incr
    {
        
        cmd =
            "notify-send -a VolumeControl -t " +
            std::to_string ( exprTime ) + " " +
            " \"Current Volume:\"" +
            ( f_Str_getVolume ( ) )
            + " -h int:value:" +
            std::to_string ( ( std::stoi ( f_Str_getVolume ( true ) ) / 1.5 ) )
            // + " -h string:volume"
        ;
    }
    
    // else
    //   if
    //     ( ctrl == 'd' ) // check if volume needs to be decr
    // {
        
    //     cmd =
    //         "notify-send -a VolumeControl -t " +
    //         std::to_string ( exprTime ) + " " +
    //         ( f_Str_getVolume ( ) )
    //         // +
    //         // " -h int:value:" +
    //         // f_Str_getVolume ( true ) + "-h string:x-dunst-stack-tag:test"
    //     ;
        
    // }
    
    std::cout
        <<  cmd
    ; // some helpful output for debugging purposes. will be imp in next ver.
    
    f_Int_exec ( cmd ); // function call to run command to display notif.
    
}

std::string
    f_Str_VolumeControl
    ( char ctrl , int step = defstp )
{
    
    std::string
        v_Str_cmd ,
        v_Str_incrVolume =
            "pamixer --allow-boost --set-limit 150 -i " +
        std::to_string ( step ) ,
        v_Str_decrVolume =
            "pamixer --allow-boost --set-limit 150 -d " +
        std::to_string ( step )
    ;
    
    switch
        ( ctrl )
    {
        
        case 'i':
            v_Str_cmd =
                v_Str_incrVolume
            ;
        break;
        
        case 'd':
            v_Str_cmd =
                v_Str_decrVolume
            ;
        break;
        
        default:
            v_Str_cmd =
                "An error occured!"
            ;
        break;
        
    }
    
    f_Int_exec ( v_Str_cmd );
    
    return v_Str_cmd;
    
}

void
    f_Vod_printHelp
    ( int argc , char* argv [ ] )
{
    
    std::print
        (
            
             "\r{} {} {}\n"
            "\n{}\n{}\n{}\n"
              "{}\n{}\n{}"
             "\n{} {} {}\n"
               "\r {} \n"
            ,
            
            "Usage:" ,
            argv [ 1 - 1 ] ,
            "<options>" ,
            "[Options]" ,
            "  -i <int> (step count) [Default]: 5" ,
            "     Increase volume by step." ,
            "  -d <int> (step count) [Default]: 5" ,
            "     Decrease volume by step." ,
            "" ,
            "Example:" ,
            argv [ 1 -1 ] ,
            "-i 15" ,
            "   Increase the volume by 15(%) steps"
            
        )
    ; // out. uses format string/
    
}


/// parse args.. simple array stuff... breaks kind of imprved in next ver.
int
    f_Int_argsParser
    ( int argc , char* argv [ ] )
{
    
    std::string
        arguments
    ;
    
    if
        ( argc > 1 )
    {
        
        for
            ( int i = 1; i < argc; ++i )
        {
            
            arguments = argv [ i ];
            
            if
                ( arguments == "-i" )
            {
                
                if
                    ( i + 1 < argc )
                {
                    
                    f_Str_VolumeControl ( 'i' , std::stoi ( argv [ i + 1 ] ) );
                    
                    f_Str_sendVolNotif ( 'i' );
                    
                    break;
                    
                }
                
                f_Str_VolumeControl ( 'i' );
                
                f_Str_sendVolNotif ( 'i' );
                
                break;
                
            }
            
            else
              if
                ( arguments == "-d" )
            {
                
                if
                    ( i + 1 < argc )
                {
                    
                    f_Str_VolumeControl ( 'd' , std::stoi ( argv [ i + 1 ] ) );
                    
                    f_Str_sendVolNotif ( 'i' );
                    
                    break;
                    
                }
                
                f_Str_VolumeControl ( 'd' );
                
                f_Str_sendVolNotif ( 'i' );
                
                break;
                
            }
            
        }
        
        return 0;
        
    }
    
    else if ( argc == 1 )
    {
        
        f_Vod_printHelp ( argc , argv );
        
        return
            EXIT_FAILURE
        ;
        
    }
    
    return
        0
    ;
    
}

int
    main
    ( int argc , char* argv [ ] )
{
    
    return
        f_Int_argsParser
        ( argc , argv )
    ;
    
    // f_Str_sendVolNotif('i');
    
}

// #include <cstdlib>
// #include <print>
// #include <ctime> // For time manipulation
// #include <string>

// int main() {
//     // Start time
//     time_t start_time = time(0);
//     std::string cmd;
    
//     // Looping condition with a for loop
//     for (int i = 0; ; i++) {
//         cmd = "notify-send \"iterations: " + std::to_string(i) + '"';
//         // Check if 5 minutes (300 seconds) have passed
//         time_t current_time = time(0);
//         if (difftime(current_time, start_time) >= 300) {
//             break; // Stop the loop after 5 minutes
//         }
//         system(cmd.c_str());
//         // Optional: Output to show the loop is running
//         std::print ( "Iteration: `{}` " , i );
        
        
//         // Add a delay to avoid a crazy fast loop (optional)
//         // This is just for demonstration purposes; adjust as needed
//         // std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Requires <thread> and <chrono>
//     }
//     std::print("\n Iterations after 5 minutes");
    
//     return 0;
// }

