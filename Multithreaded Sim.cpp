// Multithreaded Sim.cpp : Defines the entry point for the application.
//

#include "Multithreaded Sim.h"
#include "queue"

struct Location {
	double x, y, z;
};

enum SensorType {
	GPS,
	IMU,
	Radar
};

struct SensorReading {
	SensorType source;
	Location loc;
};

class ThreadQueue {
	std::queue<SensorReading> q;
	std::mutex m;
public:
	void push(const SensorReading& value) {
		std::lock_guard<std::mutex> lock(m);
		q.push(value);
	}
	bool pop(SensorReading& value) {
		std::lock_guard<std::mutex> lock(m);
		if (q.empty()) return false;
		value = q.front();
		q.pop();
		return true;
	}
};

ThreadQueue GlobalQueue;

Location GetGPSLocation(Location trueLoc) 
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	//Change to margin of error
	std::normal_distribution<> noise(0, 5);
	return { trueLoc.x + noise(gen), trueLoc.y + noise(gen), trueLoc.z + noise(gen)};
}

void GPSThread(Location trueLoc, std::mutex& m) {
	while (true) {
		Location& getGPS = Location({});
		Location reading = GetGPSLocation(trueLoc);
		{
			std::lock_guard<std::mutex> lock(m);
			getGPS = reading;
			SensorReading GPSIn;
			GPSIn.loc = getGPS;
			GPSIn.source = GPS;
			GlobalQueue.push(GPSIn);
			std::cout << "Combined Location: " << getGPS.x << ", " << getGPS.y << "\n";
		}
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
}

Location GetIMULocation(Location trueLoc) 
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::normal_distribution<> noise(0, 2);
	return { trueLoc.x + noise(gen), trueLoc.y + noise(gen), trueLoc.z + noise(gen) };
}

void IMUThread(Location trueLoc, std::mutex& m) {
	while (true) {
		Location& getIMU = Location({});
		Location reading = GetIMULocation(trueLoc);
		{
			std::lock_guard<std::mutex> lock(m);
			getIMU = reading;
			SensorReading IMUIn;
			IMUIn.loc = getIMU;
			IMUIn.source = IMU;
			GlobalQueue.push(IMUIn);
		}
		std::this_thread::sleep_for(std::chrono::seconds(30));
	}
}

Location GetRadar(Location trueLoc) {
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::normal_distribution<> noise(0, 5);
	return { trueLoc.x + noise(gen), trueLoc.y + noise(gen), trueLoc.z + noise(gen) };
}

void RadarThread(Location trueLoc, std::mutex& m) {
	while (true) {
		Location& getRadar = Location();
		Location reading = GetRadar(trueLoc);
		{
			std::lock_guard<std::mutex> lock(m);
			getRadar = reading;
			SensorReading RadarIn;
			RadarIn.loc = getRadar;
			RadarIn.source = Radar;
			GlobalQueue.push(RadarIn);
			std::cout << "Radar Location: " << getRadar.x << "\n";
		}
		std::this_thread::sleep_for(std::chrono::seconds(20));
	}
}

std::optional<Location> LatestGPS;
std::optional<Location> LatestRadar;
std::optional<Location> LatestIMU;


static void Combine() {
	SensorReading Reading;
	while (true) {
		if (GlobalQueue.pop(Reading)) {
			switch (Reading.source) {
			case SensorType::GPS:
				LatestGPS = Reading.loc; 
				break;
			case SensorType::Radar:
				LatestRadar = Reading.loc;
				break;
			case SensorType::IMU:
				LatestIMU = Reading.loc;
				break;
			}
			if (LatestGPS && LatestRadar && LatestIMU) {
				Location Combined({
					LatestGPS->x + LatestRadar->x + LatestIMU->x,
					LatestGPS->y + LatestRadar->y + LatestIMU->y,
					LatestGPS->z + LatestRadar->z + LatestIMU->z
					});
				std::cout << "Combined Location: " << Combined.x << ", " << Combined.y << "\n";
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

static void CombineThread(Location InLoc, std::mutex& m) {
	std::thread GPSThreadEx(GPSThread, InLoc, std::ref(m));
	GPSThreadEx.detach();
	//std::thread IMUThreadEx(IMUThread, m);
	//std::thread RadarThreadEX(RadarThread, m);
	//std::thread CombinedThreadEX(Combine);
}

int main()
{
	std::mutex m;
	Location InLoc = Location({ 1,1,1 });
	CombineThread(InLoc, m);
	std::cin.get();
	std::cout << "Exiting Program...";
	return 0;
}