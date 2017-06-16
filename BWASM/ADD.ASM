data segment
buf db 80, 0, 78 dup(0)
x db 10 dup(0)
y db 10 dup(0)
opx dw 0
opy dw 0
rslt db 20 dup(0)
hexdec db '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
data ends

code segment
assume cs:code, ds:data
main:
  mov ax, data
  mov ds, ax
  mov si, offset buf
  mov di, offset x
  call input
  mov opx, ax
  mov di, offset y
  call input
  mov opy, ax
  mov ax, opx
  mul opy;DX:AX
  call output
  mov dx, 0
  mov ah, 4ch
  int 21h  

input:
  push bx
  push cx
  push dx
  push si
  push di
  
  mov dx, 0
  mov ah, 0ah
  int 21h
  mov ah, 02h
  mov dl, 0dh
  int 21h
  mov dl, 0ah
  int 21h
  mov si, 2
  mov ch, 0
  mov cl, buf[1]
chagn:
  mov al, [si]
  sub al, '0'
  mov [di], al
  inc si
  inc di
  loop chagn
  mov byte ptr [di], 10
  
  pop si
  push si
  mov ch, 0	
  mov cl, buf[1]
  sub cl, 1
  mov bh, 0
  mov bl, [si]
conv:
  cmp cl, 0
  jz break1
  mov ah, 0
  mov al, 10
  mul bx
  mov bx, ax
  inc si
  add bl, [si]
  adc bh, 0
  loop conv
break1:
  mov ax, bx
  
  pop di
  pop si
  pop dx
  pop cx
  pop bx
  ret
  
output:
  push ax
  push bx
  push cx
  push dx
  push dx
  push ax
  mov ah, 2
  mov si, offset x
outx:
  mov dl, [si]
  add dl, '0'
  int 21h
  inc si
  cmp byte ptr [si], 10
  jnz outx
  mov dl, '*'
  int 21h
  mov si, offset y
outy:
  mov dl, [si]
  add dl, '0'
  int 21h
  inc si
  cmp byte ptr [si], 10
  jnz outy
  mov dl, '='
  int 21h
  mov dl, 0dh
  int 21h
  mov dl, 0ah
  int 21h
  
  pop ax
  pop dx
  push dx
  push ax
  mov di, offset rslt
  mov si, 0
decagn:
  push ax
  mov ax, dx
  mov dx, 0
  mov bx, 10
  div bx
  mov cx, ax
  pop ax
  div bx
  mov [di], dl
  inc di
  inc si
  mov dx, cx
  cmp dx, 0
  jne decagn
  cmp ax, 0
  je break2
  cmp ax, 10
  jnb decagn
  inc si
  mov [di], al
  jmp break3
break2:
  dec di
break3:
  mov cx, si
  mov ah, 2
opdec:
  mov dl, [di]
  add dl, '0'
  dec di
  int 21h
  loop opdec
  mov dl, 0dh
  int 21h
  mov dl, 0ah
  int 21h
 
  pop ax
  pop dx
  push dx
  push ax
  mov di, offset rslt
  mov si, 0
hexagn:
  push ax
  mov ax, dx
  mov dx, 0
  mov bx, 10h
  div bx
  mov cx, ax
  pop ax
  div bx
  mov [di], dl
  inc di
  inc si
  mov dx, cx
  cmp dx, 0
  jne hexagn
  cmp ax, 0
  je break4
  cmp ax, 10h
  jnb hexagn
  inc si
  mov [di], al
  jmp break5
break4:
  dec di
break5:
  
  mov cx, si
  mov ah, 2
ophex:
  mov bx, offset hexdec
  mov al, [di]
  dec di
  xlat
  mov dl, al
  int 21h
  loop ophex
  mov dl, 'h'
  int 21h
  mov dl, 0dh
  int 21h
  mov dl, 0ah
  int 21h
  
  pop ax
  pop dx
  push dx
  push ax
  mov cx, 16
  mov bx, 8000h
  mov si, 5
opbindx:
  dec si
  cmp si, 0
  jnz nos1
  push ax
  push dx
  mov ah, 2
  mov dl, ' '
  int 21h
  mov si, 4
  pop dx
  pop ax
nos1:
  mov di, dx
  and di, bx
  jz zero0
  push dx
  push ax
  mov dl, '1'
  mov ah, 2
  int 21h
  pop ax
  pop dx
  rol dx, 1
  loop opbindx
  jmp end1
zero0:
  push dx
  push ax
  mov dl, '0'
  mov ah, 2
  int 21h
  pop ax
  pop dx
  rol dx, 1
  loop opbindx
end1:
  
  mov dl, ' '
  mov ah, 2
  int 21h
  pop ax
  pop dx
  push dx
  push ax
  mov cx, 16
  mov bx, 8000h
  mov si, 5
opbinax:
  dec si
  cmp si, 0
  jnz nos2
  push ax
  push dx
  mov dl, ' '
  mov ah, 2
  int 21h
  mov si, 4
  pop dx
  pop ax
nos2:
  mov di, ax
  and di, bx
  jz zero1
  push dx
  push ax
  mov dl, '1'
  mov ah, 2
  int 21h
  pop ax
  pop dx
  rol ax, 1
  loop opbinax
  jmp end2
zero1:
  push dx
  push ax
  mov dl, '0'
  mov ah, 2
  int 21h
  pop ax
  pop dx
  rol ax, 1
  loop opbinax
end2:  
  mov ah, 2
  mov dl, 'b'
  int 21h
  mov dl, 0dh
  int 21h
  mov dl, 0ah
  int 21h

  pop ax
  pop dx
  pop dx
  pop cx
  pop bx
  pop ax
  ret
code ends
end main