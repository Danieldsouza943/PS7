// Copyright 2024 Daniel Dsouza
// compile with
// g++ stdin_boost.cpp -lboost_regex
// regex_match example
#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main() {
    std::string s, rs;
    boost::regex e;

    // Display helpful error codes
    std::cout << "Here are some helpful error codes you may encounter\n";
    std::cout << "while constructing your regex\n";
    std::cout << "error_bad_pattern " << boost::regex_constants::error_bad_pattern << std::endl;
    std::cout << "error_collate " << boost::regex_constants::error_collate << std::endl;
    std::cout << "error_ctype " << boost::regex_constants::error_ctype << std::endl;
    std::cout << "error_escape " << boost::regex_constants::error_escape << std::endl;
    std::cout << "error_backref " << boost::regex_constants::error_backref << std::endl;
    std::cout << "error_brack " << boost::regex_constants::error_brack << std::endl;
    std::cout << "error_paren " << boost::regex_constants::error_paren << std::endl;
    std::cout << "error_brace " << boost::regex_constants::error_brace << std::endl;
    std::cout << "error_badbrace " << boost::regex_constants::error_badbrace << std::endl;

    std::cout << std::endl;

    // Input regex
    std::cout << "Enter regex > ";
    std::getline(std::cin, rs);

    try {
        e = boost::regex(rs);
    } catch (const boost::regex_error &exc) {
        std::cout << "Regex constructor failed with code " << exc.code() << std::endl;
        return 1;
    }

    std::cout << "Enter line > ";

    while (std::getline(std::cin, s)) {
        std::cout << std::endl;

        if (boost::regex_match(s, e)) {
            std::cout << "string object \"" << s << "\" matched\n\n";
        }

        if (boost::regex_match(s.begin(), s.end(), e)) {
            std::cout << "range on \"" << s << "\" matched\n\n";
        }

        boost::smatch sm;  // Same as match_results<string::const_iterator> sm;
        boost::regex_match(s, sm, e);
        std::cout << "string object \"" << s << "\" with " << sm.size() << " matches\n\n";

        if (sm.size() > 0) {
            std::cout << "the matches were: ";
            for (unsigned i = 0; i < sm.size(); ++i) {
                std::cout << "[" << sm[i] << "] " << std::endl;
            }
        }

        std::cout << std::endl;

        std::cout << "Enter line > ";
    }

    return 0;
}

//
