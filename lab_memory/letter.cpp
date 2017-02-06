/**
 * @file letter.cpp
 */

#include "letter.h"

Letter::Letter() : letter('-'), count(0)
{
}
void Letter::addStudent(const string & name)
{
    count++;
}

bool Letter::operator<(const Letter& other) const
{
    return count > other.count;
}
