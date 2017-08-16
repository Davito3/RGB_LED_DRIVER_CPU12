

;******************************************************************************
;  Local Variables
;******************************************************************************

  ORG ramSegment

tvLED ds 2
  REDEF taskVector,tvLED
  REDEF taskTimer,SoftTimer0

_CLKPIN       EQU #$08
_DATAPIN      EQU #$04
_CLKDATAPINS  EQU #$0C

_LEDCOUNT     EQU #$14        ;number of LEDs

intensity ds 32
blue      ds 32
green     ds 32
red       ds 32


  REDEF ramSegment,*

  ORG prgSegment

;******************************************************************************
; Task Utilities
;******************************************************************************


LED_u_pshData:

  BCS LED_u_00000   ;branch if data set to 1(uses carry flag)
  BCC LED_u_00001   ;branch if data set to 0
LED_u_00000   ;send data of 1
  BSET PT0AD, #_DATA
  BRA LED_u_00002
LED_u_00001   ;send data of 0
  BCLR PT0AD, #_DATA
LED_u_00002   ;clock rises and then falls for data to be handled by LEDs
  BSET PT0AD, #_CLK
  BCLR PT0AD, #_CLK
  RTS


LED_u_processByte:

  LDX #8      ;loads index with 8
LED_u_00010
  ASLA        ;shift byte so that carry flag is set
  JSR LED_u_pshData     ;sends carry bit to LEDs
  DBNE X, LED_u_00010   ;8 times for full byte
  RTS

;******************************************************************************
; Task Init
;******************************************************************************
LED_Init:

  BSET DDR0AD, CLKDATAPINS          ;sets data and clock ddr to output
  BCLR PT0AD, #_DATA          ;default low
  BCLR PT0AD, #_CLK           ;

  RTS

;******************************************************************************
; Task Dispatch
;******************************************************************************
LED_Update:

  RTS

;******************************************************************************
; Sub Tasks
;******************************************************************************

LED_t_Idle:
  RTS

;******************************************************************************
; Interrupts
;******************************************************************************



  REDEF prgSegment,*
