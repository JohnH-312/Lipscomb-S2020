.code32

.global strlen1
strlen1:
    #Prologue
    push %ebp       # Save old base pointer
    mov %esp, %ebp  # Set new base pointer     # Save any used registers: edi, esi, ebx

    # main stuffs, and put anser into eax
    # put the pointer into a register edi
    mov 8(%ebp), %ecx
    cmpb $0, (%ecx)
    jz end # if it points to nuthin, jump end, return 
    add $1, %ecx
    push %ecx
    call strlen1 # else recurse with s+1 + 1
    add $4, %esp
    inc %eax    # adds 1 to previeous return
    jmp done

end:
    # Epilogue  
    mov $0, %eax   
done:   
    mov %ebp,%esp   # Deallocate local variables
    pop %ebp        # Restore caller's base pointer
    ret

.global strlen2
strlen2:
    #Prologue
    push %ebp       # Save old base pointer
    mov %esp, %ebp  # Set new base pointer
    push %edi       # Save any used registers: edi, esi, ebx
    push %esi

    # main stuffs
    mov $0, %esi # set a register to 0 esi
loopy:
    mov 8(%ebp), %edi
    add %esi, %edi
    cmpb $0, (%edi)
    jz endo # check if the first char is 0, if so jump end
    inc %esi # add 1 to register esi

    jmp loopy # jump to loopy

endo:
    mov %esi, %eax
    # Epilogue       # Recover saved registers
    pop %esi        
    pop %edi
    mov %ebp,%esp   # Deallocate local variables
    pop %ebp        # Restore caller's base pointer
    ret

.global strlen3
strlen3:
#Prologue
    push %ebp       # Save old base pointer
    mov %esp, %ebp  # Set new base pointer
    push %edi       # Save any used registers: edi, esi, ebx
    push %esi

    # Main stuff
    mov 8(%ebp), %esi # set the pointer into register esi
    mov 8(%ebp), %edi # make a copy into register edi
loop:
    cmpb $0, (%edi)
    jz endy # check if it is 0 if so jump to end
    inc %edi # increment pointer (edi)
    jmp loop # jump back to loop

endy:
    sub %esi, %edi # put edi-esi into edi
    mov %edi, %eax # move edi into eax


    # Epilogue      # Recover saved registers
    pop %esi        
    pop %edi
    mov %ebp,%esp   # Deallocate local variables
    pop %ebp        # Restore caller's base pointer
    ret
