close all
subplot(2,2,1)
plot(EKFspiral(:,2),EKFspiral(:,3),'o-')
axis equal
xlabel('x_{Pozyx}')
ylabel('y_{Pozyx}')
title('Spiral, v_l=0 to 0.3, v_r=0.3')
grid minor;

subplot(2,2,2)
plot(EKFspin(:,2),EKFspin(:,3),'o-')
axis equal
xlabel('x_{Pozyx}')
ylabel('y_{Pozyx}')
title('Spin, v_l=-0.3, v_r=0.3')
grid minor;

subplot(2,2,3)
plot(EKFstraight(:,2),EKFstraight(:,3),'o-')
axis equal
xlabel('x_{Pozyx}')
ylabel('y_{Pozyx}')
title('Straight, v_l=0.3, v_r=0.3')
grid minor;

subplot(2,2,4)
plot(EKFcircle(:,2),EKFcircle(:,3),'o-')
axis equal
xlabel('x_{Pozyx}')
ylabel('y_{Pozyx}')
title('Circle, v_l=0.1, v_r=0.3')
grid minor;
