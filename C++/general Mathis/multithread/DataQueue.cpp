#include "DataQueue.h"

DataQueue * DataQueue::instance = nullptr;

DataQueue * DataQueue::getInstance()
{
	if (instance == nullptr)
	{
		instance = new DataQueue();
	}

	return instance;
}