function [l, etheta,px,py] = coordg(x,y,theta,px1,py1,px0,py0)
v=[px1-px0,py1-py0];
w=[x-px0,y-py0];
px=px1; py=py1;
l=norm(w-(dot(w,v)/dot(v,v))*v);
theta_r=acos(dot(v,[1,0])/norm(v));
etheta=theta-theta_r;