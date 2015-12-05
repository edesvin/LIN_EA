/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LIN.c $
 * $Revision: 1.7 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 05-12-2015 $
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
/*                     |         LIN_EA     |         1.7                      */
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
#define TX_IRQ  80 /*123*/
#define RX_IRQ 79 /*122*/
#define ERROR_IRQ 81
#define PIN_TX 18 /*74*/
#define PIN_RX 19 /*75*/
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

/* Private functions */
/*============================================================================*/
void TX_ISR (void);
void RX_ISR (void);
void Error_handler (void);

/*==============================================================================
* Function: TX_ISR
* 
* Description: This function is called every time a transmission interrupt is
* generated from the LINFlex controller. It implements a state machine which
* controls the response's transmission after a valid command is received.
*
==============================================================================*/
void TX_ISR (void){

	if(LINFLEX_0.LINSR.B.HRF){ /* Header Reception Flag */
		LINFLEX_0.LINSR.B.HRF = 1;		
		
		switch (1/*LINFLEX_0.IFMI.B.IFMI*/){ /* Filter Match Index */
		
			case MATCH_INDEX_RSP:
				/* Fills the first two bytes of the buffer's register */
				LINFLEX_0.BDRL.B.DATA0 = rub_SlaveStatus;
				LINFLEX_0.BDRL.B.DATA1 = rub_LEDStatus;
				break;
				
			case MATCH_INDEX_ID:
				/* Fills the first buffer's register */
				LINFLEX_0.BDRL.B.DATA0 = rub_TeamNumber;
				LINFLEX_0.BDRL.B.DATA1 = raub_MembersInits[0];
				LINFLEX_0.BDRL.B.DATA2 = raub_MembersInits[1];
				LINFLEX_0.BDRL.B.DATA3 = raub_MembersInits[2];
				
				/* Fills the first 3 bytes of the second buffer's register */
				LINFLEX_0.BDRM.B.DATA4 = raub_MembersInits[3];
				LINFLEX_0.BDRM.B.DATA5 = raub_MembersInits[4];
				LINFLEX_0.BDRM.B.DATA6 = raub_MembersInits[5];
				break;
			
			default:
				/* Do nothing */
				break;
		}
		
		LINFLEX_0.LINCR2.B.DTRQ = 1; /* Trigger the transmission */
		
	}
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

	if(LINFLEX_0.LINSR.B.DRF){
		LINFLEX_0.LINSR.B.DRF = 1;
		
		
		switch (LINFLEX_0.BDRL.B.DATA0){
		
			case cmd_NONE:
					/* Do nothing */
				break;
			case cmd_LED_on:
				if(/*rub_SlaveStatus == */TRUE){
					rub_LEDStatus = ON;
					if(LINFLEX_0.BIDR.B.ID == 0x10){
						Set_Pin_Mode(69,0);
						Set_Pin_State(69,!Get_Pin_State(69));
					}
								
				}else{
					/* Do nothing*/
				}
				break;
			case cmd_LED_off:
				if(/*rub_SlaveStatus == */TRUE){
					rub_LEDStatus = OFF;
					if(LINFLEX_0.BIDR.B.ID == 0x10){
						Set_Pin_Mode(69,0);
						Set_Pin_State(69,!Get_Pin_State(69));
					}
								
				}else{
					/* Do nothing*/
				}
				break;
			case cmd_LED_toggling:
				if(/*rub_SlaveStatus == */TRUE){
					rub_LEDStatus = TOGGLING;
					if(LINFLEX_0.BIDR.B.ID == 0x10){
						Set_Pin_Mode(69,0);
						Set_Pin_State(69,!Get_Pin_State(69));
					}	
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
	}else if(LINFLEX_0.LINSR.B.HRF){ /* Header Reception Flag */
		LINFLEX_0.LINSR.B.HRF = 1;
	}else{
		/* Do nothing */
	}

}
/*==============================================================================
* Function: Init_LIN
* 
* Description: This function initializes the LIN controller of the board.
*
==============================================================================*/
void Init_LIN (void){
	
	Set_Pin_Mode (PIN_TX, LIN_TX);
	Set_Pin_Mode (PIN_RX, LIN_RX);
	
	LINFLEX_0.LINCR1.B.INIT = 0x01; 	/* Starting initialization mode */

    LINFLEX_0.LINCR1.B.SLEEP = 0x00; 	/* Sleep clear */

    LINFLEX_0.UARTCR.B.UART = 0x00;	 	/* LIN Mode */
	
    LINFLEX_0.LINCR2.R = 0x0000; //600
	
		/* 0 b 0110 0000 0000 0000 <- Reset status */
	
		/* Idle on Bit Error: Enabled -> Bit error resets LIN state machine.*/
		/* Idle on Identifier Parity Error: Enabled -> Identifier Parity error resets LIN state machine.*/

    LINFLEX_0.LINIBRR.R = 416; //0x00D0;
        /* Baud rate : 9600 Symbols/sec */
        /* Integer Baud Rate Factor: 208 */

    LINFLEX_0.LINFBRR.R = 11; //0x05;
        /* Fractional Baud Rate Factor: 5 */

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


/*----------------------------------------------------------- */
/*        UART preset timeout register (LINFLEX_0_UARTPTO)    */
/*----------------------------------------------------------- */
  //  LINFLEX_0.UARTPTO.R = 0x0FFF;
    
        /* Preset Timeout counter : 4095*/


/*----------------------------------------------------------- */
/*        LIN timeout control status register  (LINFLEX_0_LINTCSR)        */
/*----------------------------------------------------------- */

    LINFLEX_0.LINTCSR.R = 0x0200; /* 0 b 0000 0010 0000 0000 */
        /* LIN timeout mode 			*/
        /* Idle on Timeout: Enabled		*/
        /* Timeout Counter: Disable		*/


/*----------------------------------------------------------- */
/*        LIN output compare register  (LINFLEX_0_LINOCR)        */
/*----------------------------------------------------------- */

    LINFLEX_0.LINOCR.R = 0xFFFF;
        /* Output compare Value 1: 255*/
        /* Output compare Value 2: 255*/

/*----------------------------------------------------------- */
/*        LIN timeout control register  (LINFLEX_0_LINTOCR)        */
/*----------------------------------------------------------- */

    LINFLEX_0.LINTOCR.R = 0x0E2C; /* Default configuration */
        /* Header Timeout (Bit Time): 44*/
        /* Response Timeout: 14*/

/*----------------------------------------------------------- */
/*        LIN interrupt enable register  (LINFLEX_0_LINIER)   */
/*----------------------------------------------------------- */

    LINFLEX_0.LINIER.R = 0x0007;
        /* Header Received Interrupt: enabled  			*/ /*not so sure*/
        /* Data Transmitted Interrupt: Enabled  		 	*/ /*not so sure*/
        /* Data Reception Complete Interrupt: enabled		*/ /*not so sure*/
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

/*----------------------------------------------------------- */
/*        LIN control register 1   (LINFLEX_0_LINCR1)         */
/*----------------------------------------------------------- */

    LINFLEX_0.LINCR1.R = 0x3085; /*  0 b 0011 0000 1000 0101 sin el 8 */ 
        /* Initialization Request: Set 								*/
        /* Receiver Buffer: Locked									*/
        /* Slave Mode Break Detection Threshold: 11 bits			*/
		/* MME - Master Mode Enable: Slave							*/
		/* LBKM - Loop back Mode: Disabled							*/
		/* Self Test Mode: Disabled									*/
        /* Bypass Filter: Disable	enable								*/
		/* LIN Master Break Length: 10 bit							*/
        /* Automatic Wake-Up Mode: Enabled - Get out of sleep mode	*/ //not so sure
        /* LASE - LIN Slave Automatic Resynchronization: Enabled	*/
        /* Checksum field disable: Disabled							*/
        /* Checksum Calculation: Disabled							*/

	/* Starts filters' configuration */
	LINFLEX_0.IFER.B.FACT = 0; 		/* First deactivate filters */
	LINFLEX_0.IFMR.B.IFM  = 0; 		/*All the filters in identifier LIST mode*/
	
	/*Slave1_RSP*/
	LINFLEX_0.IFCR[0].B.DFL = 0x01;  	/*Data Field Length. Number of bytes - 1 */
	LINFLEX_0.IFCR[0].B.DIR = 0x01; 	/*Direction 0-> Receives, 1-> Transmits*/
	LINFLEX_0.IFCR[0].B.CCS = 0x00; 	/*Enhanced Checksum*/
	LINFLEX_0.IFCR[0].B.ID =  0x20;  	/*Identifier 6 bits. 0x20 with parity bits.*/	

	/*Slave1_ID*/
	LINFLEX_0.IFCR[1].B.DFL = 0x06;  	/*Data Field Length. Number of bytes - 1 */
	LINFLEX_0.IFCR[1].B.DIR = 0x01; 	/*Direction 0-> Receives, 1-> Transmits*/
	LINFLEX_0.IFCR[1].B.CCS = 0x00; 	/*Enhanced Checksum*/
	LINFLEX_0.IFCR[1].B.ID =  0x30;  	/*Identifier 6 bits. 0xF0 with parity bits.*/	
	
	/*MASTER_CMD_ALL*/
	LINFLEX_0.IFCR[2].B.DFL = 0x00;  	/*Data Field Length. Number of bytes - 1 */
	LINFLEX_0.IFCR[2].B.DIR = 0x00; 	/*Direction 0-> Receives, 1-> Transmits*/
	LINFLEX_0.IFCR[2].B.CCS = 0x01; 	/*Enhanced Checksum*/
	LINFLEX_0.IFCR[2].B.ID =  0x0F;  	/*Identifier 6 bits. 0xCF with parity bits.*/	
	
	/*MASTER_CMD_SLV1*/
	LINFLEX_0.IFCR[3].B.DFL = 0x00;  	/*Data Field Length. Number of bytes - 1 */
	LINFLEX_0.IFCR[3].B.DIR = 0x00; 	/*Direction 0-> Receives, 1-> Transmits*/
	LINFLEX_0.IFCR[3].B.CCS = 0x00; 	/*Enhanced Checksum*/
	LINFLEX_0.IFCR[3].B.ID =  0x10;  	/*Identifier 6 bits. 0x50 with parity bits.*/	
	
	LINFLEX_0.IFER.B.FACT = 0x03; 		/* Activate bits FACT[0] and FACT[1] to activate the filters 0 - 3 */
	/* Finishes filters' configuration */
	
    LINFLEX_0.LINCR1.B.INIT = 0x00; /*Initialization done*/
	
	INTC_InstallINTCInterruptHandler(&TX_ISR, TX_IRQ, 2);
	INTC_InstallINTCInterruptHandler(&RX_ISR, RX_IRQ, 3);	
	INTC_InstallINTCInterruptHandler(&Error_handler, ERROR_IRQ, 4);	
	
	INTC.CPR.R = 0;
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
