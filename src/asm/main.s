.globl exponent
 
.text
# Функция возвращает число в определенной степени
# Принимает два параметра:
# %rdi - число, возводимое в степень
# %rsi - степень, в которую надо возвести число
# Результат функции возвращается через регистр %rax
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
