// Example of using C++ Standard Library containers

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility> // pair
using namespace std;

int main () {
    // List of elements of type string.
    // The parameterless constructor that is called automatically,
    // if there is no explicit initializer, create one
    // empty list.
    list<string> ls;

    // push_front or push_back adds an element at the beginning or
    // at the end of the list.
    ls.push_back("two");
    ls.push_back("three");
    ls.push_front("one");

    // Alternatively, a list can also be created with an "initializer list"
    // be initialized in curly braces.
    ls = { "three", "two", "one" };

    // reverse reverses the order of the elements.
    ls.reverse();

    // size returns the number of elements.
    cout << ls.size() << endl;

    // "range-based for loop" to conveniently iterate through all elements.
    for (string s : ls) {
        cout << s << endl;
    }

    // front or back returns the first or last element,
    // pop_front or pop_back removes this element.
    // (The behavior of these functions is undefined for empty lists.)
    // This allows a list to also be used as a FIFO queue:

    // Table with keys of type string and associated values
    // of type int, which assigns an int value tab[s] to each string s.
    // The parameterless constructor that is called automatically,
    // if there is no explicit initializer, create one
    // empty table.
    map<string, int> tab;
    // The index operator can be used for both query and assignment
    // of the value associated with a key.
    tab["one"] = 1; cout << tab["one"] << endl;
    tab["two"] = 2; cout << tab["two"] << endl;
    tab["three"] = 3; cout << tab["three"] << endl;
    tab["two"] = -2; cout << tab["two"] << endl;

    // If a key doesn't already have a value, the
    // index operator automatically assigned and supplied the value,
    // returned by the value type's parameterless constructor.
    // (For type int, this value is 0.)
    cout << tab["four"] << endl;

    // Alternatively, a table can also be created with an "initializer list"
    // be initialized, which consists of key-value pairs.
    tab = { { "one", 11 }, { "two", 22 }, { "three", 33 } };

    // "range-based for loop" to iterate through all key-value pairs.
    // p.first or p.second returns the first or second component
    // of the pair p.
    for (pair<string, int> p : tab) {
        cout << p.first << " -> " << p.second << endl;
    }

    // Container types can also be nested.
    // Can then be appropriately nested for initialization
    // "initializer lists" are used.
    list<list<int>> ls2 = { { 1, 2 }, { }, { 3 } };

    // Or built up step by step:
    ls2.clear();
    ls2.push_back(list<int>()); // list<int>() returns an empty list.
    ls2.back().push_back(1);
    ls2.back().push_back(2);
    ls2.push_back(list<int>());
    ls2.push_back(list<int>());
    ls2.back().push_back(3);

    // Output with nested for loops.
    for (list<int> ls : ls2) {
        for (int x : ls) cout << x << " ";
        cout << endl;
    }

    // Container types can also be combined.
    // stores for each person by a pair of friends
    // Strings (first name and last name) is identified, a list
    // from friends, which are also pairs of strings
    // trades.
    map<pair<string, string>, list<pair<string, string>>> friends = {
            { { "Anton", "A." }, { { "Bertha", "B." }, { "Hugo", "H." } } },
            { { "Frieda", "F." }, { { "Gustav", "G." } } }
    };
    // When the exact type of a variable is unknown or awkward
    // is to be written, one can often use the keyword instead
    // Use auto to have the compiler determine the type automatically.
    for (auto p : friends) {
        // Since friends is a table, p is a pair.
        auto key = p.first;
        auto val = p.second;
        cout << key.first << " " << key.second;

        // val is a list of pairs, so q is a pair again.
        string sep = " -> ";
        for (auto q : val) {
            cout << sep << q.first << " " << q.second;
            sep = " | ";
        }
        cout << endl;
    }
}