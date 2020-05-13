.text
_entry:
    movl $72,%eax
    movl $msg,%ebx
    int $0x80
    movl $1,%eax
    int $0x80
msg:
    .ascii "hello,shiwei\n"
