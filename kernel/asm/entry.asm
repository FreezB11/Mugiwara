[BITS 32]
[EXTERN kernel_main]

_start:
    call kernel_main
    hlt