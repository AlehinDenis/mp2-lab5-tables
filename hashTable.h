#pragma once
#include "table.h"
#include <list>
#include <string>
#include <vector>

template <class Key>
int HashFunc(Key key, int size)
{
	return (((5 * key + 3) % 101) % size);
}

int HashFunc(std::string key, int size)
{
	int res = 0;
	for (int i = 0; i < key.size(); i++)
		res += key[i];
	return res % size;
}

template<class Key, class Data>
class HashTable
{
protected:
	std::vector<std::list<Record<Key, Data> > > dataVector;
	int size;
	int (*hashFunc)(Key, int);


public:
	HashTable(int Size = 10, int (*_hashFunc)(Key, int) = HashFunc<Key>): size(Size)
	{
		hashFunc = _hashFunc;

		dataVector.resize(size);
	}

	void Add(Key key, Data data)
	{
		int index = hashFunc(key, size);

		dataVector[index].push_back(Record<Key, Data>(key, data));
	}

	Data& Find(Key key)
	{
		int index = hashFunc(key, size);
		if (dataVector[index].size() == 0)
			return End();
		typename std::list<Record<Key, Data> >::iterator it = dataVector[index].begin();
		
		for (int i = 0; i < dataVector[index].size(); i++)
			if (it->key == key)
				return it->data;
		return End();
	}

	void Delete(Key key)
	{
		int index = hashFunc(key, size);
		typename std::list<Record<Key, Data> >::iterator it = dataVector[index].begin();
		while (it->key != key)
			it++;
		dataVector[index].erase(it);
	}

	Data& End() { return NULL; }

	int getSize() const { return size; }
};

