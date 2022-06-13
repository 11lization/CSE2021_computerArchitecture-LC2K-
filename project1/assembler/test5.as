        lw 0 1 three
        lw 0 2 nthree
        lw 0 5 L2
        add 1 2 3
        beq 0 3 L1
        noop
L1      lw 0 4 one
        add 2 4 2
        beq 1 2 done
        noop
        jalr 5 6
done    halt
L2      .fill L1
one     .fill 1
three    .fill 3
nthree   .fill -3
