#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool is_the_element_last_in_the_vector(int element, vector<int>& vector)
{

    int last_element = vector.back();

    if (element == last_element)
    {
        return true;
    }

    return false;
}

bool is_the_row_number_in_the_row_vector(int row_number, vector<int>& row_vector)
{
    for (int number : row_vector)
    {
        if (number == row_number)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    string input_filename = "";
    cout << "Input file: ";
    getline(cin, input_filename);

    ifstream input_file_object(input_filename);

    if (not input_file_object)
    {
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;

    }

    else
    {
        map<string, vector<int>> dict_of_words_and_amounts;
        int row_counter = 1;

        string row;

        while (getline(input_file_object, row))
        {
            vector<int> vector_of_rows_word_is_on;

            int start = 0;
            int end = row.find(" ", start);
            string word = row.substr(start,end);

            if ( dict_of_words_and_amounts.find(word) != dict_of_words_and_amounts.end() )
            {
                // The word was found in the map.

                dict_of_words_and_amounts.at(word).push_back(row_counter);
            }
            else
            {
                // The word was not found in the map.
                dict_of_words_and_amounts.insert( {word, vector_of_rows_word_is_on} );
                dict_of_words_and_amounts.at(word).push_back(row_counter);
            }

            while (row.find(" ", start) != string::npos)
            {
                start = end+1;
                end = row.find(" ", start);
                word = row.substr(start, end-start);

                if ( dict_of_words_and_amounts.find(word) != dict_of_words_and_amounts.end() )
                {
                    // The word was found in the map.

                    // we need to check if the current row_counter is already in the vector

                    if (is_the_row_number_in_the_row_vector(row_counter, dict_of_words_and_amounts.at(word)) == false)
                    {
                        dict_of_words_and_amounts.at(word).push_back(row_counter);
                    }

                }
                else
                {
                    // The word was not found in the map.
                    dict_of_words_and_amounts.insert( {word, vector_of_rows_word_is_on} );
                    dict_of_words_and_amounts.at(word).push_back(row_counter);
                }
            }
            row_counter += 1;
        }



        for (auto key_value_pair : dict_of_words_and_amounts)
        {
            vector<int> rows = key_value_pair.second;

            cout << key_value_pair.first << " ";
            cout << rows.size() << ": ";

            for (int row_number : rows)
            {
                // if the row_number element is the last element in the vector rows
                if (is_the_element_last_in_the_vector(row_number, rows) == true)
                {
                    cout << row_number;
                }
                else
                {
                    // else print like this
                    cout << row_number << ", ";
                }
            }

            cout << endl;
        }

        return EXIT_SUCCESS;
    }

    input_file_object.close();
}
