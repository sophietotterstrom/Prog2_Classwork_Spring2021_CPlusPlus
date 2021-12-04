#include "date.hh"
#include <iostream>

unsigned int const month_sizes[12] = { 31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31 };

Date::Date():
    day_(1), month_(1), year_(1)
{
}

Date::Date(unsigned int day, unsigned int month, unsigned int year):
    day_(day), month_(month), year_(year)
{
    if( month_ > 12 || month_ < 1 )
    {
        month_ = 1;
    }
    if ( day_ > month_sizes[month_ - 1]
         || ( month_ == 2 && is_leap_year()
             && day > month_sizes[month - 1] + 1 ) )
    {
        day_ = 1;
    }
}

Date::~Date()
{
}

void Date::advance(unsigned int days)
{
    day_ += days;
    while ( day_ > month_sizes[month_ - 1] )
    {
        if ( month_ == 2 && day_ == 29 )
        {
            return;
        }
        day_ -= month_sizes[month_ - 1];
        if ( month_ == 2 && is_leap_year() )
        {
            --day_;
        }
        ++month_;

        if ( month_ > 12 )
        {
            month_ -= 12;
            ++year_;
        }
    }
}

void Date::print() const
{
    if(day_ < 10)
    {
        std::cout << "0";
    }
    std::cout << day_ << ".";
    if(month_ < 10)
    {
        std::cout << "0";
    }
    std::cout << month_ << ".";
    if(year_ < 10)
    {
        std::cout << "0";
    }
    std::cout << year_ << std::endl;
}

bool Date::is_leap_year() const
{
    return (year_ % 4 == 0) && (!(year_ % 100 == 0) || (year_ % 400 == 0));
}
