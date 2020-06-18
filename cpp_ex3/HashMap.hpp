#include <vector>
#include <iostream>
#include <stdexcept>
#include <new>

#define BASE_SIZE 0
#define LOW_BOUND 0.25
#define HIGH_BOUND 0.75
#define RESIZE_MULTIPLIER 2
#define BASE_CAPACITY 16
#define ERR_KEY_NOT_IN_MAP "This key is not in the map"
#define ERR_NO_MAP "Bad map"
#define ERR_INVALID_LOAD_FACTORS "Bad load factor"
#define ERR_DIFF_VECS_SIZE "Bad size of insertion, vectors with different sizes."

/**
 * The HashMap class, represents a HashMap.
 * this class is generic.
 * @tparam keyT the key type.
 * @tparam valueT the value type.
 */
template<class keyT, class valueT>
class HashMap
{

private:
    using pair = std::pair<keyT, valueT>;
    using bucket = std::vector<pair>;

    int _capacity;
    int _size;
    double _lowBound;
    double _highBound;
    bucket *_table;

    /**
     * gets a size as an argument, and changes the table's size accordingly
     * @param size the new size for the table
     */
    void _changeSize(int size);

    /**
     * grows the table in case of growing beyond the upper bound
     */
    void _reHashUp();

    /**
     * Makes the table smaller in case of getting beneath the lowe bound.
     */
    void _reHashDown();

    /**
     * returns the address of a given key.
     * @param key the key number representation.
     * @return the address that the key corresponds to
     */
    int _getAddress(keyT key) const noexcept;

public:

    /**
     * A default constructor
     */
    HashMap() : _capacity(BASE_CAPACITY), _size(BASE_SIZE), _lowBound(LOW_BOUND), _highBound(HIGH_BOUND),
            _table(new bucket[BASE_CAPACITY])
    {
    }

    /**
     * A constructor that gets 2 bounds, the upper and lower bounds.
     * @param low the lower bound
     * @param high the high bound
     */
    HashMap(double low, double high);

    /**
     * A Copy constructor
     * @param map the HashMap to copy
     */
    HashMap(const HashMap &map);

    /**
     * A Move constructor
     * @param map the HashMap to move
     */
    HashMap(HashMap && map) noexcept;

    /**
     * a constructor that gets two vectors, one for the keys and one for the values and creates a
     * table accordingly
     * @param keys the keys vector of keys
     * @param values the values vector of values
     */
    HashMap(std::vector<keyT> keys, std::vector<valueT> values);

    /**
     * A destructor
     */
    ~HashMap()
    {
        delete[] _table;
    }

    /**
     * A getter for the size of the table
     * @return the size of the table
     */
    int size() const noexcept
    {
        return _size;
    }

    /**
     * A getter for the capacity of the table
     * @return the capacity of the table
     */
    int capacity() const noexcept
    {
        return _capacity;
    }

    /**
     * A function that checks if the table is empty.
     * @return true if the table is empty, false otherwise
     */
    bool empty() const noexcept
    {
        return _size == BASE_SIZE;
    }

    /**
     * A function that inserts the value to the given key in the table.
     * @return true upon success, false otherwise.
     */
    bool insert(keyT key, valueT value);

    /**
     * checks if the key is in the table.
     * @param key the key to check if it is in the table
     * @return true if the key is in the table, false otherwise
     */
    bool containsKey(const keyT &key) const noexcept;

    /**
     * a function that returns the value in a given key. throws an exception if the key does not exist.
     * @param key the key to check the value at
     * @return the value in the given key
     */
    valueT &at(const keyT &key) const;

    /**
     * A function that erases the value in a given key.
     * @param key the key to erase the value in.
     * @return true upon success, false otherwise
     */
    bool erase(const keyT &key);

    /**
     * A getter function for the loadFactor
     * @return the load factor of the table
     */
    double getLoadFactor() const noexcept
    {
        return (double) _size / _capacity;
    }

    /**
     * A function that returns the size of the bucket holding that key.
     * @param key to find the size of its bucket
     * @return int the size of the bucket holding that key.
     */
    int bucketSize(const keyT &key) const;

