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

// void Planner::remove()

void Planner::sort() {
    node *tmp = head;
    node *tmp2 = head;
    Assignment assignment;

    // Selection sort for linked list
    while (tmp != nullptr) {
        while (tmp2 != nullptr) {
            if (tmp2 -> data() < tmp -> data()) {
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

void Planner::save(ostream &out) {
    node *tmp = head;

    while (tmp != nullptr) {
        out << tmp->data(); // Uses overloaded << operator of Assignment
        tmp = tmp->next();
    }
}

void Planner::load(istream &in) {
    // Clear the existing list
    while (head != nullptr) {
        node *tmp = head;
        head = head->next();
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
