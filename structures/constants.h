#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

const int DIFFICULTY = 4;       // Número de ceros iniciales requeridos en el hash
const string HashGenesis(64, '0');

const int maxColision = 3;
const float maxFillFactor = 0.5;
const int capacityHeapDEF = 30;
const int capacityHashDEF = 10;

#endif