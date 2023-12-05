//
// Created by Filip Cepiga on 28/11/2023.
//

#ifndef PROJEKT_NETSIM_TYPES_H
#define PROJEKT_NETSIM_TYPES_H

#include <functional>

using ElementID = unsigned long long;

using TimeOffset = unsigned long long;

using Time = unsigned long long;

using ProbabilityGenerator = std::function<double()>;

#endif //PROJEKT_NETSIM_TYPES_H

