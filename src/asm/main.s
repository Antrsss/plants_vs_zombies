.text
# playing field is strictly in rax DO NOT MOVE IT TO OTHER REGISTERS PLEASE I'M BEGGING
.globl exponent
.EQU width, 9
.EQU height, 5

exponent:
    movq $1, %rax      # результат в %rax
    jmp condition      # переход к проверке условия
mainloop:
    mulq %rdi          # %rax = %rax *%rdi
    decq %rsi
condition:
    cmpq $0, %rsi
    jnz mainloop
    ret
