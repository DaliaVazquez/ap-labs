int main()

{
    int c, nl, nw, nc, state;
    state = OUT;

    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n')
        ++nl;

    if (c == ' ' || c == '\n' || c == '\t')
        state = OUT;
    else if (state == OUT) {
        state = IN;
        ++nw;
    }
    }

    printf("Lines: %d,  Words: %d, Chars: %d\n", nl, nw, nc);
    return 0;
}