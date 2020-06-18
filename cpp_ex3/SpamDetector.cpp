#include <fstream>
#include <iostream>
#include <algorithm>
#include "HashMap.hpp"

#define PSIK ','
#define MIN_DIGIT '0'
#define MAX_DIGIT '9'
#define ERR_INVALID_NUM_OF_ARGS "Usage: SpamDetector <database path> <message path> <threshold>"
#define ERR_INVALID_INPUT "Invalid input"
#define SPAM "SPAM"
#define NOT_SPAM "NOT_SPAM"
#define FUNC_FAIL -1
#define START 0
#define DATA_FILE_IND 1
#define MESSAGE_FILE_IND 2
#define THRESHOLD_IND 3
#define NUM_OF_ARGS 4

/**
 * Checks if the given string represents an int, if so returns it as an int, -1 if not.
 * @param str the string to change to int.
 * @return the int represents the str, -1 upon failure
 */
int strToInt(const std::string &str)
{
    for (const char &letter : str)
    {
        if (MIN_DIGIT <= letter && letter <= MAX_DIGIT)
        {
            continue;
        }
        return FUNC_FAIL;
    }
    return std::stoi(str);
}

/**
 * this function gets a string and changes it to lower case letters.
 * @param str the string to change to lower case
 * @return the string in lower case.
 */
std::string getLower(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
    {
        return std::tolower(c);
    });
    return str;
}


/**
 * updates the score of the file according to its lines.
 * @param path the second file path.
 * @param hashMap the hashmap that has the values and expressions of the file.
 * @param score the score of the given file, which later used to check if it is spam or not.
 * @return true upon success, false otherwise
 */
bool updateScore(const std::string &path, HashMap<std::string, int> &hashMap, int &score)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        return false;
    }
    if (f.peek() != EOF)
    {
        std::string exp;
        std::string msg;
        std::string line;
        while (std::getline(f, line))
        {
            exp = getLower(line);
            msg += exp;
        }
        for (const std::pair<std::string, int> &pair : hashMap)
        {
            size_t i = msg.find(pair.first);
            while (i != std::string::npos)
            {
                score += pair.second;
                i = msg.find(pair.first, i + 1);
            }
        }
    }
    f.close();
    return true;
}

/**
 * this function checks the file and makes a Hashmap accordingly.
 * @param path the data file path
 * @param hashMap The HashMap that has the values of the file
 * @return true upon success, false otherwise.
 */
bool makeHashMap(const std::string &path, HashMap<std::string, int> &hashMap)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        return false;
    }
    if (f.peek() != EOF)
    {
        unsigned long index;
        std::vector<int> values;
        std::vector<std::string> keys;
        std::string exp;
        std::string val;
        std::string line;
        while (std::getline(f, line))
        {
            index = line.find(PSIK);
            if (index == line.length() - 1)
            {
                f.close();
                return false;
            }
            else
            {
                exp = line.substr(START, index);
                val = line.substr(index + 1, line.length());
                int valInt = strToInt(val);
                if (valInt < 0)
                {
                    f.close();
                    return false;
                }
                exp = getLower(exp);
                try
                {
                    keys.push_back(exp);
                    values.push_back(valInt);
                }
                catch (const std::bad_alloc &e)
                {
                    f.close();
                    throw;
                }
                try
                {
                    hashMap = HashMap<std::string, int>(keys, values);
                }
                catch (const std::length_error &e)
                {
                    throw;
                }
            }
        }
    }
    f.close();
    return true;
}

/**
 * The main function of the program, this function creates a hash table, calculates the score of the second file
 * and checks if it is a spam according to the threshold.
 * @param argc the number of arguments
 * @param argv two file's paths and 1 int, the threshold
 * @return 0 upon success, 1 otherwise
 */
int main(int argc, char *argv[])
{
    if (argc == NUM_OF_ARGS)
    {
        try
        {
            HashMap<std::string, int> newHash = HashMap<std::string, int>();
            bool isSuccess;
            isSuccess = makeHashMap(argv[DATA_FILE_IND], newHash);
            if (!isSuccess)
            {
                std::cerr << ERR_INVALID_INPUT << std::endl;
                return EXIT_FAILURE;
            }
            int score = 0;
            isSuccess = updateScore(argv[MESSAGE_FILE_IND], newHash, score);
            if (!isSuccess)
            {
                std::cerr << ERR_INVALID_INPUT << std::endl;
                return EXIT_FAILURE;
            }
            int threshold = strToInt(argv[THRESHOLD_IND]);
            if (threshold <= 0)
            {
                std::cerr << ERR_INVALID_INPUT << std::endl;
                return EXIT_FAILURE;
            }
            if (threshold > score)
            {
                std::cout << NOT_SPAM << std::endl;
            }
            else
            {
                std::cout << SPAM << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    std::cerr << ERR_INVALID_NUM_OF_ARGS << std::endl;
    return EXIT_FAILURE;
}