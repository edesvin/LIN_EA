/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LIN.h $
 * $Revision: 1.4 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 03-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
* This module contains the LIN driver. It consists of an initialization of 
* the LIN controller, an error handler, and an interrupt for transmission and 
* reception.
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
/*                     |         LIN_EA     |           1.4                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: LIN.h  $
  ============================================================================*/
#ifndef LIN_H_
#define LIN_H_
/* Includes */
/*============================================================================*/
#include "IntcInterrupts.h"

#include "LIN_EA.h"

/* Public functions */
/*============================================================================*/
void Init_LIN (void);

#endif /* LIN_H_ */
