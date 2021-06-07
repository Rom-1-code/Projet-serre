#pragma once
#include <deque>
#include <mutex>

struct SerreData
{
	float temperatureInterieure;
	float humiditeInterieure;
	float humiditeSol;

	float temperatureExterieure;

	SerreData(float temperatureInterieure, float humiditeInterieure, float humiditeSol, float temperatureExterieure)
	{
		this->temperatureInterieure = temperatureInterieure;
		this->temperatureExterieure = temperatureExterieure;
		this->humiditeInterieure = humiditeInterieure;
		this->humiditeSol = humiditeSol;
	}
};

class DataQueue : private std::deque<SerreData*>
{
private:;
	std::mutex synchro;
	static DataQueue * instance;
	DataQueue() {}

public:
	static DataQueue * getInstance();
	void addData(SerreData * data)
	{
		synchro.lock();
		push_back(data);
		synchro.unlock();
	}

	SerreData * getData()
	{
		SerreData * result = nullptr;

		synchro.lock();
		if (size() > 0)
		{
			result = front();
			pop_front();
		}
		synchro.unlock();

		return result;
	}
};

