        lw 0 1 A0
        lw 0 2 A1
        lw 0 3 A2
        lw 0 4 L1
        add 0 1 6
        jalr 4 5
L2      add 6 2 6
        beq 0 6 L3
        noop
        jalr 4 5
L3      add 1 3 3
        beq 3 3 done
        noop
done    halt
A0      .fill 4
A1      .fill -1
A2      .fill 2
L1      .fill L2
