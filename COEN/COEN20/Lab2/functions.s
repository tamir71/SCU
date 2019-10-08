.thumb_func

Add:    
        LDR     R0,a
        LDR     R1,b
        ADD     R0,R0,R1
        BX      LR

.thumb_func

Less1:
        LDR     R0,a
        SUB     R0,1
        BX      LR

.thumb_func

Square2x:
        LDR     R0,x
        ADD     R0,R0,R0
        BL      Square
        BX      LR

.thumb_func

Last:
        LDR     R0,x
        LDR     R1,x
        BL      SquareRoot
        ADD     R0,R0,R1
        BX      LR
