/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LIN.c $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 01-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*	This module contains the LIN driver. It consists of an initialization of
*	the LIN controller, an error handler, and an interrupt for transmission
*	and reception.
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
 * $Log: LIN.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "LIN.h"
/*==============================================================================
* Function: TX_ISR
* 
* Description: This function is called every time a transmission interrupt is
* generated from the LINFlex controller. It implements a state machine which
* controls the response’s transmission after a valid command is received.
*
==============================================================================*/
void TX_ISR (void){
	/**/
}
/*==============================================================================
* Function: RX_ISR
* 
* Description: This function is called every time a reception interrupt is 
* generated from the LINFlex controller. It has a state machine, which controls
* the response’s reception after a valid command is received.
*
==============================================================================*/
void RX_ISR (void){
	/**/
}
/*==============================================================================
* Function: Init_LIN
* 
* Description: This function initializes the LIN controller of the board.
*
==============================================================================*/
void Init_LIN (void){
	/**/
}
/*==============================================================================
* Function: Error_handler
* 
* Description: This function handles the flags of error coming from the LIN
* controller.
*
==============================================================================*/
void Error_handler (void){
	/**/
}
