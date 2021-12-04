#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>
using namespace std;

class Player
{
public:
    Player(string name);

    string get_name();

    int get_points();

    bool has_won();

    void add_points(int added_points);

private:

    string name_;
    int points_;


};

#endif // PLAYER_HH
