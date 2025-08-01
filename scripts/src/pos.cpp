#include <iostream>
#include <string>

int main() {
    std::string confLines = "Some random text echo \" something else \"quoted\"";

    size_t pos = 0;  // Position to keep track of where we're searching

    // Loop through the string and find all occurrences of "echo"
    while ((pos = confLines.find("echo", pos)) != std::string::npos) {
        std::cout << "Found 'echo' at position " << pos << std::endl;

        // Check if the next character after "echo" is a quote (")
        if (pos + 4 < confLines.size() && confLines[pos + 4] == '"') {
            std::cout << "Found quote (\" ) right after 'echo'" << std::endl;
        }

        // Move position forward to continue searching (to avoid infinite loop)
        pos += 4; // Move past the current 'echo'
    }

    return 0;
}
