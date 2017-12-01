function [x_out,x_post,y_post,th_post]         = plant(xi,i,dt)

d=0.24; %dt=0.1;
x=xi(1); y=xi(2); dx=xi(3); dy=xi(4); ddx=xi(5); ddy=xi(6); phi=xi(7); dphi=xi(8);
th=phi+0.5*dphi*dt;
vl=i(1); vr=i(2);
x_out = ...
            [ x + dx*dt + ddx*dt^2/2
              y + dy*dt + ddy*dt^2/2
             (vl+vr)/2*cos(th)+ddx*dt
             (vl+vr)/2*sin(th)+ddy*dt
             ddx
             ddy
             phi + dphi*dt
             (vr-vl)/d               ];

x_post=x_out(1); y_post=x_out(2);th_post=x_out(7);
end