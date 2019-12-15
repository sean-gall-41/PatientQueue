/*
 * File: VectorPatientQueue
 * ------------------------
 * The implementation of the vector priority list.
 * <bits/stdc++> included to obtain INT_MAX, which is utilized in
 * upgradePatient as below.
 *
 * This file also "implements" the VectorPatientNode struct constructor, which
 * is straightforward.
 *
 * @author Sean Gallogly
 * @version 2019/07/08
 */

#include "VectorPatientQueue.h"
#include "strlib.h"
#include <bits/stdc++.h> // For INT_MAX

/* Method: VectorPatientNode (constructor)
 *
 * Params:
 *
 *  std::string name - the name of the patient to be added
 *  int priority - the priority of the patient to be added
 *  int timestamp - the current timestamp
 *
 * usage: myVector.add(VectorPatientNode("Sean", 1, incrementCounter());
 *
 */

VectorPatientNode::VectorPatientNode(std::string name,
                                     int priority, int timestamp) {
    nameAsGiven = name;
    nameToLower = toLowerCase(name);
    this->priority = priority;
    this->timestamp = timestamp;
}

//std::ostream& operator <<(std::ostream& out,
//                          const VectorPatientNode& vectorNode) {
//    return out << vectorNode.priority << ":" << vectorNode.nameAsGiven;
//}

VectorPatientQueue::VectorPatientQueue() {
    priorityQueue = Vector<VectorPatientNode>();
    counter = 0;
}

/* Method VectorPatientQueue (Destructor)
 * --------------------------------------
 * Nothing needs to be done here as we have not allocated memory from the
 * heap, at least not in this class directly.
 *
 */

VectorPatientQueue::~VectorPatientQueue() {}

/*
 * Method: clear
 *
 * Implementation Notes:
 * ---------------------
 * Calls the corresponding method from general vector object
 *
 */

void VectorPatientQueue::clear() {
    priorityQueue.clear();
}

/*
 * Method: frontName
 *
 * Implementation Notes:
 * ---------------------
 * Leverages above topPatientIndex method to select the top patient from the
 * list and that patient's name.
 *
 */

std::string VectorPatientQueue::frontName() {
    return priorityQueue[frontNodeIndex()].nameAsGiven;
}

/*
 * Method: frontPriority
 *
 * Implementation Notes:
 * ---------------------
 * Leverages above topPatientIndex method to select the top patient from the
 * list and that patient's priority.
 *
 */

int VectorPatientQueue::frontPriority() {
    return priorityQueue[frontNodeIndex()].priority;
}

/*
 * Method isEmpty
 *
 * Implementation Notes:
 * ---------------------
 * Calls the corresponding function for the general vector object.
 *
 */

bool VectorPatientQueue::isEmpty() {
    return priorityQueue.isEmpty();
}

/*
 * Method: newPatient
 *
 * Implementation Notes:
 * ---------------------
 * Initializes a new VectorPatientNode object with the given name and priority,
 * then adds that patient to the queue.
 *
 * Notice that the timestamp is incremented only after we add this patient,
 * so the very first patient will have an associated timestamp of 0.
 *
 */

void VectorPatientQueue::newPatient(std::string name, int priority) {
    VectorPatientNode newPatient = VectorPatientNode(name, priority,
                                                     getTimeStamp());
    priorityQueue.push_back(newPatient);
    incrementCounter();
}

/*
 * Method: processPatient
 *
 * Implementation Notes:
 * ---------------------
 * Obtains the top patient index, then obtains the name associated with that
 * index, removes the patient at the top index, then returns the top patient's
 * name. Runs in O(N) time, though would like to eliminate the need for
 * running through the queue twice.
 *
 */

std::string VectorPatientQueue::processPatient() {
    if (isEmpty()) {
        throw std::string("There are no patients to process!");
    } else {
        int topPatientIndex = frontNodeIndex(); //O(N)
        std::string topPatientName = priorityQueue[topPatientIndex].nameAsGiven;
        priorityQueue.remove(topPatientIndex); //O(N)
        return topPatientName;
    }
}

