//
// Created by Filip Cepiga on 12/12/2023.
// generowanie liczb losowych

#include <random>

std::random_device rd;
std::mt19937 rng(rd());

double default_probability_generator() {
    return std::generate_canonical<double, 10>(rng);
}

std::function<double()> probability_generator = default_probability_generator;