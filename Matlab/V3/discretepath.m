function [px,py,ptheta,length] = discretepath(path,dt,v)

length=0;
dl=dt*v;
px=[];
py=[];
ptheta=[];
for i=size(path,1):-1:2
    x1=path(i,1); y1=path(i,2);
    x2=path(i-1,1); y2=path(i-1,2);
    L=sqrt((x2-x1)^2+(y2-y1)^2);
    phi=atan2((y2-y1), (x2-x1));
    X(1)=x1; Y(1)=y1; th(1)=phi;
    for j=2:floor(L/dl)
        X(j)=X(j-1)+dl*cos(phi);
        Y(j)=Y(j-1)+dl*sin(phi);
        th(j)=phi;
    end
%     X(j+1)=x2; Y(j+1)=y2; 
    px=[px X]; 
    py=[py Y]; 
    ptheta=[ptheta th];
    length=length+L;
    X=[]; Y=[]; th=[];
    
end
px=px';py=py';ptheta=ptheta';
end