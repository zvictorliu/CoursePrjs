
                PRESERVE8
                

        AREA  UCOS_ARM_ASM_INT, CODE, READONLY
           

;*********************************************************************************************************
;                                            IRQ HANDLER
;
;        This handles all the IRQs
;        Note: FIQ Handler should be written similar to this
;
;*********************************************************************************************************

        IMPORT  OSIntEnter
        IMPORT  OSIntExit

        IMPORT  OSIntCtxSwFlag
        IMPORT  _IntCtxSw

  
        MACRO     
$IRQ_AsmEntery HANDLER $IRQ_CEntry
        EXPORT  $IRQ_AsmEntery              ; ����ı��
        IMPORT  $IRQ_CEntry                 ; ���õ��ⲿ���
                
$IRQ_AsmEntery
        stmfd sp!,{r0-r3,r12,lr}

        bl OSIntEnter
        bl $IRQ_CEntry
        bl OSIntExit

        ldr r0,=OSIntCtxSwFlag
        ldr r1,[r0]
        cmp r1,#1
        beq _IntCtxSw

        ldmfd sp!,{r0-r3,r12,lr}
        subs pc,lr,#4
        
        MEND
 
;���е��жϰ����µĸ�ʽ��ע��(��������ĺ궨��)
;$IRQ_AsmEntery HANDLER $IRQ_CEntry




;��ʱ��0�ж�
IRQASMTimer0  HANDLER IRQCTimer0

;��ʱ��1�ж�
;IRQASMTimer1 HANDLER IRQCTimer1

;����0�ж�
;IRQASMUart0  HANDLER IRQCUart0

;����0�ж�
;IRQASMUart1  HANDLER IRQCUart1


;�ⲿ�ж�0�ж�
;IRQASMEx0     HANDLER IRQCEx0

;�ⲿ�ж�1�ж�
;IRQASMEx1    HANDLER IRQCEx1

;�ⲿ�ж�20�ж�
;IRQASMEx2    HANDLER IRQCEx2

;SPI�ж�
;IRQASMSpi    HANDLER IRQCSpi

;I2C�ж�        
;IRQASMI2c    HANDLER IRQCI2c

          END
   
                        
