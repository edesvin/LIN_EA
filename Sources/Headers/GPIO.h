/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: GPIO.h $
 * $Revision: 1.1 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 04-12-2015 $
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
/*                     |         LIN_EA     |           1.1                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: GPIO.h  $
  ============================================================================*/
#ifndef GPIO_H_
#define GPIO_H_
/* Includes */
/*============================================================================*/
#include "MPC5606B.h"
#include "stdtypedef.h"

/* Public functions */
/*============================================================================*/
void Set_Pin_State (T_UBYTE, T_UBYTE);
void Set_Pin_Mode (T_UBYTE, T_UBYTE);
T_UBYTE Get_Pin_State (T_UBYTE);

#endif /* GPIO_H_ */
