/* NetRun C++ Wrapper (Public Domain) */
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <queue>
#include "lib/inc.h"
using std::cout;
using std::cin;



#include <deque>
#include <set>

typedef unsigned int state_t; // number of this state (0 based)

typedef char input_t; // edge datatype, like input data.  0 for espilon transitions.

struct table_entry_t {
	input_t input; // read that input (or 0 for epsilon)
	state_t next; // go to next state
};
const input_t EPSILON_TRANSITION = 0;

typedef std::vector<table_entry_t> table_list_t;

// Finite automata.  Supports both DFA and NFA/eNFA
struct FA {
	state_t start;

	std::map<state_t, table_list_t> table;

	// Set of accepting states
	std::set<state_t> accept;

	void print(const char *name="") const {
		std::cout<<"\nFA "<<name<<" { start ["<<start<<"]:\n";

		for (const auto &statelist : table) {
			std::cout<<" ["<<statelist.first<<"] table list: \n";

			for (const table_entry_t &entry : statelist.second)
				std::cout<<"    "<<entry.input<<" -> ["<<entry.next<<"]\n";
		}

		for (state_t a : accept) {
			std::cout<<"  accept ["<<a<<"]\n";
		}

		std::cout<<"}\n\n";
	}
};


typedef std::set<state_t> powerset_t;

void print(const powerset_t &p) {
	std::cout<<"  powerset ";
	for (state_t s : p) {
		std::cout<<" ["<<s<<"]";
	}
	std::cout<<"\n";
}

// Return the powerset of states reachable via espilon transitions starting from this state
powerset_t epsilon_expand(const FA &nfa, state_t start)
{
	// Algorithm: breadth-first search through the nfa's state graph along epsilon edges
	std::deque<state_t> q={start};
	powerset_t expanded;
	while (!q.empty()) {
		state_t s = q.front(); q.pop_front();
		if (expanded.count(s)>0) continue; // already added this state
		expanded.insert(s);

		// Check the transition table entries for s:
		auto table_s = nfa.table.find(s);
		if (table_s!=nfa.table.end())
		for (const auto &entry : table_s->second)
			if (entry.input==0) { // epsilon transition!  add it
				q.push_back(entry.next);
			}
	}
	return expanded;
}

// Add this powerset to the DFA, if it isn't in the dfa_from_power map already.
//   Returns a dfa state number.
state_t dfa_powerset(const powerset_t &p,std::map<powerset_t, state_t> &dfa_from_power,const FA &nfa, FA &dfa)
{
	const auto it = dfa_from_power.find(p);
	if (it!=dfa_from_power.end()) return it->second; // it's already in there

	// else need to set up new dfa state

	// grab next unused dfa state number
	state_t ds = dfa.table.size();
	dfa_from_power[p]=ds;
	dfa.table[ds]={}; // <- creates new empty table entry

	// The new dfa state accepts if *any* of the nfa states accept
	bool accepts=false;
	for (state_t ns : p)
		if (nfa.accept.count(ns)>0)
			accepts=true;

	if (accepts) dfa.accept.insert(ds);

	if (true) { // print the dfa to nfa mapping
		std::cout<<" new dfa ["<<ds<<"] "<<(accepts?"accept":" ")<<" for nfa ";
		print(p);
	}

	return ds;
}

// Convert this NFA to a DFA
//  (the nfa is const, but std::map's convenient [] lookups aren't)
FA dfa_from_nfa(FA &nfa)
{
	FA dfa;

	std::map<powerset_t, state_t> powersets;
	std::deque<powerset_t> powersets_to_search = {epsilon_expand(nfa, nfa.start)};

	dfa.start = dfa_powerset(powersets_to_search.front(), powersets, nfa, dfa);

	while (!powersets_to_search.empty()) {
		const auto powerset = powersets_to_search.front();
		powersets_to_search.pop_front();

		const auto curr_dfa_state = dfa_powerset(powerset, powersets, nfa, dfa);

		for (const auto& powerset_state : powerset) {
			state_t t = powerset_state;

			const auto nfa_table_it = nfa.table.find(t);
			if (nfa_table_it == nfa.table.end()) {
				continue;
			}


			for (const auto& v : nfa_table_it->second) {
				if (v.input == EPSILON_TRANSITION) {
					continue;
				}

				const auto new_powerset = epsilon_expand(nfa, v.next);
				powersets_to_search.push_back(new_powerset);

				const auto dest_state = dfa_powerset(new_powerset, powersets, nfa, dfa);

				const table_entry_t new_entry = {(input_t)curr_dfa_state, dest_state};
				const auto dfa_table_it = dfa.table.find(curr_dfa_state);

				if (dfa_table_it == dfa.table.end()) {
					cout << "CAN'T FIND " << new_entry.input << " (ERROR?)\n";
					continue;
				}

				dfa_table_it->second.push_back(new_entry);
			}
		}
	}


	return dfa;
}


long foo(void) {
	// The NFA to simulate "a+b" (a|b in typical regex syntax)
	//   https://ivanzuzak.info/noam/webapps/fsm_simulator/
	FA nfa;
	nfa.start=0;
	nfa.table[0]={ {0,2}, {0,4} };
	nfa.table[2]={ {'a',3} };
	nfa.table[3]={ {0,1} };
	nfa.table[4]={ {'b',5} };
	nfa.table[5]={ {0,1} };
	nfa.accept.insert(1);

	nfa.print("NFA");

	FA dfa = dfa_from_nfa(nfa);

	dfa.print("DFA");
	return 0;

}
