#
# TEST CODE FOR SW
#
        # -----------------------------------------
        # Program section (known as text)
        # -----------------------------------------
        .text

# Start symbol (must be present), exported as a global symbol.
_start: .global _start

# Export main as a global symbol
        .global main

# Label for entry point of test code
main:
        ### TEST CODE STARTS HERE ###
       # A: your failing form
        li  x1, 0x2000
        li  x3, 0x67
        sw  x3, 0(x1)
        nop; nop; nop; ebreak

        # B: same, with NOPs after the li
        li  x1, 0x2000
        nop; nop; nop; nop
        sw  x3, 0(x1)
        nop; nop; nop; ebreak

        # C: base register at 0x2000 but an offset at the store
        li  x1, 0x2000
        nop; nop; nop; nop
        sw  x3, 8(x1)
        nop; nop; nop; ebreak
        # Data section
data:
        
