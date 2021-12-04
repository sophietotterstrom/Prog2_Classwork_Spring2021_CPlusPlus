#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;

        ints.push_back(new_integer);
    }
}

bool same_values(const std::vector<int>& integers)
{
    int count = 0;
    for (int alkio : integers) {

        if ((count != (int)integers.size()-1) and (alkio == integers[count+1])){
            return true;
        } else if (alkio == integers[count+1]) {
            count += 1;
        } else {
            return false;
        }
    } return false;
}

bool is_ordered_non_strict_ascending(const std::vector < int >& integers)
{
    int count = 0;

    for (int alkio : integers) {

        if (count == (int)integers.size()-1) {
            return true;
        } else if (alkio > integers[count+1]) {
            return false;
        } count += 1;
    } return false;
}

bool is_arithmetic_series(const std::vector <int>& integers)
{
    int count = 0;

    if (integers.size() == 1) {
        return true;
    }
    int diff = integers[1] - integers[0];


    for (int alkio : integers) {

        if (count == (int)integers.size()-1) {
            return true;

        } else if ((integers[count+1] - alkio) != diff) {
            return false;

        } count += 1;
    } return false;
}

bool is_geometric_series(const std::vector <int>& integers)
{
    int count = 0;

    if (integers.size() == 1) {
        return true;
    } else if ((integers[0]==0) and (integers[1]==0)) {
        return false;
    }

    int ratio = integers[1] / integers[0];

    for (int alkio : integers) {

        if (count == (int)integers.size()-1) {
            return true;

        } else if (integers[count+1]==0) {
            return false;

        } else if ((integers[count+1] / alkio) != ratio) {
            return false;

        } count += 1;
    } return false;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
