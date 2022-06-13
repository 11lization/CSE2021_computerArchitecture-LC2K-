        lw 0 1 three
        lw 0 2 temp
        add 0 0 3
        lw 0 4 neg1
        lw 0 5 tar2
        jalr 5 6
        sw 0 3 80
        halt
tar     add 3 1 3
        add 2 4 2
        beq 0 2 done
        beq 0 0 tar
done    jalr 6 7
tar2    .fill tar
three   .fill 3
temp    .fill 1
neg1    .fill -1
