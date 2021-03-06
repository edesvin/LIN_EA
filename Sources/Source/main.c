/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: main.c $
 * $Revision: 1.2 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 06-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/* Main module that runs the main function. It is divided in system's 		  */
/* initialization and execution of the scheduler. 							  */
    
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
/*                     |         LIN_EA      |         1.2                    */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: main.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "System_Initialization.h"
#include "Kernel.h"
/*============================================================================*/

void main (void){
	System_Init();
	main_Scheduler();
}
/*============================================================================*/
