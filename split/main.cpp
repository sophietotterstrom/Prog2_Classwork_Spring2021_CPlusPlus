#include <iostream>
#include <string>
#include <vector>

using namespace std;


vector<string> split(string string_to_be_split, char separator, bool ignore_empty_parts = false) {

    vector<string> new_text;

    string::size_type start = 0;
    string::size_type end = 0;

    string word;

    if (string_to_be_split.find(separator, start) == string::npos)
    {
        new_text.push_back(string_to_be_split);
        return new_text;
    }

    while (string_to_be_split.find(separator, start) != string::npos)
    {

        end = string_to_be_split.find(separator, start);

        word = string_to_be_split.substr(start, end-start);

        if ((ignore_empty_parts == true) and (word != ""))
        {

            new_text.push_back(word);
        }

        else if (ignore_empty_parts == false)
        {
            new_text.push_back(word);
        }

        start = end+1;
    }

    string last_word = string_to_be_split.substr(end+1);
    new_text.push_back(last_word);

    return new_text;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
