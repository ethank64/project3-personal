#include "node.h"
#include "assignment.h"
#include "date_time.h"
#include <iostream>
#include <fstream>

class Planner {
    public:
        // Big 3
        Planner();
        ~Planner();
        Planner(const Planner &other);

        void add(Assignment assignment);
        void sort();
        void display(std::ostream &out);
        unsigned waiting();
        Assignment find(std::string name);
        unsigned due_next();
        unsigned average_wait();
        unsigned oldest();
        unsigned newest();
        void find_all(DateTime dueBy);
        void remove(std::string name);
        void save(std::ostream &out);
        void load(std::istream &in);
    private:
        node *head;
        node *tail;
};

std::ostream operator << (std::ostream &out, Planner &planner);