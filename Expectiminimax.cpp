#include <cfloat>
#include "Expectiminimax.h"


Expectiminimax::Expectiminimax() {
    
}

Expectiminimax::~Expectiminimax(){

}

bool Expectiminimax::reset() {
    
    return true;
}

bool Expectiminimax::init() {

    return true;
}

dir_e Expectiminimax::getAction(Grid& grid, char hint) {
    Grid backup;
    backup.copy(grid);

    dir_e bestAction = (dir_e)0;
    double bestActionValue = -DBL_MAX;
    
    double value = 0.0;

    for (int i = 0; i < 4; i++) {
        grid.copy(backup);
        if(!grid.shift( (dir_e)i )) continue;

        value = minimizer(1, 1, grid, -DBL_MAX, DBL_MAX, hint);

        if(bestActionValue > value)
            bestAction = (dir_e) i;

    }
    
    return bestAction;

}

double Expectiminimax::minimizer(int depth, bool player, Grid& grid, double alpha, double beta, char hint = 0) {
    double value = DBL_MAX;

    if(isTerminate(depth, g)) 
        return evaluate(g);

    slotNumber = grid.getSlotNo();
    Grid backup;
    backup.copy(grid);

    double score = 0.0;


    if(hint == 0){
        int maxTile = grid.getMaxTile();
        if(maxTile >= 48){
            
            int num = grid.getMaxTile() / 48;
            
            for (int i = 0; i < slotNumber; i++) {
                for(int j = 1; j <= num; j++){
                    grid.setSlot(i, j*6);
                    
                    //~ score += (1.0 / num) * evaluate(myGrid);

                    score += (1.0 / num) * maximizer(depth + 1, !player, grid, alpha, beta);
                    grid.copy(backup);
                }
            }


        }else{
        
            for (int i = 0; i < slotNumber; i++) {
                for(int j = 1; j <= 3; j++){
                    grid.setSlot(i, j);
                    
                    //~ score += (1.0 / num) * evaluate(myGrid);

                    score += (1.0 / num) * maximizer(depth + 1, !player, grid, alpha, beta);
                    grid.copy(backup);
                }
            }
        }
    }else
    {
    
        if(hint == '+' )
        {
            int num = grid.getMaxTile() / 48;
            
            for (int i = 0; i < slotNumber; i++) {
                for(int j = 1; j <= num; j++){
                    grid.setSlot(i, j*6);
                    
                    //~ score += (1.0 / num) * evaluate(myGrid);

                    score += (1.0 / num) * maximizer(depth + 1, !player, grid, alpha, beta);
                    grid.copy(backup);
                }
            }


        }else
        {
            for (int i = 0; i < slotNumber; i++) {
                grid.setSlot(i, hint-'0');
                score += maximizer(depth + 1, !player, grid, alpha, beta);
                grid.copy(backup); 
            }

        }
    
    }

    value = std::min(value, score/slotNumber);
    
    
    return value;
}

double Expectiminimax::maximizer(int depth, bool player, Grid& grid, double alpha, double beta, char hint=0) {
    double value = -DBL_MAX;

    if(isTerminated(depth, grid)) evaluate(grid);

    Grid backup;
    backup.copy(grid);

    dir_e bestAction = (dir_e)0;
    double bestActionValue = -DBL_MAX;
    
    double value = 0.0;

    for (int i = 0; i < 4; i++) {
        grid.copy(backup);
        if(!grid.shift( (dir_e)i )) continue;

        value = minimizer(1, !player, grid, alpha, beta);

        if(bestActionValue > value)
            bestAction = (dir_e) i;

    }

    return bestActionValue;
}


double Expectiminimax::evaluate(Grid& grid) {


    return 0.0;
}


