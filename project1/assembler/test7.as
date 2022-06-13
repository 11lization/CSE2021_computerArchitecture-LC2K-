        lw 0 1 one
        lw 0 2 two
        lw 0 3 three    three is undefined label
        add 0 1 4
        add 0 2 4
        add 0 3 4
        add 1 2 5
        noop
done    halt
one     .fill 1
two     .fill 2
