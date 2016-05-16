#include "stdafx.h"
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <assert.h>

#include "interval_map.cpp"

using std::string;
using std::vector;
using std::numeric_limits;

struct Tuple {
	int key;
	string value;
	Tuple(int k, string & v) {
		key = k;
		value = v;
	}
	Tuple(int k, char * v) {
		key = k;
		value = v;
	}
};


void check(const std::map<int, string> & m_map, const vector<Tuple> & data) {
	int i = 0;
	for (auto & pair : m_map) {
		assert(pair.first == data[i].key);
		assert(pair.second == data[i].value);
		i++;
	}
}




void IntervalMapTest() {
	interval_map<double, int> mapd(0);
	auto mind = numeric_limits<double>::min();
	auto maxd = numeric_limits<double>::max();

	mapd.assign(0.111, 0.111112, 1);
	mapd.assign(1123.345, 123123123123.123, 2);


	interval_map<int, string> map("EMPTY");
	auto min = numeric_limits<int>::min();
	auto max = numeric_limits<int>::max();

	//test1 simple case
	map.assign(0, 50, "A");
	map.assign(-1, 0, "A");
	map.assign(45, 50, "B");


	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(-1, "A"),
			Tuple(45, "B"),
			Tuple(50, "EMPTY"),
	});

	//test1 simple case
	map.assign(min, max, "EMPTY");
	map.assign(0, 0, "A");
	map.assign(20, 30, "B");
	map.assign(40, 50, "C");

	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(20, "B"),
			Tuple(30, "EMPTY"),
			Tuple(40, "C"),
			Tuple(50, "EMPTY"),
	});


	//test1 simple case
	map.assign(0, 10, "A");
	map.assign(20, 30, "B");
	map.assign(40, 50, "C");

	check(map.m_map, vector<Tuple> {
			Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(10, "EMPTY"),
			Tuple(20, "B"),
			Tuple(30, "EMPTY"),
			Tuple(40, "C"),
			Tuple(50, "EMPTY"),
	});

	//test2
	map.assign(5, 25, "overlap1");
	check(map.m_map, vector<Tuple> {
			Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(5, "overlap1"),
			Tuple(25, "B"),
			Tuple(30, "EMPTY"),
			Tuple(40, "C"),
			Tuple(50, "EMPTY"),
	});

	map.assign(5, 35, "overlap1");
	check(map.m_map, vector<Tuple> {
			Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(5, "overlap1"),
			Tuple(35, "EMPTY"),
			Tuple(40, "C"),
			Tuple(50, "EMPTY"),
	});


	map.assign(2, 45, "overlap2");
	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(2, "overlap2"),
			Tuple(45, "C"),
			Tuple(50, "EMPTY"),
	});

	map.assign(2, 45, "overlap2");
	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(2, "overlap2"),
			Tuple(45, "C"),
			Tuple(50, "EMPTY"),
	});

	map.assign(min, max, "EMPTY");
	map.assign(0, 10, "A");
	map.assign(20, 30, "A");
	map.assign(10, 20, "A");

	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(30, "EMPTY"),
	});


	map.assign(min, max, "EMPTY");
	map.assign(0, 10, "A");
	map.assign(5, 30, "A");

	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(30, "EMPTY"),
	});

	map.assign(min, max, "EMPTY");
	map.assign(0, 10, "A");
	map.assign(20, 30, "A");
	map.assign(8, 20, "A");

	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(30, "EMPTY"),
	});

	map.assign(min, max, "EMPTY");
	map.assign(0, 10, "A");
	map.assign(20, 30, "A");
	map.assign(12, 20, "A");

	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(10, "EMPTY"),
			Tuple(12, "A"),
			Tuple(30, "EMPTY"),
	});


	map.assign(min, max, "EMPTY");
	map.assign(0, 10, "A");
	map.assign(20, 30, "B");
	map.assign(5, 15, "A");
	map.assign(15, 28, "B");

	check(map.m_map, vector<Tuple> {
		Tuple(min, "EMPTY"),
			Tuple(0, "A"),
			Tuple(15, "B"),
			Tuple(30, "EMPTY"),
	});

	//random test
	srand(time(0));
	map.assign(min, max, "EMPTY");
	int maxi = 100000;
	for (auto i = -maxi; i < maxi; i++) {
		map.assign((rand() % 2 ? 1 : -1) * (rand() % maxi), (rand() % 2 ? 1 : -1)*(rand() % maxi), (rand() % 2) ? "A" : "B");
	}
	map.assign(-maxi >> 4 , maxi >> 4, "CHECK");


}

// run unit tests
int main(int argc, char* argv[]) {
	IntervalMapTest();
	return 0;
}
