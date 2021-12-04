#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
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




using Network = map<string, vector<string>>;


void store(Network& network, const string& id1, const string& id2)
{
    if (network.count(id1) == 0)
    {
        network[id1] = {};
    }

    if (network.count(id2) == 0)
    {
        network[id2] = {};
    }

    network.at(id1).push_back(id2);
}

void print(const Network& network, const string& current_id, const int depth = 0)
{
    for (int i = 0; i < depth; ++i)
    {
        cout << "..";
    }

    cout << current_id << endl;
    for (const string& child : network.at(current_id))
    {
        print(network, child, depth + 1);
    }
}

int count(const Network& network, const string current_id, bool count_self = false)
{
    int child_count = 0;
    if (count_self)
    {
        child_count = 1;
    }

    for (const string& child : network.at(current_id))
    {
        child_count += count(network, child, true);
    }

    return child_count;
}

int depth(const Network& network, const string& current_id, int depth_tmp = 1)
{
    int max_child_depth = depth_tmp;

    for (const string& child : network.at(current_id))
    {
        int child_depth = depth(network, child, depth_tmp + 1);
        if (child_depth > max_child_depth)
        {
            max_child_depth = child_depth;
        }
        // voisi olla myös: max_child_depth = max(max_child_depth, current_child_depth)
    }

    return max_child_depth;
}


int main()
{
    Network network;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store(network, id1, id2);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print(network, id);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            cout << count(network, id) << endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            cout << depth(network, id) << endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
