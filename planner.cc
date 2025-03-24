/**
 * planner.cc
 * @author Ethan Knotts
 */

#include "planner.h"
#include <cctype>

using namespace std;

Planner::Planner() {
    head = nullptr;
    tail = nullptr;
}

Planner::~Planner() {
    while (head != nullptr) {
        node *tmp = head;
        head = head -> next();
        delete tmp;
    }
}

Planner::Planner(const Planner &other) {
    // Initialize new private data
    head = nullptr;
    tail = nullptr;

    node *tmp = other.head;

    // Loop through the other Planner and copy over all the data
    while (tmp != nullptr) {
        add(tmp -> data());
        tmp = tmp -> next();
    }
}

void Planner::add(Assignment assignment) {
    node *tmp = new node(assignment);

    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    } else {
        // Update tail
        tail -> set_next(tmp);
        tail = tmp;
        tail -> set_next(nullptr);

        // Sort the list
        sort();
    }
}

void Planner::find_all(DateTime dueBy) {
    node *tmp = head;

    // Loop through list
    while (tmp != nullptr) {
        // Print out data of element if it's due before the dueBy date
        if (tmp -> data().get_due() < dueBy) {
            cout << tmp -> data();
        }

        tmp = tmp -> next();
    }
}

unsigned Planner::waiting() {
    node *tmp = head;
    unsigned count = 0;
    
    while (tmp != nullptr) {
        count++;
        tmp = tmp -> next();
    }

    return count;
}

Assignment Planner::find(string name) {
    node *tmp = head;

    while (tmp != nullptr) {
        if (tmp -> data().get_name() == name) {
            return tmp -> data();
        } else {
            tmp = tmp -> next();
        }
    }

    return Assignment();
}

void Planner::remove(string name) {
    node *tmp = head;
    node *prev = nullptr;

    while (tmp != nullptr) {
        if (tmp -> data().get_name() == name) {
            if (prev == nullptr) {
                head = tmp -> next();
            } else {
                prev -> set_next(tmp -> next());
            }

            delete tmp;
            break;
        } else {
            prev = tmp;
            tmp = tmp -> next();
        }
    }
}

unsigned Planner::oldest() {
    node *tmp = head;
    unsigned oldest = 0;

    while (tmp != nullptr) {
        unsigned minutesWaiting = tmp -> data().minutes_waiting();

        // Updates oldest if it's been waiting longer
        if (minutesWaiting > oldest) {
            oldest = minutesWaiting;
        }

        tmp = tmp -> next();
    }

    return oldest;
}

unsigned Planner::newest() {
    node *tmp = head;

    unsigned newest = 0;

    // Sets newest to the first element, otherwise it'll always deafult to 0
    if (tmp != nullptr) {
        newest = tmp -> data().minutes_waiting();
    }

    while (tmp != nullptr) {
        unsigned minutesWaiting = tmp -> data().minutes_waiting();

        if (minutesWaiting < newest) {
            newest = minutesWaiting;
        }

        tmp = tmp -> next();
    }

    return newest;
}

void Planner::sort() {
    node *tmp = head;
    node *tmp2 = head;
    Assignment assignment;

    // Selection sort for linked list
    while (tmp != nullptr) {
        while (tmp2 != nullptr) {
            // If the current assigment has a further due date, swap them
            // Sorts from latest to earliest
            if (tmp2 -> data() > tmp -> data()) {
                assignment = tmp2 -> data();
                tmp2 -> set_data(tmp -> data());
                tmp -> set_data(assignment);
            }

            tmp2 = tmp2 -> next();
        }

        tmp = tmp -> next();
        tmp2 = head;
    }
}

void Planner::display(ostream &out) {
    node *tmp = head;

    while (tmp != nullptr) {
        out << tmp -> data();
        tmp = tmp -> next();
    }
}

unsigned Planner::average_wait() {
    node *tmp = head;
    unsigned count = 0;
    unsigned total = 0;

    // Get the total wait time and count of elements
    while (tmp != nullptr) {
        total += tmp -> data().minutes_waiting();
        count++;
        tmp = tmp -> next();
    }

    return total / count;
}

unsigned Planner::due_next() {
    if (head == nullptr) return 0;

    Assignment nextDueAssignment = head -> data();
    return nextDueAssignment.minutes_til_due();
}

void Planner::save(ostream &out) {
    node *tmp = head;

    while (tmp != nullptr) {
        out << tmp -> data();
        tmp = tmp -> next();
    }
}

void Planner::load(istream &in) {
    // Clear the existing list
    while (head != nullptr) {
        node *tmp = head;
        head = head -> next();
        delete tmp;
    }

    tail = nullptr;

    // Read in assignments until end of file
    while (true) {
        Assignment assignment;
        assignment.input(in);

        if (in.fail()) {
            break;
        }

        add(assignment);
    }

    sort();
}

Planner Planner::operator = (const Planner &other) {
    // Check for equality edge case
    if (this == &other) return *this;

    // Initialize new private data
    head = nullptr;
    tail = nullptr;

    node *tmp = other.head;

    // Loop through the list and add all elements
    while (tmp != nullptr) {
        add(tmp -> data());
        tmp = tmp -> next();
    }

    return *this;
}
