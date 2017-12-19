function [short] = LOSsmoothen(path,map)
%UNTITLED14 Summary of this function goes here
%   Detailed explanation goes here
n=length(path);
k=1; j=1;
short=path(1,:);
while (short(size(short,1),1)~=path(n,1) || short(size(short,1),2)~=path(n,2))
    for i=n:-1:j
        if LOS(path(k,:),path(i,:),map)==1
            short=[short; path(i,:)];
            j=i+1;
            break    
        end
        
    end
    k=k+1;
end
end

