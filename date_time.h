/*************************************************************************
   I found that I wanted a class that would do both time and date,
   and so I have created this by merging the date class that I have been 
   using for many years with the MyTime class I have been using for many 
   years. I have merged the classes into a single file so that they 
   can be used as a single unit by the application programmer.

	John Dolan		    Spring 2021     Ohio University EECS
    Updated: Patricia Lindner    Feburary 2025
*************************************************************************/

#include <iostream>
#include <ctype.h>

#ifndef DATE
#define DATE
// an exception if the date entered is invalid for the month
class bad_day{
    public:
        bad_day() {monthnum = daynum = 0;}
        bad_day(int m, int d) {monthnum = m, daynum=d;}
        void msg() {std::cerr << monthnum << " has no day " << daynum << std::endl;}
    private:
        int monthnum, daynum;
};

// an exception for an invalid month number
class bad_month{
    public:
        bad_month() {monthnum = 0;}
        bad_month(int m) {monthnum = m;}
        void msg() {std::cerr << monthnum << " is an invalid month number.\n";}
    private:
        int monthnum;
};

// a simple class for holding dates
class Date{
    public:
        /**
         * @brief Construct a new Date object with default values
         * 
         */
        Date();

        /**
         * @brief Construct a new Date object with user given values
         * 
         * @param d - day 
         * @param m - month 
         * @param y - year
         */
        Date(int d, int m, int y);

        /**
         * @brief Output operator for Date objects
         * 
         * @param outs - stream to write to
         * @param d - Date to write
         * @return std::ostream& - return the stream you were writing to
         */
        friend std::ostream& operator <<(std::ostream& outs, Date d);

        /**
         * @brief Input operator for Date objects
         * 
         * @param ins - stream to read data from
         * @param d - Date object to store data in
         * @return std::istream& - return the stream you were reading from
         */
        friend std::istream& operator >>(std::istream& ins, Date& d);

        // COMPARISON OPERATORS
        /**
         * @brief Greater than comparison operator for Dates
         * 
         * @param d2 - Date object on the right hand side of the operator
         * @return true - d2 is further in the past 
         * @return false - d2 is the same Date or more recent
         */
        bool operator > (const Date& d2)const;

        /**
         * @brief Less than comparison operator for Dates
         * 
         * @param d2 - Date object on the right hand side of the operator
         * @return true - d2 is more recent 
         * @return false - d2 is the same Date or further in the past
         */
        bool operator < (const Date& d2)const;

        /**
         * @brief Equality comparison operator for Dates
         * 
         * @param d2 - Date object on the right hand side of the operator
         * @return true - d2 is the same Date 
         * @return false - d2 is not the same Date
         */
        bool operator == (const Date& d2)const;

        /**
         * @brief Inequality comparison operator for Dates
         * 
         * @param d2 - Date object on the right hand side of the operator
         * @return true - d2 is not the same Date 
         * @return false - d2 is the same Date
         */
        bool operator != (const Date& d2)const;

        /**
         * @brief Less than or equal to comparison operator for Dates
         * 
         * @param d2 - Date object on the right hand side of the operator
         * @return true - d2 is the same Date or more recent 
         * @return false - d2 is further in the past
         */
        bool operator <= (const Date& d2)const;

        /**
         * @brief Greater than or equal to comparison operator for Dates
         * 
         * @param d2 - Date object on the right hand side of the operator
         * @return true - d2 is the same Date or further in the past 
         * @return false - d2 is more recent
         */
        bool operator >= (const Date& d2)const;
	
        /**
         * @brief Returns the age in years of this date with relationship to today
         * 
         * @param tday - a date object with today's date
         * @return int - the number of years old this Date is
         */
        int age(const Date& tday)const;

        /**
         * @brief Set the values of member variables so the object has today's date
         * 
         */
        void make_today();
        
        /**
         * @brief Return how many minutes this date is since 1/1/1970
         *        This function is useful when trying to determine how long it has been between 2 dates
         * 
         * @return unsigned - number of minutes this date is since 1970
         */
        unsigned minutes_since_1970()const;

    private:
        int day;
        int month;
        int year;
        int daysallowed[13];
};

// A class that holds both a date and a time
class DateTime{
    public:
        /**
         * @brief Construct a new Date Time object with default values
         * 
         */
      	DateTime();

        /**
         * @brief Less than comparison operator for DateTime objects
         * 
         * @param other - DateTime object on the right hand side of the operator
         * @return true - other is more recent 
         * @return false - other is the same date and time or further in the past
         */
	    bool operator < (const DateTime& other)const;

        /**
         * @brief Greater than comparison operator for DateTime objects
         * 
         * @param other - DateTime object on the right hand side of the operator
         * @return true - other is further in the past 
         * @return false - other is the same date and time or more recent
         */
        bool operator > (const DateTime& other)const;

        /**
         * @brief Equality comparison operator for DateTime objects
         * 
         * @param other - DateTime object on the right hand side of the operator
         * @return true - the objects have the same date and time
         * @return false - the objects do not have the same date and time
         */
        bool operator == (const DateTime& other)const;

        /**
         * @brief Inequality comparison operator for DateTime objects
         * 
         * @param other - DateTime object on the right hand side of the operator
         * @return true - the objects do not have the same date and time
         * @return false - the objects have the same date and time
         */
        bool operator != (const DateTime& other)const;

        /**
         * @brief Read in the data for a DateTime object
         * 
         * @param ins - stream to read data from
         */
        void input(std::istream& ins);

        /**
         * @brief Output data from a DateTime object
         * 
         * @param outs - stream to write data to
         */
	    void output(std::ostream& outs)const;

        /**
         * @brief Return how many minutes this date is since 1/1/1970
         *        This function is useful when trying to determine how long it has been between 2 DateTime objects
         * 
         * @return unsigned - number of minutes this date and time is since 1970
         */
        unsigned minutes_since_1970()const;

        /**
         * @brief Set the attributes of this object for today's date and the time when the function was called
         * 
         */
        void make_now();

    private:
        Date datepart;
        int hour, minute;
};

#endif