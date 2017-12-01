%%  MAP
clf,clear,clc
sizex=200;
sizey=100;
area=2*ones(sizex,sizey);
% Obstacle=-1,Target = 0,Robot=1,Space=2

%defining target
goalx=200; goaly=100;
area(goalx,goaly)=0;

%defining obstacles
area(6:26,1:90)=-1;
area(36:76,10:100)=-1;
area(86:126,1:90)=-1;
area(146:166,10:100)=-1;
area(166:190,10:20)=-1;
area(178:200,35:45)=-1;
area(166:190,60:70)=-1;
area(178:1200,85:95)=-1;

%defining robot and target
xstart=1;ystart=1;
area(xstart,ystart)=1;%robot
x=xstart; y=ystart;
%% Initiating lists
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

optimal=LOSsmoothen(optimal,area);

[px,py,ptheta]=discretepath(optimal,0.1,0.3);
% pathx=[[1:1:length(px)]' px];
% pathy=[[1:1:length(px)]' py];
% paththeta=[[1:1:length(px)]' ptheta];

% trialx.time=[0.1:0.1:100];
% trialx.signals.values=px(1:1000);
% trialx.signals.dim=1;
% 
% trialy.time=trialx.time;
% trialy.signals.values=py(1:1000);
% trialy.signals.dim=1;
% 
% trialtheta.time=trialx.time;
% trialtheta.signals.values=ptheta(1:1000);
% trialtheta.signals.dim=1;

%%
plot(optimal(:,1),optimal(:,2),'o')
hold on
for i=1:5:length(px)
    plot(px(i),py(i),'.')
    drawnow;
    axis([0 11 0 11])   
end