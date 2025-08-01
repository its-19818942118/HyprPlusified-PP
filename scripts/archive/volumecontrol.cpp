// #include <cstdlib>
// #include <iostream>
// #include <string>

// int main(int argc, char* argv[]) {
//     if (argc < 2) {
//         std::cerr << "Usage: " << argv[0] << " [up|down|mute]\n";
//         return 1;
//     }
    
//     std::string action = argv[1];
//     int step = 5; // Default step %
//     std::string cmd = "pamixer -i " + std::to_string(step);
    
//     if (action == "up") {
//         system(cmd.c_str());
//         system("notify-send 'vol up'");
//     } else if (action == "down") {
//         cmd = "pamixer -d " + std::to_string(step);
//         system(cmd.c_str());
//         system("notify-send 'vol down'");
//     } else if (action == "mute") {
//         system("pamixer -t");
//         system("notify-send 'vol mute'");
//     } else {
//         std::cerr << "Invalid action: " << action << "\n";
//         return 1;
//     }
    
//     return 0;
// }
// ################################################################3
// #include <iostream>
// #include <cstdlib>
// #include <sstream>
// #include <string>

// // Function to execute system commands
// void execCommand(const std::string& cmd) {
//     std::system(cmd.c_str());
// }

// // Function to show volume notification
// void showVolumeNotification(const std::string& volume) {
//     std::string command = "notify-send 'Volume' '" + volume + "'";
//     execCommand(command);
// }

// // Function to get current volume
// int getCurrentVolume() {
//     std::string result;
//     char buffer[128];
//     FILE* fp = popen("amixer get Master | grep -o '[0-9]*%' | head -n 1", "r");
//     if (fp) {
//         if (fgets(buffer, sizeof(buffer), fp) != nullptr) {
//             result = std::string(buffer);
//             result.erase(result.find('%'));  // Remove the '%' character
//             fclose(fp);
//         }
//     }
//     return std::stoi(result);  // Return the volume as an integer
// }

// // Function to set the volume
// void setVolume(int delta) {
//     int currentVolume = getCurrentVolume();
//     int newVolume = currentVolume + delta;
//     if (newVolume > 100) newVolume = 100;
//     if (newVolume < 0) newVolume = 0;

//     std::stringstream cmd;
//     cmd << "amixer set Master " << newVolume << "%";
//     execCommand(cmd.str());

//     // Show the new volume notification
//     showVolumeNotification("Volume: " + std::to_string(newVolume) + "%");
// }

// // Function to mute or unmute
// void toggleMute() {
//     std::string cmd = "amixer set Master toggle";
//     execCommand(cmd);
//     showVolumeNotification("Mute toggled");
// }

// int main(int argc, char* argv[]) {
//     if (argc < 3) {
//         std::cerr << "Usage: " << argv[0] << " -t <+/->[volume] | -m mute" << std::endl;
//         return 1;
//     }

//     std::string flag = argv[1];
//     if (flag == "-t") {
//         int change = std::stoi(argv[2]);
//         setVolume(change);
//     } else if (flag == "-m") {
//         toggleMute();
//     } else {
//         std::cerr << "Invalid argument." << std::endl;
//     }

//     return 0;
// }

// ###################################################################

#include <iostream>
#include <string>
#include <cstdio> // For popen and pclose
#include <sstream>

std::string executeCommandAndReadOutput(const std::string& command) {
    // char buffer[128]; // Buffer to store output chunks
    // std::string result = ""; // String to accumulate the full output
    // FILE* pipe = popen(command.c_str(), "r"); // Open a pipe to the command's stdout

    // if (!pipe) {
    //     return "Error: popen() failed!";
    // }

    // // Read data from the pipe until end of file
    // while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    //     result += buffer; // Append the read chunk to the result string
    // }

    // pclose(pipe); // Close the pipe
    // return result;
    // std::string result; // String to accumulate the full output
    FILE* pipe = popen(command.c_str(), "r"); // Open a pipe to the command's stdout

    if (!pipe) {
        return "Error: popen() failed!";
    }

    // Use std::stringstream to accumulate output line by line
    std::stringstream ss;
    char ch;
    
    // Read data from the pipe until end of file (EOF)
    while ((ch = fgetc(pipe)) != EOF) {
        ss.put(ch); // Write the character into the stringstream
    }

    pclose(pipe); // Close the pipe
    return ss.str(); // Return the accumulated output as a string
}

int main() {
    std::string cmd;
    
    // Use std::getline to read the command as a whole line
    std::cout << "Enter a command: ";
    std::getline(std::cin, cmd);  // Use std::getline for strings, not std::cin.getline

    // Example: Get the output of the command entered by the user
    std::string output = executeCommandAndReadOutput(cmd);
    std::cout << "Command Output:\n" << output << std::endl;

    // Example: Get the output of the 'echo' command
    output = executeCommandAndReadOutput("echo 'Hello from C++!'");
    std::cout << "Command Output:\n" << output << std::endl;

    return 0;
}

