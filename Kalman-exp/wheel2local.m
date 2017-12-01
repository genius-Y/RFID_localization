function [ x_dot, y_dot, theta_dot ] = wheel2local( v_l, v_r, d ,theta)
%Converts wheel velocity to velocities in x, y direction and rotational
%velocity.
%   Input velocity v_l and v_r are the wheel velocities of the left and right
%   wheels. 
x_dot= (v_l + v_r)*cos(theta)/2;
y_dot= (v_l + v_r)*sin(theta)/2;
theta_dot= (-v_l+ v_r)./d;
end

