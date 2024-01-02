//
// Created by Filip Cepiga on 02/01/2024.
//

#ifndef PROJEKT_NETSIM_SIMULATION_HPP
#define PROJEKT_NETSIM_SIMULATION_HPP

#include "factory.hpp"

class IntervalReportNotifier {
public:
    IntervalReportNotifier(TimeOffset to) : to_(to) {}
    bool should_generate_report(Time t) { return  to_ != 1 ? t % to_ == 1 : true; }
private:
    TimeOffset to_;
};

class SpecificTurnsReportNotifier {
public:
    SpecificTurnsReportNotifier(std::set<Time> turns) : turns_(turns) {}
    bool should_generate_report(Time t) { return turns_.find(t) != turns_.end(); }
private:
    std::set<Time> turns_;
};

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf);

#endif //PROJEKT_NETSIM_SIMULATION_HPP
