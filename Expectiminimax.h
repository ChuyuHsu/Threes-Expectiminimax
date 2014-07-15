#ifndef EXPECTIMINIMAX_H

#define EXPECTIMINIMAX_H

#include "GameAgent.h"


class Expectiminimax : public GameAgent
{
public:
    Expectiminimax();
    ~Expectiminimax();

    bool reset();
    bool init();
    dir_e getAction(Grid&, char); 
private:
    double evaluate(Grid& g);
    double minimizer(int depth, bool player, Grid& g, double alpha, double beta, char hint=0);
    double maximizer(int depth, bool player, Grid& g, double alpha, double beta, char hint=0);
    
    bool isTerminated(int, Grid&);
    /* data */
};


#endif /* end of include guard: EXPECTIMINIMAX_H */
