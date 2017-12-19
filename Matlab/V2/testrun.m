x=0; y=0;
for i=(1:1:360)
    X(1)=x+d/2*cos(pi/2+i*pi/180);
    X(2)=x-d/2*cos(pi/2+i*pi/180);
    
    Y(1)=y+d/2*sin(pi/2+i*pi/180);
    Y(2)=y-d/2*sin(pi/2+i*pi/180);
    theta(i)=atan2((Y(1)-Y(2)),(X(1)-X(2)))*180/pi;
    plot(X,Y)
    hold on
end