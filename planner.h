/**
 * planner.h
 * @author Ethan Knotts
 */

#include "node.h"
#include "assignment.h"
#include "date_time.h"
#include <iostream>
#include <fstream>

template <class T>
class Planner {
    public:
        /**
         * Planner
         * @brief Default constructor, sets head and tail to null
         */
        Planner();

        // Big 3
        /**
         * ~Planner
         * @brief Destructor, makes sure dynamic memory is deallocated properly.
         */
        ~Planner();

        /**
         * Planner
         * @brief Copy constructor, copies all data from other Planner
         * @param other Planner to copy from
         */
        Planner(const Planner &other);

        /**
         * operator =
         * @brief Assignment operator, copies all data from other Planner
         * @param other Planner to copy from
         * @return Planner with copied data
         */
        Planner operator = (const Planner &other);

        /**
         * add
         * @brief Adds an assignment to the list
         * @param assignment Assignment to add
         */
        void add(Assignment assignment);

        /**
         * sort
         * @brief Sorts the list by due date
         */
        void sort();

        /**
         * display
         * @brief Displays all assignments in the list
         * @param out Output stream to display to
         */
        void display(std::ostream &out);

        /**
         * waiting
         * @brief Returns the number of assignments waiting
         * @return Number of assignments waiting
         */
        unsigned waiting();

        /**
         * find
         * @brief Finds an assignment by name
         * @param name Name of assignment to find
         * @return Assignment with the name, or default Assignment
         */
        Assignment find(std::string name);

        /**
         * due_next
         * @brief Returns the time until the next assignment is due
         * @return Time until next assignment is due
         */
        unsigned due_next();

        /**
         * average_wait
         * @brief Returns the average wait time of all assignments
         * @return Average wait time of all assignments in minutes
         */
        unsigned average_wait();

        /**
         * oldest
         * @brief Returns the time since the oldest assignment was added
         * @return Time since oldest assignment was added
         */
        unsigned oldest();

        /**
         * newest
         * @brief Returns the time since the newest assignment was added
         * @return Time since newest assignment was added
         */
        unsigned newest();

        /**
         * find_all
         * @brief Finds all assignments due by a certain date and prints them to cout
         * @param dueBy Date to find assignments due by
         */
        void find_all(DateTime dueBy);

        /**
         * remove
         * @brief Removes an assignment by name
         * @param name Name of assignment to remove
         */
        void remove(std::string name);

        /**
         * save
         * @brief Saves the planner to a file
         * @param out Output stream to save to
         */
        void save(std::ostream &out);

        /**
         * load
         * @brief Loads the planner from a file
         * @param in Input stream to load from
         */
        void load(std::istream &in);

        /**
         * reverse_display
         * @brief Prints the all assignments in the list in reverse order
         * @param out Output stream to display to
         */
        void reverse_display(std::ostream &out);
    private:
        node *head;
        node *tail;
};