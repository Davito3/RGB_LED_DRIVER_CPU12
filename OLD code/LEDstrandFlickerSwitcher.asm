;******************************************************************************
;*  Name of the program
;*  What it does
;*  How to assemble me- [as12 LEDstrandFlickerSwitcher.asm -LLEDstrandFlickerSwitcher.lst]
;******************************************************************************

  org $2000

PTP       EQU $0258
PTPDDR    EQU $025A

PTADRW    EQU $0274
DIPPULUP  EQU $0278
ENAPULUP  EQU $007C

PTAD      EQU $0270
DIPSWITCH EQU $0271

_CLK      EQU #$08
_DATA     EQU #$04
_BOTH     EQU #$0C


_LEDCOUNT  EQU #14            ;number of LEDs


intensity ds 32
blue      ds 32
green     ds 32
red       ds 32

waiter    ds 1
waiter2   ds 1
waiter3   ds 1

pIndex    ds 1
pIndex2   ds 1
pIndex3   ds 1

AmountB   ds 1
AmountG   ds 1
AmountR   ds 1
AmountB2  ds 1
AmountG2  ds 1
AmountR2  ds 1

PatternSelect ds 1
PatternSelect2 ds 1

OneSecCnt ds 1

SoftTimer0 ds 2
SoftTimer1 ds 2

USRIN_Port  EQU $0240
USRIN_DDR   EQU $0242
USRIN_PUPEN EQU $0244

USRIN_bit1  EQU %00000010
USRIN_bit2  EQU %00001000

;******************************************************************************
;   Utilities
;******************************************************************************

  org $c000

timer0:

  MOVW #$0030 SoftTimer0      ;100 cycles w/ 10ms = 1 second
timer0_loop
  LDX SoftTimer0
  BNE timer0_loop
timer0_exit
  RTS


wait:

  MOVB #$03 waiter3
timerloop3:
  MOVB #$FF waiter2
timerloop2:
  MOVB #$FF waiter
timerloop:
  DEC waiter
  BNE timerloop
  DEC waiter2
  BNE timerloop2
  DEC waiter3
  BNE timerloop3
  RTS


setData:

  BCS dataOf1                 ;makes it so input 0 equals
  BCC dataOf0                 ;data of 0 and vise versa
dataOf1:
  BSET PTAD #_DATA
  BRA clkRise
dataOf0:
  BCLR PTAD #_DATA
clkRise:
  BSET PTAD #_CLK             ;rising edge of clock _/
  BCLR PTAD #_CLK             ;falling edge of clock \_
  RTS


Process_Byte:

  LDX #$08
cycle8:
  ASLA
  JSR setData
  DBNE X, cycle8
  RTS


;******************************************************************************
; Task 1 - LED Processing
;******************************************************************************

;==============================================================================
; LED Utilities

Start_Frame:

  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  RTS


LED_SendIntensity:

  LDY #intensity                        ;should probably or this with #$E0
  LDAA B,Y
  JSR Process_Byte
  RTS


LED_SendBlue:

  LDY #blue
  LDAA B,Y
  JSR Process_Byte
  RTS


LED_SendGreen:

  LDY #green
  LDAA B,Y
  JSR Process_Byte
  RTS


LED_SendRed:

  LDY #red
  LDAA B,Y
  JSR Process_Byte
  RTS


End_Frame:

  LDAA #$FF
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  LDAA #$00
  JSR Process_Byte
  RTS

;==============================================================================
; Task

LED_Process:

  JSR Start_Frame
  LDAB #00                    ;index used in utilities
LED_CLK
  JSR LED_SendIntensity
  JSR LED_SendBlue
  JSR LED_SendGreen
  JSR LED_SendRed
  INCB
  CMPB #_LEDCOUNT
  BNE LED_CLK
  JSR End_Frame

LED_exit
  RTS




;******************************************************************************
; Task 2 - Input
;******************************************************************************

;==============================================================================
; Input Utilities

INPUT_Process:

  ; LDAA USRIN_Port
  ; BITA
  BRSET USRIN_Port,#USRIN_bit1,INPUT_Select2
  BRSET USRIN_Port,#USRIN_bit2,INPUT_Select1
  BRA INPUT_Select3

