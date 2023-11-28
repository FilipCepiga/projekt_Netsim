//
// Created by Filip Cepiga on 28/11/2023.
//
#ifndef PROJEKT_NETSIM_PACKAGE_H
#define PROJEKT_NETSIM_PACKAGE_H

#endif //PROJEKT_NETSIM_PACKAGE_H

class Package {
public:
    Package;
    Package();
    Package(ElementID);
    Package(Package&&);
    operator=(Package&&) : Package&;
    get_id(): ElementID {query};
    ~Package();

private:
    ElementID id_;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};
