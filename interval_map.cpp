#include "stdafx.h"
#include <map>
#include <limits>
#include <iterator> 


template<class K, class V>
class interval_map {
	friend void IntervalMapTest();

private:
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	};

	// Assign value val to interval [keyBegin, keyEnd). 
	// Overwrite previous values in this interval. 
	// Do not change values outside this interval.
	// Conforming to the C++ Standard Library conventions, the interval 
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, 
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, const V& val) {
		if (!(keyBegin < keyEnd))
			return;

		// 1. Position at the prev that is < keyBegin (special case when keyBegin is std::numeric_limits<K>::lowest() and it == begin())
		auto it = --m_map.upper_bound(keyBegin);
		V prevVal = it->second;
		bool exact = !(it->first < keyBegin);
		if (it != m_map.begin() && exact) {
			--it;
		}

		// 2. Start new interval at keyBegin if the previous one had different val (this creates interval [prev, keyBegin) -> prevVal)
		if (it->second != val) {
			it = m_map.insert(it, std::make_pair(keyBegin, val));
			it->second = val;
		}

		// 3. Delete intervals inside [keyBegin, keyEnd)
		++it;
		while (it != m_map.end() && !(keyEnd < it->first)) {
			prevVal = it->second;
			m_map.erase(it++);
		}

		// 4. Create interval [keyEnd, next) -> prevVal
		if (prevVal != val)
			m_map.insert(it, std::make_pair(keyEnd, prevVal));
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}
};
