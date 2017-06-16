data segment
  row dw 0h
  col dw 0h
  tmp dw 0h
data ends

code segment
assume cs:code, ds:data
  mov ax, 0b800h;clear the scree with black background.
  mov es, ax
  mov di, 0h
  mov al, ' '
  mov ah, 07h
  mov cx, 7d1h
clrscr:
  mov es:[di], ax
  add di, 2h
  dec cx
  jnz clrscr
  
  mov di, 0h;initialize the variables.
  mov row, 0h 
  mov col, 0h

  mov cx, 100h;the main loop to print.
print:
  mov ax, row;calculate the position of this charactor.
  mov bl, 160
  mul bl
  mov di, ax
  mov ax, col
  mov bl, 14
  mul bl
  add di, ax
  
  mov ax, col;calculate which charactor is to be shown.
  mov bl, 19h
  mul bl
  mov dx, row
  add ax, dx
  mov ah, 4h
  mov es:[di], ax;print the charactor with red.
  inc di
  inc di
  mov ah, 0h;print the ascii number of this charactor.
  mov bl, 10h
  div bl
  mov tmp, ax
  mov ah, 2h
  add ax, '0'
  mov dx, ax
  cmp dl, '9'
  jna nch1
  add ax, 7h
nch1:
  mov es:[di], ax
  inc di
  inc di
  mov ax, tmp
  mov al, ah
  mov ah, 2h
  add ax, '0'
  mov dx, ax
  cmp dl, '9'
  jna nch2
  add ax, 7h
nch2:
  mov es:[di], ax
  inc row
  mov bx, 19h
  sub bx, row
  jnz cont;
  mov row, 0h;if this colume is full, turn to next colume.
  inc col
cont:
  dec cx
  jnz print
  
  mov si, 1000h;delay a few seconds and exit.
outloop:
  xor cx, cx
inloop:
  dec cx
  jnz inloop
  dec si
  jnz outloop
  mov ax, 4c00h
  int 21h
code ends
end