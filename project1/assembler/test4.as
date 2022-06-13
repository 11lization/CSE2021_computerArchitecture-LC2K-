start   lw 0 1 three
        lw 0 2 four
        add 0 1 3
        add 0 2 1
        add 0 3 2
        add 1 2 4
        beq 1 2 done
        noop
done    halt
three   .fill 3
four    .fill 4
