function [idx,c_no]=find_boundary_ids(x,A)
%% intro
%    known the no of lines in each row
%    finding the discontinuity in the no of lines in the rows creates 
%    boundaries those ids of rows of image are returned as output
%    input - x:no_of_lines_vector
%            A:map with obstacles
%    output- idx:boundaries ids
%            c_no: no of subcells formed
%% code
idx=[];
c_no=no_of_lines(A(1,:));
for i=2: size(x,1)
   if  x(i-1)~=x(i)   
       [output1, idy1]=no_of_lines(A(i-1,:));
       [output2, idy2]=no_of_lines(A(i,:));
       if(output1>output2)
         idx=[idx;i-1];
         c_no=c_no+output2;
       else
         idx=[idx;i];
         c_no=c_no+output2;
       end
       
   end
end
end