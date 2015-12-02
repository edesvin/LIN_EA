/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LIN.c $
 * $Revision: 1.1 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 02-12-2015 $
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
/*                     |         LIN_EA     |         1.1                      */
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
* controls the response's transmission after a valid command is received.
*
==============================================================================*/
void TX_ISR (void){
	
	/*Check whether it is necessary to check that a header was just received. It would be necessary
	if other flags enter here.*/
	
	
	/* LINFLEX_0.BDRL.R = ptr_info[FMI]*/
	LINFLEX_0.BDRL.R = 0xABCD;
	LINFLEX_0.BDRM.R = 0x00;
	
	LINFLEX_2.LINCR2.B.DDRQ = 1;
	
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
	LINFLEX_2.LINCR1.B.INIT = 0x01; /*Enter initialization mode.*/

    LINFLEX_2.LINCR1.B.SLEEP = 0x00; /* Sleep clear */

    LINFLEX_2.UARTCR.B.UART = 0x00; /* UART Mode: Disabled */
	
    LINFLEX_2.LINCR2.R = 0x6000; /* 0 b 0110 0000 0000 0000 <- Reset status */
        /* Idle on Bit Error: Enabled -> Bit error reset LIN state machine.*/
        /* Idle on Identifier Parity Error: Enabled -> Identifier Parity error reset LIN state machine.*/

	/* Baudrate generator */
    LINFLEX_2.LINIBRR.R = 0x00D0;
        /* Baudrate : 19200 Symbols/sec */
        /* Integer Baud Rate Factor: 208*/

    LINFLEX_2.LINFBRR.R = 0x05;
        /* Fractional Baud Rate Factor: 5*/

    LINFLEX_2.UARTCR.R = 0x0000;
        /* UART Mode: Disable*/
        /* Parity transmit/check: Disable*/
        /* Parity Control Option: Even Parity*/
        /* Word Length in UART mode: 7 bit data + parity*/
        /* Tx FIFO/buffer mode: Disabled */
        /* Rx FIFO/buffer mode: Disabled */
        /* Transmitter data field length / Tx FIFO counter (Bytes):1*/
        /* Receiver Data Field Length /Rx FIFO counter  (Bytes): 1*/
        /* Transmitter : Disable*/
        /* Receiver : Disable*/


/*----------------------------------------------------------- */
/*        UART preset timeout register (LINFLEX_2_UARTPTO)        */
/*----------------------------------------------------------- */
    LINFLEX_2.UARTPTO.R = 0x0FFF;
        /* Preset Timeout counter : 4095*/


/*----------------------------------------------------------- */
/*        LIN timeout control status register  (LINFLEX_2_LINTCSR)        */
/*----------------------------------------------------------- */

    LINFLEX_2.LINTCSR.R = 0x0200; /* 0 b 0000 0010 0000 0000 */
        /* LIN timeout mode: Disabled*/
        /* Idle on Timeout: Enabled*/
        /* Timeout Counter: Disable*/


/*----------------------------------------------------------- */
/*        LIN output compare register  (LINFLEX_2_LINOCR)        */
/*----------------------------------------------------------- */

    LINFLEX_2.LINOCR.R = 0xFFFF;
        /* Output compare Value 1: 255*/
        /* Output compare Value 2: 255*/

/*----------------------------------------------------------- */
/*        LIN timeout control register  (LINFLEX_2_LINTOCR)        */
/*----------------------------------------------------------- */

    LINFLEX_2.LINTOCR.R = 0x0E2C;
        /* Header Timeout (Bit Time): 44*/
        /* Response Timeout: 14*/

/*----------------------------------------------------------- */
/*        LIN interrupt enable register  (LINFLEX_2_LINIER)        */
/*----------------------------------------------------------- */

    LINFLEX_2.LINIER.R = 0x0000;

        /* Header Received Interrupt: Disabled    */
        /* Data Transmitted Interrupt: Disabled    */
        /* Data Reception Complete Interrupt: Disabled    */
        /* Data Buffer Empty Interrupt: Disabled    */
        /* Data Buffer Full Interrupt: Disabled    */
        /* Wakeup Interrupt: Disabled    */
        /* LIN State Interrupt: Disabled    */
        /* Buffer Overrun Error Interrupt: Disabled    */
        /* Frame Error Interrupt: Disabled    */
        /* Header Error Interrupt: Disabled    */
        /* Checksum Error Interrupt: Disabled    */
        /* Bit Error Interrupt: Disabled    */
        /* Output Compare Interrupt: Disabled    */
        /* Stuck at Zero Interrupt: Disabled    */

/*----------------------------------------------------------- */
/*        LIN control register 1   (LINFLEX_2_LINCR1)        */
/*----------------------------------------------------------- */

    LINFLEX_2.LINCR1.R = 0x0081; /* 0 b 0000 0000 1000 0001   */
        /* Initialization Request: Set */
        /* MME - Master Mode Enable: Slave*/
        /* Receiver Buffer: Not Locked*/
        /* LBKM - Loopback Mode: Disabled*/
        /* Self Test Mode: Disabled*/
        /* LIN Master Break Length: 10 bits*/
        /* Slave Mode Break Detection Threshold: 11 bits*/
        /* Bypass Filter: Enabled*/
        /* Automatic Wake-Up Mode: Disabled*/
        /* Checksum field: Enabled*/
        /* Checksum Calculation: Disabled*/
        /* LIN Slave Automatic Resynchronization: Disabled*/

		
	/*Activate filters.*/
	LINFLEX_2.IFER.B.FACT = 0x0000;
	LINFLEX_2.IFMI.B.IFMI = 0x0000;
	LINFLEX_2.IFMR.B.IFM  = 0x0000;
	//LINFLEX_2.IFCR0.R = 0x00;

    LINFLEX_2.LINCR1.B.INIT = 0;
        /*Initialization Request: Clear */
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
