/* Rasse2
 *
 * Description:
 * Program first reads information concerning 
 * tramways from the input file, stores them into 
 * a suitable data structure, and then permits the 
 * user to make searches, insertions, and removals 
 * in the data structure in question.
 *
 * Program author
 * Name: Sophie Tötterström
 * Student number: 050102822
 * UserID: knsoto
 * E-Mail: sophie.totterstrom@tuni.fi
 *
 * */

#include "stop.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

// Split function from a previous assignment written by a TA.
// I take no credit. For bug fixes or clarifications contact prog2@tuni.fi
// Takes a string, a separing character, and whether
// or not the function returns empty strings.
// Returns a vector of the split elements in the string.
vector<string> split(const string& s,
                     const char delimiter,
                     bool ignore_empty = false)
{
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// Checks file format, returns 0 if an invalid format in file error occurs.
// Assigns zero if stops doesn't have a given distance (starting stop of a line).
int check_row(vector<string>& row_elements)
{
    // Enter this if statement, if the row has two split characters, but
    // no distance value. Assign distance of zero.
    // Eg. East;Sammonaukio;
    if (row_elements.size()==3)
    {
        if (row_elements[2] == "")
        {
            row_elements[2] = "0.0";
        }
    }

    // Only one separator character, thus a index of 2 does not
    // exist to begin with. Now we add an element instead of reassigning.
    // Eg. South;Hervannan kampus
    else if (row_elements.size()==2)
    {
        row_elements.push_back("0.0");
    }
    else
    {
        // In all other cases, file formatting is wrong.
        return 0;
    }

    // If line (row_elements at index 0) or stop name (index = 1) is
    // an empty string, file formatting is wrong. Return zero.
    if (row_elements[0].size()==0 or row_elements[1].size()==0)
    {
        return 0;
    }

    // File formatted succesfully with valid distance values.
    // All conditions have been met. Return one to indicate success.
    return 1;
}

// Takes row elements, makes a Stop object, and adds them to the chosen data
// structure (a map with the line name as the key and a vector of Stops as the value).
// Returns 0 to indicate duplicates and doesn't add it to the map.
// Return value 1 indicates success.
int data_constructor(vector<string>& row_elements,
                      map<string, vector<Stop>>& map_of_lines_and_stops)
{
    // Declare variables to improve readibility.
    // Convert distance string to a float using a built in function.
    string line = row_elements[0];
    string stop = row_elements[1];
    float distance = stof(row_elements[2]);

    // Create a stop object with the given data.
    Stop stop_object = Stop(stop, distance);

    // Loop through the vector of stops for a given line.
    vector<Stop> vector_of_stop_objects = map_of_lines_and_stops[line];
    for (int i = 0; i < (int)vector_of_stop_objects.size(); i++)
    {
        // Initialize an object at an index of the loop to compare the new object to.
        Stop temp_stop_object = vector_of_stop_objects[i];

        if (stop_object.get_stop() == temp_stop_object.get_stop())
        {
            // Duplicate stop names found. Object should not be added
            // to the line. Return 0 to indicate failure.
            return 0;
        }
        else if (stop_object.get_distance() == temp_stop_object.get_distance())
        {
            // Duplicate stop distances found. Same result as above.
            return 0;
        }
    }

    // Now we know stop name or distance is not in the map.
    // Add stop to the line vector. 1 indicates success.
    map_of_lines_and_stops[line].push_back(stop_object);
    return 1;
}

// This function takes a user given command and
// returns it as upper case letters.
string make_command_upper(string command_lower_or_upper)
{
    string new_command = "";

    for (char letter : command_lower_or_upper)
    {
        // Runs each letter through built in function toupper
        // and adds it the the new, upper-case command.
        char new_letter = toupper(letter);
        new_command.push_back(new_letter);
    }
    return new_command;
}

// This function parses a command string into a vector
// containing a command and associated arguments.
vector<string> make_command(string command_string)
{
    // Declare a vector to store the words in.
    vector<string> command_vector;

    // Look for spaces as separator characters. Stop when no
    // more spaces are found in the string.
    while (command_string.find(' ') != string::npos)
    {
        string word;

        // If string starts with a ", look for second " to create a word
        if (command_string.find('"') == 0)
        {
            // Find the index of the enclosing ".
            int end_index = command_string.find('"', 1);

            // Create a single word from the substring inside "",
            // ignoring space characters.
            word = command_string.substr(1, end_index - 1);

            // Reassign command_string to be the rest of the string.
            if (end_index + 1 == (int)command_string.size())
            {
                // If the second " is at the end of the string,
                // make command string an empty string.
                command_string = "";
            }
            else
            {
                // Otherwise, make the command string start at the
                // beginning character of the next word (end_index + 2
                // to move past the closing " and a space separator)
                command_string = command_string.substr(end_index + 2);
            }
        }
        else
        {
            // Find the index of the first space in the string
            int split_index = command_string.find(' ');

            // Create a word from the starting index to first space
            word = command_string.substr(0, split_index);

            // Create a substring from the index after the first space (split_index + 1)
            // to the end of the string
            command_string = command_string.substr(split_index + 1);
        }
        // Add the word to the vector
        command_vector.push_back(word);
    }
    // If the last word in the command string isn't
    // an empty string, add it to the vector.
    if (command_string.size() != 0)
    {
        command_vector.push_back(command_string);
    }

    // Make first string uppercase to format it as a valid command
    command_vector[0] = make_command_upper(command_vector[0]);

    return command_vector;
}

// Command: LINES
// Prints tramlines in alphabetical order.
void print_lines(map<string, vector<Stop>>& map_of_lines_and_stops)
{
    cout << "All tramlines in alphabetical order:" << endl;
    for (auto key_value_pair : map_of_lines_and_stops)
    {
        // First element of key_value_pair is the line,
        // second element would be the vector of Stops
        cout << key_value_pair.first << endl;
    }

}

// Command: STOPS
// Prints the stops of a given tramline in alphabetical order.
void print_stops(map<string, vector<Stop>>& map_of_lines_and_stops)
{
    // Initialize a set of stop names.
    // Used a set as it is automatically in alphabetical order,
    // and it does not allow duplicates.
    set<string> set_of_stops = {};

    // Loop through all lines.
    for (auto key_value_pair : map_of_lines_and_stops)
    {
        // Loop through the vector of stops at a line.
        for (Stop stop : key_value_pair.second)
        {
            // Add a stop name in the vector to the set.
            string stop_name = stop.get_stop();
            set_of_stops.insert(stop_name);
        }
    }

    cout << "All stops in alphabetical order:" << endl;
    for (string stop_name_in_set : set_of_stops)
    {
        cout << stop_name_in_set << endl;
    }
}

// Command: LINE
// Prints all stops in a given tramline.
void print_line_info(vector<string> command_vect,
                     map<string, vector<Stop>>& map_of_lines_and_stops)
{
    // Make sure the command is valid.
    // Vector should have the command LINE and one argument.
    if (command_vect.size() != 2)
    {
        cout << "Error: Invalid input." << endl;
    }
    else
    {
        string line = command_vect[1];

        // Check to see if the line is a key in the map. If not, print error.
        if (map_of_lines_and_stops.find(line) == map_of_lines_and_stops.end())
        {
            cout << "Error: Line could not be found." << endl;
        }
        else
        {
            cout << "Line " << line <<" goes through these stops in "
                                      "the order they are listed:" << endl;

            // Loop though the vector of a given line and
            // prints each stop with its distance.
            for (Stop stop : map_of_lines_and_stops[line])
            {
                cout << " - " << stop.get_stop() << " : "
                     << stop.get_distance() << endl;
            }
        }
    }
}

// Command: ADDLINE
// Adds a tramline to the map. Initializes the value as an empty vector.
void add_line(vector<string> command_vect,
              map<string, vector<Stop>>& map_of_lines_and_stops)
{
    // Validates the amount of arguments.
    if (command_vect.size() != 2)
    {
        cout << "Error: Invalid input." << endl;
    }
    else
    {
        string line = command_vect[1];

        // Check if the line is already in the map,
        // if it is, print error message don't add it again.
        if (map_of_lines_and_stops.find(line) != map_of_lines_and_stops.end())
        {
            cout << "Error: Stop/line already exists." << endl;
        }
        else
        {
            // Initialize the value at a new line to be an empty vector.
            vector<Stop> vector_at_key = {};
            map_of_lines_and_stops[line] = vector_at_key;
            cout << "Line was added." << endl;
        }
    }
}

// Command: STOP
// Prints the lines a given stop is in.
void print_stop_info(vector<string> command_vect,
                     map<string, vector<Stop>>& map_of_lines_and_stops)
{
    // Validates user input.
    if (command_vect.size() != 2)
    {
        cout << "Error: Invalid input." << endl;
    }
    else
    {
        // Assigns the stop name from the user input. Initializes a
        // vector, which will include the lines the stop is on.
        string stop_name = command_vect[1];
        vector<string> vector_of_lines_the_stop_is_on;

        // Loops through the map.
        for (auto key_value_pair : map_of_lines_and_stops)
        {
            string line_name = key_value_pair.first;

            // Loops through the stops in a vector of a specific line.
            for (Stop stop : key_value_pair.second)
            {
                if (stop.get_stop() == stop_name)
                {
                    // Checks to see if the stop is in the line and if it is,
                    // adds it to the vector of lines the stop is on.
                    vector_of_lines_the_stop_is_on.push_back(line_name);
                }
            }
        }
        // If no lines have been added to the vector,
        // the stop is not on any lines. Print accordingly.
        if (vector_of_lines_the_stop_is_on.size()==0)
        {
            cout << "Error: Stop could not be found." << endl;
        }
        else
        {
            cout << "Stop " << stop_name
                 << " can be found on the following lines:" << endl;
            for (string line : vector_of_lines_the_stop_is_on)
            {
                cout << " - " << line << endl;
            }
        }
    }
}

// Command: DISTANCE
// Calculates the distance between two given stops.
void calculate_distance(vector<string> command_vect,
                        map<string, vector<Stop>>& map_of_lines_and_stops)
{
    // Make sure user input is valid.
    if (command_vect.size() != 4)
    {
        cout << "Error: Invalid input." << endl;
    }
    else
    {
        // Assign variable names for clarity.
        string line = command_vect[1];
        string first_stop = command_vect[2];
        string second_stop = command_vect[3];

        // First check if the line is valid.
        if (map_of_lines_and_stops.find(line) == map_of_lines_and_stops.end())
        {
            cout << "Error: Line could not be found." << endl;
        }
        else
        {
            vector<Stop> vect_of_stops_at_line = map_of_lines_and_stops[line];

            // Initialize the indexes of both stops to be -1. If the stops
            // are found in the line, the index will be changes accordingly.
            // Else we can use this to get the correct print out.
            int index_of_first_stop = -1;
            int index_of_second_stop = -1;

            // Loop through all the stops in the given line.
            for (int index = 0;
                 index < (int)vect_of_stops_at_line.size();
                 index++)
            {
                // If either stop is found, update the index.
                if (vect_of_stops_at_line[index].get_stop() == first_stop)
                {
                    index_of_first_stop = index;
                }
                if (vect_of_stops_at_line[index].get_stop() == second_stop)
                {
                    index_of_second_stop = index;
                }
            }

            // If the index of either stop is -1, it has not been found in the
            // line. Print accordingly.
            if ((index_of_first_stop == -1) or (index_of_second_stop == -1))
            {
                cout << "Error: Stop could not be found." << endl;
            }
            else
            {
                // Assign variable names for clarity.
                Stop stop_obj_1 = vect_of_stops_at_line[index_of_first_stop];
                Stop stop_obj_2 = vect_of_stops_at_line[index_of_second_stop];
                float stop_dist_1 = stop_obj_1.get_distance();
                float stop_dist_2 = stop_obj_2.get_distance();
                float distance_between_stops;

                // Calculate absolute value distance and
                // print it in the desired format.
                if (stop_dist_1 > stop_dist_2)
                {
                    distance_between_stops = stop_dist_1 - stop_dist_2;
                }
                else
                {
                    distance_between_stops = stop_dist_2 - stop_dist_1;
                }

                cout << "Distance between "
                     << first_stop << " and "
                     << second_stop << " is "
                     << distance_between_stops << endl;
            }
        }
    }
}

// Command: REMOVE
// Removes a given stop from all lines its on.
void remove_stop(vector<string> command_vect,
                  map<string, vector<Stop>>& map_of_lines_and_stops)
{
    // Validates user input.
    if (command_vect.size() != 2)
    {
        cout << "Error: Invalid input." << endl;
    }
    else
    {
        // Initialize variables for clarity and a found flag
        // which will be used for making sure print out is correct.
        string stop_name = command_vect[1];
        bool found_flag = false;

        // Loops through map.
        for (auto key_value_pair : map_of_lines_and_stops)
        {
            string line_name = key_value_pair.first;
            vector<Stop> vect_of_stops_at_line = key_value_pair.second;

            // Initialize the index at -1 so it can be updated
            // the give the  index of the stop. Else it will be
            // used to make sure printout is okay.
            int stop_index = -1;

            // Loops through stops of a given line.
            for (int index = 0; index < (int)vect_of_stops_at_line.size(); index++)
            {
                // If user given stop is found in a stop vector,
                // update index to tell where it is.
                if (vect_of_stops_at_line[index].get_stop() == stop_name)
                {
                    stop_index = index;
                }
            }
            if (stop_index != -1)
            {
                // -1 tells stop was found somewhere (at stop_index).
                // Remove the stop at this index. Change found flag to true
                // to indicate this for later printing.
                vect_of_stops_at_line.erase(vect_of_stops_at_line.begin() + stop_index);
                map_of_lines_and_stops[line_name] = vect_of_stops_at_line;
                found_flag = true;
            }
        }
        if (found_flag == false)
        {
            cout << "Error: Stop could not be found." << endl;
        }
        else
        {
            cout << "Stop was removed from all lines." << endl;
        }
    }
}

// Command: ADDSTOP
// Adds a given stop to a line with a given distance value.
void add_stop(vector<string> command_vect,
              map<string, vector<Stop>>& map_of_lines_and_stops)
{
    // Validate user input.
    if (command_vect.size() != 4)
    {
        cout << "Error: Invalid input." << endl;
    }
    else
    {
        // Assign variables for clarity.
        string line = command_vect[1];
        string new_stop = command_vect[2];
        float distance = stof(command_vect[3]);
        bool stop_exists = false;

        // Check to see if the given line exists.
        if (map_of_lines_and_stops.find(line) == map_of_lines_and_stops.end())
        {
            cout << "Error: Line could not be found." << endl;
        }
        else
        {
            // Create a new stop object with the given data.
            Stop new_stop_object = Stop(new_stop, distance);

            // Loop through the vector of Stops at a given line to handle
            // cases where the stop name or diśtance already exists.
            vector<Stop> vector_of_stop_objects = map_of_lines_and_stops[line];
            for (int i = 0; i < (int)vector_of_stop_objects.size(); i++)
            {
                // Create a temporary Stop object for comparisons.
                Stop temp_stop_object = vector_of_stop_objects[i];

                if (new_stop_object.get_stop() == temp_stop_object.get_stop())
                {
                    cout << "Error: Stop/line already exists." << endl;
                    stop_exists = true;
                }
                else if (new_stop_object.get_distance() == temp_stop_object.get_distance())
                {
                    cout << "Error: Stop/line already exists." << endl;
                    stop_exists = true;
                }
            }
            // If the stops was found, the flag was changed to true.
            // If it hasn't been changed, we can proceed with adding the stop.
            if (stop_exists == false)
            {
                // Loop through the vector to check distances and find
                // the position of where to insert the stop.
                // Initialize index of stop at 0.
                int index = 0;
                for (Stop stop_object_in_vect : map_of_lines_and_stops[line])
                {
                    if (stop_object_in_vect.get_distance() <
                            new_stop_object.get_distance())
                    {
                        // Increment index every time distance of the stop to be
                        // added is bigger than the stop we are comparing to.
                        index++;
                    }
                }
                // Insert stop at the found index.
                map_of_lines_and_stops[line]
                        .insert(map_of_lines_and_stops[line]
                                .begin() + index, new_stop_object);

                cout << "Stop was added." << endl;
                return;
            }
        }
    }
}

// Short and sweet main.
int main()
{
    print_rasse();

    // Ask for user input for the file.
    string input_filename = "";
    cout << "Give a name for input file: ";
    getline(cin, input_filename);

    ifstream input_file_object(input_filename);

    // Program cannot open the input file
    if (not input_file_object)
    {
        cout << "Error: File could not be read." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        // Initializing the data structure to which infromations
        // from the file will be added. Using a map to make
        // searching through it convenient. Value at key is a vector
        // of Stop objects.
        map<string, vector<Stop>> map_of_lines_and_stops;

        string row;

        // Loop through all rows in the input document.
        while (getline(input_file_object, row))
        {
            // Vector stores stop information as separate
            // strings as vector elements.
            vector<string> row_elements = split(row, ';', false);

            // Both these functions return 1 is execution was succesfull.
            // Else print error and return to exist program.
            if (check_row(row_elements) != 1)
            {
                cout << "Error: Invalid format in file." << endl;
                return EXIT_FAILURE;
            }

            if (data_constructor(row_elements, map_of_lines_and_stops) != 1)
            {
                cout << "Error: Stop/line already exists." << endl;
                return EXIT_FAILURE;
            }
        }

        // Ask for user input to manage the User Interface menu.
        // Different commands call different functions.
        string command_string;
        cout << "tramway> ";
        getline(cin, command_string);

        // From the user input command_string we create a vector
        // of command elements by using the make_command function.
        vector<string> command_vector = make_command(command_string);
        string command = command_vector[0];

        while (command != "QUIT")
        {
            if (command == "LINES")
            {
                print_lines(map_of_lines_and_stops);
            }

            else if (command == "LINE")
            {                
                print_line_info(command_vector, map_of_lines_and_stops);
            }

            else if (command == "STOPS")
            {
                print_stops(map_of_lines_and_stops);
            }

            else if (command == "STOP")
            {
                print_stop_info(command_vector, map_of_lines_and_stops);
            }

            else if (command == "DISTANCE")
            {
                calculate_distance(command_vector, map_of_lines_and_stops);
            }

            else if (command == "ADDLINE")
            {
                add_line(command_vector, map_of_lines_and_stops);
            }

            else if (command == "ADDSTOP")
            {
                add_stop(command_vector, map_of_lines_and_stops);
            }

            else if (command == "REMOVE")
            {
                remove_stop(command_vector, map_of_lines_and_stops);
            }

            else
            {
                cout << "Error: Invalid input." << endl;

            }

            // After looping once, continue asking for user input
            // until the user gives the command "QUIT".
            command_string = "";
            cout << "tramway> ";
            getline(cin, command_string);
            command_vector = make_command(command_string);
            command = command_vector[0];
        }
    }
    return EXIT_SUCCESS;
}
