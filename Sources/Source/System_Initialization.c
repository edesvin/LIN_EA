
/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: System_Initialization.c $
 * $Revision: 1.2 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 04-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
    
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
/*                     |         LIN_EA      |         1.2                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: System_Initialization.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "System_Initialization.h"

/* Private functions */
/*============================================================================*/
void Mode_Entry(void);
/*==============================================================================
* Function: System_Init
* Description: This function calls the functions that initializes the mode +
* of operation, peripherals, and the scheduler.
*
==============================================================================*/
void System_Init(void){
	Mode_Entry();
	InitPIT();
	Init_LED();
	Init_LIN();
	Global_Init();
}
/*==============================================================================
* Function: Mode_Entry
* Description: It initializes the mode of operation.
*
==============================================================================*/
void Mode_Entry(void){
	ME.RUN[0].R = 0x001F0074;
	ME.RUNPC[0].R = 0x000000FE;
	ME.MCTL.R = 0x40005AF0;
	ME.MCTL.R = 0x4000A50F; 
}

