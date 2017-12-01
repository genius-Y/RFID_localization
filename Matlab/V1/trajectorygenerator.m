function [x,y,thm] = trajectorygenerator(xi,yi,thmi,l,r,v,dt)
x=zeros(1,ceil(l));y=zeros(1,ceil(l)); thm=zeros(1,ceil(l));
x(1)=xi; y(1)=yi; thm(1)=thmi;
dl=dt*v;
dr=dl/r;
t=1;
while abs(xi-x)<=l-dl
   t=t+1;
   x(t)=x(t-1)+dl; y(t)=y(t-1);
   thm(t)=atan((y(t-1)-y(t))/(x(t-1)-x(t)));
end
% th=-pi/2;
% 
% while abs(yi-y)<=r-dr
%    t=t+1;
%    x(t)=x(t-1)+r*cos(th);
%    y(t)=y(t-1)+r+r*sin(th);
%    thm(t)=th;
%    th=th+dr;
%    
% end
plot(x,y,'ro')
end