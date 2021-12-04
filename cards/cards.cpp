#include "cards.hh"

using namespace std;

// TODO: Implement the methods here

Cards::Cards() :
    size_(0),
    top_(nullptr),
    bottom_(nullptr)
{

}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data;
    new_card->id = id;
    new_card->next = top_;

    if (size_ > 0)
    {
        top_->prev = new_card;
    }

    top_ = new_card;

    ++size_;

    if (size_ == 1)
    {
        bottom_ = top_;
    }
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    int i = 1;
    Card_data* current = top_;

    while (current != nullptr)
    {
        s << i << ": " << current->id << endl;
        ++i;
        current = current->next;
    }
}

bool Cards::remove(int &id)
{
    if (size_ == 0)
    {
        return false;
    }

    id = top_->id;
    Card_data* second = top_->next;

    delete top_;
    top_ = second;

    if (top_ != nullptr)
    {
        top_->prev = nullptr;
    }

    --size_;

    if (size_ == 0)
    {
        bottom_ = nullptr;
    }

    // palauttaa true, kun jotain poistettiin
    return true;
}

bool Cards::bottom_to_top()
{
    if (size_ <= 1)
    {
        return false;
    }

    Card_data* old_top = top_;
    Card_data* old_bottom = bottom_;

    bottom_ = old_bottom->prev;

    old_bottom->prev->next = nullptr;
    old_bottom->next = old_top;
    old_bottom->prev = nullptr;

    old_top->prev = old_bottom;

    top_ = old_bottom;

    /*
    old_bottom->next = old_top;
    top_ = old_bottom;
    bottom_ = new_bottom;
    new_bottom->next = nullptr;

    */

    return true;
}

bool Cards::top_to_bottom()
{
    if (size_ <= 1)
    {
        return false;
    }

    Card_data* old_top = top_;
    Card_data* old_bottom = bottom_;

    top_ = old_top->next;

    old_top->prev = old_bottom;
    old_top->next->prev = nullptr;
    old_top->next = nullptr;

    old_bottom->next = old_top;

    bottom_ = old_top;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    int i = 1;
    Card_data* current = bottom_;
    while (current != nullptr)
    {
        s << i << ": " << current->id << endl;
        ++i;
        current = current->prev;
    }
}

Cards::~Cards()
{
    Card_data* current = top_;
    while (current != nullptr)
    {
        Card_data* temporary = current->next;
        delete current;
        current = temporary;
    }
}

