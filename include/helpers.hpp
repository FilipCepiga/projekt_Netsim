//
// Created by Filip Cepiga on 12/12/2023.
// generator liczb losowych

#ifndef PROJEKT_NETSIM_HELPERS_HPP
#define PROJEKT_NETSIM_HELPERS_HPP

#include <functional>
#include <random>

#include "types.hpp"

extern std::random_device rd;
extern std::mt19937 rng;
extern double default_probability_generator();
extern ProbabilityGenerator probability_generator;

#endif //PROJEKT_NETSIM_HELPERS_HPP
