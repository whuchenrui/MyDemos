/*
 * My implementation for string functions
 */

// trim(), remove specific characters from left and/or right side of input string
const char* whitespace = " \t\n\r\f\v";

// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t = whitespace) {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s, const char* t = whitespace) {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (left & right)
inline std::string& trim(std::string& s, const char* t = whitespace) {
    return ltrim(rtrim(s, t), t);
}


/*
 * Test cases
 */
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    string t0 = "";
    string t1 = "  hi  ";
    string t2 = " \t\n\r\r\n\v\fhi";
    string t3 = "hi \r\n\r\n\t\v\f";
    string t4 = "hi";
    string t5 = "\r\n\t\f\v";

    cout << trim(t0, whitespace) << endl;
    cout << trim(t1, whitespace) << endl;
    cout << trim(t2, whitespace) << endl;
    cout << trim(t3, whitespace) << endl;
    cout << trim(t4, whitespace) << endl;
    cout << trim(t5, whitespace) << endl;
    assert(t0.size() == 0);
    assert(t1.size() == 2);
    assert(t2.size() == 2);
    assert(t3.size() == 2);
    assert(t4.size() == 2);
    assert(t5.size() == 0);

    return 0;
}