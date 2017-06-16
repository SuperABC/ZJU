data segment
buf db 80, 0, 78 dup(0);filename
ex db 'exit'
tmpf db 256 dup(0);buf
hexdec db '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
opf db 'Cannot open file!', 0dh, 0ah, '$'
showline db '00000000:            |           |           |             '
showcont db '                '
handle dw 0
tmpb db 4 dup(0);offset
filesize db 4 dup(0);file_size
pageb dw 0;bytes_in_buf
rowb db 0;bytes_in_row
rows db 0
next dw 0
data ends

code segment
assume cs:code, ds:data
main:
	mov ax, data
	mov ds, ax
opagn:
	call input
	call open
	jnz opagn
	call fsize
mloop:
	call fread
	call fshow
	call getch
	jnz mloop
	call close
	jmp opagn
endpro:
	mov dx, 0
	mov ah, 4ch
	int 21h  
	
input:
	push ax
	push bx
	push cx
	push dx
	mov dx, offset buf
	mov ah, 0ah
	int 21h
	mov bl, buf[1]
	mov buf[bx+2], 0
	mov ah, 02h
	mov dl, 0dh
	int 21h
	mov dl, 0ah
	int 21h
	mov ax, data
	mov es, ax
	cld
	lea si, buf[2]
	lea di, ex[0]
	mov cx, 4
	repe cmpsb
	jnz notq
	mov ah, 4ch
	int 21h
notq:
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
open:
	push ax
	push bx
	push cx
	push dx
	mov ah, 3dh
	mov al, 0
	mov dx, offset buf[2]
	int 21h
	mov handle, ax
	adc handle, 0
	cmp handle, ax
	je success
	mov dx, offset opf
	mov ah, 09h
	int 21h
	mov ax, 1
	jmp oend
success:
	mov ax, 0
oend:
	and ax, ax
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
fsize:
	push ax
	push bx
	push cx
	push dx
	mov ah, 42h
    mov al, 2
    mov bx, handle
    mov cx, 0
    mov dx, 0
    int 21h
    mov word ptr filesize[2], dx
    mov word ptr filesize[0], ax
	mov word ptr tmpb[2], 0
	mov word ptr tmpb[0], 0
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
fread:
	push ax
	push bx
	push cx
	push dx
	mov ax, word ptr filesize[0]
	sub ax, word ptr tmpb[0]
	mov bx, word ptr filesize[2]
	sbb bx, word ptr tmpb[2];bx:ax
	cmp bx, 0
	jne full
	cmp ax, 100h
	jb nfull
full:
	mov pageb, 100h
	jmp fend
nfull:
	mov pageb, ax
fend:
	mov ah, 42h
    mov al, 0
    mov bx, handle
    mov cx, word ptr tmpb[2]
    mov dx, word ptr tmpb[0]
    int 21h
	mov ah, 3Fh
    mov bx, handle
    mov cx, pageb
    mov dx, data
    mov ds, dx
    mov dx, offset tmpf
    int 21h
	
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
fshow:
	push ax
	push bx
	push cx
	push dx
	push si
	push di
	mov ax, 0b800h
	mov es, ax
	mov di, 0
	cld
	mov cx, 780h
	mov al, 20h
	mov ah, 07h
	rep stosw;clear the screen
	mov ax, pageb
	add ax, 0fh
	mov bl, 10h
	div bl
	mov rows, al
	mov cl, rows
	mov ch, 0
	mov rows, 0
shagn:
	cmp cl, 1
	je lastr
	mov rowb, 10h
	sub pageb, 10h
	call showr;rowb = 每行字节数; tmpb = 第一字节地址; tmpf = 内容; rows = 行号;
	jmp shlo
lastr:
	mov ax, pageb
	mov rowb, al
	call showr;rowb = 每行字节数; tmpb = 第一字节地址; tmpf = 内容; rows = 行号;
	jmp shend
shlo:
	inc rows
	loop shagn
shend:
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
;rowb = 每行字节数; tmpb = 第一字节地址; tmpf = 内容; rows = 行号;
showr:
	push ax
	push bx
	push cx
	push dx
	mov al, rows
	mov bl, 10h
	mul bl
	push ax
	mov cx, word ptr tmpb[0]
	mov dx, word ptr tmpb[2]
	add cx, ax
	adc dx, 0;dx:cx
	mov al, dh
	call chhex
	mov showline[0], ah
	mov showline[1], al
	mov al, dl
	call chhex
	mov showline[2], ah
	mov showline[3], al
	mov al, ch
	call chhex
	mov showline[4], ah
	mov showline[5], al
	mov al, cl
	call chhex
	mov showline[6], ah
	mov showline[7], al
	pop bx
	
	mov cx, 16
	mov di, 10
	push bx
