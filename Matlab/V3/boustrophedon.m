function [scp,map] = boustrophedon(s_start,map,model)
%   Boustrophedon function given a start point, list of backtracking points
%   and incrementally constructed covered area as model constucts 
%   boustrophedon patterns and returns the critical point, the updated 
%   model and the list of backtracking points.
%   Obstacle=-1, Virtual Obstacle=-2, Target = 0,Robot=1,Space=2

% map=zeros(size(model));             % Intiate with empty map
s=s_start;          % s_start of form (x-coorsinate,y-coordinate)
map(s(1,1),s(1,2))=-2;
move=1;
while move==1 % s not a critical point
    
    sensor=pseudosense(s,model);
    for i=1:-1:-1
        for j=1:-1:-1
        xi=s(1,1)+i;
        yi=s(1,2)+j;
        if xi>0 && yi>0
            if sensor(2+i,2+j)==-1
               map(xi,yi)=-1;
            end
        end
        end
    end
    
    
    [s,map,move] = Oxmove(s,map);
    if move==0
        scp=s;      
    end
end