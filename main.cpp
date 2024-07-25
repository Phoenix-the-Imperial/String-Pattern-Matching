#include <iostream>
#include <stdint.h>
#include <string>

class Automaton
{
    public:
    char loop_char;
    int loop_state;
    int state;
    int start_index;
    std::string pattern;

    public:
    Automaton(const std::string pattern);
    ~Automaton(void) {};

    bool make_transition(const char& input_char, const size_t& current_index);
    size_t find_first_match(const std::string& str);
};

Automaton::Automaton(const std::string pattern)
{
    this->state = -1;
    this->start_index = 0;
    this->pattern = pattern;
    this->loop_char = pattern[0];
    size_t i = 0;
    while (++i < pattern.length() && pattern[i] == this->loop_char);
    this->loop_state = i - 1;
}


bool Automaton::make_transition(const char& input_char, const size_t& current_index)
{
    if (state == int(pattern.length() - 1))
        return true;
    else if (state == loop_state && input_char == loop_char)
    {
        start_index = current_index - loop_state;
    }
    else if (input_char == pattern[state + 1])
        state++;
    else
    {
        state = -1;
        start_index = current_index + 1;
    }
    return false;
}

size_t Automaton::find_first_match(const std::string& str)
{
    size_t i = 0;
    bool done = false;
    while (!done && i < str.length())
    {
        done = make_transition(str[i], i);
        i++;
    }
    return start_index;
}

int main()
{
    /* Pattern string */
    std::string p = "hack";
    /* String to search for the pattern string */
    std::string s = "hhhackerrank";
    Automaton a = Automaton(p);
    auto first_match = a.find_first_match(s);
    std::cout << "Match found at index: " << first_match << std::endl;
    return 0;
}
