#include <print>
#include <chrono>
#include <cstdio>
#include <csignal>
#include <unistd.h>
#include <sys/ioctl.h>

void
    get_termSize
    ( int &rows , int &cols )
{
    
    struct winsize w;
    ioctl ( STDOUT_FILENO , TIOCGWINSZ , &w );
    rows = w.ws_row;
    cols = w.ws_col;
    
}

void
    print
    ( [[maybe_unused]] int rows , [[maybe_unused]] int cols )
{
    
    std::string frame{};
    
    for (auto i{1}; i <= cols; ++i) {
        
        frame += std::format("{}", "━");
        
    }
    
    frame += '\n';
    
    for
        ( auto i { 2 }; i <= rows - 1; ++i )
    {
        
        frame += std::format ("\033[{};1H┃", i); // Left border at column 1
        frame += std::format ("\033[{};{}H┃\n\r", i, cols); // Right border at last column
    }

    for (auto i{1}; i <= cols; ++i) {

        frame += std::format("{}", "━");
    }

    std::print("{}", frame.data());
    std::fflush(stdout);
}

int rows, cols;

void handleResise(int) {
  std::print("\033[3J\033[2J\033[H");
  std::fflush(stdout);
  get_termSize(rows, cols);
  print(rows, cols);
}

int main() {

  std::signal(SIGWINCH, handleResise);

  while (true) {
  }
}
