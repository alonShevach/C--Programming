#include <cmath>
#include <iostream>
#include "Fractal.h"

/**
* The constructor of the class
* @param dim the fractal's dimension
*/
Fractal:: Fractal(int dim)
: _dim(dim), _size(0)
{
}

/**
 * The function that prints the Fractal on the screen.
 */
void Fractal::draw() const
{
    int size = (int)pow(this->_size, this->_dim);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (!this->toDraw(i, j))
            {
                std::cout << SPACE;
            }
            else
            {
                std::cout << DRAW_SIGN;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
 * the class's constructor
 * @param size the fractal's size.
 */
SierpinskiCarpet:: SierpinskiCarpet(int size)
: Fractal(size)
{
    _size = BASE_CARPET_SIZE;
}

/**
 * A method that checks whether it should be # or " " in the given coordinate, overriding the fractal method.
 * @param xA the x axis
 * @param yA the y axis
 * @return true for printing #, false otherwise.
 */
bool SierpinskiCarpet:: toDraw(int xA, int yA) const
{
    while (yA != 0 || xA != 0)
    {
        if (yA % _size != 1 || xA % _size != 1)
        {
            xA /= _size;
            yA /= _size;
        }
        else
        {
            return false;
        }
    }
    return true;
}

/**
 * the class's constructor
 * @param size the fractal's size.
 */
SierpinskiTriangle:: SierpinskiTriangle(int size)
: Fractal(size)
{
    _size = BASE_TRIANGLE_SIZE;
}

/**
 * A method that checks whether it should be # or " " in the given coordinate, overriding the fractal method.
 * @param xA the x axis
 * @param yA the y axis
 * @return true for printing #, false otherwise.
 */
bool SierpinskiTriangle:: toDraw(int xA, int yA) const
{
    while (yA != 0 || xA != 0)
    {
        if (yA % _size != 1 || xA % _size != 1)
        {
            xA /= _size;
            yA /= _size;
        }
        else
        {
            return false;
        }
    }
    return true;
}

/**
 * the class's constructor
 * @param size the fractal's size.
 */
Vicsek:: Vicsek(int size)
: Fractal(size)
{
    _size = BASE_VICSEK_SIZE;
}

/**
 * A method that checks whether it should be # or " " in the given coordinate, overriding the fractal method.
 * @param xA the x axis
 * @param yA the y axis
 * @return true for printing #, false otherwise.
 */
bool Vicsek:: toDraw(int xA, int yA) const
{
    while (yA != 0 || xA != 0)
    {
        if (yA % _size == 1 || xA % _size == 1)
        {
            if (xA - 1 < 0 || yA - 1 < 0 || xA + 1 > pow(3, _dim) || yA + 1 > pow(3, _dim))
            {
                return false;
            }
            if (!(toDraw(xA - 1, yA - 1)))
            {
                return false;
            }
        }
        xA /= _size;
        yA /= _size;
    }
    return true;
}