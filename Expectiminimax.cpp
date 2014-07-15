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

int DEPTH = 2;

dir_e Expectiminimax::getAction(Grid& grid, char hint) {
    Grid backup;
    backup.copy(grid);
    
    //std::cout << std::endl;

    dir_e bestAction = (dir_e)0;
    double bestActionValue = -DBL_MAX;
    
    double value = -DBL_MAX;

    for (int i = 0; i < 4; i++) {
        grid.copy(backup);
        if(!grid.shift( (dir_e)i )) continue;

        value = minimizer(DEPTH, 1, grid, -DBL_MAX, DBL_MAX, hint);
        //std::cout << "Dir(" << (dir_e)i << "), value: " << value << std::endl;

        if(bestActionValue < value){
            bestAction = (dir_e) i;
            bestActionValue = value; 
        }


    }

    grid.copy(backup);
    //std::cout << "Dir: " << bestAction << std::endl;    
    return bestAction;

}

double Expectiminimax::minimizer(int depth, bool player, Grid& grid, double alpha, double beta, char hint ) {
    double value = DBL_MAX;
    //std::cout << "minimizer" << std::endl;
    if(isTerminated(depth, grid)) 
        return evaluate(grid);

    int slotNumber = grid.getSlotNo();
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
                    
                    //~ score += (1.0 / num) * evaluate(grid);

                    score += (1.0 / num) * maximizer(depth - 1, !player, grid, alpha, beta);
                    grid.copy(backup);
                }
            }


        }else{
        
            for (int i = 0; i < slotNumber; i++) {
                for(int j = 1; j <= 3; j++){
                    grid.setSlot(i, j);
                    
                    //~ score += (1.0 / num) * evaluate(grid);

                    score += (1.0 / 3.0) * maximizer(depth - 1, !player, grid, alpha, beta);
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
                    
                    //~ score += (1.0 / num) * evaluate(grid);

                    score += (1.0 / num) * maximizer(depth - 1, !player, grid, alpha, beta);
                    grid.copy(backup);
                }
            }


        }else
        {
            for (int i = 0; i < slotNumber; i++) {
                grid.setSlot(i, hint-'0');
                score += maximizer(depth - 1, !player, grid, alpha, beta);
                grid.copy(backup); 
            }

        }
    
    }

    value = std::min(value, score/slotNumber);
    
    
    return value;
}

double Expectiminimax::maximizer(int depth, bool player, Grid& grid, double alpha, double beta, char hint) {
    double value = -DBL_MAX;
    //std::cout << "maximizer" << std::endl;
    if(isTerminated(depth, grid)) 
        return evaluate(grid);

    Grid backup;
    backup.copy(grid);

    dir_e bestAction = (dir_e)0;
    double bestActionValue = -DBL_MAX;
    

    for (int i = 0; i < 4; i++) {
        grid.copy(backup);
        if(!grid.shift( (dir_e)i )) continue;

        value = minimizer(depth - 1, !player, grid, alpha, beta);

        if(bestActionValue < value)
            bestAction = (dir_e) i;
            bestActionValue = value;

    }

    return bestActionValue;
}


double Expectiminimax::evaluate(Grid& grid) {
    double maxWeight = 1.0;
    double emptyWeight = 1.0;
    
    double value =
        //smoothness()*smmothweight + 
        //monotonicity()*monoWeight + 
        grid.getMaxTile() * maxWeight + 
        grid.getEmptyBlkNo() * emptyWeight; 

    return value;
}


bool Expectiminimax::isTerminated(int depth, Grid& grid) {
    ////std::cout << depth << std::endl;
	if(depth == 0)
		return true;

	Grid backup;
	backup.copy(grid);
	bool left = grid.shift(LEFT); grid.copy(backup);
	bool up = grid.shift(UP); grid.copy(backup);
	bool down = grid.shift(DOWN); grid.copy(backup);
	bool right  = grid.shift(RIGHT); 
	grid.copy(backup);
	if(left || down || right || up){
		return false;
	}

	return true;
}

