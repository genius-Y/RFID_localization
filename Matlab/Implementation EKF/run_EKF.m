clear, clc, clf
load('4style.mat')
data=combined;

% xi=[data(1,2),data(1,3),0,0,0,0,data(1,6)-pi/2,data(1,7)]';
% x_in=[data(1,2),data(1,3),0,0,0,0,data(1,6)-pi/2,data(1,7)]';
xi=[10.7,2.8,0,0,0,0,data(1,6)-pi/2,data(1,7)];
x_in=xi;

P_post_prev=999*ones(8,8);
% In model and input
sigx=0.000001;
sigy=0.000001;
sigdx=0.000001;
sigdy=0.000001;
sigddx=0.000001;
sigddy=0.000001;
sigphi=0.000001;
sigdphi=0.000001;
% In sensors
sigvl=0.000001;
sigvr=0.000001;
sig=[sigx,sigy,sigdx,sigdy,sigddx,sigddy,sigphi,sigdphi,sigvl,sigvr];
% sig=0.000001*ones(1,10);
x=zeros(1,length(data)-1);
y=x;
data(:,6)=data(:,6)-pi/2;
theta=x;
for j=2:length(data)
    dt=data(j,1)-data(j-1,1);
    m=data(j,2:7)';
    i=data(j,8:9)';
    [xi_post,P_post,xk,yk,thk] = EKF(dt,m,xi,i,P_post_prev,sig);
    [x_out,x_post,y_post,th_post] = plant(x_in,i,dt);
    x_in=x_out;
    xi=xi_post;
    P_post_prev=P_post;
%     x(i,:)=xi;
%     p(i)=P_post;
    x(j-1)=xk; y(j-1)=yk; theta(j-1)=thk; t(j-1)=dt;
    x_act(j-1)=x_post; y_act(j-1)=y_post; theta_act(j-1)=th_post;
    
end
% clearvars -except x y t theta data P_post
d=0.15;
clf
figure(1)
hold on

subplot(2,1,1)
plot(data(:,2),data(:,3),'.')
hold on
plot(x,y)
hold on

plot(x_act,y_act)
axis equal

subplot(2,1,2)
plot(theta*180/pi)
hold on
plot(data(:,6)*180/pi)

plot(theta_act*180/pi)


%%
figure(2)
h1=animatedline('Marker','.','LineStyle','none','MarkerEdgeColor','r');
h2=animatedline('Marker','.','LineStyle','none','MarkerEdgeColor','b');
h3=animatedline('Marker','.','LineStyle','none','MarkerEdgeColor','g');
for T=1:1:length(x)
   addpoints(h1,x(T),y(T))
   addpoints(h2,x_act(T),y_act(T))
   addpoints(h3,data(T,2),data(T,3))
   drawnow
end

legend('Filtered','Model','UWB')
%%
plot([min(data(:,2)), max(data(:,2))],[min(data(:,3)), max(data(:,3))])

for i=round(linspace(1,length(x),200)) %1:5:length(x)
X(1)=x(i)+d/2*cos(pi/2+theta(i));
X(2)=x(i)-d/2*cos(pi/2+theta(i));
X(3)=x(i)+d*cos(theta(i));
Y(1)=y(i)+d/2*sin(pi/2+theta(i));
Y(2)=y(i)-d/2*sin(pi/2+theta(i));
Y(3)=y(i)+d*sin(theta(i));
hold on

fill(X,Y,'r')
% hold off
axis equal
r=2;
xmin=x(i)-r; xmax=x(i)+r; ymin=y(i)-r; ymax=y(i)+r; 
% axis ([xmin xmax ymin ymax])

drawnow;
% pause(0.1)
end
% hold on
% plot([min(data(:,2)), max(data(:,2))],[data(1,3), data(end,3)])