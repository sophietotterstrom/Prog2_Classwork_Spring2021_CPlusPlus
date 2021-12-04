#ifndef DATE_HH
#define DATE_HH


class Date
{
public:
    // Default constructor.
    // Uses the default value 1 for day, month, and year.
    Date();

    // Constructor.
    // If any of the given parameter is out of sensible limits
    // default value 1 used instead.
    Date(unsigned int day, unsigned int month, unsigned int year);

    // Destructor
    ~Date();

    // Advances the date with given amount of days.
    // Can't be anvanced by negative amounts.
    void advance(unsigned int days);

    // Prints the date (dd.mm.yyyy).
    void print() const;

private:
    unsigned int day_;
    unsigned int month_;
    unsigned int year_;

    // Returns true if the year of the date is a leap year,
    // otherwise returns false.
    bool is_leap_year() const;
};

#endif // DATE_HH
