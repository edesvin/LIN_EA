/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LIN_EA.c $
 * $Revision: 1.1 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 03-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*	It is in charge of executing the main application of the program. It 
*	contains two functions, which also contain the state machines to control 
*	the LED status and the slave state.
*/
/*============================================================================*/
/* COPYRIGHT (C) CONTINENTAL AUTOMOTIVE 2014                                  */
/* AUTOMOTIVE GROUP, Interior Division, Body and Security                     */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*                                                                            */
/*============================================================================*/
/*============================================================================*/
/*                    REUSE HISTORY - taken over from                         */
/*============================================================================*/
/*  DATABASE           |        PROJECT     | FILE VERSION (AND INSTANCE)     */
/*----------------------------------------------------------------------------*/
/*                     |         LIN_EA     |         1.1                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: LIN_EA.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "LIN_EA.h"
/*============================================================================*/
extern volatile T_UBYTE rub_LEDStatus = OFF;
extern volatile T_UBYTE rub_SlaveStatus = ON;

extern volatile T_UBYTE rub_NewSlaveState = ON	;

/*============================================================================*/
T_UBYTE Led_OFF_State (T_UBYTE);
T_UBYTE Led_ON_State (T_UBYTE);
T_UBYTE Led_TOGGLING_State (T_UBYTE);

T_UBYTE Slave_FALSE_State (T_UBYTE);
T_UBYTE Slave_TRUE_State (T_UBYTE);
/*==============================================================================
* Function: Get_LED_Status
* 
* Description: This function is called every time the task 1 is executed.
* It has a state machine, which controls the response’s reception after a 
* valid command is received.
*
==============================================================================*/
void LED_status (void){
	
	static T_UBYTE rub_StaMach_LED = OFF;
	
	switch(rub_StaMach_LED){
		
		case OFF:
			
			rub_StaMach_LED = Led_OFF_State(rub_StaMach_LED);
			break;
		
		case ON:
			
			rub_StaMach_LED = Led_ON_State(rub_StaMach_LED);
			break;
		
		case TOGGLING:
			
			rub_StaMach_LED = Led_TOGGLING_State(rub_StaMach_LED);
			break;
		
		default:
			/* Do nothing	*/
			break;
	}
}
/*==============================================================================
* Function: Get_LED_Status
* 
* Description: This function is executed every 20 milliseconds in the task 0.
* It has a state machine, which controls the response’s reception after a valid
* command is received.
*
==============================================================================*/
void Set_SlaveState (void){
	
	static T_UBYTE rub_StaMach_SLAVE = ON;
	
	switch (rub_StaMach_SLAVE) {
	
		case FALSE:
			
			rub_StaMach_SLAVE = Slave_FALSE_State(rub_StaMach_SLAVE);
			
			break;
			
		case TRUE:
			
			rub_StaMach_SLAVE = Slave_TRUE_State(rub_StaMach_SLAVE);
					
			break;	
		
		default:
			/* Do nothing	*/
			break;
	}
}

/*==============================================================================
* Function: Led_OFF_State
* 
* Description: 
*
==============================================================================*/

T_UBYTE Led_OFF_State (T_UBYTE lub_StaMach_LED){
	
	T_UBYTE varStatus = 0;
	
	if(rub_LEDStatus == OFF){
				
		Set_LED_Status(OFF);
	}
	
	else if(rub_LEDStatus == ON){
	
		lub_StaMach_LED = ON;
		Set_LED_Status(ON);
	}
	
	else if(rub_LEDStatus == TOGGLING){
		
		lub_StaMach_LED = TOGGLING;
		varStatus = Get_LED_Status();
		Set_LED_Status(!varStatus);
	}
	
	else{
		/* Do nothing	*/
	}
	
	return lub_StaMach_LED;
}
/*==============================================================================
* Function: Led_ON_State
* 
* Description: 
*
==============================================================================*/
T_UBYTE Led_ON_State (T_UBYTE lub_StaMach_LED){
	
	T_UBYTE varStatus = 0;
	
	if(rub_LEDStatus == ON){
				
		Set_LED_Status(ON);
	}
	
	else if(rub_LEDStatus == OFF){
	
		lub_StaMach_LED = OFF;
		Set_LED_Status(OFF);
	}
	
	else if(rub_LEDStatus == TOGGLING){
		
		lub_StaMach_LED = TOGGLING;
		varStatus = Get_LED_Status();
		Set_LED_Status(!varStatus);
	}
			
	else{
		/* Do nothing	*/
	}
	
	return lub_StaMach_LED;
}
/*==============================================================================
* Function: Led_TOGGLING_State
* 
* Description: 
*
==============================================================================*/
T_UBYTE Led_TOGGLING_State (T_UBYTE lub_StaMach_LED){
	T_UBYTE varStatus = 0;
	
	if(rub_LEDStatus == TOGGLING){

		varStatus = Get_LED_Status();
		Set_LED_Status(!varStatus);
	}

	else if(rub_LEDStatus == OFF){
		
		lub_StaMach_LED = OFF;
		Set_LED_Status(OFF);
	}
	
	else if(rub_LEDStatus == ON){
	
		lub_StaMach_LED = ON;
		Set_LED_Status(ON);
	}

	else{
		/* Do nothing	*/
	}
	
	return lub_StaMach_LED;
}
/*==============================================================================
* Function: Slave_FALSE_State
* 
* Description: 
*
==============================================================================*/
T_UBYTE Slave_FALSE_State (T_UBYTE lub_StaMach_SLAVE){
	if(rub_NewSlaveState == FALSE){
		
		rub_SlaveStatus = FALSE;
	}
	
	else if(rub_SlaveStatus == TRUE){
	
		lub_StaMach_SLAVE = TRUE;
		rub_SlaveStatus = TRUE;
	}
	
	else{
		/* Do nothing	*/
	}
}
/*==============================================================================
* Function: Slave_TRUE_State
* 
* Description: 
*
==============================================================================*/
T_UBYTE Slave_TRUE_State (T_UBYTE lub_StaMach_SLAVE){
	if(rub_NewSlaveState == TRUE){
		
		rub_SlaveStatus = TRUE;
	}
	
	else if(rub_SlaveStatus == FALSE){
	
		lub_StaMach_SLAVE = FALSE;
		rub_SlaveStatus = FALSE;
	}
	
	else{
		/* Do nothing	*/
	}
}
