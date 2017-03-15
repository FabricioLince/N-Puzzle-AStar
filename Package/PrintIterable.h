#ifndef PRINT_ITEABLES_H
#define PRINT_ITEABLES_H

/**
    This file should be included after all the std includes
    as it checks for definitions made there
 **/

#include <ostream>

extern char *default_sep;
extern char *default_begin;
extern char *default_end;
extern char *default_map_begin;
extern char *default_map_end;
extern char *default_vector_begin;
extern char *default_vector_end;
extern char *default_map_sep;
extern char *default_pair_sep;

template < class Iterable >
std::ostream& printIterable(std::ostream& out, Iterable& i,
                            const char* sep =   default_sep,
                            const char* begin = default_begin,
                            const char*end =    default_end);

/** Print Iterators **/

#ifdef _GLIBCXX_VECTOR

template < typename T >
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vector)
{
    return printIterable(out, vector, default_sep, default_vector_begin, default_vector_end);
}
#endif

#ifdef _GLIBCXX_MAP

template < typename K, typename V >
std::ostream& operator<<(std::ostream& out, const typename std::pair<K, V>& mapIterator)
{
    return out << mapIterator.first << default_pair_sep << mapIterator.second;
}

template < typename K, typename V >
std::ostream& operator<<(std::ostream& out, const std::map<K, V>& map)
{
    return printIterable(out, map, default_map_sep, default_map_begin, default_map_end);
}

#endif // _GLIBCXX_MAP

#ifdef _GLIBCXX_LIST

template < typename T >
std::ostream& operator<<(std::ostream& out, const std::list<T>& list)
{
    return printIterable(out, list, ", ");
}

#endif // _GLIBCXX_LIST

#ifdef _DEQUE_H

template < typename T >
std::ostream& operator<<(std::ostream& out, const std::deque<T>& deque)
{
    return printIterable(out, deque, ", ");
}

#endif //_DEQUE_H

#ifdef LINKED_LIST_H

template < typename T >
std::ostream& operator<<(std::ostream& out, LinkedList<T>& list)
{
    if (list.isEmpty()) return out << "(empty)";
    return printIterable(out, list, " --> ") << " --> NULL";
}

#endif

/** end Print Iterators **/

template < class Iterable >
std::ostream& printIterable(std::ostream& out, const Iterable& i, const char* sep = ", ", const char* begin="", const char*end="")
{
    out << begin;
    typename Iterable::const_iterator it = i.begin();
    while (it != i.end())
    {
        /** @TODO change to out << it **/
        out << *it;
        it++;
        if (it != i.end()) out << sep;
    }
    return out << end;
}


#endif
