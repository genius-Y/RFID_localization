function [x]=create_boundaries(x,cp)
%% intro
% if there is a critical point creating a line makes more borders
% and that behaviour is not needed, the border should be made in the
% direction of free space till the obstacle
%input - cp:critical points uses y-coords
%         x: the whole map
%output- x:changed map (with better borders)

%% code

for iter=1:size(cp,1)
   iter
   i=cp(iter,1);
   k=cp(iter,2)+1;
   if(x(i,k)==1) %right side free space
       % 0 is black ie obstacle and 1 is white free space
       while(x(i,k+1)~=0)&&(k<size(x,2)-1)
           x(i,k)=0;
           k=k+1; %moving right side
       end
   end
   k=cp(iter,2)-1;
   if(x(i,k)==1) %left side free space
        % 0 is black ie obstacle and 1 is white free space 
        while((x(i,k-1)==1)&(k>2))
            x(i,k)=0;
            k=k-1;
        end
   end    
end
imshow(x);
end