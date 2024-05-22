//
// Created by davidl09 on 5/22/24.
//

#ifndef CLIPARSE_CLIPARSE_H
#define CLIPARSE_CLIPARSE_H

#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>

class CliParser : public std::vector<std::string_view> {
public:
    CliParser(int argc, char *argv[]) : std::vector<std::string_view>(argv, argv + argc) {
        erase(begin());
    }

    void addArg(const std::string& arg) {
        expectedArgs.push_back(arg);
    }

    void addArg(std::string&& arg) {
        expectedArgs.emplace_back(arg);
    }

    template <typename T>
    T get(const std::string& key) {
        const auto keyFound = std::ranges::find_first_of(*this, [&key](std::string_view str) -> bool {
            return str.starts_with(key);
        });

        if (keyFound == end()) {
            throw std::invalid_argument("Requested parameter " + key + " is not found in argv.\n");
        }
        
        if (*keyFound == key) {
            if (keyFound + 1 == end()) {
                throw std::invalid_argument("No value associated with requested parameter " + key);
            }
            
            const auto value = keyFound[1];
            
            return convert_to<T>(value);
        } //value passed without space separator, e.g. -f10;
        
        std::string_view value;
        const auto valuePos = (keyFound->contains('=') ? keyFound->find('=') + 1 : key.length() + 1);
        
        value = {keyFound->begin() + valuePos, keyFound->end()};
        
        return convert_to<T>(value);
    }

    bool get(const std::string& key) {
        return std::ranges::any_of(this->begin(), this->end(), [&key](std::string_view str) -> bool {
            return str.contains(key);
        });
    }

private:
    template <typename T>
    static T convert_to(std::string_view arg) {
        std::stringstream ss;
        ss << arg;
        T result;
        ss >> result;
        return result;
    }
    
    std::vector<std::string> expectedArgs;
};

#endif //CLIPARSE_CLIPARSE_H
