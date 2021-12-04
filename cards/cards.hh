#ifndef CARDS_HH
#define CARDS_HH

#include <iostream>

class Cards {

    public:
      // A dynamic structure must have a constructor
      // that initializes the top item as nullptr.
      Cards();

      // Adds a new card with the given id as the topmost element.
      void add(int id);

      // Prints the content of the data structure with ordinal numbers to the
      // output stream given as a parameter starting from the first element.
      void print_from_top_to_bottom(std::ostream& s);

      // Removes the topmost card and passes it in the reference parameter id to the caller.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool remove(int& id);

      // Moves the last element of the data structure as the first one.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool bottom_to_top();

      // Moves the first element of the data structure as the last one.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool top_to_bottom();

      // Prints the content of the data structure with ordinal numbers to the
      // output stream given as a parameter starting from the last element.
      void print_from_bottom_to_top(std::ostream& s);

      // A dynamic data structure must have a destructor
      // that can be called to deallocate memory,
      // when the data structure is not needed any more.
      ~Cards();

    private:
      struct Card_data
      {
        int id = 1;
        // edellinen kortti
        Card_data* prev = nullptr;
        // pinossa alaspäin, seuraava kortti
        Card_data* next = nullptr;
      };

      int size_ = 0;
      // ensimmäinen kortti, päälimmäisin
      Card_data* top_;
      Card_data* bottom_;

      // You can use the function below in the implementation of
      // the method print_from_bottom_to_top.
      int recursive_print(Card_data* top, std::ostream& s);

};

#endif // CARDS_HH
