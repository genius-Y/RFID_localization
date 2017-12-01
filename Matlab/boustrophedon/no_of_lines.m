function [output, idy]=no_of_lines(x)
%% intro
% to find no of lines by horizontal intersections on the map
% check the continuity of the free space in the row matrix
% input- x:row matrix
% output- ouput:no of intersections+1 which is no_ of lines
%       - idy:ids of critical points
%% code
if x(1)==1
    output=1;
else
    output=0;
end
idy=[];

for i=2:size(x,2)
    %if there is change from obstacle to free space increase output
    % 0 is black ie obstacle and 1 is white free space
    if ((x(i-1)==0)& (x(i)==1))
        output=output+1;
        idy=[idy;i-1];
    end
    if((x(i-1)==1)& (x(i)==0))
        idy=[idy;i-1];
    end    
end
end

