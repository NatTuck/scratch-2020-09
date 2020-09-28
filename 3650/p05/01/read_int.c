
int*
get_a_pointer_to_five()
{
    // this never works
    // &five isn't a valid location after return
    //int five = 5;
    //return &five;
   
    // This is OK
    // as long as we remember to free the pointer
    // eventually
    int* five = malloc(sizeof(int));
    *five = 5;
    return five;
}

void
read_int(int* x)
{
    scanf("%d", x);
}

int
main()
{
    int zz;        // stack
    read_int(&zz); 

}

/*
stack:
  frame for main:
   - x
  frame for read_int:
   (nothing)


