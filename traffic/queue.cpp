#include "queue.hh"
#include <iostream>

using namespace std;

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle) :
    first_(nullptr),
    last_(nullptr),
    is_green_(false),
    cycle_(cycle)
{
}

// Destructor that deletes all the remaining vehicles from the queue.
Queue::~Queue()
{
    Vehicle* current = first_;
    while (current)
    {
        Vehicle* removable = current;
        current = current->next;
        delete removable;
    }
}

// Inserts a vehicle, the register number of which is reg, to the queue.
void Queue::enqueue(string register_number)
{
    Vehicle* new_car_in_queue = new Vehicle;
    new_car_in_queue->reg_num = register_number;
    new_car_in_queue->next = nullptr;

    if (is_green_)
    {
        cout << "GREEN: The vehicle "
             << new_car_in_queue->reg_num
             << " need not stop to wait" << endl;
    }
    else
    {

        if (first_ == nullptr) //this is an empty queue
        {
            first_ = new_car_in_queue;
            return;
        }

        if (first_->next == nullptr) // que only has one element
        {
            first_->next = new_car_in_queue;
            return;
        }

        Vehicle* current = first_;
        while (current and current->next)
        {
            current = current->next;
        }
        current->next = new_car_in_queue;
    }
}

// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
void Queue::switch_light()
{
    string text = "";
    if (is_green_) {
        is_green_ = false;
        text = "RED";
    } else if (not is_green_) {
        is_green_ = true;
        text = "GREEN";
    }

    // CASE : no cars in line
    if (first_ == nullptr)
    {
        cout << text << ": No vehicles waiting in traffic lights" << endl;
    }

    // CASE : cars in line
    else if (is_green_)
    {
        cout << "GREEN" << ": Vehicle(s) ";
        for (int index = 0; index < (int)cycle_; index++)
        {
            if (first_ and first_->next)
            {
                cout << first_->reg_num << " ";
                first_ = first_->next;
            }
            else if (first_)
            {
                cout << first_->reg_num << " ";
                first_ = nullptr;
            }

        }
        cout << "can go on" << endl;
        is_green_ = false;
    }


}

// Resets the attribute cycle_.
void Queue::reset_cycle(unsigned int new_cycle)
{
    cycle_ = new_cycle;

}

// Prints the color of traffic light and the register numbers of those
// cars that are waiting in the traffic light queue (if any).
void Queue::print()
{
    string text = "";
    if (is_green_) {
        text = "GREEN";
    } else if (not is_green_){
        text = "RED";
    }

    if (first_ == nullptr)
    {
        cout << text << ": No vehicles waiting in traffic lights" << endl;
    }
    else
    {
        cout << text << ": Vehicle(s) ";

        Vehicle* current = first_;
        while (current)
        {
            cout << current->reg_num << " ";
            current = current->next;
        }

        cout << "waiting in traffic lights" << endl;
    }
}
