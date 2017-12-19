function [map] = pseudosense(s,model,map)
% Uses provided model to check and mark obstacles in the incrementally
% generated map. 
% if sensor detects an obstacle it marks the corresponding coordinate as -1 in the map

for i=1:-1:-1
    for j=1:-1:-1
        xs=s(1,1)+i;
        ys=s(1,2)+j;
        if xs>0 && ys>0
            if model(xs,ys)==-1
                map(xs,ys)=-1; %sensor(2+i,2+j)=-1;
            end
        end
    end
end

end

