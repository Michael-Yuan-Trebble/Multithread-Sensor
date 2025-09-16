# Multithread-Sensor

## A Multithreaded Sensor Reader in C++ using CMake

I built this project to teach myself multithreading in C++ and exporting CSV files in C++. My goals for this project are to gain experience in:
- Implementing threads and handling them safely
- Integrate variability in a C++ program
- Create and then analyze data contained in the CSV

## Features

Currently, the location data is hardcoded, something I will change in the future, numerics for the randomness and timer values are also not indictive of what the sensors should be.
The sensors are as follows:
- GPS
- Radar
- IMU
All sensor readings, including the combined of all three, are written into a CSV.

## Tech Stack

- C++ 17
- CMake 3.8

## Future Plans

In the future I plan to add a Python program that takes in the CSV data and plots it onto a graph via Mathplotlib.
For the C++ program itself, I also plan to refine the variability and sensor timings to create a more realistic set of data.
I also plan to be able to let the user input a location instead of hardcoding it