    /**
     * A function that returns the index of the bucket holding that key.
     * @param key to find the size of its bucket
     * @return int the size of the index of bucket holding that key.
     */
    int bucketIndex(const keyT &key) const;

    /**
     * A function that clears all the table values
     */
    void clear() noexcept;

    /**
     * copy operator = that get a map and move it to the current map.
     * @param map the map to move
     * @return a reference to this map.
     */
    HashMap &operator=(const HashMap &map);

    /**
     * move operator = that get a map and move it to the current map.
     * @param map the map to move
     * @return a reference to this map.
     */
    HashMap &operator=(HashMap && map) noexcept;

    /**
     * Operator [] that returns the value in the given key.
     * @param key a key to give the value in
     * @return a reference to the value in the key
     */
    valueT &operator[](const keyT &key);

    /**
     * a const method for the Operator [] that returns the value in the given key.
     * @param key a key to give the value in
     * @return the value in the key, cannot be changed
     */
    valueT operator[](const keyT &key) const noexcept;

    /**
     * the == operator for the HashMap class
     * @param map another hashmap to check whether they are equal.
     * @return true if the maps are equal, false otherwise
     */
    bool operator==(const HashMap &map) const noexcept;

    /**
     * the != operator for the HashMap class
     * @param map another hashmap to check whether they are equal.
     * @return true if the maps are not equal, false otherwise
     */
    bool operator!=(const HashMap &map) const noexcept;

    /**
     * An inner class which describes the iterator which runs on the HashMap
     */
    class iterator
    {

    private:
        friend class HashMap;

        const HashMap &_hashMap;
        bucket *_outIterator;
        typename bucket::iterator _inIterator;

        /**
        * The iterator constructor that returns an iterator on the map's first pair.
        * @param map the current map object.
        */
        explicit iterator(const HashMap &map) noexcept;

        /**
        * The iterator constructor that returns an iterator on the map's last pair.
        * @param map the current map object.
        * @param isLast a flag to differ the constructors.
        */
        iterator(const HashMap &map, bool isLast) noexcept: _hashMap(map),
                _outIterator(&map._table[map.capacity() - 1]), _inIterator(_outIterator->end())
        {
            bool removeWarn = isLast;
            if (removeWarn)
            {
                return;
            }
        }

    public:

        /**
         * the ++ postfix operator
         * @param num a flag that differs this from the prefix operator
         * @return a reference to the current iterator.
         */
        const iterator operator++(int) noexcept;

        /**
         * the ++ prefix operator
         * @return A reference to the current iterator object + 1
         */
        iterator &operator++() noexcept;

        /**
         * the -> operator
         * @return the memory address of the iterator's content
         */
        pair *operator->() const noexcept
        {
            return &(*_inIterator);
        }

        /**
         * the * operator
         * @return the iterator's content
         */
        pair operator*() const noexcept
        {
            return *_inIterator;
        }

        /**
         * the == operator
         * @param iter the iterator to compare to the current iterator.
         * @return true if they are equal, false otherwise
         */
        bool operator==(const iterator &iter) const noexcept
        {
            return _inIterator == iter._inIterator;
        }

        /**
         * the != operator
         * @param iter the iterator to compare to the current iterator.
         * @return true if they are not equal, false otherwise
         */
        bool operator!=(const iterator &iter) const noexcept
        {
            return _inIterator != iter._inIterator;
        }
    };

    typedef typename HashMap<keyT, valueT>::iterator iterator;

    /**
     * A function that returns the first pair in the map.
     * @return the first pair
     */
    const iterator begin() const noexcept
    {
        return iterator(*this);
    }

    /**
     * A function that returns the last pair in the map.
     * @return the last pair
     */
    const iterator end() const noexcept
    {
        return iterator(*this, true);
    }

    /**
     * A const function that returns the first pair in the map.
     * @return the first pair
     */
    const iterator cbegin() const noexcept
    {
        return iterator(*this);
    }

