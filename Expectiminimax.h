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
    double evaluate(Grid& g);
    double minimizer(int depth, bool player, Grid& g, double alpha, double beta, char hint);
    double maximizer(int depth, bool player, Grid& g, double alpha, double beta, char hint);
    /* data */
};


#endif /* end of include guard: EXPECTIMINIMAX_H */
