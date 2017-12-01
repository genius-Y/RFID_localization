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

%%
velocity=0.3;
pxi=2 ; pyi=2; pthetai=45*pi/180; pl=8;pr=0.3;
xi=xstart; yi=ystart ; theta_mi=0*pi/180;
dt=0.1; 
k1=4;k2=4;
d=0.15;
xi0=[xi,yi,0,0,0,0,theta_mi,0]';

% Adding sensor noises

noiseUWB=0.01;
noiseAcc=0.1;
noiseMag=0.001;
noiseGyro=0.001;
noiseIn=0.0001;

%% Tuning

% In model and input
sigx=0.1;
sigy=sigx;
sigdx=0.1;
sigdy=0.1;
sigddx=0.1;
sigddy=0.1;
sigphi=0.01;
sigdphi=0.1;
% In sensors
sigvl=0.1;
sigvr=0.1;
sig=[sigx,sigy,sigdx,sigdy,sigddx,sigddy,sigphi,sigdphi,sigvl,sigvr];
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
[px,py,ptheta,L]=discretepath(optimal,dt,velocity);
t=L/velocity-22;
t1=t-22;
pathx.time=0.1:0.1:t;
pathx.signals.values=px(1:(length(pathx.time)));
pathx.signals.dim=1;

pathy.time=pathx.time;
pathy.signals.values=py(1:(length(pathx.time)));
pathy.signals.dim=1;

paththeta.time=pathx.time;
paththeta.signals.values=ptheta(1:(length(pathx.time)));
paththeta.signals.dim=1;

%%


sim('Astar_EKF_and_controller')

%%
figure(1);
% close all
m=2; n=4;
clf
subplot(m,n,1)
plot(xk,yk,':','LineWidth',1.5), hold on, plot(x,y,'r-',px,py)
legend('filtered location','actual location','path')
title('position')
grid minor
axis equal
subplot(m,n,5)
plot(thetak*180/pi,'.'), hold on, plot(thetar*180/pi), plot(theta*180/pi) 
title('orientation')
grid minor
subplot(m,n,2)
plot(vr)
title('Right wheel velocity')
grid minor
subplot(m,n,6)
plot(vl)
title('left wheel velocity')
grid minor
subplot(m,n,3)
plot(l)
title('Longitudnal error')
grid minor
subplot(m,n,7)
plot(etheta*180/pi)
title('Orientation error')
grid minor
subplot(m,n,4)
plot(vel)
title('robot velocity')
grid minor
subplot(m,n,8)
plot(omega)
title('Robot angular velocity')
grid minor

%%
figure(2); 
anim8(x,y,theta,d*10,px,py)