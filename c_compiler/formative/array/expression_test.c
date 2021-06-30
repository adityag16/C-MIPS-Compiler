int f()
{
    int i;
    int x[8];
    int acc;
    x[0] = 8;
    x[1] = 9;
    x[2] = 10;
    x[3] = 11;
    x[4] = 12;
    x[5] = 13;
    x[6] = 14;
    x[7] = 15;
    acc = 0;
    for(i=8; i<16; i++){
        acc = acc + x[i-8];
    }
    return acc;

}