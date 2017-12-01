close, clear, clc
th=-pi/2; x(1)=0;y(1)=0;r=0.5;
t=1; l=1;dt=0.1;v=0.3;
dl=l*dt*v;
dr=dl/r;
while abs(0-y)<=2*r
   t=t+1;
   x(t)=x(1)+r*cos(th);
   y(t)=y(1)-r+r*sin(th);
   thm(t)=th;
   th=th+dr;
end
subplot(2,1,1)
plot(x,y,'ro')
subplot(2,1,2)
plot(y)