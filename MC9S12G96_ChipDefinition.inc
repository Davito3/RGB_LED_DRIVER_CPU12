;*****************************************************************************************
;*
;*	MCS12G96 Chip Definition
;*
;*****************************************************************************************

RAM_Start				EQU	$2000					; 8K RAM Memory Map
RAM_End					EQU	$3FFF					; last byte of RAM
RAM_Length				EQU	RAM_End-RAM_Start+1		; size of RAM section

EEPROM_Start			EQU	$0400				; 3K EEPROM Memory Map
EEPROM_End				EQU	$0FFF				; last byte of EEPROM
EEPROM_Length			EQU	EEPROM_End-EEPROM_Start+1
EEPROM_SectorLen		EQU	4						; a minimum of 4 bytes is erased, 2 bytes burned

FLASH_UnPagedStart		EQU	$C000				; Unpaged FLASH segment - always in Map High Mem
FLASH_UnPagedEnd		EQU	$FFFF
FLASH_UnPagedLowStart	EQU	$4000
FLASH_UnPagedLowEnd		EQU	$7FFF
;
FLASH_PagedStart		EQU	$8000				; FLASH Memory Paged Window
FLASH_PagedEnd			EQU	$BFFF				; last buyte of FLASH paged window
FLASH_NumPages			EQU	4					; 4 pages of 16K each: 64K
FLASH_SectorLen			EQU	512
FLASH_PhraseLen			EQU	8

INTERRUPT_DefaultBase	EQU	$FF80			; default int vector base - unpaged segment
; all device specific interrupts go here
INTERRUPT_Reset			EQU	$FFFE			; unmaskable, non-relocatable vectors
INTERRUPT_Clock			EQU	$FFFC
INTERRUPT_COP			EQU	$FFFA

;PORTA	EQU	$00					; Port A Data
;PORTB	EQU	$01					; Port B Data
;DDRA	EQU	$02					; Port A Data Direction
;DDRB	EQU	$03					; Port B Data Direction

MODE			EQU	$0B					; Memory Map Control
MODE_MODC		EQU	%10000000			; 
;
;	Port Integration Module
;
PUCR			EQU	$0C					; Pull Up Control for A,B,C,D,E,BKGND ports
PUCR_BKPUE		EQU	%01000000			; 
PUCR_PDPEE		EQU	%00010000			; 
;PUCR_PUPDE	EQU	%00001000			; 
;PUCR_PUPCE	EQU	%00001000			; 
;PUCR_PUPBE	EQU	%00001000			; 
;PUCR_PUPAE	EQU	%00001000			; 
;
DIRECT			EQU	$11					; Direct memory base address {$00xx to $FFxx}
;
MMCCTL			EQU	$13				;
MMCCTL_NVMRES	EQU	%00000001		; 
;
PPAGE			EQU	$15				; Current Memory Page {$0..$F)
;
PARTIDH			EQU	$1A					; part ID
PARTIDL			EQU	$1B
PartID			EQU	$F180				; G96 and G128
;
ECLKCTL			EQU	$1C				; E Clock Control
ECLKCTL_NECLK	EQU	%10000000		;
ECLKCTL_NCLKX2	EQU	%01000000		;
ECLKCTL_DIV16	EQU	%00100000		;
ECLKCTL_EDIV	EQU	$1F				; E clk divider bits
;
IRQCR			EQU	$1E				; IRQ Control
IRQCR_IRQE		EQU	%10000000		; edge
IRQCR_IRQEN		EQU	%01000000		; enable
;
;	DEBUG MODULE $20 thru $2F
;

