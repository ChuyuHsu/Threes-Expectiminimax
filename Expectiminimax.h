#ifndef EXPECTIMINIMAX_H

#define EXPECTIMINIMAX_H

#include "GameAgent.h"

class Expectiminimax
{
public:
    Expectiminimax();
    ~Expectiminimax();

    bool reset();
    bool init();
    dir_e getAction(Grid&, char); 
private:
    /* data */
};


#endif /* end of include guard: EXPECTIMINIMAX_H */
