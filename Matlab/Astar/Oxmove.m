function [s,map,move] = Oxmove(s,map)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
xs=s(1,1); ys=s(1,2); move=1;
if map(xs,ys+1) ~=-1 && map(xs,ys+1) ~=-2
        ys=ys+1;    
    elseif map(xs,ys-1) ~=-1 && map(xs,ys-1) ~=-2
        ys=ys-1;
    elseif map(xs+1,ys) ~=-1 && map(xs+1,ys) ~=-2
        xs=xs+1;
    elseif map(xs-1,ys) ~=-1 && map(xs-1,ys) ~=-2
        xs=xs-1;
    else
        move = 0;
end
    s=[xs,ys];
    map(s(1,1),s(1,2))=-2;
end

