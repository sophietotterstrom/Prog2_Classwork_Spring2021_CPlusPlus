#include "player.hh"

Player::Player(string name):
    name_(name)
{
    points_ = 0;
}

string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return points_;
}

bool Player::has_won()
{
    if (points_ == 50) {
        cout << "Game over! The winner is " << name_ << "!" << endl;
        return true;
    } else {
        return false;
    }
}

void Player::add_points(int added_points)
{
    if (points_ + added_points > 50) {
        points_ = 25;

        string name = this->get_name();
        cout << name << " gets penalty points!" << endl;

    } else {
        points_ += added_points;
    }
}
