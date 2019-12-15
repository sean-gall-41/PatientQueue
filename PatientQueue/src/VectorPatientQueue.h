/*
 * File: VectorPatientQueue.h
 * --------------------------
 * This file serves to define the VectorPatientQueue class as well as the
 * VectorPatientNode struct. Both are used in conjucntion to implement a
 * priority queue.
 *
 *
 * @author Sean Gallogly
 * @version 2019/07/08
 */

#pragma once

#include <iostream>
#include <string>
#include "patientqueue.h"
#include "vector.h"

/*
 * struct: VectorPatientNode
 * -------------------------
 * A struct which contains variables facillitating implementation of priority
 * list utilizing a vector. The idea is that each struct contains all the
 * relevant patient information, so the implementation of priority list
 * using a vector amounts to creating a vector of such structs.
 *
 * Two strings representing the name of the given patient in slightly different
 * ways: this is to prevent extraneous calling of toLowerCase function in the
 * implementation.
 *
 */

struct VectorPatientNode {
    std::string nameAsGiven;
    std::string nameToLower;
    int priority;
    int timestamp;

    VectorPatientNode(std::string name = "", int priority = 0,
                      int timestamp = 0);
};

//std::ostream& operator <<(std::ostream& out, const VectorPatientNode& vectorNode);

/*
 * Class: VectorPatientQueue extends PatientQueue
 * ----------------------------------------------
 * A class representing a priority list of patients, which themselves are
 * represented by VectorPatientNode structs. Private attribute frontNodeIndex
 * is included to trivialize the frontPriority and frontName methods, and to
 * eliminate redundant code. Private attributes incrememntCounter and
 * getTimeStamp are included to get and set the current time stamp, an
 * abstraction helping to break ties of priority in this implementation of the
 * priority list
 *
 */

class VectorPatientQueue : public PatientQueue {
public:

    /*
     * Method: VectorPatientQueue (constructor)
     *
     * Usage: thisPatientQueue = VectorPatientQueue(); OR
     *        VectorPatientQueue myQueue;
     *
     */

    VectorPatientQueue();

    ~VectorPatientQueue();

    /*
     * Method: clear
     *
     * Usage: myQueue.clear();
     * -----------------------
     * Clears the current queue of all patients, setting its size to 0
     *
     */

    void clear();

    /*
     * Method: frontName
     *
     * Returns: the name of the top priority patient
     *
     * Usage: std::string urgentPatientName = myQueue.frontName();
     *
     */

    std::string frontName();

    /*
     * Method: frontPriority
     *
     * Returns: the priority of the top priority patient
     *
     * Usage: int urgentPatientPriority = myQueue.frontPriority();
     *
     */

    int frontPriority();

    /*
     * Method isEmpty
     *
     * Returns: true if caller instance is empty, else false
     *
     * Usage: if (myQueue.isEmpty());
     *
     */

    bool isEmpty();

    /*
     * Method: newPatient
     *
     * Params:
     *
     *  std::string name - name of the patient to be added to the queue
     *  int priority - the priority assigned to the patient to be added to
     *                 queue
     *
     * Usage: myQueue.newPatient(newPatientName, newPatientPriority);
     *
     */

    void newPatient(std::string name, int priority);

    /*
     * Method: processPatient
     *
     * Throws: std::string if the queue is empty.
     *
     * Returns: the name of the top priority patient if the queue is nonempty
     *
     * Usage: std::string processedName = myQueue.processPatient();
     * ------------------------------------------------------------
     * This method, in addition to returning the name of the top priority
     * patient, also removes that patient from the queue.
     *
     */

    std::string processPatient();

    /*
     * Method: upgradePatient
     *
     * Params:
     *
     *  std::string name - name of patient we wish to upgrade
     *  int newPriority - the priiority we wish to upgrade the patient to
     *
     * Throws: std::string if either the patient to be upgraded already has a
     *         higher priority than that we wish to upgrade it to OR if the
     *         requested patient does not exist in the current queue.
     *
     * Usage: myQueue.upgradePatient("Steve", 3);
     * ------------------------------------------
     * "Upgrades" the patient given if that patient exists in the queue to
     * the priority given, if the given priority is higher than the patient's
     * current priority
     *
     */

    void upgradePatient(std::string name, int newPriority);

    /*
     * Method toString
     *
     * Returns: a string representation of the current priority list
     *
     * Usage: std::cout << myQueue.toString();
     *
     */

    std::string toString();

private:

    Vector<VectorPatientNode> priorityQueue;

    /*
     * Method: frontNodeIndex
     *
     * Throws: std::string if either the queue calling the method is empty or
     *         two patients have the same time stamp (for debugging)
     *
     * Returns: the index of the top priority patient in the queue
     *
     * Usage: int bestIndex = myQueue.frontNodeIndex();
     *
     */

    int frontNodeIndex();
    int counter;

    /*
     * Method: incrementCounter
     *
     * Usage: myQueue.incrementCounter();
     *
     */

    void incrementCounter();

    /*
     * Method: getTimeStamp
     *
     * Returns: an int representing the current "time"
     *
     * Usage: int currentTime = myQueue.getTimeStamp();
     *
     */

    int getTimeStamp();

};