INPUT_Select1
;  BRSET USRIN_Port,#USRIN_bit1,INPUT_Select2
  MOVB #$03, OneSecCnt
  MOVB #%00000001, PatternSelect
  BRA INPUT_exit
INPUT_Select2
  BRSET USRIN_Port,#USRIN_bit2,INPUT_Idle
  MOVB #$03, OneSecCnt
  MOVB #%00000010, PatternSelect
  BRA INPUT_exit
INPUT_Select3
  MOVB #%00100000, PatternSelect
  BRA INPUT_exit
INPUT_Idle
;  MOVB #%00100000, PatternSelect
INPUT_exit
  RTS


;==============================================================================
; Task



; DIP_Process:
;
;   BRSET DIPSWITCH,%10000000,DIP_Tst2
;   MOVB #%10000000, PatternSelect
;   BRA   DIP_exit
; DIP_Tst2
;   BRSET DIPSWITCH,%01000000,DIP_Tst3
;   MOVB #%01000000, PatternSelect
;   BRA   DIP_exit
; DIP_Tst3
;   BRSET DIPSWITCH,%00100000,DIP_Tst4
;   MOVB #%00100000, PatternSelect
;   BRA   DIP_exit
; DIP_Tst4
;   BRSET DIPSWITCH,%00010000,DIP_Tst5
;   MOVB #%00010000, PatternSelect
;   BRA   DIP_exit
; DIP_Tst5
;   BRSET DIPSWITCH,%00001000,DIP_Tst6
;   MOVB #%00001000, PatternSelect
;   BRA   DIP_exit
; DIP_Tst6  ;blink blue every other
;   BRSET DIPSWITCH,%00000100,DIP_Tst7
;   MOVB #%00000100, PatternSelect
;   BRA   DIP_exit
; DIP_Tst7  ;blink blue every other with green
;   BRSET DIPSWITCH,%00000010,DIP_Tst8
;   MOVB #$04, OneSecCnt
;   MOVB #%00000010, PatternSelect
;   BRA   DIP_exit
; DIP_Tst8  ;blink blue every other with red
;   BRSET DIPSWITCH,%00000001,DIP_default
;   MOVB #$04, OneSecCnt
;   MOVB #%00000001, PatternSelect
;   BRA   DIP_exit
; DIP_default
; ;  JSR DIP_Default
;
; DIP_exit
;  RTS




;******************************************************************************
; Task 3 - Patterns
;******************************************************************************

;==============================================================================
; Pattern Utilities

Pattern_TurnAllBlue:

  LDAB #$00
Pattern_AllBLoop
  LDY #intensity
  MOVB #$FF, B,Y
  LDY #blue
  MOVB #$FF, B,Y
  LDY #green
  MOVB #$00, B,Y
  LDY #red
  MOVB #$00, B,Y
  INCB
  CMPB #_LEDCOUNT
  BNE Pattern_AllBLoop
  RTS


Pattern_TurnAllGreen:

  LDAB #$00
Pattern_AllGLoop
  LDY #intensity
  MOVB #$FF, B,Y
  LDY #blue
  MOVB #$00, B,Y
  LDY #green
  MOVB #$FF, B,Y
  LDY #red
  MOVB #$00, B,Y
  INCB
  CMPB #_LEDCOUNT
  BNE Pattern_AllGLoop
  RTS


Pattern_TurnAllRed:

  LDAB #$00
Pattern_AllRLoop
  LDY #intensity
  MOVB #$FF, B,Y
  LDY #blue
  MOVB #$00, B,Y
  LDY #green
  MOVB #$00, B,Y
  LDY #red
  MOVB #$FF, B,Y
  INCB
  CMPB #_LEDCOUNT
  BNE Pattern_AllRLoop
  RTS


Pattern_TurnAllWhite:

  LDAB #$00
Pattern_WhiteLoop
  LDY #intensity
  MOVB #$FF, B,Y
  LDY #blue
  MOVB #$FF, B,Y
  LDY #green
  MOVB #$FF, B,Y
  LDY #red
  MOVB #$FF, B,Y
  INCB
  CMPB #_LEDCOUNT
  BNE Pattern_WhiteLoop
  RTS


