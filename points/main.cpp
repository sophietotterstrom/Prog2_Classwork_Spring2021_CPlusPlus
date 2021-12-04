#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

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
        cout << "Final scores: " << endl;

        string line;

        map<string, int> map_aka_dict_of_names_and_points;

        while (getline(input_file_object, line))
        {
            int split_index = line.find(":");

            string name_key;


            name_key = line.substr(0, split_index);
            string points_value_string = line.substr(split_index+1, line.length()-1);

            stringstream string_to_int(points_value_string);
            int points_value = 0;
            string_to_int >> points_value;


            if ( map_aka_dict_of_names_and_points.find(name_key) != map_aka_dict_of_names_and_points.end() )
            {
                // The word was found in the map.
                // increment

                map_aka_dict_of_names_and_points.at(name_key) += points_value;
            }
            else
            {
                // The word was not found in the map.
                map_aka_dict_of_names_and_points.insert( {name_key, points_value});
            }

        }

        for (auto name_and_points : map_aka_dict_of_names_and_points)
        {
            cout << name_and_points.first << ": " << name_and_points.second << endl;
        }
    }


    input_file_object.close();
}
