loop:
	jmp loop ; Keeping the CPU busy by entering an infinite loop

times 510-($-$$) db 0 ; Filling the rest of the sector with 0s
dw 0xAA55 ; Indicating that this is a boot sector
