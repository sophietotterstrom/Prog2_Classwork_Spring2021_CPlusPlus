#include "stop.hh"

Stop::Stop(string stop_name,
           float distance_from_start_of_line):
    stop_name_(stop_name),
    distance_from_start_of_line_(distance_from_start_of_line)
{}

// Simple getter methods.

string Stop::get_stop()
{
    return stop_name_;
}

float Stop::get_distance()
{
    return distance_from_start_of_line_;
}
