#ifndef INTERNODECOM_LIBRARY_H
#define INTERNODECOM_LIBRARY_H

#include <physical_interface/Physical.h>

class Backend{

public:
    Physical * physical;
    //TODO: protocol data link - this should be something like HDLC, Ethernet/IP, ...
    //TODO: protocol Network - this should be accumodate things like, TCP,
};

class Core{

};

class Frontend{

};

#endif //INTERNODECOM_LIBRARY_H