    /**
     * A const function that returns the last pair in the map.
     * @return the last pair
     */
    const iterator cend() const noexcept
    {
        return iterator(*this, true);
    }
};

template<class keyT, class valueT>

/**
* The iterator constructor that returns an iterator on the map's pairs.
* @param map the current map object.
*/
HashMap<keyT, valueT>::iterator::iterator(const HashMap &map) noexcept : _hashMap(map),
        _outIterator(&map._table[map.capacity() - 1]), _inIterator(_outIterator->end())
{
    for (int i = 0; i < _hashMap.capacity(); i++)
    {
        if (_hashMap._table[i].empty())
        {
            continue;
        }
        _outIterator = &_hashMap._table[i];
        break;
    }
    _inIterator = _outIterator->begin();
}


template<class keyT, class valueT>

/**
 * the ++ postfix operator
 * @param num a flag that differs this from the prefix operator
 * @return a reference to the current iterator.
 */
const typename HashMap<keyT, valueT>::iterator HashMap<keyT, valueT>::iterator::operator++(int) noexcept
{
    iterator temp = *this;
    ++(*this);
    return temp;
}

template<class keyT, class valueT>

/**
 * the ++ prefix operator
 * @return A reference to the current iterator object + 1
 */
typename HashMap<keyT, valueT>::iterator &HashMap<keyT, valueT>::iterator::operator++() noexcept
{
    _inIterator++;
    if (_outIterator != &_hashMap._table[_hashMap.capacity() - 1] && _inIterator == _outIterator->end())
    {
        if (_inIterator == _outIterator->end())
        {
            do
            {
                _outIterator++;
            } while (_outIterator->empty() && _outIterator != &_hashMap._table[_hashMap.capacity() - 1]);
            _inIterator = _outIterator->begin();
        }
    }
    return *this;
}

template<class keyT, class valueT>

/**
 * returns the address of a given key.
 * @param key the key number representation.
 * @return the address that the key corresponds to
 */
void HashMap<keyT, valueT>::_changeSize(int size)
{
    bucket *temp = _table;
    try
    {
        _table = new bucket[size];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] temp;
        throw;
    }
    _size = 0;
    int oldCapacity = _capacity;
    _capacity = size;
    for (int i = 0; i < oldCapacity; i++)
    {
        for (pair p: temp[i])
        {
            try
            {
                insert(p.first, p.second);
            }
            catch (const std::bad_alloc &e)
            {
                delete[] temp;
                throw;
            }
        }
    }
    delete[] temp;
}

template<class keyT, class valueT>

/**
 * grows the table in case of growing beyond the upper bound
 */
void HashMap<keyT, valueT>::_reHashUp()
{
    if (getLoadFactor() <= _highBound)
    {
        return;
    }
    try
    {
        _changeSize(_capacity * RESIZE_MULTIPLIER);
    }
    catch (const std::bad_alloc &e)
    {
        throw;
    }
}

template<class keyT, class valueT>

/**
 * Makes the table smaller in case of getting beneath the lowe bound.
 */
void HashMap<keyT, valueT>::_reHashDown()
{
    if (getLoadFactor() >= _lowBound)
    {
        return;
    }
    try
    {
        _changeSize(_capacity / RESIZE_MULTIPLIER);
    }
    catch (const std::bad_alloc &e)
    {
        throw;
    }
}

template<class keyT, class valueT>

/**
 * Returns the address of the given value in the table by the hash function
 * @param x the numeric representation of a key
 * @return the address of the given value in the table by the hash function
 */
int HashMap<keyT, valueT>::_getAddress(keyT key) const noexcept
{
    return (int) std::hash<keyT>{}(key) & (_capacity - 1);
}

template<class keyT, class valueT>

/**
 * A constructor that gets 2 bounds, the upper and lower bounds.
 * @param low the lower bound
 * @param high the high bound
 */
