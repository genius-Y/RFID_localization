clearvars -except trialx trialy trialtheta area
clc
velocity=0.3;
pxi=2 ; pyi=2; pthetai=45*pi/180; pl=4;pr=1;
xi=1.5; yi=2.3 ; theta_mi=30*pi/180;
dt=0.1; t=40;
k1=8;k2=1;
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

sim('Path_planner_with_controller_localization')

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
anim8(x,y,theta,d,px,py)