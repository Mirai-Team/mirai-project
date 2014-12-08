#include <string>
#include <algorithm> // remove(), erase()
#include <sstream> // for locale

#include "General/string_functions.hpp"

using namespace std;

void mp::strip_letter(string &str, const char &letter)
{
    str.erase(remove(str.begin(), str.end(), letter), str.end());
}

string mp::upper(string text)
{
    locale loc;

    for (unsigned int i{ 0 } ; i < text.length() ; i++)
    {
        text[i] = toupper(text[i], loc);
    }

    return text;
}

vector<string> mp::split(const string &text, const char &separator, unsigned int limit)
{
    istringstream iss{ text };
    string word;
    vector<string> words;

    unsigned int i{ 0 };
    while (getline(iss, word, separator) and limit != 0 and i < limit)
    {
        i++;
        words.push_back(word);
    }

    return words;
}

string mp::replace(string &text, string to_replace, string replace_with)
{
    return(text.replace(text.find(to_replace), to_replace.length(), replace_with));
}
