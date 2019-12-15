// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
#include "patientqueue.h"

class LinkedListPatientQueue : public PatientQueue {
public:
    LinkedListPatientQueue();
    ~LinkedListPatientQueue();
    std::string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(std::string name, int priority);
    std::string processPatient();
    void upgradePatient(std::string name, int newPriority);
    std::string toString();

private:
    PatientNode* frontNode;
    void upgradePatient(std::string name, int newPriority,
                        PatientNode* &currentNode,
                        PatientNode* previous);
};
