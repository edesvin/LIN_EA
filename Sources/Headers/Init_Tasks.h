/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Init_Tasks.h $
 * $Revision: 1.2 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 03-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
		This file contains the type definitions and the prototypes for the 
		functions used to initialize the software.
	
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
/*                     |         LIN_EA     |           1.2                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: Init_Tasks.h  $
  ============================================================================*/
#ifndef INIT_TASKS_H_
#define INIT_TASKS_H_
/* Includes */
/*============================================================================*/
#include "TASKS.h"
/* Constants and types */
/*============================================================================*/
typedef enum{
	
	E_TSK_TASK0,
	E_TSK_TASK1,
	
	/*Write here your new tasks*/
	
	E_TSK_N_OF
	
}E_TASKS;
/*============================================================================*/
typedef struct{
	
	void(*F_Pointer)(void);		/*	Function Pointer	*/	
	T_UWORD uw_T;				/* 	Period				*/
	T_UWORD uw_Offset;			/*	Offset				*/
	
}S_STAT;

/* Public functions */
/*============================================================================*/
extern void Global_Init(void);

#endif /* INIT_TASKS_H_ */
