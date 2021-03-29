.text

    .global exit
    exit:
        cli ; Disable all interrupts.
        sleep ; Put the microcontroller into sleep mode.
