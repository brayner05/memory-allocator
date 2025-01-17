
.text
.globl _brk
.globl _sbrk

# Set the program break to the address passed in %rdi.
_brk:
    pushq %rbp
    movq %rsp, %rbp
    
    movq $12, %rax      # Set syscall to brk(1)
    movq %rdi, %rdi     # The parameter passed to _brk will be used as an argument
    syscall             # Call brk(1)

    popq %rbp
    ret

# Increase the program break by the amount passed in %rdi
_sbrk:
    pushq %rbp
    movq %rsp, %rbp
    
    pushq %rdi          # Store the offset on the stack
    xorq %rdi, %rdi     # Set argument to 0
    call _brk           # Call _brk with 0 as the argument
    popq %rdi           # Retrieve the offset from the stack
    pushq %rax          # Store the current program break on the stack
    
    addq (%rsp), %rdi   # Add the offset to the current program break
    call _brk           # Set the program break to the old program break + offset

    popq %rax           # Return the old program break
    popq %rbp
    ret
