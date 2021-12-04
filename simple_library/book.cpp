#include "book.hh"
#include <iostream>
using namespace std;

Book::Book(string author, string title):
    title_(title), author_(author)
{
    loaned_status_ = false;
}

void Book::print()
{
    // The information about a book can be printed in the form: author : title.
    // If the book is not loaned, the printing method prints the text available.
    // If the book is loaned, the printing method prints the dates when the book
    // has been loaned and when it should be returned. More precise printing form
    // can be seen in the example below.

    cout << this->author_ << " : " << this->title_ << endl;

    if (loaned_status_ == false) {
        cout << "- available" << endl;
    } else {

        cout << "- loaned: ";
        this->loaning_date_.print();
        cout << "- to be returned: ";
        this->return_date_.print();
    }
}

void Book::loan(Date loaning_date)
{
    if (loaned_status_ == true) {
        cout << "Already loaned: cannot be loaned" << endl;
    } else {
        loaned_status_ = true;

        loaning_date_ = loaning_date;

        loaning_date.advance(28);
        return_date_ = loaning_date;
    }
}

void Book::renew()
{
    if (loaned_status_ == false) {
        cout << "Not loaned: cannot be renewed" << endl;
    } else {
        return_date_.advance(28);
    }
}

void Book::give_back()
{
    loaned_status_ = false;

}
