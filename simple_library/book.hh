#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include <date.hh>
using namespace std;


class Book
{
public:
    Book(string author, string title);

    void print();

    void loan(Date loaning_date);

    void renew();

    void give_back();

private:

    string title_;
    string author_;
    bool loaned_status_;

    Date loaning_date_;
    Date return_date_;

};

#endif // BOOK_HH
