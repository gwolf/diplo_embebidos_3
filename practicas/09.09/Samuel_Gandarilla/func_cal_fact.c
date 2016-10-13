int fact (int a) {
    int temp, fac;
    temp=a-1;
    fac=a;
    while(temp>=1)
     {
       fac=fac*temp;
        temp--;
     }
    return fac;
}


