/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LIN.c $
 * $Revision: 1.2 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 03-12-2015 $
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
/*                     |         LIN_EA     |         1.2                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: LIN.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "LIN.h"
/*============================================================================*/
/* Constants and types */
/*============================================================================*/

typedef enum{
	cmd_NONE,
	cmd_LED_on,
	cmd_LED_off,
	cmd_LED_toggling,
	cmd_disable_slv,
	cmd_enable_slv
}t_cmdType;

typedef enum { 
	MATCH_INDEX_RSP,
	MATCH_INDEX_ID
}MATCH_INDEX;

typedef enum { 
	IDLE,
	TRANSMISSION
}TX_STATES;

/*============================================================================*/

extern volatile T_UBYTE rub_SlaveStatus;
extern volatile T_UBYTE rub_LEDStatus;

/*============================================================================*/

T_UBYTE raub_MembersInits[6] = {'A','Z','S','E','E','V'};
T_UBYTE rub_TeamNumber = 1;

/*============================================================================*/
/* Private functions */
T_UBYTE IdleState(T_UBYTE);
T_UBYTE TxState(T_UBYTE);

/*============================================================================*/
/*==============================================================================
* Function: TX_ISR
* 
* Description: This function is called every time a transmission interrupt is
* generated from the LINFlex controller. It implements a state machine which
* controls the response's transmission after a valid command is received.
*
==============================================================================*/
void TX_ISR (void){
	static T_UBYTE rub_TxStateVar = IDLE;
	
	switch (rub_TxStateVar) {
	
		case IDLE:
			rub_TxStateVar = IdleState(rub_TxStateVar);
			break;
			
		case TRANSMISSION:
			rub_TxStateVar = TxState(rub_TxStateVar);
			break;
			
		case default:
			/* Do nothing. */
			break;
	
	}
	
}
/*==============================================================================
* Function: Tx_IdleState
* 
* Description: 
* 
* 
*
==============================================================================*/
T_UBYTE IdleState(T_UBYTE lub_TxStateVar){

	if(LINFLEX_0.LINSR.B.HRF){ /* Header Reception Flag */
		LINFLEX_0.LINSR.B.HRF = 1;
		lub_TxStateVar = TRANSMISSION;
		
		switch (LINFLEX_0.IFMI.B.IFMI){ /* Filter Match Index */
		
			case MATCH_INDEX_RSP:
				/* Fills the first two bytes of the buffer's register */
				LINFLEX_0.BDRL.DATA0 = rub_SlaveStatus;
				LINFLEX_0.BDRL.DATA1 = rub_LEDStatus;
				break;
				
			case MATCH_INDEX_ID:
				/* Fills the first buffer's register */
				LINFLEX_0.BDRL.DATA0 = rub_TeamNumber;
				LINFLEX_0.BDRL.DATA1 = raub_MembersInits[0];
				LINFLEX_0.BDRL.DATA2 = raub_MembersInits[1];
				LINFLEX_0.BDRL.DATA3 = raub_MembersInits[2];
				
				/* Fills the first 3 bytes of the second buffer's register */
				LINFLEX_0.BDRM.DATA0 = raub_MembersInits[3];
				LINFLEX_0.BDRM.DATA1 = raub_MembersInits[4];
				LINFLEX_0.BDRM.DATA2 = raub_MembersInits[5];
				break;
			
			case default:
				/* Do nothing */
				break;
		}
		
		LINFLEX_2.LINCR2.B.DTRQ = 1; /* Trigger the transmission */
		
	}else{
		/* Do nothing */
	}
	
	return lub_TxStateVar;
}
/*==============================================================================
* Function: Tx_TransmissionState
* 
* Description: 
* 
* 
*
==============================================================================*/
T_UBYTE TxState(T_UBYTE lub_TxStateVar){

	if(LINFLEX_0.LINSR.B.DTF){ /*Data Transmission Completed Flag */ 
	/* ******Bit_error and time out implementation must be done********* */
		LINFLEX_0.LINSR.B.DTF = 1;
		lub_TxStateVar = IDLE;		
	}else{
		/* Do nothing */
	}
	
	return lub_TxStateVar;
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

	switch (LINFLEX_0.BDRL.DATA0){
	
		case cmd_NONE:
				/* Do nothing */
			break;
		case cmd_LED_on:
			rub_LEDStatus = ON;
			break;
		case cmd_LED_off:
			rub_LEDStatus = OFF;
			break;
		case cmd_LED_toggling:
			rub_LEDStatus = TOGGLING;
			break;
		case cmd_disable_slv:
			rub_SlaveStatus = FALSE;
			break;
		case cmd_enable_slv:
			rub_SlaveStatus = TRUE;
			break;
		case default:
			/* Do nothing */
			break;
	}	

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
	/*To be implemented.*/
}
