function new_row = append2open(x,y,parentx,parenty,hn,gn,fn)
% Populates open list

new_row=[1,8];
new_row(1,1)=1;
new_row(1,2)=x;
new_row(1,3)=y;
new_row(1,4)=parentx;
new_row(1,5)=parenty;
new_row(1,6)=hn;
new_row(1,7)=gn;
new_row(1,8)=fn;
end

