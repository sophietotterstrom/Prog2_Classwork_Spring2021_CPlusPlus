#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_filename = "";
    cout << "Input file: ";
    getline(cin, input_filename);

    string output_filename = "";
    cout << "Output file: ";
    getline(cin, output_filename);

    ifstream input_file_object(input_filename);

    if (not input_file_object)
    {
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        ofstream output_file_object(output_filename);

        string line;
        int count = 1;

        while (getline(input_file_object, line))
        {
           output_file_object << count << " " << line << endl;

           count += 1;
        }

        output_file_object.close();
        input_file_object.close();
    }
}
