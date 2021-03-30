.text

    .global exit
    exit:
        cli ; Disable all interrupts.
        sleep ; Put the microcontroller into sleep mode.
        rjmp .-4 ; As soon as the watchdog stops the sleep mode, go back to it.
