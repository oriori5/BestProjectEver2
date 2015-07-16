/*
 * PriorityQueue.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */
#include <queue>
#include <vector>

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

using namespace std;
#include "Location.h"
typedef pair<unsigned, Location> pel;

class comparPriorityPair
{
public :
	inline bool operator ()(const pel& lhs,const pel& rhs)
	{
			return lhs.first > rhs.first;
	}
};

class PriorityQueue
{
private :
	priority_queue<pel, vector<pel>,comparPriorityPair> elements;

public:
	inline bool empty()
	{
		return elements.empty();
	}

	inline void put(Location item, unsigned priority)
	{
		elements.push({priority,item});
	}

	inline Location get()
	{
		Location best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};


#endif /* PRIORITYQUEUE_H_ */
