
#include "LinkedListPatientQueue.h"
#include "strlib.h"

LinkedListPatientQueue::LinkedListPatientQueue() {
    frontNode = nullptr;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    clear();
}

void LinkedListPatientQueue::clear() {
    while (frontNode) {
        PatientNode*  next = frontNode->next;
        delete frontNode;
        frontNode = next;
    }
}

std::string LinkedListPatientQueue::frontName() {
    if (!frontNode) {
        throw std::string("Queue must be non-empty to obtain highest priority "
                          "patient");
    } else return frontNode->name;
}

int LinkedListPatientQueue::frontPriority() {
    if (!frontNode) {
        throw std::string("Queue must be non-empty to obtain highest priority "
                          "patient");
    } else return frontNode->priority;
}

bool LinkedListPatientQueue::isEmpty() {
    return frontNode == nullptr;
}


void LinkedListPatientQueue::newPatient(std::string name, int priority) {

    PatientNode* thisNode = new PatientNode(name, priority);
    if (isEmpty()) { //frontnode empty
        thisNode->next = frontNode;
        frontNode = thisNode;
    } else if (!frontNode->next) { // One element
        if (priority < frontNode->priority) {// new patient higher priority
            thisNode->next = frontNode;
            frontNode = thisNode;
        } else {
            thisNode->next = frontNode->next; // gets null
            frontNode->next = thisNode;
        }
    } else {// more than one element
//        bool addToFront = false;
//        PatientNode* temp = frontNode;
//        while(temp->next && (temp->next)->priority > priority && !addToFront) {
//            if (temp->priority > priority) addToFront = true;
//            else temp = temp->next;
//        }
//        if (addToFront) {
//          thisNode->next = temp;
//          frontNode = thisNode;
//        } else if (!temp->next) temp->next = thisNode;
//        else {
//            thisNode->next = temp->next;
//            temp->next = thisNode;
//        }
        PatientNode* temp; // maintain frontNode, make a temp pointer
        for(temp = frontNode; temp->next; temp = temp->next) {
            if (priority > temp->priority) {
                if (priority > (temp->next)->priority) continue;
                else if (priority < (temp->next)->priority){
                    thisNode->next = temp->next;
                    temp->next = thisNode;
                    break;
                } else {
                    continue;
                }

            } else if (priority < temp->priority) {
                thisNode->next = temp;
                //frontNode?? Why note temp?
                frontNode = thisNode;
                break;
            } else {
                if (priority > (temp->next)->priority) continue;
                else if (priority < (temp->next)->priority){
                    thisNode->next = temp->next;
                    temp->next = thisNode;
                    break;
                } else continue;
            }
        }
        // If we reached the end, place thisNode at the end!
        if (!temp->next) {
            temp->next = thisNode;
        }

    }
}\

std::string LinkedListPatientQueue::processPatient() {
    if (!frontNode) {
        throw std::string("There are no patients to process!");
    } else {
        PatientNode* temp = frontNode;
        if (frontNode->next) frontNode = frontNode->next;
        else frontNode = nullptr;
        return temp->name;
//        std::string frontName = frontNode->name;
//        PatientNode*  next = frontNode->next;
//        delete frontNode;
//        frontNode = next;
//        return frontName;
    }
}

void LinkedListPatientQueue::upgradePatient(std::string name, int newPriority) {
    if (isEmpty()) throw std::string("There are no patients to upgrade!");
    else if (!frontNode->next){ // One patient in queue
        if (frontNode->name == name) {
            if (frontNode->priority < newPriority) {
                throw std::string("The new priority is greater than or "
                                  "equal to the current priority");
            } else {
                // No need to do anything else but update the current node's
                // priority because this node is only node in list!
                frontNode->priority = newPriority;
            }
        } else throw std::string("There are no patients with the given name "
                                 "in the list.");
    } else { // More than one patient in the list
        // initialize our "marker" to the front of the list
        PatientNode* current = frontNode;
        // Flag for (unrealistic case) when we want to update priority of
        // first person in lis
        bool modifyFront = false;
        while (current->next && (current->next)->name != name && !modifyFront) {
            // Only occurs when current == frontNode (as far as I know)
            if (current->name == name) {
                modifyFront = true;
            } else current = current->next;
        }
        if (!current->next) {
            throw std::string("There is no patient with that name");
        } else { //Either modifyFront == true, or found patient in middle
            // If found patient at front, no need fiddling with links
            // Just check for lower new priority and alter, or throw exception.
            if (modifyFront) {
                if (current->priority < newPriority) {
                    throw std::string("The new priority is greater than or "
                                      "equal to the current priority");
                } else current->priority = newPriority;
            } else {
                // Otherwise we have to fiddle with links, "re-add" the patient
                // to the list, then delete the current node, which is a copy
                // of the new patient added.
                PatientNode* toModify = current->next;
                if (toModify->priority < newPriority) {
                    throw std::string("The new priority is greater than or "
                                      "equal to the current priority");
                } else {
                    // Make "previous" to "toModify" link with toModify->next
                    // then reintroduce the node "toModify" with new priority
                    // in the correct location, then delete the original
                    // "copy" of toModify.
                    current->next = toModify->next;
                    newPatient(name, newPriority);
                    delete toModify;
                }
            }
        }
    }
}

std::string LinkedListPatientQueue::toString() {
    std::string output = "{";
    PatientNode* temp = frontNode;
    while (temp) {
        output += integerToString(temp->priority) + ":" +
                temp->name + ", ";
        temp = temp->next;
    }

    if (output.length() > 2) {
        output = output.substr(0, output.length()-2);
    }
    output += "}";
    return output;
}
