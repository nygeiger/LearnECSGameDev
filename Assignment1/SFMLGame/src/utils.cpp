#include <string>
#include <sstream>

bool compareStrings(std::string str1, std::string str2)
{
    if (str1.length() != str2.length())
        return false;

    for (int i = 0; i < str1.length(); ++i)
    {
        if (tolower(str1[i]) != tolower(str2[i]))
            return false;
    }
    return true;
}

template <typename Iter>
Iter nth_occurence(Iter first, Iter last,
                   Iter first_, Iter last_,
                   unsigned nth)
{
    Iter it = std::search(first, last, first_, last_);
    if (nth == 0)
        return it;
    if (it == last)
        return it;
    return nth_occurence(it + std::distance(first_, last_), last,
                         first_, last_, nth - 1);
    // https://stackoverflow.com/questions/18972258/index-of-nth-occurrence-of-the-string
}

int string_nth_occurrence(const std::string &str, const std::string &findMe, int nth)
{
    size_t pos = 0;
    int cnt = 0;

    if (nth == 0)
    {
        // # returns std::string::npos if doesn't find
        return str.find(findMe, 0);
    }

    while (cnt != nth)
    {
        pos += 1;
        pos = str.find(findMe, pos);
        if (pos == std::string::npos)
            return -1;
        cnt++;
    }
    return pos;
    // https://stackoverflow.com/questions/18972258/index-of-nth-occurrence-of-the-string
}

// Function to split a string into tokens based on a
// delimiter
void splitString1(std::string &input, char delimiter,
                  std::string arr[], int &index)
{
    // Creating an input string stream from the input string
    std::istringstream stream(input);

    // Temporary string to store each token
    std::string token;

    // Read tokens from the string stream separated by the
    // delimiter
    while (getline(stream, token, delimiter))
    {
        // Add the token to the array
        arr[index++] = token;
    }
//https: // www.geeksforgeeks.org/how-to-split-string-into-an-array-in-cpp/
}

std::vector<std::string> splitString2(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