/*
 * Method: upgradePatient
 *
 * Implementation Notes:
 * ---------------------
 * The highestPriority kind of works like a greatest lower bound: if the
 * argument name exists in our queue and there are multiple instances of it in
 * the queue then we updte the priority whenever we find an instance of this
 * name with a smaller priority than an instance we have already checked. Thus,
 * if we had initialized highestPriority to a value lower than any possible
 * priority (we assume all priorities are greater than zero) we would never
 * update the value of highestPriority!
 *
 */

void VectorPatientQueue::upgradePatient(std::string name, int newPriority) {
    int thisPatientIndex = -1;
    int highestPriority = INT_MAX;
    for (int i = 0; i < priorityQueue.size(); i++) {
        if (priorityQueue[i].nameAsGiven == name) {
            if (priorityQueue[i].priority < newPriority) {
                throw std::string("This patient already has a priority "
                                  "greater than that entered.");
            } else if (priorityQueue[i].priority == newPriority) {
                throw std::string("This patient already has the given priority!");
            } else {
                if (priorityQueue[i].priority < highestPriority) {
                    thisPatientIndex = i;
                    highestPriority = priorityQueue[thisPatientIndex].priority;
                }
            }
        }
    }
    if (thisPatientIndex == -1) {
        throw std::string("The person given is not in the current queue.");
    } else {
        priorityQueue[thisPatientIndex].priority = newPriority;
    }
}

/*
 * Method toString
 *
 * Implementation Notes:
 * ---------------------
 * Simply loops through the queue using a gneralized for each loop, then
 * removes the last ", " left over from the last element of the list. Finally,
 * appends a " }" onto the outgoing string variable.
 *
 */
std::string VectorPatientQueue::toString() {
    std::string output = "{";
    for (VectorPatientNode node : priorityQueue) {
        output += integerToString(node.priority) + ":" + node.nameAsGiven + ", ";
    }
    if (output.length() > 2) {
        output = output.substr(0, output.length()-2);
    }
    output += "}";
    return output;
}

/*
 * Method: frontNodeIndex
 *
 * Implementation Notes
 * ------------------------------------------------
 * conducts some common sense checks: clearly, cannot return the top priority
 * patient index if the queue is empty, and also if somehow two patients
 * have the same time stamp, which should be impossible, if coded correctly.
 *
 * initializes the top priority, top time stamp, and top index from the first
 * element of the list, then loops through the rest of the list in order to
 * determine which (if any) patients have a higher priority. Ties of priority
 * are broken by ordering of time stamps. For each newly found "top" priority
 * patient the top priority and top index are saved, for later checks as well
 * as for the eventual return statement.
 *
 */

int VectorPatientQueue::frontNodeIndex() {
    if (isEmpty()) {
        throw std::string("Queue must be non-empty to obtain highest priority "
                          "patient");
    } else {
        int topPriority = priorityQueue[0].priority;
        int topTimeStamp = priorityQueue[0].timestamp;
        int topIndex = 0;

        for (int i = 1; i < priorityQueue.size(); i++) {
            int currentPriority = priorityQueue[i].priority;
            if (currentPriority < topPriority) {
                topPriority = currentPriority;
                topIndex = i;
            } else if (currentPriority == topPriority) {
                int currentTimeStamp = priorityQueue[i].timestamp;
                if (currentTimeStamp < topTimeStamp) {
                    topTimeStamp = currentTimeStamp;
                    topIndex = i;
                } else if (currentTimeStamp == topTimeStamp) {
                    throw std::string("This is impossible, but here for"
                                      "debugging purposes.");
                }
            }
        }
        return topIndex;
    }
}

void VectorPatientQueue::incrementCounter() {
    counter++;
}

int VectorPatientQueue::getTimeStamp() {
    return counter;
}
