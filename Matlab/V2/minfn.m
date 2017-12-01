function min_index = minfn(OPEN,OPEN_COUNT,goalx,goaly)
% This function takes the list OPEN as its input and returns the index of 
% the node that has the least cost
temp=[];
i=1;
set=0;
j=0;
for k=1:OPEN_COUNT
     if (OPEN(k,1)==1)
         temp(i,:)=[OPEN(k,:) k]; 
         if OPEN(k,2)==goalx && OPEN(k,3)==goaly
             set=1;
             j=k;
         end
         i=i+1;
     end
end
 if set == 1 % one of the successors is the goal node so send this node
     min_index=j;
 end
 %Send the index of the smallest node
 if size(temp ~= 0)
  [~,temp_min]=min(temp(:,8));
  min_index=temp(temp_min,9);
 else
     min_index=-1;%The temp_array is empty i.e No more paths are available.
 end
    
end

