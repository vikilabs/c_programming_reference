/* Sample State Machine in C

 *
 *	Author:
 *		Viki (a) Vignesh Natarajan
 *		viki@vikilabs.org	
 *
 *  This code is free to use and experiment. Have Fun ;-)
 *  
 */
#include <stdio.h>
#include <stdlib.h>

/* Names Convention: 
 * [ For Global variable, datatype, enum and functions ]
 * [ Local variable can be named any way, as you wish ] 
 * [ Kindly refer to this naming convention before working on the code ]
 *
 * Naming Order: 
 * 
 * <Variable/Const/Type><DataType/Function/Pointer/Pnemonic><Pnemonic><Name>
 *
 * Example:
 *
 *		tEnSt		: type Enum State
 *		cFnStExit	: constant Function State Exit 
 *		tFpSt		: type Function Pointer State 
 *		vFpSt		: variable Function Pointer State
 *		vEnCurSte	: variable Enum Current State
 *
 *
 * Naming prefix1 reference:
 *
 *		v : variable
 *		t : datatype
 *		c : constant 
 *		a : array 
 *
 * Naming prefix2 reference:
 *
 *		En  : Enum
 *		St  : Structure
 *		In  : Integer
 *		Fl  : Float
 *		Db  : Double
 *		Cr  : Character
 *		Fn  : Function
 *		Fp  : Function Pointer
 *		Pt  : Pointer
 *		
 *	
 * Other Pnenomics:
 * 
 *		Cur : Current
 *		Nxt : Next
 *		Prv : Previous
 *		Ste : State
 *		Res : Result/Return Code
 *		Trn : Transition
 *		Tbl : Table
 *		
 */

/* Number of state and state_code_t should be in sync */
typedef enum {
	cEnSteEntry,		/* State Code 1*/
	cEnSteProcess1,
	cEnSteProcess2,
	cEnSteExit			/* State Code n*/
} tEnSte;

typedef enum{
	cEnResSuccess,
	cEnResFailure
} tEnRes;

/* Function pointer to store state function */
typedef tEnRes (*tFpSte) (void);

static tEnRes cFnSteEntry(void);
static tEnRes cFnSteExit(void);
static tEnRes cFnSteProcess1(void);
static tEnRes cFnSteProcess2(void);

/* State Transition Structure */
typedef struct{
	tEnSte  vEnCurSte;
	tEnRes  vEnCurRes;	
	tEnSte  vEnNxtSte;
}tStSteTrn;

/* Array of function pointers, Action for each states */
/* Number of aFpSte and eState_t should be in sync */
static tFpSte aFpSte[] = {
	cFnSteEntry,		/* Function Name 1*/
	cFnSteProcess1,
	cFnSteProcess2,
	cFnSteExit			/* Function Name n*/
};

/*State Transition Table*/
static tStSteTrn aStSteTrnTbl[] = {
	{cEnSteEntry,	 cEnResSuccess, cEnSteProcess1},
	{cEnSteEntry,	 cEnResFailure, cEnSteExit},
	{cEnSteProcess1, cEnResSuccess, cEnSteProcess2},
	{cEnSteProcess1, cEnResFailure, cEnSteExit},
	{cEnSteProcess2, cEnResSuccess, cEnSteExit},
	{cEnSteProcess2, cEnResFailure, cEnSteExit},
};

/* Return success or failure upon the process you choose
 */
static tEnRes cFnSteEntry(void)
{
	printf("entry state\n");
	return cEnResSuccess;
}

static tEnRes cFnSteExit(void)
{
	printf("exit state\n");
	return cEnResSuccess;
}

static tEnRes cFnSteProcess1(void)
{
	printf("process1 state\n");
	return cEnResSuccess;
}

static tEnRes cFnSteProcess2(void)
{
	printf("process2 state\n");
	return cEnResSuccess;
}

static tEnSte cFnGetNextState(tEnSte CurSte, tEnRes CurRes)
{
	tEnSte NxtSte = cEnSteExit;

	int len = sizeof(aStSteTrnTbl) / sizeof(tStSteTrn);
	
	for(int i=0; i < len; i++){
		if( (aStSteTrnTbl[i].vEnCurSte == CurSte) && 
		    (aStSteTrnTbl[i].vEnCurRes == CurRes) ){
			NxtSte  = aStSteTrnTbl[i].vEnNxtSte;
			break;
		}
	}

	return NxtSte;
}

int main()
{
	tFpSte vFpSte;
	tEnSte vEnCurSte = cEnSteEntry;
	tEnRes vEnCurRes;

	while(1){
		vFpSte	 = aFpSte[ vEnCurSte ];
		vEnCurRes = vFpSte();

		if(vEnCurSte == cEnSteExit){
			break;
		}

		/* Find the next state and set it to current state */
		vEnCurSte = cFnGetNextState(vEnCurSte, vEnCurRes);
	}
	
	return 0;
}
