clear, clc
load ('4style','straight')
dt=0.02;
m=straight(:,2:7)';
in=[0.3,0.3];
xi=zeros(1,8);
P=999*eye(8);
sig=0.000001*ones(1,10);

for i=1:10
    [xi_post(:,i),P_post,xk,yk, thk] = EKF(dt,m(:,i),xi,in,P,sig);
    xi=xi_post(:,i);
    P=P_post;
end
xi_post