HashMap<keyT, valueT>::HashMap(double low, double high) : _capacity(BASE_CAPACITY), _size(BASE_SIZE)
{
    if (low < high && 0 < low && high < 1)
    {
        _highBound = high;
        _lowBound = low;
        _table = new bucket[BASE_CAPACITY];
    }
    else
    {
        throw std::invalid_argument(ERR_INVALID_LOAD_FACTORS);
    }
}

template<class keyT, class valueT>

/**
 * a constructor that gets two vectors, one for the keys and one for the values and creates a
 * table accordingly
 * @param keys the keys vector of keys
 * @param values the values vector of values
 */
HashMap<keyT, valueT>::HashMap(std::vector<keyT> keys, std::vector<valueT> values): HashMap()
{
    if (keys.size() == values.size())
    {
        for (int i = 0; i < (int) keys.size(); i++)
        {
            (*this)[keys[i]] = values[i];
        }
    }
    else
    {
        throw std::length_error(ERR_DIFF_VECS_SIZE);
    }
}

template<class keyT, class valueT>

/**
 * A Copy constructor
 * @param map the HashMap to copy
 */
HashMap<keyT, valueT>::HashMap(const HashMap &map): _capacity(map._capacity), _size(map._size),
        _lowBound(map._lowBound), _highBound(map._highBound)
{
    _table = new bucket[map._capacity];
    for (int i = 0; i < _capacity; i++)
    {
        _table[i] = map._table[i];
    }
}

template<class keyT, class valueT>

/**
 * A Move constructor
 * @param map the HashMap to move
 */
HashMap<keyT, valueT>::HashMap(HashMap && map) noexcept: _capacity(map._capacity), _size(map._size),
        _lowBound(map._lowBound), _highBound(map._highBound), _table(map._table)
{
    map._table = nullptr;
}

template<class keyT, class valueT>

/**
 * a function that returns the value in a given key. throws an exception if the key does not exist.
 * @param key the key to check the value at
 * @return the value in the given key
 */
valueT &HashMap<keyT, valueT>::at(const keyT &key) const
{
    if (_table != nullptr)
    {
        for (pair &p: _table[_getAddress(key)])
        {
            if (!(p.first == key))
            {
                continue;
            }
            return p.second;
        }
        throw std::out_of_range(ERR_KEY_NOT_IN_MAP);
    }
    throw std::out_of_range(ERR_NO_MAP);
}

template<class keyT, class valueT>

/**
 * A function that inserts the value to the given key in the table.
 * @return true upon success, false otherwise.
 */
bool HashMap<keyT, valueT>::insert(keyT key, valueT value)
{
    if (!containsKey(key))
    {
        _size++;
        try
        {
            _table[_getAddress(key)].push_back(pair(key, value));
            _reHashUp();
        }
        catch (const std::bad_alloc &e)
        {
            throw;
        }
        return true;
    }
    return false;
}


template<class keyT, class valueT>

/**
 * checks if the key is in the table.
 * @param key the key to check if it is in the table
 * @return true if the key is in the table, false otherwise
 */
bool HashMap<keyT, valueT>::containsKey(const keyT &key) const noexcept
{
    for (pair &p: _table[_getAddress(key)])
    {
        if (!(p.first == key))
        {
            continue;
        }
        return true;
    }
    return false;
}

template<class keyT, class valueT>

/**
 * A function that erases the value in a given key.
 * @param key the key to erase the value in.
 * @return true upon success, false otherwise
 */
bool HashMap<keyT, valueT>::erase(const keyT &key)
{
    if (!containsKey(key))
    {
        return false;
    }
    int hashVal = _getAddress(key);
    for (int i = 0; i < (int) _table[hashVal].size(); i++)
    {
        if (!(_table[hashVal][i].first == key))
        {
            continue;
        }
        _table[hashVal].erase(_table[hashVal].begin() + i);
        _size--;
        try
        {
            _reHashDown();
        }
        catch (const std::bad_alloc &e)
        {
            throw;
        }
        return true;
    }
    return false;
}

template<class keyT, class valueT>

/**
 * A function that returns the size of the bucket holding that key.
 * @param key to find the size of its bucket
 * @return int the size of the bucket holding that key.
 */
