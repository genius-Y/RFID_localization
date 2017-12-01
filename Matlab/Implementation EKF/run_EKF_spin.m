load('data_straightline.mat')

xi=[EKFspin(1,2),EKFspin(1,3),0,0,0,0,EKFspin(1,6),EKFspin(1,7)]';
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
x=zeros(1,length(EKFspin)-1);
y=x;
theta=x;
for j=2:length(EKFspin)
    dt=EKFspin(j,1)-EKFspin(j-1,1);
    m=EKFspin(j,2:7)';
    i=EKFspin(j,8:9)';
    [xi_post,P_post,xk,yk,thk] = EKF(dt,m,xi,i,P_post_prev,sig);
    xi=xi_post;
    P_post_prev=P_post;
%     x(i,:)=xi;
%     p(i)=P_post;
    x(j-1)=xk; y(j-1)=yk; theta(j-1)=thk*180/pi; t(j-1)=dt;
end
clearvars -except x y theta EKFspin
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
% plot([min(EKFspin(:,2)), max(EKFspin(:,2))],[EKFspin(1,3), EKFspin(end,3)])