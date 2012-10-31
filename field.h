#ifndef FIELD_H
#define FIELD_H

#include <QVector>

enum Cell
{
    CL_CLEAR=0,
    CL_X,
    CL_O
};

class Field
{
public:
    Field();
    void setField(int x, int y, Cell value);
    Cell getField(int x, int y);
    void clear();
private:
    QVector<Cell> field;
};

#endif // FIELD_H
