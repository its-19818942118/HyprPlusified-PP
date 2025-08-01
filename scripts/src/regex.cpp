
// #include <iostream>
// #include <regex>
// #include <string>
// #include <sstream>

// int main() {
//     std::string input = f_Str_exec("hyprctl globalshortcuts");

//     // Regular expression to match everything before the first space
//     std::regex pattern("^\\S+");

//     // Use a stringstream to process the entire input, including multiline
//     std::stringstream ss(input);
//     std::string line;

//     while (std::getline(ss, line)) {
//         if (line.empty()) {
//             std::cout << "Skipping empty line..." << std::endl;  // Clear debug message for empty line
//             continue;  // Skip empty lines (stray newlines)
//         }

//         std::smatch match;
//         if (std::regex_search(line, match, pattern)) {
//             std::cout << "Matched part: " << match.str() << std::endl;
//         } else {
//             std::cout << "No match found in line: " << line << std::endl;
//         }
//     }

//     return 0;
// }
