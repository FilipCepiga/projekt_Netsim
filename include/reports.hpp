//
// Created by Filip Cepiga on 02/01/2024.
//

#ifndef PROJEKT_NETSIM_REPORTS_HPP
#define PROJEKT_NETSIM_REPORTS_HPP

#include "factory.hpp"

void generate_structure_report(const Factory& f, std::ostream& os);
void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time t);


#endif //PROJEKT_NETSIM_REPORTS_HPP


