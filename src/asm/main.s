#нулевой столбец - дошел ли зомби до газонокосилки или нет (~ - не дошел, = - дошел)

.text
.globl step
.EQU width, 11
.EQU height, 5

# %rdi - указатель на поле (массив размером 55 символов) 

# procedure
step:
    movq $0, %rcx
    movq %rdi, %rsi #сохраняем, чтобы двигать зомби

lawnowers:             
    cmpb $'~', (%rsi) 
    jnz run_lawnower #т.е. не равны <=> зомби уже доходил до газонокосилки
        
    addq $11, %rsi

    incq %rcx
    cmpq $5, %rcx #условие окончанмя цикла
    je zombies

    jmp lawnowers

run_lawnower:
    movq %rsi, %rbx
    movq $0, %rax

search_lawnower:
    incq %rbx
    incq %rax
    cmpq $11, %rax
    je last_cell

    cmpb $'>', (%rbx)
    jnz search_lawnower

    movb $'.', (%rbx)
    incq %rbx

    cmpb $'~', (%rbx)
    je last_cell
    cmpb $'=', (%rbx)
    je last_cell

    movb $'.', (%rbx)
    incq %rbx
    movb $'.', (%rbx)
    incq %rbx
    movb $'>', (%rbx)

last_cell:              # конец строки, газонокосилку убираем
    addq $11, %rsi
    incq %rcx
    jmp lawnowers 

zombies:
    movq $0, %rcx  # счётчик
    movq %rdi, %rsi

zombies_step:
    cmpq $56, %rcx
    je bullets

    movb (%rsi), %al       # загружаем символ из текущей ячейки в регистр AL

    # Проверяем, если символ является зомби, то сдвигаем его
    cmpb $'&', %al
    je is_zombie
    cmpb $'$', %al
    je is_zombie
    cmpb $'@', %al
    je is_zombie

    # Если это не зомби, сдвигаем символ
    incq %rsi              # увеличиваем указатель на следующий элемент
    incq %rcx              # увеличиваем счетчик
    jmp zombies_step       # продолжаем цикл

is_zombie:
    incq %rcx 
    decq %rsi
    cmpb $'>', (%rsi)
    jz change_to_1 #меняется на '=' - в следующем запуске step газонокосилка поедет

    cmpb $'=', (%rsi)
    je finish_bad

    cmpb $'#', (%rsi)
    je wallnut_full

    cmpb $'*', (%rsi)
    je bullet

    jmp later

bullet:
    incq %rsi

    cmpb $'&', (%rsi)
    je small_zomb

    cmpb $'$', (%rsi)
    je middle_zomb

    cmpb $'@', (%rsi)
    je big_zomb

small_zomb:
    movb $'.', (%rsi)
    decq %rsi
    movb $'.', (%rsi)
    addq $2, %rsi
    incq %rcx
    jmp zombies_step

middle_zomb:
    movb $'.', (%rsi)
    decq %rsi
    movb $'&', (%rsi)
    addq $2, %rsi
    incq %rcx
    jmp zombies_step

big_zomb:
    movb $'.', (%rsi)
    decq %rsi
    movb $'$', (%rsi)
    addq $2, %rsi
    incq %rcx
    jmp zombies_step

wallnut_full:
    movb $'|', (%rsi)
    addq $2, %rsi
    jmp zombies_step

later:
    incq %rsi
    movb (%rsi), %al
    movb $'.', (%rsi)
    decq %rsi
    movb %al, (%rsi)

    incq %rsi
    jmp zombies_step

change_to_1:
    decq %rsi
    movb $'=', (%rsi)  
    addq $3, %rsi
    incq %rcx

    jmp zombies_step

plants: 
    movq %rdi, %rsi
    movq $0, %rcx #счетчик

plants_step: 
    cmpq $56, %rcx
    je generate_zombie

    incq %rsi
    incq %rcx

    cmpb $'?', (%rsi)
    je load_a_gun

    cmpb $'!', (%rsi)
    je fire

    jmp plants_step

load_a_gun:
    movb $'!', (%rsi)
    jmp plants_step

fire:
    movb $'?', (%rsi)
    incq %rsi

find_empty_place:
    cmpb $'&', (%rsi)
    je kill_zombie
    cmpb $'$', (%rsi)
    je wound_zombie
    cmpb $'@', (%rsi)
    je wound_biggest_zombie

    cmpb $'.', (%rsi)
    je place_fire

    incq %rsi
    jmp find_empty_place

