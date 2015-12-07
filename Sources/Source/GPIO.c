/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: GPIO.c $
 * $Revision: 1.4 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 06-12-2015 $
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
/*                     |         LIN_EA      |         1.4                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: GPIO.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "GPIO.h"
/* Defines */
/*============================================================================*/
#define R_OUTPUT 	0x0200
#define R_INPUT 	0x0100
#define R_LIN_TX	0x0604
#define R_LIN_RX	0x0103
/*============================================================================*/
typedef enum{
	S_OUTPUT,
	S_INPUT,
	S_LIN_TX,
	S_LIN_RX
}PIN_MODES;
/*==============================================================================
* Function: Set_Pin_State
* 
* Description: Changes the logic level of the output pin selected.
*
==============================================================================*/
void Set_Pin_State (T_UBYTE lub_PIN, T_UBYTE lub_STATE){
	
	SIU.GPDO[lub_PIN].B.PDO = !lub_STATE;

}
/*==============================================================================
* Function: Set_Pin_Mode
* 
* Description: This function changes the pin mode of the selected pin to 
* the selected mode.
*
==============================================================================*/
void Set_Pin_Mode (T_UBYTE lub_PIN, T_UBYTE lub_MODE ){

	switch(lub_MODE){
	
		case S_OUTPUT:
			SIU.PCR[lub_PIN].R = R_OUTPUT;
			break;
			
		case S_INPUT:
			SIU.PCR[lub_PIN].R = R_INPUT;
			break;
			
		case S_LIN_TX:
			SIU.PCR[lub_PIN].R = R_LIN_TX;
			break;
			
		case S_LIN_RX:
			SIU.PCR[lub_PIN].R = R_LIN_RX;
			break;
			
		default:
			/* It shall do nothing */
			break;
			
	}
}
/*==============================================================================
* Function: Get_Pin_State
* 
* Description: This function returns the state of the given pin.
*
==============================================================================*/
T_UBYTE Get_Pin_State (T_UBYTE lub_PIN){
	
	return !SIU.GPDO[lub_PIN].B.PDO;

}