Pattern_TurnAllOff:

  LDAB #$00
Pattern_OffLoop
  LDY #intensity
  MOVB #$E0, B,Y
  LDY #blue
  MOVB #$00, B,Y
  LDY #green
  MOVB #$00, B,Y
  LDY #red
  MOVB #$00, B,Y
  INCB
  CMPB #_LEDCOUNT
  BNE Pattern_OffLoop
  RTS


Pattern_Default:

  LDAB #$00
Pattern_DefaultLoop
  LDY #intensity
  MOVB #$E1, B,Y
  LDY #blue
  MOVB #$FF, B,Y
  LDY #green
  MOVB #$FF, B,Y
  LDY #red
  MOVB #$FF, B,Y
  INCB
  CMPB #_LEDCOUNT
  BNE Pattern_DefaultLoop
  RTS


Pattern_TstPattern:

  LDAB pIndex3
  ANDB #$0F
  LDY #blue
  MOVB #$FF, B,Y
  LDY #green
  MOVB #$00, B,Y
  LDY #red
  MOVB #$00, B,Y
  LDY #intensity
  MOVW #$FFE0, B,Y
  INC pIndex3
  JSR timer0                  ;1s timer
; JSR wait
; JSR wait
; JSR wait
  RTS


Pattern_Eother:

  LDAB #$00
Pattern_EotherLoop
  LDAA pIndex
  BITA #$01
  BEQ Pattern_EotherOff
Pattern_EotherOn
  LDY #intensity
  MOVB #$FF, B,Y
  LDY #blue
  MOVB AmountB, B,Y
  LDY #green
  MOVB AmountG, B,Y
  LDY #red
  MOVB AmountR, B,Y
  INC pIndex
  BRA Pattern_EotherLoopEnd
Pattern_EotherOff
  LDY #intensity              ;currently the same as DIP_TurnAllOff
  MOVB #$FF, B,Y              ;but is able to change to diff color if need be
  LDY #blue
  MOVB AmountB2, B,Y
  LDY #green
  MOVB AmountG2, B,Y
  LDY #red​
  MOVB AmountR2, B,Y
  INC pIndex
Pattern_EotherLoopEnd
  INCB
  CMPB #_LEDCOUNT
  BNE Pattern_EotherLoop
; JSR wait
; JSR wait
; JSR wait
Pattern_Eother_exit
  RTS


Pattern_Blink:

  LDAA pIndex2
  BITA #01
  BEQ Pattern_BlinkOff
Pattern_BlinkOn
  ;must specify before the (AmountR/G/B) amounts
  JSR Pattern_Eother
  INC pIndex2
  BRA Pattern_Blink_exit
Pattern_BlinkOff
  MOVB #$00, AmountB
  MOVB #$00, AmountG
  MOVB #$00, AmountR
  JSR Pattern_Eother
;  JSR Pattern_TurnAllOff
  INC pIndex2
Pattern_Blink_exit
  JSR timer0                  ;1s timer
;  JSR wait
;  JSR wait
  RTS


Pattern_BlinkBlue:

  MOVB #$FF, AmountB
  MOVB #$00, AmountG
  MOVB #$00, AmountR
  MOVB #$00, AmountB2         ;these ones used for the "every other" color
  MOVB #$00, AmountG2
  MOVB #$00, AmountR2
  JSR Pattern_Blink
Pattern_BBlue_exit
  RTS


Pattern_BlinkBlueWGreen:

  MOVB #$FF, AmountB
  MOVB #$00, AmountG
  MOVB #$00, AmountR
  MOVB #$00, AmountB2         ;these ones used for the "every other" color
  MOVB #$FF, AmountG2
  MOVB #$00, AmountR2
Pattern_BBlueWGreenLoop
  JSR Pattern_Blink
  DEC OneSecCnt
  BNE Pattern_BBlueWGreen_exit
  MOVB #%00000100, PatternSelect
Pattern_BBlueWGreen_exit
  RTS


Pattern_BlinkBlueWRed:

  MOVB #$FF, AmountB
  MOVB #$00, AmountG
  MOVB #$00, AmountR
  MOVB #$00, AmountB2         ;these ones used for the "every other" color
  MOVB #$00, AmountG2
  MOVB #$FF, AmountR2
