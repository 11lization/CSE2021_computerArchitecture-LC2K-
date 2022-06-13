        lw 0 1 two
        lw 0 2 five
L1      add 0 1 2
        add 2 2 3
        add 0 1 2
L1      add 3 3 4       we used same label twice
        beq 3 4 L1
        noop
done    halt
two     .fill 2
five    .fill 5
