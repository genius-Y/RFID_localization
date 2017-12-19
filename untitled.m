clear, clc
out=[7.709    4.130   -0.130   -6.145   -3.142   -3.003    1.502];


k1=4; k2=2; vel=0.25; 
px=11; py=3.6; pth=pi*0;
x=out(1);
y=out(2);
th=out(4);
eth=th-pth;
w=[x-px, y-py];
rot=[cos(pth) sin(pth); -sin(pth) cos(pth)];
d=rot*w';
nl=[0 1]*d;
omega_l=-k1*nl*vel*(sin(eth)/eth) 
omega_th=- k2*eth
omega=omega_l+omega_th
