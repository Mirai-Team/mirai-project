#include <string>
#include <algorithm> // remove(), erase()
#include <sstream> // for locale

#include "MiraiProject/util/string_functions.hpp"

using namespace std;

void mp::stripLetter(string &str, const char &letter)
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

string mp::replace(string &text, string toReplace, string replaceWith)
{
    return(text.replace(text.find(toReplace), toReplace.length(), replaceWith));
}
