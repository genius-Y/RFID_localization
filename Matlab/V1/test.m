clear, clc
initial.x0=[0,0,0,0,0,0,0,0].';
initial.P = zeros(8,8);
initial.R = diag([1, 1, 0.1, 0.1, 0.1, 0.1]);
initial.M = diag([10, 10]);
dt=0.01;
%z=[1,3,0.2,0.1,2,0.1].';
%[xhatout,Phatout] = extendedKalman(z,uhat,dt,initial)

%%

xk=xout(:,1);
yk=xout(:,2);
plot(x,y,xk,yk)