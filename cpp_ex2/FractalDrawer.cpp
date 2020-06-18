#include <vector>
#include "Fractal.h"
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>

#define BAD_NUM_OF_ARGS "Usage: FractalDrawer <file path>"
#define INVALID_INPUT "Invalid input"
#define BAD_MEMORY_ALLOCATION "Memory allocation failed"
#define NUM_OF_ARGS 2
#define MAX_FRAC_DIM 6
#define MIN_FRAC_DIM 1
#define CARPET_NUM 1
#define TRIANGLE_NUM 2
#define VICSEK_NUM 3
#define SEPERETOR ","
#define FILE_ENDING ".csv"

/**
 * A factory function that creates the currect fractal according to the given type and size
 * @param type the int representing the fractal type.
 * @param size the size of the fractal.
 * @return a fractal pointer.
 */
Fractal* fractalFactory(int type, int size)
{
    switch(type)
    {
        case CARPET_NUM:
            return new SierpinskiCarpet(size);
        case TRIANGLE_NUM:
            return new SierpinskiTriangle(size);
        case VICSEK_NUM:
            return new Vicsek(size);
        default:
            return new SierpinskiCarpet(size);
    }
}

/**
 * A function that deletes the memory allocations to vector.
 * @param vec a vector to delete.
 */
void vectorDelete(std::vector<Fractal*> & vec)
{
    for (int i = 0; i < (int)vec.size(); i++)
    {
        delete vec[i];
    }
}

/**
 * a function that reads from the filestream and adds to the vector the valid fractals
 * @param fileStream a filestream.
 * @param vec the vector to add to.
 * @return true upon success, false otherwise.
 */
bool fillVector(boost::filesystem::ifstream &fileStream, std::vector<Fractal *> &vec)
{
    int type, size, counter;
    std::string currLine;
    while (std::getline(fileStream, currLine))
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        boost::char_separator<char> sep{SEPERETOR, "", boost::keep_empty_tokens};
        tokenizer tok(currLine, sep);
        counter = 0;
        type = 0;
        size = 0;
        for (tokenizer::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter)
        {
            if (*tok_iter < "0" || *tok_iter > "9" || (*tok_iter).size() > 1)
            {
                vectorDelete(vec);
                fileStream.close();
                std:: cerr << INVALID_INPUT << std::endl;
                return false;
            }
            if (counter == 0)
            {
                type = std::stoi(*tok_iter);
            }
            else if(counter == 1)
            {
                size = std::stoi(*tok_iter);
            }
            else
            {
                vectorDelete(vec);
                fileStream.close();
                std:: cerr << INVALID_INPUT << std::endl;
                return false;
            }
            ++counter;
        }
        if (size < MIN_FRAC_DIM || size > MAX_FRAC_DIM || type < CARPET_NUM || type > VICSEK_NUM)
        {
            vectorDelete(vec);
            fileStream.close();
            std:: cerr << INVALID_INPUT << std::endl;
            return false;
        }
        try
        {
            vec.push_back(fractalFactory(type, size));
        }
        catch (std::bad_alloc& e)
        {
            vectorDelete(vec);
            fileStream.close();
            std::cerr << BAD_MEMORY_ALLOCATION << std::endl;
            return false;
        }
    }
    return true;
}

/**
 * The main function of the project, this function checks if the given file is valid, if not it returns 1.
 * this function is also incharge on reading from the file, creating the fractals and drawing them.
 * @param argc the length of the paramaters.
 * @param argv the user's input
 * @return 0 upon success, 1 otherwise.
 */
int main(int argc, char* argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        std:: cerr << BAD_NUM_OF_ARGS << std::endl;
        return EXIT_FAILURE;
    }

    boost::filesystem::ifstream fileStream(argv[1]);
    std::string extension = boost::filesystem::extension(argv[1]);
    if (extension != FILE_ENDING || !fileStream.is_open())
    {
        std:: cerr << INVALID_INPUT << std::endl;
        return EXIT_FAILURE;
    }
    if (fileStream.peek() != EOF)
    {
        std::vector<Fractal *> vec;
        bool exit_type = fillVector(fileStream, vec);
        if (!exit_type)
        {
            return EXIT_FAILURE;
        }
        for (int i = (int) vec.size() - 1; i >= 0; --i)
        {
            vec[i]->draw();
            delete vec[i];
        }
    }
    fileStream.close();
    return EXIT_SUCCESS;
}


