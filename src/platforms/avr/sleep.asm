.text

    .global sleep
    sleep:
        push r23
        push r22
        push r21
        mov r22, r25
        mov r21, r24
        ldi r23, 0x01
        out 0x17, r23
        ldi r23, 0xFF
        out 0x18, r23
        rcall sleep2
        ldi r23, 0x0
        out 0x18, r23
        mov r25, r22
        mov r24, r21
        rcall sleep2
        pop r21
        pop r22
        pop r23
        ret

    sleep2: ; clockCycles: UInt16 => r25:r24
        sbiw r24, 1 ; r25:r24
        brne sleep2
        ret
