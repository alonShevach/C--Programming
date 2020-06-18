#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H

#define BASE_TRIANGLE_SIZE 2
#define BASE_CARPET_SIZE 3
#define BASE_VICSEK_SIZE 3
#define SPACE ' '
#define DRAW_SIGN '#'

#include <iostream>

/**
 * The fractal abstract class
 */
class Fractal
{
protected:

    int _dim;
    int _size;

    /**
    * The constructor of the class
    * @param dim the fractal's dimension
    */
    explicit Fractal(int dim);

    /**
     * A method that checks whether it should be # or " " in the given coordinate
     * @param xA the x axis
     * @param yA the y axis
     * @return true for printing #, false otherwise.
     */
    virtual bool toDraw(int xA, int yA) const = 0;

public:

    /**
     * The function that prints the Fractal on the screen.
     */
    void draw() const;

    /**
     * default destructor.
     */
    virtual ~Fractal() = default;
};

/**
 * the Sierpinski Carpet class, extending Fractal
 */
class SierpinskiCarpet: public Fractal
{
protected:

    /**
     * A method that checks whether it should be # or " " in the given coordinate, overriding the fractal method.
     * @param xA the x axis
     * @param yA the y axis
     * @return true for printing #, false otherwise.
     */
    bool toDraw(int xA, int yA) const override;

public:

    /**
     * the class's constructor
     * @param size the fractal's size.
     */
    explicit SierpinskiCarpet(int size);

};

/**
 * the SierpinskiTriangle class, extending Fractal
 */
class SierpinskiTriangle: public Fractal
{
protected:

    /**
     * A method that checks whether it should be # or " " in the given coordinate, overriding the fractal method.
     * @param xA the x axis
     * @param yA the y axis
     * @return true for printing #, false otherwise.
     */
    bool toDraw(int xA, int yA) const override;


public:

    /**
     * the class's constructor
     * @param size the fractal's size.
     */
    explicit SierpinskiTriangle(int size);

};

/**
 * the Vicsek class, extending Fractal
 */
class Vicsek: public Fractal
{
protected:

    /**
     * A method that checks whether it should be # or " " in the given coordinate, overriding the fractal method.
     * @param xA the x axis
     * @param yA the y axis
     * @return true for printing #, false otherwise.
     */
    bool toDraw(int xA, int yA) const override;

public:

    /**
     * the class's constructor
     * @param size the fractal's size.
     */
    explicit Vicsek(int size);

};

#endif //CPP_EX2_FRACTAL_H
