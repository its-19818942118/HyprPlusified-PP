// #include <cstddef>
// #include <print>
// #include <unistd.h>
// #include <sys/ioctl.h>

// void
//     get_termSize
//     ( int &rows , int &cols )
// {
//     struct winsize w;
//     ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
//     rows = w.ws_row;
//     cols = w.ws_col;
// }

// int
//     colsChecker
//     ( int &cols )
// {
    
//     if
//         ( ( cols / 2 - 1 ) % 2 == 0 )
//     {
        
//         return 
        
//     }
    
// }

// void
//     print_mainHeader
//     ( int &rows , int &cols )
// {
    
//     std::print ( "╭" );
    
//     for
//     ( size_t i { 0 }; ( i < cols / 2 - 1 ); ++i )
//     {
        
//         std::print ( "{}" , "─" );
        
//     }
    
//     std::println ( "{}" , "╮" );
    
//     std::print ( "{}" , "│" );
    
//     for
//         ( size_t i { 0 }; ( i < cols / 4 - 2 ); ++i )
//     {
        
//         std::print ( " " );
        
//     }
    
//     std::print ( "Cli" );
    
    
    
//     std::println ( "{}" , "│" );
    
//     // -----------------------------------------------------------------------//
    
//     std::print ( "╰" );
    
//     for
//     ( size_t i { 0 }; ( i < cols / 2 - 1 ); ++i )
//     {
        
//         std::print ( "{}" , "─" );
        
//     }
    
//     std::println ( "{}" , "╯" );
    
    
// }

// int
//     main
//     ( )
// {
    
//     int
//         rows , cols
//     ;
    
//     get_termSize ( rows , cols );
    
//     std::println ( "Welcome To the CLI" );
    
//     std::println ( "Terminal rows: {} , cols: {} " , rows , cols );
    
//     print_mainHeader ( rows , cols );
    
// }

#include <print>
#include <cstddef>
#include <unistd.h>
#include <sys/ioctl.h>

void
    get_termSize
    ( int &rows , int &cols )
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row;
    cols = w.ws_col;
}

int
    main
    ( void )
{
    
    int rows , cols;
    
    get_termSize(rows, cols);
    
    std::println("rows: {} , cols: {}" , rows , cols);
    
    
    // We are checking if the integar `i` is greater than cols. and printing out the exact number of stuff = cols.
    // if cols = 4? i will add +1 until i = 4 which is then i = cols
    for
        ( size_t i { 0 }; i < cols; ++i )
    {
        
        std::print("-");
        
    }
    
    std::print("\n{}" , "|");
    
}