;
;	Clock and Power Management $34 - $3F
;
;	After Reset:
;	50 MHz VCOCLK operation Post divider is 0x03, 
;	so PLLCLK is VCOCLK divided by 4, that is 12.5MHz and Bus Clock is 6.25MHz.
;
;	PLLCLK = VCOCLK / (POSTDIV+1)
;	BUS CLK = PLLCLK / 2
;
SYNR			EQU	$34				;
;
CPMUREFDIV			EQU	$35				; Reference Divider Register
CPMUREFDIV_REFFRQ		EQU	$C0			; - bits
CPMUREFDIV_REFFRQ_1		EQU	$00			; -- 1MHz <= fREF <= 2MHz
CPMUREFDIV_REFFRQ_2		EQU	$40			; -- 2MHz < fREF <= 6MHz
CPMUREFDIV_REFFRQ_6		EQU	$80			; -- 6MHz < fREF <= 12MHz
CPMUREFDIV_REFFRQ_12	EQU	$C0			; -- fREF >12MHz
CPMUREFDIV_REFDIV		EQU	$0F			; - bits
;
POSTDIV			EQU	$36				; Post divider
POSTDIV_Bits	EQU	$1F				; - bits used in the divider
;
CPMUFLG			EQU	$37				;
CPMUFLG_RTIF	EQU	%10000000		; RTI Interrupt Flag
CPMUFLG_PORF	EQU	%01000000		; Power on reset Flag
CPMUFLG_LVRF	EQU	%00100000		; Low Voltage Reset Flag
CPMUFLG_LOCKIF	EQU	%00010000		; PLL Lock Interrupt Flag
CPMUFLG_LOCK	EQU	%00001000		; Lock Status Bit
CPMUFLG_ILAF	EQU	%00000100		; Illegal Address Reset Flag
CPMUFLG_OSCIF	EQU	%00000010		; Oscillator Interrupt Flag
CPMUFLG_UPOSC	EQU	%00000001		; Oscillator Status Bit
;
CPMUINT			EQU	$38				;
CPMUINT_RTIE	EQU	%10000000		; RTI Interrupt Enable
CPMUCLKS		EQU	$39				; Clock source selection for PLL, RTI and COP
CPMUCLKS_RTI	EQU	%00000010		; RTI clk source select
CPMUCLKS_COP1	EQU	%00010000		; high bit of COP OSC Select table
CPMUCLKS_COP0	EQU	%00000001		; low bit
CPMUPLL			EQU	$3A				;
CPMURTI			EQU	$3B				;
CPMURTI_RTDEC	EQU	%10000000		; Use Decimal Divder Chain
CPMUCOP			EQU	$3C				;
CPMUCOP_RSBCK	EQU	%01000000		; stop RTI and COP in Active Background Mode
CPMUARMCOP		EQU	$3F				; 
;
;	TIM $40 - $6F
;
TIOS			EQU	$40				;	Bit mapped 0 = input capture / 1 = output compare
CFORC			EQU	$41				;	Bit Mapped
OC7M			EQU	$42				;	Bit Mapped
OC7D			EQU	$43				;	Bit Mapped
;
TCNT			EQU	$44				; free running counter
TCNTH			EQU	$44				;
TCNTL			EQU	$45				;
;
TSCR1			EQU	$46				;	Control / Status
TSCR1_TEN		EQU	%10000000		;	Timer Enable 
TSCR1_TSWAI		EQU	%01000000		;	Timer Module Stops While in Wait
TSCR1_TSFRZ		EQU	%00100000		;	Timer Stops While in Freeze Mode
TSCR1_TFFCA		EQU	%00010000		;	Timer Fast Flag Clear All
TSCR1_PRNT		EQU	%00001000		;	Precision Timer
TTOV			EQU	$47				;	Toggle On Overflow - bit mapped
;
TCTL1			EQU	$48				;	Output Mode - 2-bit mapped 00 = none, 01 = toggle, 10 = clear, 11 = set
TCTL1_BITS7		EQU	%11000000		; bits for Timer 7 mode
TCTL1_TOGL7		EQU	%01000000
TCTL1_CLR7		EQU	%10000000
TCTL1_SET7		EQU	%11000000
TCTL1_BITS6		EQU	%00110000		; bits for Timer 6 mode
TCTL1_TOGL6		EQU	%00010000
TCTL1_CLR6		EQU	%00100000
TCTL1_SET6		EQU	%00110000
TCTL1_BITS5		EQU	%00001100		; bits for Timer 5 mode
TCTL1_TOGL5		EQU	%00000100
TCTL1_CLR5		EQU	%00001000
TCTL1_SET5		EQU	%00001100
TCTL1_BITS4		EQU	%00000011		; bits for Timer 5 mode
TCTL1_TOGL4		EQU	%00000001
TCTL1_CLR4		EQU	%00000010
TCTL1_SET4		EQU	%00000011
;
TCTL2			EQU	$49				;	
TCTL2_BITS3		EQU	%11000000		; bits for Timer 3 mode
TCTL2_TOGL3		EQU	%01000000
TCTL2_CLR3		EQU	%10000000
TCTL2_SET3		EQU	%11000000
TCTL2_BITS2		EQU	%00110000		; bits for Timer 2 mode
TCTL2_TOGL2		EQU	%00010000
TCTL2_CLR2		EQU	%00100000
TCTL2_SET2		EQU	%00110000
TCTL2_BITS1		EQU	%00001100		; bits for Timer 1 mode
TCTL2_TOGL1		EQU	%00000100
TCTL2_CLR1		EQU	%00001000
TCTL2_SET1		EQU	%00001100
TCTL2_BITS0		EQU	%00000011		; bits for Timer 0 mode
TCTL2_TOGL0		EQU	%00000001
TCTL2_CLR0		EQU	%00000010
TCTL2_SET0		EQU	%00000011
;
TCTL3			EQU	$4A				;	Input Capture Mode - 2-bit mapped - 00 = disabled, 01 = rising, 10 = falling, 11 = both
TCTL3_BITS7		EQU	%11000000		; bits for Timer 7 mode
TCTL3_RIS7		EQU	%01000000
TCTL3_FAL7		EQU	%10000000
TCTL3_BOTH7		EQU	%11000000
TCTL3_BITS6		EQU	%00110000		; bits for Timer 6 mode
TCTL3_RIS6		EQU	%00010000
TCTL3_FAL6		EQU	%00100000
TCTL3_BOTH6		EQU	%00110000
TCTL3_BITS5		EQU	%00001100		; bits for Timer 5 mode
TCTL3_RIS5		EQU	%00000100
TCTL3_FAL5		EQU	%00001000
TCTL3_BOTH5		EQU	%00001100
TCTL3_BITS4		EQU	%00000011		; bits for Timer 5 mode
TCTL3_RIS4		EQU	%00000001
TCTL3_FAL4		EQU	%00000010
TCTL3_BOTH4		EQU	%00000011
;
TCTL4			EQU	$4B				;
TCTL4_BITS3		EQU	%11000000		; bits for Timer 3 mode
TCTL4_RIS3		EQU	%01000000
TCTL4_FAL3		EQU	%10000000
TCTL4_BOTH3		EQU	%11000000
TCTL4_BITS2		EQU	%00110000		; bits for Timer 2 mode
TCTL4_RIS2		EQU	%00010000
TCTL4_FAL2		EQU	%00100000
TCTL4_BOTH2		EQU	%00110000
TCTL4_BITS1		EQU	%00001100		; bits for Timer 1 mode
TCTL4_RIS1		EQU	%00000100
TCTL4_FAL1		EQU	%00001000
TCTL4_BOTH1		EQU	%00001100
TCTL4_BITS0		EQU	%00000011		; bits for Timer 0 mode
TCTL4_RIS0		EQU	%00000001
TCTL4_FAL0		EQU	%00000010
TCTL4_BOTH0		EQU	%00000011
;
TIE				EQU	$4C				;	bit mapped
;;TSCR2			EQU	$4E				;
TSCR2			EQU	$4D				;
TSCR2_TOI		EQU	%10000000		; overflow interrupt
TSCR2_TCRE		EQU	%00001000		; 
TSCR2_PR2		EQU	%00000100		; prescalers
TSCR2_PR1		EQU	%00000010
TSCR2_PR0		EQU	%00000001
;;TFLG1			EQU	$4F				;	bit mapped
TFLG1			EQU	$4E				;	bit mapped
TFLG2			EQU	$4F				;	
TFLG2_TOF		EQU	%10000000		; Timer Overflow Flag
;
TC0				EQU	$50
TC0H			EQU	$50				;	Timer 0 Counter High
TC0L			EQU	$51				;	Timer 0 Counter Low
TC1				EQU	$52
TC1H			EQU	$52
TC1L			EQU	$53
TC2				EQU	$54
TC2H			EQU	$54
TC2L			EQU	$55
TC3				EQU	$56
TC3H			EQU	$56
TC3L			EQU	$57
TC4				EQU	$58
TC4H			EQU	$58
TC4L			EQU	$59
TC5				EQU	$5A
TC5H			EQU	$5A
TC5L			EQU	$5B
TC6				EQU	$5C
TC6H			EQU	$5C
TC6L			EQU	$5D
TC7				EQU	$5E
TC7H			EQU	$5E
TC7L			EQU	$5F
;
PACTL			EQU	$60				; Pulse Accumulator Control
PAFLG			EQU	$61				;
PACNTH			EQU	$62				;
PACNTL			EQU	$63				;
OCPD			EQU	$6C				;
PTPSR			EQU	$6E				;
;
;	ADC $70 - $9F
;
ATDCTL0			EQU	$70				; ADC Module Controls
ATDCTL0_WRAP	EQU	%00001111		; Wrap channel bits
;
ATDCTL1			EQU	$71				;
ATDCTL1_ETRIG	EQU	%10000000		; External trigger select
ATDCTL1_SRES	EQU	%01100000		; resolution bits 00 = 8, 01 = 10
ATDCTL1_SRES10	EQU	%00100000
ATDCTL1_SMP_DIS	EQU	%00010000		; Discharge before conversion
ATDCTL1_ETRIGCH	EQU	%00001111		; External trigger select bits
;
ATDCTL2			EQU	$72				;
ATDCTL2_AFFC	EQU	%01000000		; Fast Flag Clear All
ATDCTL2_ETRIGLE	EQU	%00010000		; External trigger Level/Edge
ATDCTL2_ETRIGP	EQU	%00001000		; External trigger Polarity
ATDCTL2_ETRIGE	EQU	%00000100		; External trigger Enable
ATDCTL2_ASCIE	EQU	%00000010		; ATD Sequence Complete Interrupt Enable
ATDCTL2_ACMPIE	EQU	%00000001		; ATD Compare Interrupt Enable
;
ATDCTL3			EQU	$73				;
ATDCTL3_DJM		EQU	%10000000		; Result Register Data Justification 0 = left, 1 = right
ATDCTL3_SEQLEN	EQU	%01111000		; Conversion Sequence Length
ATDCTL3_FIFO	EQU	%00000100		; Result Register FIFO mode
ATDCTL3_FRZ		EQU	%00000011		; Debug mode freeze bits
;
ATDCTL4			EQU	$74				;
ATDCTL4_SMP		EQU	%11100000		; Sample Time Select bits
ATDCTL4_PRS		EQU	%00011111		; ATD Clock Prescaler
;
ATDCTL5			EQU	$75				;
ATDCTL5_SC		EQU	%01000000		; Special Channel Conversion Bit
ATDCTL5_SCAN	EQU	%00100000		; Continuous Conversion Sequence Mode
ATDCTL5_MULT	EQU	%00010000		; Multi-Channel Sample Mode
ATDCTL5_CHAN	EQU	%00001111		; Analog Input Channel Select Code
;
ATDSTAT0		EQU	$76				; Status
ATDSTAT0_SCF	EQU	%10000000		; Sequence Complete Flag
ATDSTAT0_ETORF	EQU	%00100000		; External Trigger Overrun Flag
ATDSTAT0_FIFOR	EQU	%00010000		; Result Register Overrun Flag
ATDSTAT0_CC		EQU	%00001111		; Conversion Counter Bits
;
ATDCMPEH		EQU	$78				; Compare Enable for Conversion Number {bit[0..11] }
ATDCMPEL		EQU	$79				;
;
ATDSTAT2H		EQU	$7A				; Conversion Complete Flags { bit[0..11] }
ATDSTAT2L		EQU	$7B				;
;
ATDDIENH		EQU	$7C				; ATD Digital Input Enable on channel { bit[0..11] }
ATDDIENL		EQU	$7D				;
;
ATDCMPHTH		EQU	$7E				; Compare Operation Higher Than Enable for conversion number {bit[0..1] }
ATDCMPHTL		EQU	$7F				;
;
ATDDR0			EQU	$80				; ADC Results (double register)
ATDDR1			EQU	$82
ATDDR2			EQU	$84
ATDDR3			EQU	$86
ATDDR4			EQU	$88
ATDDR5			EQU	$8A
ATDDR6			EQU	$8C
ATDDR7			EQU	$8E
ATDDR8			EQU	$90
ATDDR9			EQU	$92
ATDDR10			EQU	$94
ATDDR11			EQU	$96
ATDDR12			EQU	$98
ATDDR13			EQU	$9A
ATDDR14			EQU	$9C
ATDDR15			EQU	$9E
;
;	PWM	$A0 - $C7
;
PWME			EQU	$A0				; Enable
PWMPOL			EQU	$A1				; Polarity
PWMCLK			EQU	$A2				; Clock Select ( A,B,AB,etc )
PWMPRCLK		EQU	$A3				; Prescale A,B
PWMCAE			EQU	$A4				; Center Align
PWMCTL			EQU	$A5				; Control - Concat and freeze
PWMCLKAB		EQU	$A6				; AB Clock Select
PWMSCLA			EQU	$A8				; Scale A
PWMSCLB			EQU	$A9				; Scale B
PWMCNT0			EQU	$AC				; 8-bit Up/Down Counters
PWMCNT1			EQU	$AD
PWMCNT2			EQU	$AE
PWMCNT3			EQU	$AF
PWMCNT4			EQU	$B0
PWMCNT5			EQU	$B1
PWMCNT6			EQU	$B2
PWMCNT7			EQU	$B3
PWMPER0			EQU	$B4				; Periods
PWMPER1			EQU	$B5
PWMPER2			EQU	$B6
PWMPER3			EQU	$B7
PWMPER4			EQU	$B8
PWMPER5			EQU	$B9
PWMPER6			EQU	$BA
PWMPER7			EQU	$BB
PWMDTY0			EQU	$BC				; Duty Cycles
PWMDTY1			EQU	$BD
PWMDTY2			EQU	$BE
PWMDTY3			EQU	$BF
PWMDTY4			EQU	$C0
PWMDTY5			EQU	$C1
PWMDTY6			EQU	$C2
PWMDTY7			EQU	$C3
;
;	SCI 0 $C8 - $CF
;
SCI0ASR1		EQU	$C8				; Aux mode
SCI0ACR1		EQU	$C9				; Aux Mode
SCI0ACR2		EQU	$CA				; Aux Mode
;
SCI0BDH			EQU	$C8				; Baud Rate divider
SCI0BDL			EQU	$C9				; SCI baud rate = SCI bus clock / (16 x SBR[12:0])
;
SCI0CR1			EQU	$CA				; Control Reg 1
SCICR1_LOOPS	EQU	%10000000		; Loop Mode
SCICR1_SCISWAI	EQU	%01000000		; Stop in Wait Mode
SCICR1_RSRC		EQU	%00100000		; RCVR Source in Loop Mode (can connect RX to TX internally)
SCICR1_M		EQU	%00010000		; 9 Bit Mode ( 0 = 8,1,N )
SCICR1_WAKE		EQU	%00001000		; Wake on address Mark
SCICR1_ILT		EQU	%00000100		; Idle Line Type
SCICR1_PE		EQU	%00000010		; Parity Enable
SCICR1_PT		EQU	%00000001		; Parity Type if PE ( 0 = even )
;
SCI0CR2			EQU	$CB				; 
SCICR2_TIE		EQU	%10000000		; TX Int Enable
SCICR2_TCIE		EQU	%01000000		; TX Complete Interrupt Enable
SCICR2_RIE		EQU	%00100000		; RX Int Enable
SCICR2_ILIE		EQU	%00010000		; Idle Line Int Enable
SCICR2_TE		EQU	%00001000		; TX Enable
SCICR2_RE		EQU	%00000100		; RX Enable
SCICR2_RWU		EQU	%00000010		; RX Wake Up
SCICR2_SBK		EQU	%00000001		; Send Break
;
SCI0SR1			EQU	$CC				; Status Flag Register - clears interrupts - applies to all SCIx
SCISR1_TDRE		EQU	%10000000		; TD Reg Empty
SCISR1_TC		EQU	%01000000		; Transmit Complete
SCISR1_RDRF		EQU	%00100000		; RD Reg Full
SCISR1_IDLE		EQU	%00010000		; Idle Line Flag
SCISR1_OR		EQU	%00001000		; Overrun
SCISR1_NF		EQU	%00000100		; Noise Flag
SCISR1_FE		EQU	%00000010		; Framing Error
SCISR1_PF		EQU	%00000001		; Parity Error
;
SCI0SR2			EQU	$CD				; Status Reg 2 - Alternate mode stuff
;
SCI0DRH			EQU	$CE				; Data Reg High
SCI0DRL			EQU	$CF				; Data Reg Low
;
;	SCI 1 $D8 - $D7
;
SCI1BDH			EQU	$D0				; 
SCI1ASR1		EQU	$D0				; 
SCI1BDL			EQU	$D1				; 
SCI1ACR1		EQU	$D1				; 
SCI1CR1			EQU	$D2				; 
SCI1ACR2		EQU	$D2				; 
SCI1CR2			EQU	$D3				; 
SCI1SR1			EQU	$D4				; 
SCI1SR2			EQU	$D5				; 
SCI1DRH			EQU	$D6				; 
SCI1DRL			EQU	$D7				; 
;
;	SPI 0 $D8 - $DF
;
SPI0CR1			EQU	$D8				; Control Register 1
SPICR1_SPIE		EQU	%10000000		;  Int enable
SPICR1_SPE		EQU	%01000000		;  SPI enable
SPICR1_SPTIE	EQU	%00100000		;  TX Int enable
SPICR1_MSTR		EQU	%00010000		;  Master enable
SPICR1_CPOL		EQU	%00001000		;  Clock Polarity
SPICR1_CPHA		EQU	%00000100		;  Clock Phase
SPICR1_SSOE		EQU	%00000010		;  Slave Select Output Enable
SPICR1_LSBFE	EQU	%00000001		;  LSB First enable
;
SPI0CR2			EQU	$D9				; Control Register 2
SPICR2_XFRW		EQU	%01000000		; 16 Bit XFER
SPICR2_MODFEN	EQU	%00010000		; Mode Fault Enable
SPICR2_BIDIROE	EQU	%00001000		; OE in Bidi Mode
SPICR2_SPISWAI	EQU	%00000010		; Stop in Wait Mode
SPICR2_SPC0		EQU	%00000001		; Serial Pin 0
;
SPI0BR			EQU	$DA				; Baud Rate Register
SPIBR_SPPR		EQU	%01110000		; PreSelection bits
SPIBR_SPR		EQU	%00000111		; Selection bits
SPIBR_12KHZ		EQU	%01110111		; slowest rate
SPIBR_130KHZ	EQU	%00100110		; 130.21khz
SPIBR_12MHZ		EQU	%00000000		; fastest rate
;
SPI0SR			EQU	$DB				; Status Register
SPISR_SPIF		EQU	%10000000		; Int Flag
SPISR_SPTEF		EQU	%00100000		; TX Int Flag
SPISR_MODF		EQU	%00010000		; Mode Fail Flag
;
SPI0DRH			EQU	$DC				; Data Hi  { 15..8 }
SPI0DRL			EQU	$DD				; Data Low { 7..0 }
;
;	SCI 2 $E8 - $EF
;
SCI2BDH			EQU	$E8				; 
SCI2ASR1		EQU	$E8				; 
SCI2BDL			EQU	$E9				; 
SCI2ACR1		EQU	$E9				; 
SCI2CR1			EQU	$EA				; 
SCI2ACR2		EQU	$EA				; 
SCI2CR2			EQU	$EB				; 
SCI2SR1			EQU	$EC				; 
SCI2SR2			EQU	$ED				; 
SCI2DRH			EQU	$EE				; 
SCI2DRL			EQU	$EF				; 
;
;	SPI 1 $F0 - $F7
;
SPI1CR1			EQU	$F0				; 
SPI1CR2			EQU	$F1				; 
SPI1BR			EQU	$F2				; 
SPI1SR			EQU	$F3				; 
SPI1DRH			EQU	$F4				; 
SPI1DRL			EQU	$F5				; 
;
;	SPI 2 $F8 - $FF
;
SPI2CR1			EQU	$F8				; 
SPI2CR2			EQU	$F9				; 
SPI2BR			EQU	$FA				; 
SPI2SR			EQU	$FB				; 
SPI2DRH			EQU	$FC				; 
SPI2DRL			EQU	$FD				; 
;
;	FLASH Module FTMRG  $100 - $113
;
FCLKDIV			EQU	$100			; Flash Clock Divider
FCLKDIV_FDIVLD	EQU	$80				; - Clock Divider Loaded (RO)
FCLKDIV_FDIVLCK	EQU	$40				; - Clock Divider Locked
FCLKDIV_DivMask	EQU	$3F				; - Clock Divider Bits
FCLKDIV_1		EQU	$00				; -- 1.0 to 1.6 MHz Bus Clock
FCLKDIV_2		EQU	$01				; -- 1.6 to 2.6
FCLKDIV_3		EQU	$02				; -- 2.6 to 3.6
FCLKDIV_4		EQU	$03				; -- 3.6 to 4.6
FCLKDIV_5		EQU	$04				; -- 4.6 to 5.6
FCLKDIV_6		EQU	$05				; -- 5.6 to 6.6		POSTDIV = 3 (Default) 
FCLKDIV_7		EQU	$06				; -- 6.6 to 7.6
FCLKDIV_8		EQU	$07				; -- 7.6 to 8.6		POSTDIV = 2 (Default)
FCLKDIV_9		EQU	$08				; -- 8.6 to 9.6
FCLKDIV_10		EQU	$09				; -- 9.6 to 10.6
FCLKDIV_11		EQU	$0A				; -- 10.6 to 11.6
FCLKDIV_12		EQU	$0B				; -- 11.6 to 12.6	POSTDIV = 1 (Default)
FCLKDIV_13		EQU	$0C				; -- 12.6 to 13.6
FCLKDIV_14		EQU	$0D				; -- 13.6 to 14.6
FCLKDIV_15		EQU	$0E				; -- 14.6 to 15.6
FCLKDIV_16		EQU	$0F				; -- 15.6 to 16.6
FCLKDIV_17		EQU	$10				; -- 16.6 to 17.6
FCLKDIV_18		EQU	$11				; -- 17.6 to 18.6
FCLKDIV_19		EQU	$12				; -- 18.6 to 19.6
FCLKDIV_20		EQU	$13				; -- 19.6 to 20.6
FCLKDIV_21		EQU	$14				; -- 20.6 to 21.6
FCLKDIV_22		EQU	$15				; -- 21.6 to 22.6
FCLKDIV_23		EQU	$16				; -- 22.6 to 23.6
FCLKDIV_24		EQU	$17				; -- 23.6 to 24.6
FCLKDIV_25		EQU	$18				; -- 24.6 to 25.6	POSTDIV = 0 (Default)
;
FSEC			EQU	$101			; Flash Security Register
FSEC_KEYEN		EQU	$C0				; - Backdoor Key Security Enable Bits
FSEC_KEYEN_EN	EQU	$80				; -- Enabled ( all other patterns are Disabled )
FSEC_RNV		EQU	$3C				; - Reserved Nonvolatile Bits
FSEC_SEC		EQU	$03				; - Flash Security Bits
FSEC_SEC_NOT	EQU	$02				; -- Unsecured (all other patterns are Secured)
;
FCCOBIX			EQU	$102			; Flash CCOB Index Register
FCCOBIX_Bits	EQU	$03				; - Common Command Register Index
;
FCNFG			EQU	$104			; Flash Configuration Register
FCNFG_CCIE		EQU	$80				; - Command Complete Interrupt Enable
FCNFG_IGNSF		EQU	$10				; - Ignore Single Bit Fault
FCNFG_FDFD		EQU	$02				; - Force Double Bit Fault Detect
FCNFG_FSFD		EQU	$01				; - Force Single Bit Fault Detect
;
FERCNFG			EQU	$105			; Flash Error Configuration Register
FERCNFG_DFDIE	EQU	$02				; - Double Bit Fault Detect Interrupt Enable
FERCNFG_SFDIE	EQU	$01				; - Single Bit Fault Detect Interrupt Enable
;
FSTAT			EQU	$106			; Flash Status Register
FSTAT_CCIF		EQU	$80				; - Command Complete Interrupt Flag
FSTAT_ACCERR	EQU	$20				; - Flash Access Error Flag
FSTAT_FPVIOL	EQU	$10				; - Flash Protection Violation Flag
FSTAT_MGBUSY	EQU	$08				; - Memory Controller Busy Flag
FSTAT_RSVD		EQU	$04				; - Reserved Bit
FSTAT_MGSTAT	EQU	$03				; - Memory Controller Command Completion Status Flag
;
FERSTAT			EQU	$107			; Flash Error Status Register
FERSTAT_DFDIF	EQU	$02				; - Double Bit Fault Detect Interrupt Flag
FERSTAT_SFDIF	EQU	$01				; - Single Bit Fault Detect Interrupt Flag
;
FPROT			EQU	$108			; P-Flash Protection Register
FPROT_FPOPEN	EQU	$80				; - Flash Protection Operation Enable
FPROT_RNV6		EQU	$40				; - Reserved Nonvolatile Bit
FPROT_FPHDIS	EQU	$20				; - Flash Protection Higher Address Range Disable
FPROT_FPHS		EQU	$18				; - Flash Protection Higher Address Size
FPROT_RNV		EQU	$07				; - Reserved Nonvolatile Bits
;
EEPROT			EQU	$109			; EEPROM Protection Register
EEPROT_DPOPEN	EQU	$80				; - EEPROM Protection Control
EEPROT_DPSbits	EQU	$1F				; - EEPROM Protection Size
EEPROT_DPS_32	EQU	$00				; -- $0400 – $041F
EEPROT_DPS_64	EQU	$01				; -- $0400 – $043F
EEPROT_DPS_96	EQU	$02				; -- $0400 – $045F
EEPROT_DPS_128	EQU	$03				; -- $0400 – $047F
EEPROT_DPS_160	EQU	$04				; -- $0400 – $049F
EEPROT_DPS_192	EQU	$05				; -- $0400 – $04BF
EEPROT_DPS_224	EQU	$06				; -- $0400 – $04BF
EEPROT_DPS_256	EQU	$07				; -- $0400 – $04BF
EEPROT_DPS_288	EQU	$08				; -- $0400 – $04BF
EEPROT_DPS_320	EQU	$09				; -- $0400 – $04BF
EEPROT_DPS_352	EQU	$0A				; -- $0400 – $04BF
EEPROT_DPS_384	EQU	$0B				; -- $0400 – $04BF
EEPROT_DPS_416	EQU	$0C				; -- $0400 – $04BF
EEPROT_DPS_448	EQU	$0D				; -- $0400 – $04BF
EEPROT_DPS_480	EQU	$0E				; -- $0400 – $04BF
EEPROT_DPS_512	EQU	$0F				; -- $0400 – $05FF
;
FCCOB			EQU	$10A			; Flash Common Command Object Register
FCCOBHI			EQU	$10A
FCCOBLO			EQU	$10B
FCCOB_EVAB		EQU	$01				; Erase Verify All Blocks
FCCOB_EVB		EQU	$02				; Erase Verify Block
FCCOB_EVPS		EQU	$03				; Erase Verify P-Flash Section
FCCOB_RO		EQU	$04				; Read Once
FCCOB_PP		EQU	$06				; Program P-Flash
FCCOB_PO		EQU	$07				; Program Once
FCCOB_EAB		EQU	$08				; Erase All Blocks
FCCOB_EFB		EQU	$09				; Erase Flash Block
FCCOB_EPS		EQU	$0A				; Erase P-Flash Sector
FCCOB_UF		EQU	$0B				; Unsecure Flash
FCCOB_VBAK		EQU	$0C				; Verify Backdoor Access Key
FCCOB_SUML		EQU	$0D				; Set User Margin Level
FCCOB_SFML		EQU	$0E				; Set Field Margin Level
FCCOB_EVEES		EQU	$10				; Erase Verify EEPROM Section
FCCOB_PEE		EQU	$11				; Program EEPROM
FCCOB_EEES		EQU	$12				; Erase EEPROM Sector
;
FOPT			EQU	$110			; Flash Option Register
;
FCMD_VerifyALL			EQU	$01				; verify all blocks erased 
FCMD_VerifyBlock		EQU	$02				; verify specific block erased
FCMD_VerifyPsect		EQU	$03				; verify P Section erased
FCMD_ReadOnce			EQU	$04				; read  dedicated 64 byte field that was programmed once
FCMD_ProgramP			EQU	$06				; Program P section phrase
FCMD_ProgramOnce		EQU	$07				; Program dedicated 64 byte P section (write once)
FCMD_EraseAll			EQU	$08				; Erase all P and D blocks (must be un protected)
FCMD_EraseBlock			EQU	$09				; Erase P or D block
FCMD_EraseAllP			EQU	$0A				; Erase all P sector blocks
FCMD_EraseSector		EQU	$0A				; Erase P sector
FCMD_UnsecurePD			EQU	$0B				; Erase all P and D blocks then release security
FCMD_VerBackdoor		EQU	$0C				; Verify Backdoor Access Key
FCMD_SetUserMargin		EQU	$0D				; Set user Margin Level
FCMD_SetFieldMargin		EQU	$0E				; Set Field Margin Level
FCMD_EraseVerEEPROM		EQU	$10				; Erase Verify EEPROM Section
FCMD_ProgramEEPROM		EQU	$11				; Program EEPROM
FCMD_EraseEEPROMsector	EQU	$12				; Erase EEPROM Sector
;
;	INt Base
;
IVBR	EQU		$120			; Interrupt module base ( not RESET nor COP )
;
;	CAN  $140 - $17F
;
PTT		EQU		$240			; Port T Data							PORT T
PTIT	EQU		$241			; INPUT State Register ( R Only)
DDRT	EQU		$242			; Port T Data Direction
PERT	EQU		$244			; PullUp Enable
PPST	EQU		$245			; Pull Up/Down ( Falling Edge Sensitivity / Pull Up = 0 )
;
;	$246,$247 reserved
;
PTS		EQU		$248			; I/O state								PORT S
PTIS	EQU		$249			; INPUT State Register ( R Only)
DDRS	EQU		$24A			; Data Direction
PERS	EQU		$24C			; PullUp Enable
PPSS	EQU		$24D			; Pull Up/Down ( Falling Edge Sensitivity / Pull Up = 0 )
WOMS	EQU		$24E			; Wired-OR Mode Select
;
PRR0	EQU		$24F			; Alternate Pin Routing
;
PTM		EQU		$250			; I/O state								PORT M
PTIM	EQU		$251			; INPUT State Register ( R Only)
DDRM	EQU		$252			; Data Direction
PERM	EQU		$254			; PullUp Enable
PPSM	EQU		$255			; Pull Up/Down ( Falling Edge Sensitivity / Pull Up = 0 )
WOMM	EQU		$256			; Wired-OR Mode Select
;
PKGCR	EQU		$257			; Package Code Reg
;
PTP		EQU		$258			; I/O state								PORT P
PTIP	EQU		$259			; INPUT State Register ( R Only)
DDRP	EQU		$25A			; Data Direction
PERP	EQU		$25C			; PullUp Enable
PPSP	EQU		$25D			; Pull Up/Down ( Falling Edge Sensitivity / Pull Up = 0 ) 
PIEP	EQU		$25E			; Interrupt Enable
PIFP	EQU		$25F			; Interrupt Flags
;
;	ANALOG Comparator - Not available on G96
;
;ACMPC	EQU		$260			; 
;ACMPS	EQU		$261			; 
;
PTJ		EQU		$268			; Port J Data 							PORT J
PTIJ	EQU		$269			; INPUT State Register ( R Only)
DDRJ	EQU		$26A			; Data Direction
PERJ	EQU		$26C			; PullUp Enable
PPSJ	EQU		$26D			; Pull Up/Down ( Up = 0 )
PIEJ	EQU		$26E			; Interrupt Enable
PIFJ	EQU		$26F			; Interrupt Flags
;
PT0AD	EQU		$270			; I/O state								PORT AD
PT1AD	EQU		$271			; I/O state
PTI0AD	EQU		$272			; INPUT State Register ( R Only)
PTI1AD	EQU		$273			; INPUT State
DDR0AD	EQU		$274			; Data Direction 8-11
DDR1AD	EQU		$275			; Data Direction 0-7
;
;RVACTL	EQU		$276			; reference voltage attenuator - not available on G96
;
PRR1	EQU		$277			; Alternate Pin Routing (QFP100 Only)
;
PER0AD	EQU		$278			; PullUp Enable 8-11					PORT AD
PER1AD	EQU		$279			; PullUp Enable 0-7
PPS0AD	EQU		$27A			; Pull Up/Down 8-11 ( Up = 0 )
PPS1AD	EQU		$27B			; Pull Up/Down 0-7 ( Up = 0 )
PIE0AD	EQU		$27C			; Interrupt Enable 8-11
PIE1AD	EQU		$27D			; Interrupt Enable 0-7
PIF0AD	EQU		$27E			; Interrupt Flags 8-11
PIF1AD	EQU		$27F			; Interrupt Flags 0-7
;
;	More Clock and Power Management $2F0 - $2FF
;
CPMULVCTLEQU	EQU	$2F1			; 
CPMUAPICTLEQU	EQU	$2F2			; 
CPMUACLKTREQU	EQU	$2F3			; 
CPMUAPIRHEQU	EQU	$2F4			; 
CPMUAPIRLEQU	EQU	$2F5			; 
IRCTRIMHEQU		EQU	$2F8			; 
IRCTRIMLEQU		EQU	$2F9			; 
CPMUOSCEQU		EQU	$2FA			; 
CPMUPROTEQU		EQU	$2FB			; 

; DAC Not available on G96

;
;	DAC 0 $3C0 - $3C7
;

;
;	DAC 1 $3C8 - $3CF
;




