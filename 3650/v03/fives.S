/*
    - take a string as argv[1]
    - determine if all characters are 5's
    - print "all fives" if so
    - print "not all fives" if not

Examples:
    ./fives 5555   => all fives
    ./fives goat   => not all fives
    ./fives 5a5555   => not all fives
*/

    .global main
    .text

    // int all_match(char* text, char cc)
    /*
    while (*text) {
       if (*text != cc) {
          return 0
       }
       text++
    }
    return 1

Vars:
    - text is %rdi
    - cc is %sil
    - *text is %r10b
    */

all_match:
    enter $0, $0

all_matches_loop_cond:
    mov (%rdi), %r10b
    cmp $0, %r10b
    je all_matches_loop_done

    cmp %r10b, %sil
    je all_match_loop_next

    mov $0, %rax
    jmp all_matches_done

all_match_loop_next:
    inc %rdi
    jmp all_matches_loop_cond
all_matches_loop_done:
    mov $1, %rax

all_matches_done:
    leave
    ret


    /*
    for (int ii = 0; ii < strlen(text); ++ii) {
       if (text[ii] != cc) { return 0 }
    }
    return 1
    */



    
    // int main(int argc, char* argv[])
    /*
       if (all_match(argv[1], '5') {
          puts("all fives")
       }
       else {
          puts("not all fives")
       }
       return 0

       Variable mapping: (empty?)
    */

main:
    enter $0, $0

    mov 8(%rsi), %rdi
    mov $'5, %sil
    call all_match
    cmp $0, %rax
    jne main_then
    jmp main_else

main_then:
    mov $all_fives, %rdi
    jmp main_done

main_else:
    mov $not_all_fives, %rdi
    jmp main_done

main_done:
    call puts
    mov $0, %rax
    leave
    ret

    .data
all_fives:  .string "all fives"
not_all_fives:  .string "not all fives"
