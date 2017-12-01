function index = indexof(OPEN,x,y)

    i=1;
    while OPEN(i,2) ~= x || OPEN(i,3) ~= y
        i=i+1;
    end
    index=i;
end
