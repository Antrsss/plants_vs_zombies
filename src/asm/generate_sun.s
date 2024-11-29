.data
playing_field: .asciz "0>!%.@..%..0>..?@.%%%.0>.?*..%...1>&........0>!!.@....."

.text
.globl _start

_start:
    #пропиши сам :D

generate_sun:
    movq $0, %rcx #счетчик клетки поля
    movq %rsi, %rbx #счетчик солнышек (второй параметр процедуры)
                    #в rdi находится строка - 1ый параметр процедуры

field_loop:
    cmpq $55, %rcx
    je add_auto_sun

    cmpb $'%', (%rdi)
    je add_sun

    incq %rcx
    incq %rdi

    jmp field_loop

add_sun:
    addq $25, %rbx
    incq %rcx
    incq %rdi
    jmp field_loop

add_auto_sun:
    addq $5, %rbx #типа автоматическая генерация солнышек
    movq %rbx, %rax

    ret
