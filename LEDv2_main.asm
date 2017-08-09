;******************************************************************************
; LED strip controller project using tasks
; Controls the led strip from pololu
; How to Assemble: []
;******************************************************************************

#include MC9S12G96_ChipDefinition.inc

ramSegment  EQU $2000
prgSegment  EQU $C000

  ORG ramSegment

sharedValue ds 1
SoftTimer0 ds 2             ; LED Task
SoftTimer1 ds 2             ; Pattern Task
SoftTimer2 ds 2             ; USR Task

  REDEF ramSegment,*

  red 


;******************************************************************************
; Tasks
;******************************************************************************
  ORG prgSegment

taskVector EQU 0      ; Create name for Dispatch Vector
taskTimer EQU 0      ; Create name for Task Timer

#include LEDv2_USRIN_handler.inc
#include LEDv2_PATTERN_handler.inc
#include LEDv2_LED_handler.inc



;******************************************************************************
; Init
;******************************************************************************
  ORG prgSegment

PowerOn_Reset:

  LDS $3FFF


  JSR LED_Init

;******************************************************************************
; Main
;******************************************************************************

main:




  BRA main
;*****************************************************************************************
;	Interrupt Handler
;*****************************************************************************************

RT_Interrupt
	RTI

;*****************************************************************************************
;	Interrupts
;*****************************************************************************************
; Comment out the default interrupt vectors IF USED by tasks
;
ACMP_Interrupt
	BRA	*
OSC_Interrupt
	BRA	*
PLL_Interrupt
	BRA	*
FLerr_Interrupt
	BRA	*
FLcmd_Interrupt
	BRA	*
CANwu_Interrupt
	BRA	*
CANerr_Interrupt
	BRA	*
CANrx_Interrupt
	BRA	*
CANtx_Interrupt
	BRA	*
PortP_Interrupt
	BRA	*
LVI_Interrupt
	BRA	*
API_Interrupt
	BRA	*
ADCcmp_Interrupt
	BRA	*
PortAD_Interrupt
	BRA	*
Spurious_Interrupt
	BRA	*
PortJ_Interrupt
	BRA	*

ADC_Interrupt
	RTI


SCI2_Interrupt
	RTI

SCI1_Interrupt
	RTI

SCI0_Interrupt
	RTI

SPI2_Interrupt
	RTI

SPI1_Interrupt
	RTI

SPI0_Interrupt
	RTI


PAO_Interrupt
	RTI

PAI_Interrupt
	RTI

TC0_Interrupt
	RTI

TC1_Interrupt
	RTI

TC2_Interrupt
	RTI

TC3_Interrupt
	RTI

TC4_Interrupt
	RTI

TC5_Interrupt
	RTI

TC6_Interrupt
	RTI

TC7_Interrupt
	RTI

TOv_Interrupt
	RTI

;RT_Interrupt
;	RTI

IRQ_Interrupt
	RTI

XIRQ_Interrupt
	RTI

SW_Interrupt
	RTI

Trap_Interrupt
	JMP	PowerOn_Reset

COP_TimeoutReset
	JMP	PowerOn_Reset

COP_Clk_Reset
	JMP	PowerOn_Reset


	REDEF	prgSegment,*

;*************************************************************************************************
;	Interrupt Vectors
;*************************************************************************************************

	ORG	INTERRUPT_DefaultBase

	DW	Spurious_Interrupt					; 80
	DW	PortAD_Interrupt					; 82
	DW	ADCcmp_Interrupt					; 84
	DW	$FFFF								; 86	reserved
	DW	API_Interrupt						; 88
	DW	LVI_Interrupt						; 8A
	DW	$FFFF								; 8C	reserved
	DW	PortP_Interrupt						; 8E
	DW	$FFFF								; 90 - AE
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	$FFFF
	DW	CANtx_Interrupt						; B0	CAN TX
	DW	CANrx_Interrupt						; B2	CAN RX
	DW	CANerr_Interrupt					; B4	CAN Error
	DW	CANwu_Interrupt						; B6	CAN WakeUp
	DW	FLcmd_Interrupt						; B8	FLcmd_Interrupt
	DW	FLerr_Interrupt						; BA	FLerr_Interrupt
	DW	SPI2_Interrupt						; BC	SPI2_Interrupt
	DW	SPI1_Interrupt						; BE	SPI1_Interrupt
	DW	$FFFF								; C0
	DW	SCI2_Interrupt						; C2	SCI2_Interrupt
	DW	$FFFF								; C4
	DW	PLL_Interrupt						; C6
	DW	OSC_Interrupt						; C8
	DW	$FFFF								; CA	reserved
	DW	ACMP_Interrupt						; CC
	DW	PortJ_Interrupt						; CE
	DW	$FFFF								; D0	reserved
	DW	ADC_Interrupt						; D2	ADC_Interrupt
	DW	SCI1_Interrupt						; D4	SCI1_Interrupt
	DW	SCI0_Interrupt						; D6	SCIX_Interrupt
	DW	SPI0_Interrupt						; D8	SPI0_Interrupt
	DW	PAI_Interrupt						; DA	PAI_Interrupt
	DW	PAO_Interrupt						; DC	PAO_Interrupt
	DW	TOv_Interrupt						; DE	TOv_Interrupt
	DW	TC7_Interrupt						; E0	TC7_Interrupt
	DW	TC6_Interrupt						; E2	TC6_Interrupt
	DW	TC5_Interrupt						; E4	TC5_Interrupt
	DW	TC4_Interrupt						; E6	TC4_Interrupt
	DW	TC3_Interrupt						; E8	TC3_Interrupt
	DW	TC2_Interrupt						; EA	TC2_Interrupt
	DW	TC1_Interrupt						; EC	TC1_Interrupt
	DW	TC0_Interrupt						; EE	TC0_Interrupt
	DW	RT_Interrupt						; F0	RT_Interrupt
	DW	IRQ_Interrupt						; F2	IRQ_Interrupt
	DW	XIRQ_Interrupt						; F4	XIRQ_Interrupt
	DW	SW_Interrupt						; F6	SW_Interrupt
	DW	Trap_Interrupt						; F8	Trap_Interrupt
	DW	COP_TimeoutReset					; FA	COP_TimeoutReset
	DW	COP_Clk_Reset						; FC	COP_Clk_Reset
	DW	PowerOn_Reset						; FE	Bootloader Startup Vector
