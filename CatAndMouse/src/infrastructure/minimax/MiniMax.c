#include "MiniMax.h"
#include <stdio.h>
#include "stdbool.h"

struct MiniMaxResult getBestChild(
		void* state,
		unsigned int maxDepth,
		ListRef (*getChildren) (void* state),
		FreeFunc freeState,
		int (*evaluate) (void* state),
		int isMaxPlayer,
		int alpha,
		int beta) {

	struct MiniMaxResult result;
	struct MiniMaxResult childResult;
	ListRef childrenlistTemp;

	bool isFirstChild;;
	int index = 0;

	result.index = 0;
	result.value = evaluate(state);

	/*if there is a winner or depth is 0 return*/
	if (result.value == MAX_EVALUATION || result.value == MIN_EVALUATION ||
		maxDepth == 0) return result;

	// Recursion Condition
	if (maxDepth > 0) {
		--maxDepth; // Checking children in lower depth
		ListRef childrenslist = NULL;
		childrenslist = getChildren(state);
		childrenlistTemp = childrenslist;
		isFirstChild = true;

		if (isMaxPlayer) { // If it is max player
			do {
				if (headData(childrenlistTemp) != NULL) {
					int Score = getBestChild(headData(childrenlistTemp),maxDepth,
						      getChildren, freeState ,evaluate,!isMaxPlayer,
							  alpha, beta).value;
					if ( (Score > alpha) || (isFirstChild)) {
						result.index = index;
						alpha = Score;
						result.value = alpha;
						isFirstChild = false;
					}
				}
				if (beta <= alpha) break;
				index++;
				childrenlistTemp = tail(childrenlistTemp);
			} while (childrenlistTemp != NULL);

		}
		else { // If it is min player
			do {
				if (headData(childrenlistTemp) != NULL) {
					int Score = getBestChild(headData(childrenlistTemp),maxDepth,
							  getChildren, freeState ,evaluate,!isMaxPlayer,
							  alpha, beta).value;
					if  ((Score < beta) || (isFirstChild)){
						result.index = index;
						beta = Score;
						result.value = beta;
						isFirstChild = false;
					}
				}
				if (beta <= alpha) break;
				index++;
				childrenlistTemp = tail(childrenlistTemp);
			} while (childrenlistTemp != NULL);
		}

		// Free the memory of the list
		destroyList(childrenslist,freeState);
	}
	return result;
}

