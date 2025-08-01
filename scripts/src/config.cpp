#include <cstddef>
#include <cstdlib>
#include <print>
#include <string>
#include <fstream>
#include <iostream>

namespace
    confReader
{
    
    std::string
        homeDir =
        static_cast <std::string>
        ( std::getenv ( "HOME" ) ) + "/"
    ;
    
    /* Accepts a config file path */
    std::string
        readConfLine
        ( std::string confFile = "$HOME/.config/hyprpp/config.txt" )
    {
        
        std::string
            line ,
            confLines ,
            toReplace = "$HOME" ,
            replaceHomePath = homeDir
        ;
        
        size_t pos = confFile.find ( toReplace ); 
        
        while
            ( pos != std::string::npos )
        {
            
            confFile.replace
                ( pos , toReplace.length ( ) , replaceHomePath )
            ;
            pos =
                confFile.find
                ( replaceHomePath , pos + toReplace.length ( ) )
            ;
            
        }
        
        std::fstream configFile ( confFile );
        
        if
            ( configFile.is_open ( ) )
        {
            
            while
                ( std::getline ( configFile , line ) )
            {
                
                confLines += line + '\n';
                
            }
            
        }
        
        return
            confLines
        ;
        
    }
    
    void
        parseConfig
        ( )
    {
        
        std::string
            confLines =
            readConfLine ( )
        ;
        
        size_t
            pos = 0
        ;
        
        for
            ( size_t i { }; i < confLines.size ( ); ++i )
        {
            
            while
                (
                    ( pos = confLines.find ( "echo" , pos ) ) !=
                    std::string::npos
                )
            {
                
                if
                    (
                        pos + 5 < confLines.size ( ) &&
                        confLines [ pos + 5 ] == '='
                    )
                {
                    
                    if
                        (
                            pos + 7 < confLines.size ( ) &&
                            confLines [ pos + 7 ] == '"' // look for `"`
                        )
                    {
                        
                        std::print("{} found" , confLines[pos + 7]);
                        
                    }
                    
                    if
                        (
                            pos + i + 1 < confLines.size ( ) &&
                            confLines [ pos + i ] != '"'
                        )
                    {
                        
                        pos += 1;
                        std::print ( "{}" , pos + i + 1 );
                        continue;
                        
                    }
                    
                }
                
                pos += 4;
                
            }
            
        }
        
    }
    
}

int
    main
    ( )
{
    
    std::string
        confFile =
        "$HOME/.config"
    ;
    
    std::cout
        <<  confReader::readConfLine ( confFile )
    ;
    
    confReader::parseConfig ( );
    
    return 0;
    
}