int HashMap<keyT, valueT>::bucketSize(const keyT &key) const
{
    if (containsKey(key))
    {
        return (int) _table[_getAddress(key)].size();
    }
    throw std::out_of_range(ERR_KEY_NOT_IN_MAP);
}

template<class keyT, class valueT>

/**
 * A function that returns the index of the bucket holding that key.
 * @param key to find the size of its bucket
 * @return int the size of the index of bucket holding that key.
 */
int HashMap<keyT, valueT>::bucketIndex(const keyT &key) const
{
    if (containsKey(key))
    {
        return (int) _table[_getAddress(key)];
    }
    throw std::out_of_range(ERR_KEY_NOT_IN_MAP);
}

template<class keyT, class valueT>

/**
 * A function that clears all the table values
 */
void HashMap<keyT, valueT>::clear() noexcept
{
    for (int i = 0; i < _capacity; i++)
    {
        _table[i].clear();
    }
    _size = 0;
}

template<class keyT, class valueT>

/**
 * move operator = that get a map and move it to the current map.
 * @param map the map to move
 * @return a reference to this map.
 */
HashMap<keyT, valueT> &HashMap<keyT, valueT>::operator=(HashMap && map) noexcept
{
    if (this == &map)
    {
        return *this;
    }
    _capacity = map._capacity;
    _size = map._size;
    _lowBound = map._lowBound;
    _highBound = map._highBound;
    delete[] _table;
    _table = map._table;
    map._table = nullptr;
    return *this;
}

template<class keyT, class valueT>

/**
 * copy operator = that get a map and move it to the current map.
 * @param map the map to move
 * @return a reference to this map.
 */
HashMap<keyT, valueT> &HashMap<keyT, valueT>::operator=(const HashMap &map)
{
    _capacity = map._capacity;
    _size = map._size;
    _highBound = map._highBound;
    _lowBound = map._lowBound;
    delete[] _table;
    try
    {
        _table = new bucket[_capacity];
        for (int i = 0; i < _capacity; i++)
        {
            _table[i] = map._table[i];
        }
    }
    catch (const std::bad_alloc &e)
    {
        throw;
    }
    return *this;
}


template<class keyT, class valueT>

/**
 * a const method for the Operator [] that returns the value in the given key.
 * @param key a key to give the value in
 * @return the value in the key, cannot be changed
 */
valueT HashMap<keyT, valueT>::operator[](const keyT &key) const noexcept
{
    valueT val = valueT();
    for (pair p: _table[_getAddress(key)])
    {
        if (!(p.first == key))
        {
            continue;
        }
        return p.second;
    }
    return val;
}

template<class keyT, class valueT>

/**
 * Operator [] that returns the value in the given key.
 * @param key a key to give the value in
 * @return a reference to the value in the key
 */
valueT &HashMap<keyT, valueT>::operator[](const keyT &key)
{
    valueT val = valueT();
    if (containsKey(key))
    {
        return at(key);
    }
    try
    {
        insert(key, val);
    }
    catch (const std::bad_alloc &e)
    {
        throw;
    }
    return at(key);
}


template<class keyT, class valueT>

/**
 * the != operator for the HashMap class
 * @param map another hashmap to check whether they are equal.
 * @return true if the maps are not equal, false otherwise
 */
bool HashMap<keyT, valueT>::operator!=(const HashMap &map) const noexcept
{
    return *this != map;
}

template<class keyT, class valueT>

/**
 * the == operator for the HashMap class
 * @param map another hashmap to check whether they are equal.
 * @return true if the maps are equal, false otherwise
 */
bool HashMap<keyT, valueT>::operator==(const HashMap &map) const noexcept
{
    if (_highBound == map._highBound && _lowBound == map._lowBound && _size == map._size && _capacity == map._capacity)
    {
        for (pair pair1 : map)
        {
            if (!containsKey(pair1.first))
            {
                return false;
            }
            try
            {
                if (at(pair1.first) != pair1.second)
                {
                    return false;
                }
            }
            catch (const std::out_of_range &e)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

