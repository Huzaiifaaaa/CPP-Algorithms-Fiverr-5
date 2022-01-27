#include <set>

// Entry of a priority queue consisting of a priority
// prio with type P and additional data data with type D.
// The priority prio may not directly, but only by calling
// be changed by changePrio.
// (For some reason, it's more convenient that Entry be global and
// is not defined within PrioQueue.)
template <typename P, typename D>
struct Entry {
    P prio;
    D data;

    // initialization with priority p and additional data d.
    Entry (P p, D d) : prio(p), data(d) {}
};

// Minimum priority queue with P-type priorities
// and additional data of type D.
// Where PrioQueue uses P for a given type
// becomes, a less than operator (<) for the type P must be known.
// Other comparison operators (<=, >, >=, ==, !=) are not required.
template <typename P, typename D>
struct PrioQueue {
    using Entry = ::Entry<P, D>;

    struct LessThan {
    	bool operator() (Entry* e1, Entry* e2) const {
        	if (e1->prio < e2->prio) return true;
        	if (e2->prio < e1->prio) return false;
        	return e1 < e2;
    	}
    };

    std::set<Entry*, LessThan> entries;

    // Is the queue currently empty?
    bool isEmpty() {
    	return entries.empty();
    }

    // create a new entry with priority p and additional data d,
    // add to the queue and return.
    // (Entries created by insert must be approved by the user
    // become after using extractMinimum or remove from the
    // queue have been removed and are no longer needed.)
    Entry* insert (P p, D d) {
    	Entry* e = new Entry(p, d);
    	entries.insert(e);
    	return e;
    }

    // Return entry with minimum priority.
    // (Null pointer on an empty queue.)
    Entry* minimum() {
    	if (entries.empty()) return nullptr;
    	return *entries.begin();
    }

    // Return entry with minimum priority
    // and dequeue (but not release).
    // (Without effect on an empty heap with a null pointer as the result value.)
    Entry* extractMinimum() {
    	Entry* e = minimum();
    	if (e) entries.erase(entries.begin());
    	return e;
    }

    // Does the queue contain the entry e?
    // (Result value false if e is a null pointer.)
    bool contains (Entry* e) {
    	return entries.count(e);
    }

    // Dequeue (but not release) entry e.
    // (Has no effect with result value false if e is a null pointer
    // or e does not belong to the current queue.)
    bool remove (Entry* e) {
    	return entries. erase(e);
    }

    // Change the priority of entry e to p.
    // (Has no effect with result value false if e is a null pointer
    // or e does not belong to the current queue.)
    bool changePrio (Entry* e, P p) {
    	if (!remove(e)) return false;
    	e->prio = p;
    	entries.insert(e);
    	return true;
    }
};