Pattern_BBlueWRedLoop
  JSR Pattern_Blink
  DEC OneSecCnt
  BNE Pattern_BBlueWRed_exit
  MOVB #%00000100, PatternSelect
Pattern_BBlueWRed_exit
  RTS


;==============================================================================
; Task

Pattern_Process:

  BRCLR PatternSelect,%10000000,Pattern_Tst2
  JSR Pattern_TurnAllBlue
  LBRA   Pattern_exit
Pattern_Tst2
  BRCLR PatternSelect,%01000000,Pattern_Tst3
  JSR Pattern_TurnAllGreen
  LBRA   Pattern_exit
Pattern_Tst3
  BRCLR PatternSelect,%00100000,Pattern_Tst4
  JSR Pattern_TurnAllRed
  LBRA   Pattern_exit
Pattern_Tst4
  BRCLR PatternSelect,%00010000,Pattern_Tst5
  JSR Pattern_TurnAllWhite
  LBRA   Pattern_exit
Pattern_Tst5
  BRCLR PatternSelect,%00001000,Pattern_Tst6
  JSR Pattern_TurnAllOff
  LBRA   Pattern_exit
Pattern_Tst6
  BRCLR PatternSelect,%00000100,Pattern_Tst7
  JSR Pattern_BlinkBlue
  LBRA   Pattern_exit
Pattern_Tst7
  BRCLR PatternSelect,%00000010,Pattern_Tst8
  JSR Pattern_BlinkBlueWGreen
  LBRA   Pattern_exit
Pattern_Tst8
  BRCLR PatternSelect,%00000001,Pattern_Tst9
  JSR Pattern_BlinkBlueWRed
  LBRA   Pattern_exit
Pattern_Tst9
  BRCLR PatternSelect2,%00000001,Pattern_Tst_Default
  JSR Pattern_TstPattern
  LBRA   Pattern_exit
Pattern_Tst_Default

Pattern_exit
  RTS



;******************************************************************************
; Interrupt Handlers
;******************************************************************************
RTIHandler:       ; FFF0

  BSET $0037 #$80             ;reset the interrupt

  LDAA PTP
  EORA #$20                   ;used w/ scope to configuring timer time(10ms)
  STAA PTP
RTIH_00000
  LDX SoftTimer0
  BEQ RTIH_00001
  DEX
  STX SoftTimer0
RTIH_00001
  LDX SoftTimer1
  BEQ RTIH_00002
  DEX
  STX SoftTimer1
RTIH_00002
  RTI

DoNothing:        ; FFF2
  RTI


;******************************************************************************
; Init
;******************************************************************************

init:

  LDS #$3FFF                  ;load stack pointer

  MOVB #_BOTH PTADRW          ;sets data and clock outputs to ON

  MOVW #$0FFF DIPPULUP        ;sets the pull enable registers with $OFFF
  MOVW #$00FF ENAPULUP        ;sets the register for enabling pull ups?

  BSET USRIN_PUPEN,(USRIN_bit1|USRIN_bit2)

  BCLR PTAD #_DATA            ;default low
  NOP
  BCLR PTAD #_CLK

  MOVB #$00 PatternSelect     ;resets pattern selecter
  MOVB #$00 PatternSelect2    ;resets pattern selecter

  MOVB #$19 $003B             ;sets time for timer interrupt
  BSET $0038 #$80             ;enable a timer interrupt

  BSET PTPDDR #$20

  CLI
  JSR timer0
;******************************************************************************
; Mianline
;******************************************************************************

main:

;  JSR DIP_Process
  JSR INPUT_Process
  JSR Pattern_Process
  JSR LED_Process
  BRA main


;******************************************************************************
; Interrupts
;******************************************************************************



  org $fff0

  dw RTIHandler      ; FFF0
  dw DoNothing       ; FFF2
  dw DoNothing       ; FFF4
  dw DoNothing       ; FFF6
  dw DoNothing       ; FFF8
  dw DoNothing       ; FFFA
  dw DoNothing       ; FFFC
  dw init            ; FFFE
