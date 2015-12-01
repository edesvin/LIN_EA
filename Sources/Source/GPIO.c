/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: GPIO.c $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 01-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
 *		This module handles the registers needed to configure ports and 
 * 		change state of pins.
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
/*                     |         LIN_EA      |         1.0                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: GPIO.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "GPIO.h"
/*==============================================================================
* Function: Set_Pin_State
* 
* Description: Changes the logic level of the output pin selected.
*
==============================================================================*/
void Set_Pin_State (T_UBYTE, T_UBYTE){
	/**/
}
/*==============================================================================
* Function: Set_Pin_Mode
* 
* Description: This function changes the pin mode of the selected pin to 
* the selected mode.
*
==============================================================================*/
void Set_Pin_Mode (T_UBYTE, T_UBYTE){
	/**/
}
/*==============================================================================
* Function: Get_Pin_State
* 
* Description: This function returns the state of the given pin.
*
==============================================================================*/
T_UBYTE Get_Pin_State (T_UBYTE){
	/**/
}
