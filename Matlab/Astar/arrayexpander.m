function array = arrayexpander(x,y,goalx,goaly,hn,closed,sizex,sizey)
% Expand array function: Takes a node and returns expanded list of
% sucessors with calculated f(n) values for each. also ensures the
% successors are not on closed list
%   Arguments passed are:   (x,y) position of current node
%                           (goalx,goaly) Position of goal to calc g(n)
%                           h(n) distance to (x,y) from start
%                           closed all paths that have been explored
%                           (sizex,sizey) grid size
array=[];
    i=1;
    
    for j= 1:-1:-1
        for k= 1:-1:-1
            if (j~=k || j~=0)  %The node itself is not its successor
                succ_x = x+j;
                succ_y = y+k;
                if( (succ_x >0 && succ_x <=sizex) && (succ_y >0 && succ_y <=sizey))%node within array bound
                    flag=1;                    
                    for c1=1:size(closed,1)
                        if(succ_x == closed(c1,1) && succ_y == closed(c1,2))
                            flag=0;
                        end
                    end%End of for loop to check if a successor is on closed list.
                    if (flag == 1)
                        array(i,1) = succ_x;
                        array(i,2) = succ_y;
                        array(i,3) = hn+sqrt((x-succ_x)^2 + (y-succ_y)^2);%cost of travelling to node
                        array(i,4) = sqrt((succ_x-goalx)^2 + (succ_y-goaly)^2);%distance between node and goal
                        array(i,5) = array(i,3)+array(i,4);%fn
                        i=i+1;
                    end%Populate the exp_array list!!!
                end% End of node within array bound
            end%End of if node is not its own successor loop
        end%End of j for loop
    end%End of k for loop    