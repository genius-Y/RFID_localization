function [] = anim8(x,y,theta,d,px,py)
clf
plot(px,py,'--')
legend off
hold on
for i=round(linspace(1,length(x),200)) %1:5:length(x)
X(1)=x(i)+d/2*cos(pi/2+theta(i));
X(2)=x(i)-d/2*cos(pi/2+theta(i));
X(3)=x(i)+d*cos(theta(i));
Y(1)=y(i)+d/2*sin(pi/2+theta(i));
Y(2)=y(i)-d/2*sin(pi/2+theta(i));
Y(3)=y(i)+d*sin(theta(i));
hold on
plot([px(i),x(i)],[py(i),y(i)],'k')
fill(X,Y,'r')
hold off
axis equal
axis ([min(x) max(max(x),max(px)) min(y) max(max(y),max(py))])
if i==1
    pause(3)
end
drawnow;
end
end

