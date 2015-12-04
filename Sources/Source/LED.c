/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LED.c $
 * $Revision: 1.1 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 02-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*		This module configures and handles the state of the LED.
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
 * $Log: LED.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "LED.h"
/* Defines */
/*============================================================================*/
#define OUTPUT 	0
#define	LED_PIN	68
#define OFF 	0
#define ON 		1
/*==============================================================================
* Function: Init_LED
* 
* Description: This function initializes the pin used for the LED.
*
==============================================================================*/
void Init_LED (void){
	
	Set_Pin_Mode(LED_PIN, OUTPUT);
	Set_Pin_State(LED_PIN, OFF);
	
}
/*==============================================================================
* Function: Get_LED_Status
* 
* Description: This function returns the state of the LED.
* 
*
==============================================================================*/
T_UBYTE Get_LED_Status ( void ) {

	return Get_Pin_State( LED_PIN );
	
}
/*==============================================================================
* Function: Set_LED_Status
* 
* Description: This function changes the LED status depending on the parameter 
* received.
*
==============================================================================*/
void Set_LED_Status ( T_UBYTE lub_STATUS ) {
	
	Set_Pin_State( LED_PIN, lub_STATUS ) ; 
	
}
