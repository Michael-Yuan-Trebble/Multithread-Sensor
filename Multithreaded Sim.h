#pragma once

#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include <mutex>
#include <optional>
#include <queue>
#include <condition_variable>
#include <fstream>
#include <string>
#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

double GPS_Noise = 0.0;
double IMU_Noise = 0.0;
double Radar_Noise = 0.0;
double GPS_Interval = 0.0;
double IMU_Interval = 0.0;
double Radar_Interval = 0.0;