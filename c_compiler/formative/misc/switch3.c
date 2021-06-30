int g(int x)
{
    switch(x){
        case 0:
        case 1:
            switch(x){
                case 0:
                case 1: 
                    x++;
                    break;

                case 2:
                case 3:
                    break;
                case 4:
                    break;
            }
        case 2:
        case 3:
            break;
    }

    return x;
}
