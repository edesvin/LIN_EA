/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LIN_EA.c $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 01-12-2015 $
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
/*                     |         LIN_EA     |         1.0                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: LIN_EA.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "LIN_EA.h"
/*==============================================================================
* Function: Get_LED_Status
* 
* Description: This function is called every time the task 1 is executed.
* It has a state machine, which controls the response�s reception after a 
* valid command is received.
*
==============================================================================*/
void LED_status (void){
	/**/
}
/*==============================================================================
* Function: Get_LED_Status
* 
* Description: This function is executed every 20 milliseconds in the task 0.
* It has a state machine, which controls the response�s reception after a valid
* command is received.
*
==============================================================================*/
void Set_SlaveState (T_UBYTE){
	/**/
}
