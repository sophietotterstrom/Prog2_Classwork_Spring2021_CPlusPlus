/* Class represents a Stop with private attributes "name" and "distance".
 * Also includes public getter-methods to return attributes.
 *
 * Could have been modeled as a struct in the main
 * as methods don't do that much, but I chose to use
 * a class incase I needed to make more complex methods.
 */

#ifndef STOP_HH
#define STOP_HH

#include <string>

using namespace std;

class Stop
{
public:
    Stop(string stop_name, float distance_from_start_of_line);
    string get_stop();
    float get_distance();

private:
    string stop_name_;
    float distance_from_start_of_line_;

};

#endif // STOP_HH
