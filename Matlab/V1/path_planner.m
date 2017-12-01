function [x,y] = path_planner(xi,yi,thetai,l,v,dt)
x=zeros(1,ceil(l));y=zeros(1,ceil(l)); thm=zeros(1,ceil(l));
x(1)=xi; y(1)=yi; thm(1)=thetai;
dl=dt*v;
% dr=dl/r;
t=1;
while abs(x-xi)<=(l-dl)*cos(thetai)
   t=t+1;
   x(t)=x(t-1)+dl*cos(thetai); y(t)=y(t-1)+dl*sin(thetai);
   thm(t)=atan((y(t-1)-y(t))/(x(t-1)-x(t)));
end
end

