/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LIN.c $
 * $Revision: 1.9 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 07-12-2015 $
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
/*                     |         LIN_EA     |         1.9                      */
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
#define RX_IRQ 79 
#define PIN_TX 18 
#define PIN_RX 19 
#define PRIORITY_2 2

#define MASTER_CMD_ALL		(0x0F)

/*Slave 1*/
#define MASTER_CMD_SLV1		(0x10)
#define SLAVE1_RSP			(0x20)
#define SLAVE1_ID			(0x30)
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
	LIN_TX = 2,
	LIN_RX
}PIN_STATE;

/* Exported variables */
/*============================================================================*/
extern volatile T_UBYTE rub_NewSlaveState;
extern volatile T_UBYTE rub_SlaveStatus;
extern volatile T_UBYTE rub_LEDStatus;

/* Private variables */
/*============================================================================*/

static T_UBYTE raub_MembersInits[6] = {'A','Z','S','E','E','V'};
static T_UBYTE rub_TeamNumber = 1;
T_ULONG br = 0;
T_ULONG br2 = 0;

/* Private functions */
/*============================================================================*/
static void RX_ISR (void);
static void Header_handler (void);
static void Data_reception (void);
/*==============================================================================
* Function: Init_LIN
* 
* Description: This function initializes the LIN controller of the board.
* 
* Calculation of the initial Baud Rate (BR):
* LFDIV = LINIBRR + LINFBRR/16
* BR = f / ( 16 * LFDIV )
* 
* if f = 64 MHz, LINIBRR = 416, and LINFBRR = 11,
* Then:
* LFDIV = 416 + 11/16 = 416.6874
* BR = 64 E6 / ( 16 * 416.6874 ) = 9599.51 ~ 9600 Symbols/seconds	
* 
==============================================================================*/
void Init_LIN (void){
	
	Set_Pin_Mode (PIN_TX, LIN_TX);
	Set_Pin_Mode (PIN_RX, LIN_RX);
	
	LINFLEX_0.LINCR1.B.INIT = 0x01; 	/* Starting initialization mode */

    LINFLEX_0.LINCR1.B.SLEEP = 0x00; 	/* Sleep clear */

    LINFLEX_0.UARTCR.B.UART = 0x00;	 	/* LIN Mode */
	
    LINFLEX_0.LINCR2.R = 0x6000;
	
		/* 0 b  0110 0000 0000 0000 <- Reset status */
		/* Idle on Bit Error: Enabled -> Bit error resets LIN state machine.*/
		/* Idle on Identifier Parity Error: Enabled -> Identifier Parity error resets LIN state machine.*/
  
    LINFLEX_0.LINFBRR.R = 11; 
		/* Baud rate : 9600 Symbols/seconds					*/
        /* Fractional Baud Rate Factor: 11					*/
    
    LINFLEX_0.LINIBRR.R = 416; //340 and 11 = 11740.96 9.4% max: 10944 365; 10938.3 si.. 353
        /* Integer Baud Rate Factor: 416 */

    LINFLEX_0.UARTCR.R = 0x0000;
        /* UART Mode: Disable*/
        /* Parity transmit/check: Disable*/
        /* Parity Control Option: Even Parity*/
        /* Word Length in UART mode: 7 bit data + parity*/
        /* Tx FIFO/buffer mode: Disabled */
        /* Rx FIFO/buffer mode: Disabled */
        /* Transmitter data field length / Tx FIFO counter (Bytes):1 */
        /* Receiver Data Field Length /Rx FIFO counter  (Bytes): 1 */
        /* Transmitter : Disable*/
        /* Receiver : Disable*/

    LINFLEX_0.UARTPTO.R = 0x0FFF;
        /* Preset Timeout counter : 4095 (Default value) 		*/

    LINFLEX_0.LINTCSR.R = 0x0200; /* 0 b 0000 0010 0000 0000 	*/
        /* LIN timeout mode 							 		*/
        /* Idle on Timeout: Enabled								*/
        /* Timeout Counter: Disable								*/

    LINFLEX_0.LINOCR.R = 0xFFFF;
        /* Output compare Value 1: 255 (Default value) 			*/
        /* Output compare Value 2: 255 (Default value) 			*/

    LINFLEX_0.LINTOCR.R = 0x0E2C; /* Default configuration	*/
        /* Header Timeout (Bit Time): 44 (Default value) 	*/
        /* Response Timeout: 14 (Default value) 			*/

    LINFLEX_0.LINIER.R = 0x0005;
        /* Header Received Interrupt: Enabled  				*/ 
        /* Data Transmitted Interrupt: Disabled  		 	*/ 
        /* Data Reception Complete Interrupt: Enabled		*/
        /* Data Buffer Empty Interrupt: Disabled  		 	*/
        /* Data Buffer Full Interrupt: Disabled  		 	*/
        /* Wakeup Interrupt: Disabled   				 	*/
        /* LIN State Interrupt: Disabled					*/
        /* Buffer Overrun Error Interrupt: Disabled   	 	*/
        /* Frame Error Interrupt: Disabled    				*/
        /* Header Error Interrupt: Disabled    				*/
        /* Checksum Error Interrupt: Disabled    			*/
        /* Bit Error Interrupt: Disabled    				*/
        /* Output Compare Interrupt: Disabled    			*/
        /* Stuck at Zero Interrupt: Disabled    			*/

    LINFLEX_0.LINCR1.R = 0x3085; /*  0 b 0011 0000 1000 0101 		*/ 
        /* Initialization Request: Set 								*/
        /* Receiver Buffer: Locked									*/
        /* Slave Mode Break Detection Threshold: 11 bits			*/
		/* MME - Master Mode Enable: Slave							*/
		/* LBKM - Loop back Mode: Disabled							*/
		/* Self Test Mode: Disabled									*/
        /* Bypass Filter: Enabled									*/
		/* LIN Master Break Length: 10 bit							*/
        /* Automatic Wake-Up Mode: Enabled - Get out of sleep mode	*/ 
        /* LASE - LIN Slave Automatic Resynchronization: Enabled	*/
        /* Checksum field disable: Disabled							*/
        /* Checksum Calculation: Disabled							*/
    	
    LINFLEX_0.LINCR1.B.INIT = 0x00; /* Initialization done */
    
	INTC_InstallINTCInterruptHandler(&RX_ISR, RX_IRQ, PRIORITY_2);	
	
	INTC.CPR.R = 0;
}