place_fire:
    movb $'*', (%rsi)
    movq %rdi, %rsi
    addq %rcx, %rsi
    jmp plants_step

kill_zombie:
    movb $'.', (%rsi)
    movq %rdi, %rsi
    addq %rcx, %rsi
    jmp plants_step

wound_zombie:
    movb $'&', (%rsi)
    movq %rdi, %rsi
    addq %rcx, %rsi
    jmp plants_step

wound_biggest_zombie:
    movb $'$', (%rsi)
    movq %rdi, %rsi
    addq %rcx, %rsi
    jmp plants_step

bullets:
    movq %rdi, %rsi
    movq $55, %rcx
    addq $54, %rsi

bullet_step:
    cmpq $0, %rcx
    je plants

    cmpb $'*', (%rsi)
    je run

    decq %rsi
    decq %rcx

    jmp bullet_step

run:
    movb $'.', (%rsi)

run_bullet:
    incq %rsi
    cmpb $'=', (%rsi)
    je last_bullet_cell

    cmpb $'~', (%rsi)
    je last_bullet_cell

    cmpb $'&', (%rsi)
    je hit_small_zomb

    cmpb $'$', (%rsi)
    je hit_middle_zomb

    cmpb $'@', (%rsi)
    je hit_big_zomb

    cmpb $'.', (%rsi)
    jnz run_bullet

    movb $'*', (%rsi)
    movq %rdi, %rsi
    addq %rcx, %rsi
    decq %rcx
    decq %rsi
    jmp bullet_step

hit_small_zomb:
    movb $'.', (%rsi)
    decq %rsi
    movb $'.', (%rsi)
    decq %rsi
    jmp bullet_step

hit_middle_zomb:
    movb $'&', (%rsi)
    decq %rsi
    movb $'.', (%rsi)
    decq %rsi
    jmp bullet_step

hit_big_zomb:
    movb $'$', (%rsi)
    decq %rsi
    movb $'.', (%rsi)
    decq %rsi
    jmp bullet_step

last_bullet_cell:
    decq %rsi
    movb $'.', (%rsi)
    jmp bullet_step

generate_zombie:
    rdtsc
    movq $0, %rdx
    movq $6, %rcx
    div %rcx

    movq %rdx, %rbx #сгенерированное случайное число - номер грядки, в которой появится зомби

    rdtsc
    movq $0, %rdx
    movq $3, %rcx
    div %rcx

    movq %rdx, %rax #сгенерированное случайное число - вид зомби

    cmpq $1, %rbx
    je place_on_line_1

    cmpq $2, %rbx
    je place_on_line_2

    cmpq $3, %rbx
    je place_on_line_3

    cmpq $4, %rbx
    je place_on_line_4

    cmpq $5, %rbx
    je place_on_line_5

    jmp finish_good

place_on_line_1:
    addq $10, %rdi

    cmpq $0, %rax
    je place_small_zombie

    cmpq $1, %rax
    je place_middle_zombie

    cmpq $2, %rax
    je place_big_zombie

place_on_line_2:
    addq $21, %rdi
    
    cmpq $0, %rax
    je place_small_zombie

    cmpq $1, %rax
    je place_middle_zombie

    cmpq $2, %rax
    je place_big_zombie

place_on_line_3:
    addq $32, %rdi
    
    cmpq $0, %rax
    je place_small_zombie

    cmpq $1, %rax
    je place_middle_zombie

    cmpq $2, %rax
    je place_big_zombie

place_on_line_4:
    addq $43, %rdi
    
    cmpq $0, %rax
    je place_small_zombie

    cmpq $1, %rax
    je place_middle_zombie

    cmpq $2, %rax
    je place_big_zombie

place_on_line_5:
    addq $54, %rdi
    
    cmpq $0, %rax
    je place_small_zombie

    cmpq $1, %rax
    je place_middle_zombie

    cmpq $2, %rax
    je place_big_zombie

place_small_zombie:
    movb $'&', (%rdi)
    jmp finish_good

place_middle_zombie:
    movb $'$', (%rdi)
    jmp finish_good

place_big_zombie:
    movb $'@', (%rdi)
    jmp finish_good

finish_bad:
    movq $-1, %rax
    jmp end

finish_good:
    movq $1, %rax
    jmp end

end:
    ret
