start:
xor eax, eax
xor ebx, ebx
xor ecx, ecx
xor edx, edx   

mov bl, 1
add esp, string - start 
mov  ecx, esp
mov  dl, 5
mov al, 4
int 0x80               

mov al, 1
mov bl, 1
dec bl
int 0x80 

string:
db "FUCK",0xa