/*==============================================================================
* Function: RX_ISR
* 
* Description: This function is called every time a reception interrupt is 
* generated from the LINFlex controller. It calls the Header_handler
* or Data_reception function if the Header Reception Flag or Data Received Flag
* are set, respectively.  
*
==============================================================================	*/
static void RX_ISR (void){
	
	if(LINFLEX_0.LINSR.B.HRF){ 			/* Header Reception Flag 				*/
		
		Header_handler();
		LINFLEX_0.LINSR.B.HRF = 1;		/* Header Reception Flag Cleared		*/
		
	}else if(LINFLEX_0.LINSR.B.DRF){ 	/* Data Received Flag 					*/
		
		Data_reception();
		LINFLEX_0.LINSR.B.DRF = 1; 		/* Data Received Flag cleared			*/
		
	}else{
		/* Do nothing */
	}

}
/*==============================================================================
* Function: Header_handler
* 
* Description: This function is called every time a header is received. 
* It is in charge of discard an invalid ID or setting the parameters to 
* receive or send the response.
*
==============================================================================	*/
static void Header_handler (void){
	switch(LINFLEX_0.BIDR.B.ID){
		case MASTER_CMD_ALL:
			LINFLEX_0.BIDR.B.DFL = 0; /* 1 byte - 1 */
			LINFLEX_0.BIDR.B.DIR = 0; /* Reception */
			LINFLEX_0.BIDR.B.CCS = 1; /* Classic checksum */
			break;
			
		case MASTER_CMD_SLV1:
			LINFLEX_0.BIDR.B.DFL = 0; /* 1 byte - 1 */
			LINFLEX_0.BIDR.B.DIR = 0; /* Reception */
			LINFLEX_0.BIDR.B.CCS = 1; /* Classic checksum */
			break;
			
		case SLAVE1_RSP:	
			/* Fills the first two bytes of the buffer's register */
			LINFLEX_0.BDRL.B.DATA0 = rub_LEDStatus;
			LINFLEX_0.BDRL.B.DATA1 = rub_SlaveStatus;
			LINFLEX_0.BIDR.B.DFL = 1; /* 2 bytes - 1  */
			LINFLEX_0.BIDR.B.DIR = 1; /* Transmission */
			LINFLEX_0.BIDR.B.CCS = 1; /* Classic checksum */
						
			LINFLEX_0.LINCR2.B.DTRQ = 1; /* Trigger the transmission */
			break;
			
		case SLAVE1_ID:
			/* Fills the first buffer's register */
			LINFLEX_0.BDRL.B.DATA0 = rub_TeamNumber;
			LINFLEX_0.BDRL.B.DATA1 = raub_MembersInits[0];
			LINFLEX_0.BDRL.B.DATA2 = raub_MembersInits[1];
			LINFLEX_0.BDRL.B.DATA3 = raub_MembersInits[2];
			
			/* Fills the first 3 bytes of the second buffer's register */
			LINFLEX_0.BDRM.B.DATA4 = raub_MembersInits[3];
			LINFLEX_0.BDRM.B.DATA5 = raub_MembersInits[4];
			LINFLEX_0.BDRM.B.DATA6 = raub_MembersInits[5];
			
			LINFLEX_0.BIDR.B.DFL = 6; /* 7 bytes - 1  */
			LINFLEX_0.BIDR.B.DIR = 1; /* Transmission */
			LINFLEX_0.BIDR.B.CCS = 1; /* Classic checksum */
							
			LINFLEX_0.LINCR2.B.DTRQ = 1; /* Trigger the transmission */
			break;
			
		default:
			LINFLEX_0.LINCR2.B.DDRQ = 1; /* Data Discard Request */
			break;
	}
}
/*==============================================================================
* Function: Data_reception
* 
* Description: This function is called every time a Data Reception Flag is set. 
* It is in charge of setting flags depending on the command received in the 
* response.
*
==============================================================================	*/
static void Data_reception (void){
	switch (LINFLEX_0.BDRL.B.DATA0){
		case cmd_NONE:
				/* Do nothing */
			break;
			
		case cmd_LED_on:
			if(rub_SlaveStatus == TRUE){
				rub_LEDStatus = ON;			
			}else{
				/* Do nothing*/
			}
			break;
			
		case cmd_LED_off:
			if(rub_SlaveStatus == TRUE){
				rub_LEDStatus = OFF;								
			}else{
				/* Do nothing*/
			}
			break;
			
		case cmd_LED_toggling:
			if(rub_SlaveStatus == TRUE){
				rub_LEDStatus = TOGGLING;
				br = LINFLEX_0.LINFBRR.R;
				br2 = LINFLEX_0.LINIBRR.R;
			}else{
				/* Do nothing*/
			}
			break;
			
		case cmd_disable_slv:
			rub_NewSlaveState = FALSE;
			break;
			
		case cmd_enable_slv:
			rub_NewSlaveState = TRUE;
			break;
			
		default:
			/* Do nothing */
			break;
	}	
}
