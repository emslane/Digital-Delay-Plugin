/*
  ==============================================================================

    DSP.h
    Created: 19 Dec 2025 8:00:34pm
    Author:  ersla

  ==============================================================================
*/

#pragma once

#include <cmath>

inline void panningEqualPower(float panning, float& left, float& right) { //inline is needed cuz writing complete code of a function in a header file
    float x = 0.7853981633974483f * (panning + 1.0f); //big num is pi/4
    left = std::cos(x);
    right = std::sin(x);
}