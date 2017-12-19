function [optimalpath] = Astar(start,goal,map)

[sizex,sizey]=size(map);
area=2*ones(sizex,sizey);
for i=1:sizex
    for j=1:sizey
        if map(i,j)==-1 || map(i,j) ==0
            area(i,j)=-1;
        end
    end
end

xstart=start(1,1); ystart=start(1,2);
goalx=goal(1,1); goaly=goal(1,2);
area(goalx,goaly)=0;
% Initiating lists
x=xstart; y=ystart;
area(xstart,ystart)=1;
open=[];
closed=[];
%move obstacles to closed list
i=1;%Dummy counter
for j=1:sizex
    for k=1:sizey
        if(area(j,k) == -1)
            closed(i,1)=j; 
            closed(i,2)=k; 
            i=i+1;
        end
    end
end

%Initiating from start node (xnode,ynode)=(x,y)

xnode=x;
ynode=y;
CLOSED_count=size(closed,1);
OPEN_count=1;
hn=0;
gn=sqrt((goalx-x)^2 + (goaly-y)^2);
fn=gn+hn;
open(OPEN_count,:)=append2open(xnode,ynode,xnode,ynode,hn,gn,fn);
open(OPEN_count,1)=0;
CLOSED_count=CLOSED_count+1;
closed(CLOSED_count,1)=xnode;
closed(CLOSED_count,2)=ynode;
path=0;

%% A-star begins here

while ((xnode ~= goalx || ynode ~= goaly) && path==0)

    array=arrayexpander(xnode,ynode,hn,goalx,goaly,closed,sizex,sizey);
        
    for i=1:size(array,1)
        set=0;
        for j=1:OPEN_count
            if array(i,1) == open(j,2) && array(i,2) == open(j,3)
                open(j,8)=min(open(j,8),array(i,5));
                if open(j,8) == array(i,5)
                    open(j,4)=xnode;
                    open(j,5)=ynode;
                    open(j,6)=array(i,3);
                    open(j,7)=array(i,4);
                end
                set=1;
            end
        end
        if set == 0
            OPEN_count=OPEN_count+1;
            open(OPEN_count,:)=append2open(array(i,1),array(i,2),xnode,ynode,array(i,3),array(i,4),array(i,5));
        end
    end
    
    minindex=minfn(open,OPEN_count,goalx,goaly);
    if minindex ~= -1
        xnode=open(minindex,2);
        ynode=open(minindex,3);
        hn=open(minindex,6);
        CLOSED_count=CLOSED_count+1;
        closed(CLOSED_count,1)=xnode;
        closed(CLOSED_count,2)=ynode;
        open(minindex,1)=0;
    else
        path=1;
    end
end


%% Optimal path determination
i=size(closed,1);
optimal=[];
x=closed(i,1);
y=closed(i,2);
i=1;
optimal(i,1)=x;
optimal(i,2)=y;
i=i+1;

if ((x==goalx) && (y==goaly))
    index=0;
    parentx=open(indexof(open,x,y),4);
    parenty=open(indexof(open,x,y),5);
    while parentx ~= xstart || parenty ~=ystart
        optimal(i,1)=parentx;
        optimal(i,2)=parenty;
        index=indexof(open,parentx,parenty);
        parentx=open(index,4);
        parenty=open(index,5);
        i=i+1;
    end
end
optimal(i,1)=xstart;
optimal(i,2)=ystart;

%% smoothening path based on LOS
% optimalpath=optimal;
optimalpath=LOSsmoothen(optimal,area);
end