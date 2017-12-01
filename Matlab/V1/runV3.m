%% Running the Localizaton algorithm without controller
clear, clc
%% Adding sensor noises

noiseUWB=0.01;
noiseAcc=0.1;
noiseMag=0.01;
noiseGyro=0.01;
noiseIn=0.001;

%% Initiating
xi0=[0 0 0 0 0 0 0 0]';
i0=[0 0]';
dt=0.1;
d=0.15;
time=15;
%% Tuning
t=50;
% In model and input
sigx=0.1;
sigy=sigx;
sigdx=0.1;
sigdy=0.1;
sigddx=0.1;
sigddy=0.1;
sigphi=0.1;
sigdphi=0.1;
% In sensors
sigvl=0.1;
sigvr=0.1;
sig=[sigx,sigy,sigdx,sigdy,sigddx,sigddy,sigphi,sigdphi,sigvl,sigvr];

%in measurements
%% Simulation
sim('uni_model_V3')

%% Output
%clc, close
figure(1)
clf
axis equal
%axis([-2,10,-10,2])
h1 = animatedline('Color','r','LineStyle','-.');
h2 = animatedline('Color','b','Marker','.','LineStyle','none');
h3 = animatedline('Color','g','LineWidth',2);
for i=1:length(timeout)
    addpoints(h1,x(i),y(i));
    addpoints(h2,x_uwb(i),y_uwb(i))
    addpoints(h3,xout(i,1),xout(i,2))
    drawnow
end

%var(x_uwb), var(y_uwb)

%%
figure(2); clf
analyseEKFresults(x,y,theta,xout,Pout,timeout,x_uwb,y_uwb,theta_mag)
