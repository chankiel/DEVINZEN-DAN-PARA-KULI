#ifndef PEMAIN_HPP
#define PEMAIN_HPP

#include <iostream>
#include <vector>
#include "matrixarea.hpp"
using namespace std;

template <class T>
class Pemain
{
protected:
    MatrixArea<T> inventory;

public:
    Pemain();
    Pemain(int rows, int cols); // : MatrixArea(rows, cols)
    Pemain(const Pemain &);
    ~Pemain();

    // specifics
    cetakPenyimpanan();
    makan(int, int);          // loc item yg dimakan
    beli(int, int, int, int); // loc item yang dibeli, loc item akan disimpan
    jual(int, int);           // loc item yg akan dijual
};

#endif