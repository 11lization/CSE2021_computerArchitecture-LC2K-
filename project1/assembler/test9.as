        lw 0 1 five
        lw 1 2 3
start   add 1 2 1
        beq 0 1 7654321     offset field don't fit in 16 bits
        beq 0 0 start
        noop
done    halt
five    .fill 5
pos1    .fill 1
neg1    .fill -1
stAddr  .fill start
