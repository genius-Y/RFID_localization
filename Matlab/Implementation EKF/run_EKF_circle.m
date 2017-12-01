load('data_straightline.mat')

xi=[EKFcircle(1,2),EKFcircle(1,3),0,0,0,0,EKFcircle(1,6),EKFcircle(1,7)]';
P_post_prev=zeros(8,8);
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
x=zeros(1,length(EKFcircle)-1);
y=x;
theta=x;
for j=2:length(EKFcircle)
    dt=EKFcircle(j,1)-EKFcircle(j-1,1);
    m=EKFcircle(j,2:7)';
    i=EKFcircle(j,8:9)';
    [xi_post,P_post,xk,yk,thk] = EKF(dt,m,xi,i,P_post_prev,sig);
    xi=xi_post;
    P_post_prev=P_post;
%     x(i,:)=xi;
%     p(i)=P_post;
    x(j-1)=xk; y(j-1)=yk; theta(j-1)=thk*180/pi; t(j-1)=dt;
end
clearvars -except x y theta EKFcircle
d=0.15;
clf


for i=round(linspace(1,length(x),200)) %1:5:length(x)
X(1)=x(i)+d/2*cos(pi/2+theta(i));
X(2)=x(i)-d/2*cos(pi/2+theta(i));
X(3)=x(i)+d*cos(theta(i));
Y(1)=y(i)+d/2*sin(pi/2+theta(i));
Y(2)=y(i)-d/2*sin(pi/2+theta(i));
Y(3)=y(i)+d*sin(theta(i));
hold on

fill(X,Y,'r')
hold off
axis equal
r=2;
xmin=x(i)-r; xmax=x(i)+r; ymin=y(i)-r; ymax=y(i)+r; 
axis ([min(x) max(x) min(x) max(x)])

drawnow;
pause(0.1)
end
% hold on
% plot([min(EKFcircle(:,2)), max(EKFcircle(:,2))],[EKFcircle(1,3), EKFcircle(end,3)])