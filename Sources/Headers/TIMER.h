/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: TIMER.h $
 * $Revision: 1.3 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 04-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*	This file contains the configurations that must be done to achieve the 
*	periodic interrupt that gives the Ticks to the scheduler.
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
/*                     |         LIN_EA     |           1.3                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: TIMER.h  $
  ============================================================================*/
#ifndef TIMER_H_
#define TIMER_H_
/* Includes */
/*============================================================================*/
#include "IntcInterrupts.h"

#include "Kernel.h"

/* Public functions */
/*============================================================================*/
void InitPIT (void);

#endif /* TIMER_H_ */
