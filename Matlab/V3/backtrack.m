function [bp] = backtrack(path,map,scp)
b=[]; xs=scp(1,1); ys=scp(1,2); d=[];
for i=1:size(path,1)
    x=path(i,1); y=path(i,2);
    mu= myval(x+1,y,x+1,y-1)+myval(x+1,y,x+1,y+1)+...
        myval(x-1,y,x-1,y-1)+myval(x-1,y,x-1,y+1)+...
        myval(x,y-1,x-1,y-1)+myval(x,y-1,x+1,y+1);
    if mu>0
        b=[b;[x,y]];
    end
end
for j=1:size(b,1)
    dist=sqrt((b(j,1)-xs)^2+(b(j,2)-ys)^2);
    d=[d, dist];
end
[distance,i]=min(d);
bp=b(i,:);
    function b = myval(x1,y1,x2,y2)
        if map(x1,y1)==0 && (map(x2,y2)==-1 || map(x2,y2)==-2)
            b=1;
        else
            b=0;
        end
    end

end

