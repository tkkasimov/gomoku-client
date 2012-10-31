#include "field.h"

Field::Field()
{
    clear();
}

void Field::setField(int x, int y, Cell value)
{
    const int i = x+y*15;
    field[i] = value;
}

Cell Field::getField(int x, int y)
{
    const int i = x+y*15;
    return field.at(i);
}

void Field::clear()
{
    field.fill(CL_CLEAR, 225);
}
