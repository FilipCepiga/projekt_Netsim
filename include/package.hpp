//
// Created by Filip Cepiga on 5/12/2023.
//
#ifndef PROJEKT_NETSIM_PACKAGE_H
#define PROJEKT_NETSIM_PACKAGE_H

#include "types.hpp"
#include <set>


class Package {
public:
    Package();
    explicit Package(ElementID ID) : ID_(ID) { assigned_IDs.insert(ID_); }
    Package(Package &&package)  noexcept : ID_(package.ID_) {}
    Package &operator=(Package &&package) noexcept ;
    ElementID get_id() const { return ID_; }
    ~Package();

private:
    ElementID ID_;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif //PROJEKT_NETSIM_PACKAGE_H