shhexagn:
	mov al, byte ptr tmpf[bx]
	call chhex
	mov byte ptr showline[di], ah
	inc di
	mov byte ptr showline[di], al
	inc di
	inc di
	inc bx
	mov ax, di
	sub al, 10
	mov dl, 3
	div dl
	cmp al, rowb
	jnb lnhexend
	loop shhexagn
lnhexend:
	cmp di, 58
	je nozz
	mov byte ptr showline[di], ' '
	inc di
	jmp lnhexend
nozz:
	pop bx
	mov cx, 16
	mov di, 59
shcont:
	mov dl, byte ptr tmpf[bx]
	mov byte ptr showline[di], dl
	inc di
	inc bx
	mov ax, di
	sub ax, 58
	cmp al, rowb
	ja lnend
	loop shcont
lnend:
	cmp di, 75
	je nosp
	mov byte ptr showline[di], ' '
	inc di
	loop lnend
nosp:
	mov ax, 0b800h
	mov es, ax
	mov al, 0a0h
	mov bl, rows
	mul bl
	mov di, ax
	mov bx, 0
print:
	cmp showline[bx], '|'
	mov ah, 0fh
	jnz dark
	cmp bx, 59
	jnb dark
	jmp light
dark:
	mov ah, 07h
light:
	mov al, showline[bx]
	mov es:[di], ax
	inc di
	inc di
	inc bx
	cmp bx, 74
	jna print
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
chhex:
    push bx
	push cx
	push dx
	mov bx, offset hexdec
	mov ah, 0
	mov cl, 4
	shl ax, cl
	mov ch, al
	mov al, ah
	xlat
	mov dh, al
	mov al, ch
	mov cl, 4
	shr al, cl
	xlat
	mov ah, dh
	pop dx
	pop cx
	pop bx
	ret
	
getch:
	push ax
	push bx
	push cx
	push dx
    mov ah, 0
    int 16h
	cmp ax, 11bh
	je getend1
	cmp ax, 4800h
	je keyup
	cmp ax, 4900h
	je keyup
	cmp ax, 5000h
	je keydown
	cmp ax, 5100h
	je keydown
	cmp ax, 4700h
	je pageup1
	cmp ax, 4737h
	je pageup1
	cmp ax, 4F00h
	je pagedown1
	cmp ax, 4F31h
	je pagedown1
	jmp getfin
keyup:
    mov cx, word ptr tmpb[2]
    mov dx, word ptr tmpb[0]
	sub dx, 100h
	sbb cx, 0
	mov word ptr tmpb[2], cx
	mov word ptr tmpb[0], dx
	jnc getfin1
	mov dx, 0
	mov cx, 0
	mov word ptr tmpb[2], cx
	mov word ptr tmpb[0], dx
	jmp getfin
getend1:
	jmp getend2
keydown:
    mov cx, word ptr tmpb[2]
    mov dx, word ptr tmpb[0]
	add dx, 100h
	adc cx, 0
	mov word ptr tmpb[2], cx
	mov word ptr tmpb[0], dx
	;add dx, 100h
	;adc cx, 0
	cmp cx, word ptr filesize[2]
	jb getfin
	cmp dx, word ptr filesize[0]
	jna getfin
	sub dx, 100h
	sbb cx, 0
	mov word ptr tmpb[2], cx
	mov word ptr tmpb[0], dx
	jmp getfin

getend2:
	jmp getend
pageup1:
	jmp pageup
pagedown1:
	jmp pagedown
getfin1:
	jmp getfin

pageup:
	mov word ptr tmpb[2], 0
	mov word ptr tmpb[0], 0
	jmp getfin
pagedown:
	mov cx, 0
	mov dx, 0
pdagn:
	add dx, 100h
	adc cx, 0
	cmp cx, word ptr filesize[2]
	jb pdagn
	cmp dx, word ptr filesize[0]
	jb pdagn
	sub dx, 100h
	sbb cx, 0
	mov word ptr tmpb[2], cx
	mov word ptr tmpb[0], dx
	jmp getfin
getfin:
	mov ax, 1
	and ax, ax
	jmp getcont
getend:
	mov ax, 0
	and ax, ax
	mov ax, 0b800h
	mov es, ax
	mov di, 0
	cld
	mov cx, 780h
	mov al, 20h
	mov ah, 07h
	rep stosw
getcont:
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
close:
	push ax
	push bx
	push cx
	push dx
	mov ah, 3Eh
    mov bx, handle
    int 21h
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
code ends
end main