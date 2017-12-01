function [x_out,x_post,y_post,th_post]         = plant(x_in,i,dt)


d=0.24;
x=x_in(1); y=x_in(2); dx=x_in(3); dy=x_in(4); ddx=x_in(5); ddy=x_in(6); phi=x_in(7); dphi=x_in(8); 
th=phi+0.5*dphi*dt;
vl=i(2); vr=i(1);
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