.code16
.global start

start:  # this starts bios
    movb $0x00, %ah
    movb $0x03, %al
    int $0x10

begin:  # this is the begenning of the code (the reason this inst in start is because i want to jmp here to loop without restarting bios
    movw $message, %si
    call print_char

gen_number:
    movb $0x00, %al     # make al 0x00
    outb %al, $0x70     # give 00 to the port 0x70 to tell the clock to give us seconds
    inb $0x71, %al      # read from the clock port 0x71 (this puts a binary encoded seconds time in al)
    and $0x0f, %al      # and al with 0x0f. This clears the first digit of the seconds (ex. makes 51 -> 01
    or $0x30, %al       # or 0x30 with al. This encodes as as ASCII
    movb %al, %bl       # store al in bl because many commands need al

read_char:
    movb $0x00, %ah     # these 2 lines call to the bios to read a character
    int $0x16           # it's ascii encodeing is in al
    movw $number, %si   # i load my number string into %si to print later
    movb %al, (%si)     # this replaces the first char of the number string (now in %si) with what is in al
    movb %al, %bh       # i then store al in bh because other functions need al
    call print_char     #this will print the user given char with \r\n

check:
    cmp %bh, %bl        # this compares bh (the user given char) with bl (the "random" number) and sets flags
    je right            # if they are equal this jumps to the right function
    movw $wrong_str, %si# if it doesnt jump (ie they are not the same) these lines load the wront_str into si and print it
    call print_char
    jmp begin           # this jumps to the begin functoin which loops over the whole program 

right:                  # this function loads the right_str and prints it then jumps to the begenning
    movw $right_str, %si
    call print_char
    jmp begin

print_char:         # this is a copy of the print_char from hello.s
    lodsb
    test %al, %al
    jz done
    movb $0x0E, %ah
    int $0x10
    jmp print_char

message:
    .string "What number am I thinking of (0-9)?"

wrong_str:
    .string "Wrong!\r\n"

right_str:
    .string "Right! Congragulations.\r\n"

number: #general 3byte string to print any character by replacing the first byte
    .string "\x00\r\n"

done: #this is here so the functions can properly return
    ret

.fill 510 - (. - start), 1, 0
.byte 0x55
.byte 0xAA
