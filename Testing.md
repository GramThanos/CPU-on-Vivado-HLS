# Testing the CPU

## Test programs executed

Register file initialization before program execution.
```text
R1  00000000000000000000000000000001
R2  00000000000000000000000000000010
R3  00000000000000000000000000000011
R4  00000000000000000000000000000100
```

Test program 1 (unrelated commands with NOPs between them)
```Assebly
#func rd   rt   rt
ADD   R5   R1   R2
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
ADD   R6   R3   R4
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
ADD   R7   R1   R3
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
AND   R7   R1   R3
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
```

Test program 2 (unrelated commands)
```Assebly
#func rd   rt   rt
ADD   R8   R1   R2
ADD   R9   R3   R4
ADD   R10  R1   R3
NOP   R0   R0   R0
```

Test program 3 (commands with relations)
```Assebly
#func rd   rt   rt
ADD   R11  R1   R2
ADD   R12  R11  R3
ADD   R13  R12  R4
SUB   R14  R11  R1
OR    R14  R3   R2
NOP   R0   R0   R0
```