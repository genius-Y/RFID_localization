clearvars -except test2 unnamed %, clf
test=unnamed(105:end,:);
x_in=test(1,1:8);
d=0.24;
for i=1:length(test) %round(linspace(1,length(test),500)) 
X(1)=test(i,1)+d/2*cos(pi/2+test(i,7));
X(2)=test(i,1)-d/2*cos(pi/2+test(i,7));
X(3)=test(i,1)+d*cos(test(i,7));
Y(1)=test(i,2)+d/2*sin(pi/2+test(i,7));
Y(2)=test(i,2)-d/2*sin(pi/2+test(i,7));
Y(3)=test(i,2)+d*sin(test(i,7));
hold on
in=[0.1;0.3];
[x_out,x_post,y_post,th_post] = plant(x_in,in,test(i,9));
x_in=x_out;
x(1)=x_post+d/2*cos(pi/2+th_post);
x(2)=x_post-d/2*cos(pi/2+th_post);
x(3)=x_post+d*cos(th_post);
y(1)=y_post+d/2*sin(pi/2+th_post);
y(2)=y_post-d/2*sin(pi/2+th_post);
y(3)=y_post+d*sin(th_post);
fill(X,Y,'r')
% fill(x,y,'b')
% hold off
axis equal
r=2;
% xmin=x(i)-r; xmax=x(i)+r; ymin=y(i)-r; ymax=y(i)+r; 
% axis ([xmin xmax ymin ymax])

drawnow;
% pause(0.1)
end
% hold on
% plot([min(test(:,2)), max(test(:,2))],[test(1,3), test(end,3)])