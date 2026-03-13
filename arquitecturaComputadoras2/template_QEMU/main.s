	.data
	f: .dword 1
	g: .dword 2
	h: .dword 3
	i: .dword 4
	j: .dword 5
	.text
	ldr x0,f
	ldr x1,g
	ldr x2,h
	ldr x3,i
	ldr x4,j

	MUL x2,x2,x3
	ADD x1,x1,x2
	SUB x0,x1,x4
	
end:
infloop: B infloop
