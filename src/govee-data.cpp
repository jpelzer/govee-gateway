#include <sys/types.h>
#include <sstream>
#include "govee-data.h"

#include <iostream>

using namespace std;

void GoveeData::decodeData(const char* const data)
{
	int iTemp = int(data[3]) << 16 | int(data[4]) << 8 | int(data[5]);
	temperatureC = float(iTemp) / 10000.0;
	humidity = float(iTemp % 1000) / 10.0;
	battery = int(data[6]);

	ma = int(data[8]);
	temperatureF = temperatureC*9/5+32;
}

void GoveeData::calcAverage(std::queue<GoveeData>* it)
{
	signed int rssi_temp=0;             	//!< separate rssi variable to calculate rssi average
	int sz =it->size();							//!< size of iterator
	// read all values in queue and calculate averages
	while (!it->empty())
	{
		temperatureF += it->front().temperatureF;
		temperatureC += it->front().temperatureC;
		humidity += it->front().humidity;
		battery += it->front().battery;
		rssi_temp += (it->front().rssi);
		ma += (it->front().ma);
		it->pop();
	}
	temperatureF = temperatureF / sz;
	temperatureC = temperatureC / sz;
	humidity = humidity / sz;
	battery = battery / sz;
	rssi_temp = int(rssi_temp / sz);
	ma = ma /sz ;
	rssi = static_cast<signed char>(rssi_temp);
}
