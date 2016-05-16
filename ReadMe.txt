interval_map<K,V> is a data structure that efficiently associates intervals of keys of type K with values of type V. 

interval_map<K, V> is implemented on top of std::map. 

Each key-value-pair (k,v) in the m_map member means that the value v is associated to the interval from k (including) to the next key (excluding) 
in m_map.

Example: the std::map (0,'A'), (3,'B'), (5,'A') represents the mapping

0 -> 'A'
1 -> 'A'
2 -> 'A'
3 -> 'B'
4 -> 'B'
5 -> 'A'
6 -> 'A'
7 -> 'A'
... all the way to numeric_limits<key>::max()
