        lw 0 1 B1
        lw 0 6 B2
        add 1 1 2
        add 1 2 3
done    add 2 3 4
        add 4 1 5
        beq 5 6 done
        noop
        halt
B1      .fill 2
B2      .fill 70
