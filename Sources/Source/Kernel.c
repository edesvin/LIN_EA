/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Kernel.c $
 * $Revision: 1.2 $
 * $Author:		Edgar Escayola Vinagre	$
 *		 		Adrian Zacarias Siete	$
 *			
 * $Date: 04-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
    This file contains the main implementation of the scheduler.
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
/*                     |           LIN_EA   |           1.2                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: Kernel.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/

#include "Kernel.h"

/* Exported Variables */
/*============================================================================*/
extern const S_STAT cas_STAT[E_TSK_N_OF];
extern volatile T_UWORD raub_DynConuter[E_TSK_N_OF];

/* Private Variables */
/*============================================================================*/
static volatile T_UBYTE rub_Tick_Flag = 0;
/*==============================================================================
* Function: ISR_Tick
* 
* Description: This function is the one that handles the clock Ticks in order to 
* trigger the tasks. This interrupt runs periodically every millisecond according 
* to the configuration of the PIT.
*
==============================================================================*/
void Tick_ISR(void){

	rub_Tick_Flag = 1;
	PIT.CH[0].TFLG.B.TIF = 1;

}
/*============================================================================*/
void main_Scheduler(void){

	T_UWORD luw_i;

	while(1){

		if(rub_Tick_Flag){
			
			rub_Tick_Flag = 0;

			for(luw_i = 0; luw_i < E_TSK_N_OF; luw_i++){
				
				if(raub_DynConuter[luw_i] > 0){
					
					raub_DynConuter[luw_i]--;
					
				}else{
					
					raub_DynConuter[luw_i] = cas_STAT[luw_i].uw_T - 1;
					(cas_STAT[luw_i].F_Pointer)();
					
				}
				
			}

		}
		
	}

}
