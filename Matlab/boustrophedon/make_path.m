function [path]=make_path(A,x,dist,no_of_cells,idx)
%% intro
% takes the map with boundaries and obstacles
% and generates the path in each subcell 
% input - A: map with boundaries and obstacles
%         x: lines vector (which tells how many subcells are there in each
%         row)
%         dist: how much robot can sense while following path (to create
%         that much gap b/w the path lines)
%         no_of_cells: number of subcells used to generate no of subpaths
%         idx: boundary ids
% output- path

% now this is simply a snake game
%% code
path=cell(no_of_cells,1);
flag=0;% move right
k=1;
temp=idx(1);
for i=1:size(idx,1)
    [p,c_no]=find_boundary_ids(x(1:idx(i)-1),A(1:idx(i)-1,:));
end
for i=1:dist:size(A,1) 
    kprev=k;
    if i>temp
       if (find(idx==temp)+1)<=size(idx,1)
            [p,k]=find_boundary_ids(x(1:temp-1),A(1:temp-1,:));
            temp=idx(find(idx==temp)+1);
            flag=0;
            k=k+1;
       else
           temp=size(A,1);
           [p,k]=find_boundary_ids(x(1:temp-1),A(1:temp-1,:));
           flag=0;
       end
    end
m= no_of_lines(A(i,:));
    if(x(i)==0) %skip row
        continue;
    else
        if flag==0
            j=2;
            while(j<size(A,2))%moving right
                if (A(i,j)==0)
                    j=j+1;
                    continue
                end
                path{k}=[path{k};j,i];
                j=j+1;
                if (A(i,j-1)==1)&&(A(i,j)==0)
                    k
                    i
                    j
                    
                    k=k+1
                end
            end
            flag=1;
        else
            j=size(A,2)-1;
            while (j>1)
                if (A(i,j)==0)
                    j=j-1;
                    continue
                end
                
                path{k}=[path{k};j,i];
                j=j-1;
                if (A(i,j+1)==1)&(A(i,j)==0)
%                     [output, idy]=no_of_lines(A(i,:))
%                     k=k+sum(find(idy<j))
%                     k
%                     i
%                     j
                    k=k-1
                end
            end
            flag=0;
        end
    end

end

end