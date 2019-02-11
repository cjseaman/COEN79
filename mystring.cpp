/*
 * Collin Seaman
 * COEN 79 Lab 5
 * 1/8/2019
 *
 * Implementation of a custom string class with operator overloading and dynamic
 * memory allocation.
 *
 * INVARIANTS:
 *    Current_length and allocated must be greater than or equal
 * to zero, attempts to decrememnt past 0 will result in errors.
 *
*/

#include <iostream>
#include <assert.h>
#include "mystring.h"

using namespace coen79_lab5;

namespace coen79_lab5 {


    string::string(const char str[ ]) {
        current_length = strlen(str);
        allocated = current_length;
        characters = new char[allocated];
        strncpy(characters, str, allocated);
        characters[current_length] = '\0';
    }

    string::string(char c) {
        current_length = 1;
        allocated = 2;
        characters = new char[allocated];
        characters[0] = c;
        characters[1] = '\0';
    }

    string::string(const string& source) {
        current_length = source.current_length;
        allocated = source.current_length + 1;
        characters = new char[allocated];
        strncpy(characters, source.characters, allocated);
    }
    string::~string( ) {
        allocated = 0;
        current_length = 0;
        delete[] characters;
    }

    void string::operator +=(const string& addend) {
        reserve(current_length + addend.current_length);
        strncat(characters, addend.characters, allocated);
        current_length += addend.current_length;

    }

    void string::operator +=(const char addend[ ]) {
        reserve(current_length + strlen(addend));
        strncat(characters, addend, allocated);
        current_length += strlen(addend);
    }

    void string::operator +=(char addend) {
        reserve(current_length);
        characters[current_length] = addend;
        current_length++;
        characters[current_length] = '\0';
    }

    void string::reserve(size_t n) {
        char *temp = new char[n + allocated];
        strncpy(temp, characters, allocated);
        delete[] characters;
        characters = temp;
        allocated += n;
    }

    string& string::operator =(const string& source) {

        reserve(source.current_length);
        current_length = source.current_length;
        strncpy(characters, source.characters, current_length);
        return *this;
    }

    void string::insert(const string& source, unsigned int position) {
        assert(position <= current_length);
        reserve(source.current_length + current_length);
        char buffer[current_length - position];
        strncpy(buffer, characters + position, current_length - position);
        strncpy(characters + position + source.current_length, buffer, current_length - position);
        strncpy(characters + position, source.characters, source.current_length);
        current_length += source.current_length;
    }

    void string::dlt(unsigned int position, unsigned int num) {
        assert(position + num <= current_length);
        size_t i;
        for(i = position; i <= (current_length - num); i++) {
            characters[i] = characters[i + num];
        }
        characters[current_length] = '\0';
        current_length -= num;
    }

    void string::replace(char c, unsigned int position) {
        assert(position < current_length);
        characters[position] = c;
    }
    void string::replace(const string& source, unsigned int position) {
        assert(position + source.current_length <= current_length);
        strncpy(&characters[position], source.characters, source.current_length);
    }

    char string::operator [ ](size_t position) const {
        assert(position < current_length);
        return characters[position];
    }

    int string::search(char c) const {
        int i;
        for(i = 0; i < current_length; i++) {
            if(characters[i] == c) {
                return i;
            }
        }
        return -1;
    }

    int string::search(const string& substring) const {
        int i;
        for(i = 0; i < (current_length - substring.current_length) + 1; i++) {
            if(strncmp(&characters[i], substring.characters, substring.current_length) == 0) {
                return i;
            }
        }
        return -1;
    }

    unsigned int string::count(char c) const {
        unsigned int x = 0, i;
        for(i = 0; i < current_length; i++) {
            if(characters[i] == c) {
                x++;
            }
        }
        return x;
    }

    std::ostream& operator <<(std::ostream& outs, const string& source) {
        outs << source.characters;
        return outs;
    }

    bool operator ==(const string& s1, const string& s2) {
        return (strncmp(s1.characters, s2.characters, s1.current_length) == 0);
    }

    bool operator !=(const string& s1, const string& s2) {
        if(s1 == s2) {
            return false;
        } else return true;
    }
    bool operator > (const string& s1, const string& s2) {
        return (strncmp(s1.characters, s2.characters, s1.current_length) > 0);
    }

    bool operator < (const string& s1, const string& s2) {
        return (strncmp(s1.characters, s2.characters, s1.current_length) < 0);
    }

    bool operator >=(const string& s1, const string& s2) {
        return ((s1 == s2) || (s1 > s2));
    }

    bool operator <=(const string& s1, const string& s2) {
        return ((s1 == s2) || (s1 < s2));
    }

    string operator +(const string& s1, const string& s2) {
        string temp(s1);
        temp += s2;
        return temp;
    }

    string operator +(const string& s1, const char addend[ ]) {
        string temp(s1);
        temp += addend;
        return temp;
    }

    string& string::operator =(const char array[ ]) {
        reserve(strlen(array));
        strncpy(characters, array, allocated);
        current_length = strlen(array);
        return *this;
    }

    std::istream& operator >> (std::istream& ins, string& target) {
        char buff[100] = {'\0'};
        ins >> buff;
        target = string(buff);
        return ins;
    }
}
